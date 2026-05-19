package main

import (
	"image"
	"image/color"
	"math"
	"os"
	"time"
	"unicode/utf8"

	"golang.org/x/exp/shiny/driver/gldriver"
	"golang.org/x/exp/shiny/screen"
	"golang.org/x/image/font"
	"golang.org/x/image/font/gofont/gobold"
	"golang.org/x/image/font/gofont/goregular"
	"golang.org/x/image/font/opentype"
	"golang.org/x/mobile/event/key"
	"golang.org/x/mobile/event/lifecycle"
	"golang.org/x/mobile/event/mouse"
	"golang.org/x/mobile/event/paint"
	"golang.org/x/mobile/event/size"
)

// Design tokens
var (
	colBG       = color.RGBA{0x1C, 0x1C, 0x1C, 0xFF}
	colSurface  = color.RGBA{0x2A, 0x2A, 0x2A, 0xFF}
	colInput    = color.RGBA{0x30, 0x30, 0x30, 0xFF}
	colText     = color.RGBA{0xD2, 0xD2, 0xD2, 0xFF}
	colWhite    = color.RGBA{0xFF, 0xFF, 0xFF, 0xFF}
	colMuted    = color.RGBA{0x9B, 0x9B, 0x9B, 0xFF}
	colAccent   = color.RGBA{0x5D, 0xC2, 0xAF, 0xFF}
	colCBBorder = color.RGBA{0xD9, 0xD9, 0xD9, 0xFF}
)

// Font faces — recreated by initFonts() when scale changes.
var (
	faceNormal font.Face
	faceBold14 font.Face
	faceBold18 font.Face
)

func mustFace(ttf []byte, sizePt, dpi float64) font.Face {
	f, err := opentype.Parse(ttf)
	if err != nil {
		panic(err)
	}
	face, err := opentype.NewFace(f, &opentype.FaceOptions{
		Size:    sizePt,
		DPI:     dpi,
		Hinting: font.HintingFull,
	})
	if err != nil {
		panic(err)
	}
	return face
}

func faceFromFile(path string, sizePt, dpi float64) (font.Face, error) {
	data, err := os.ReadFile(path)
	if err != nil {
		return nil, err
	}
	f, err := opentype.Parse(data)
	if err != nil {
		return nil, err
	}
	return opentype.NewFace(f, &opentype.FaceOptions{
		Size:    sizePt,
		DPI:     dpi,
		Hinting: font.HintingFull,
	})
}

func initFonts() {
	dpi := 72.0 * currentScale
	jp, errJP := faceFromFile("fonts/NotoSansJP.ttf", 14, dpi)
	b14, errB14 := faceFromFile("fonts/InterBold.ttf", 14, dpi)
	b18, errB18 := faceFromFile("fonts/InterBold.ttf", 18, dpi)

	if errJP == nil {
		faceNormal = jp
	} else {
		faceNormal = mustFace(goregular.TTF, 14, dpi)
	}
	if errB14 == nil {
		faceBold14 = b14
	} else {
		faceBold14 = mustFace(gobold.TTF, 14, dpi)
	}
	if errB18 == nil {
		faceBold18 = b18
	} else {
		faceBold18 = mustFace(gobold.TTF, 18, dpi)
	}
}

// Hit region registry — rebuilt on every render call.
// Bounds are stored in PHYSICAL pixel coordinates.
type region struct {
	bounds image.Rectangle
	action func()
}

var regions []region

// inputRect holds the input field bounds in physical pixels.
var inputRect image.Rectangle

func main() {
	initFonts()

	gldriver.Main(func(s screen.Screen) {
		// On macOS/cocoa, NewWindowOptions.Width/Height are in physical pixels.
		// doNewWindow() divides by backingScaleFactor to get logical points.
		// To show an 800×600 pt window on 2x Retina, pass 1600×1200.
		const initW, initH = 1600, 1200
		w, err := s.NewWindow(&screen.NewWindowOptions{
			Width:  initW,
			Height: initH,
			Title:  "ToDo",
		})
		if err != nil {
			panic(err)
		}
		defer w.Release()

		// Start with a buffer that matches the target physical size.
		buf, err := s.NewBuffer(image.Point{initW, initH})
		if err != nil {
			panic(err)
		}

		var (
			bufWidth  = initW
			bufHeight = initH
			sz        size.Event
			state     = NewAppState()
			focused   = false
		)

		// Ticker to drive cursor blinking; sends a paint event every 500 ms.
		go func() {
			ticker := time.NewTicker(500 * time.Millisecond)
			defer ticker.Stop()
			for range ticker.C {
				w.Send(paint.Event{})
			}
		}()

		// ensureBuf recreates the buffer when the physical dimensions or
		// scale factor change (e.g. window moved to a different monitor).
		ensureBuf := func(pxW, pxH int, scale float64) {
			sameSize := pxW == bufWidth && pxH == bufHeight
			sameScale := math.Abs(scale-currentScale) < 0.001
			if sameSize && sameScale {
				return
			}
			buf.Release()
			currentScale = scale
			initFonts()
			buf, err = s.NewBuffer(image.Point{pxW, pxH})
			if err != nil {
				panic(err)
			}
			bufWidth, bufHeight = pxW, pxH
		}

		for {
			e := w.NextEvent()
			switch e := e.(type) {
			case lifecycle.Event:
				if e.To == lifecycle.StageDead {
					return
				}

			case size.Event:
				sz = e
				scale := float64(sz.PixelsPerPt)
				if scale < 0.5 {
					scale = 1.0
				}
				if sz.WidthPx > 0 && sz.HeightPx > 0 {
					ensureBuf(sz.WidthPx, sz.HeightPx, scale)
				}
				w.Send(paint.Event{})

			case paint.Event:
				render(buf.RGBA(), state, focused)
				w.Upload(image.Point{}, buf, image.Rect(0, 0, bufWidth, bufHeight))
				w.Publish()
				_ = sz

			case mouse.Event:
				if e.Direction == mouse.DirPress && e.Button == mouse.ButtonLeft {
					// cocoa.m multiplies cursor position by backingScaleFactor,
					// so e.X/e.Y are already in physical pixels — same coordinate
					// space as our rendered regions. No transform needed.
					pt := image.Pt(int(e.X), int(e.Y))
					if pt.In(inputRect) {
						focused = true
					} else {
						focused = false
						for _, reg := range regions {
							if pt.In(reg.bounds) {
								reg.action()
								break
							}
						}
					}
					w.Send(paint.Event{})
				}

			case key.Event:
				if focused && e.Direction != key.DirRelease {
					switch e.Code {
					case key.CodeReturnEnter:
						if e.Direction == key.DirPress {
							state.AddTodo(state.InputText)
							state.InputText = ""
						}
					case key.CodeDeleteBackspace:
						if len(state.InputText) > 0 {
							_, n := utf8.DecodeLastRuneInString(state.InputText)
							state.InputText = state.InputText[:len(state.InputText)-n]
						}
					default:
						if e.Rune >= ' ' {
							state.InputText += string(e.Rune)
						}
					}
					w.Send(paint.Event{})
				}
			}
		}
	})
}