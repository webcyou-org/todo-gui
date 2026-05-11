package main

import (
	"image"
	"image/color"
	"image/draw"
	"math"

	"golang.org/x/image/font"
	"golang.org/x/image/math/fixed"
)

// currentScale is the physical-pixels-per-logical-point ratio (e.g. 2.0 on Retina).
// Updated by the size.Event handler; read by sc() and toLogical() everywhere.
var currentScale float64 = 1.0

// sc converts a design-token value (logical pixels) to physical pixels.
func sc(v int) int {
	return int(math.Round(float64(v) * currentScale))
}


func fillRect(rgba *image.RGBA, r image.Rectangle, col color.RGBA) {
	draw.Draw(rgba, r, image.NewUniform(col), image.Point{}, draw.Src)
}

func strokeRect(rgba *image.RGBA, r image.Rectangle, col color.RGBA) {
	fillRect(rgba, image.Rect(r.Min.X, r.Min.Y, r.Max.X, r.Min.Y+1), col)
	fillRect(rgba, image.Rect(r.Min.X, r.Max.Y-1, r.Max.X, r.Max.Y), col)
	fillRect(rgba, image.Rect(r.Min.X, r.Min.Y, r.Min.X+1, r.Max.Y), col)
	fillRect(rgba, image.Rect(r.Max.X-1, r.Min.Y, r.Max.X, r.Max.Y), col)
}

func drawTextAt(rgba *image.RGBA, face font.Face, x, y int, col color.RGBA, text string) int {
	d := &font.Drawer{
		Dst:  rgba,
		Src:  image.NewUniform(col),
		Face: face,
		Dot:  fixed.P(x, y),
	}
	d.DrawString(text)
	return d.Dot.X.Ceil()
}

func measureText(face font.Face, text string) int {
	return font.MeasureString(face, text).Ceil()
}

// vertCenter returns the text baseline y for text vertically centered in [topY, topY+h).
func vertCenter(face font.Face, topY, h int) int {
	m := face.Metrics()
	return topY + (h+m.Ascent.Ceil()-m.Descent.Ceil())/2
}

func fillCircle(rgba *image.RGBA, cx, cy, r int, col color.RGBA) {
	r2 := float64(r * r)
	for dy := -r; dy <= r; dy++ {
		for dx := -r; dx <= r; dx++ {
			if float64(dx*dx+dy*dy) <= r2 {
				rgba.SetRGBA(cx+dx, cy+dy, col)
			}
		}
	}
}

func strokeCircle(rgba *image.RGBA, cx, cy, r, lw int, col color.RGBA) {
	outer2 := float64(r * r)
	inner := float64(r - lw)
	inner2 := inner * inner
	for dy := -r; dy <= r; dy++ {
		for dx := -r; dx <= r; dx++ {
			d2 := float64(dx*dx + dy*dy)
			if d2 >= inner2 && d2 <= outer2 {
				rgba.SetRGBA(cx+dx, cy+dy, col)
			}
		}
	}
}

func drawLine(rgba *image.RGBA, x0, y0, x1, y1 int, col color.RGBA) {
	dx := absInt(x1 - x0)
	dy := -absInt(y1 - y0)
	sx, sy := 1, 1
	if x0 > x1 {
		sx = -1
	}
	if y0 > y1 {
		sy = -1
	}
	err := dx + dy
	for {
		rgba.SetRGBA(x0, y0, col)
		if x0 == x1 && y0 == y1 {
			break
		}
		e2 := 2 * err
		if e2 >= dy {
			if x0 == x1 {
				break
			}
			err += dy
			x0 += sx
		}
		if e2 <= dx {
			if y0 == y1 {
				break
			}
			err += dx
			y0 += sy
		}
	}
}

func drawThickLine(rgba *image.RGBA, x0, y0, x1, y1, thickness int, col color.RGBA) {
	angle := math.Atan2(float64(y1-y0), float64(x1-x0))
	for t := 0; t < thickness; t++ {
		px := int(math.Round(float64(t) * math.Sin(angle)))
		py := int(math.Round(float64(t) * -math.Cos(angle)))
		drawLine(rgba, x0+px, y0+py, x1+px, y1+py, col)
		if t > 0 {
			drawLine(rgba, x0-px, y0-py, x1-px, y1-py, col)
		}
	}
}

func drawCheckmark(rgba *image.RGBA, cx, cy int, col color.RGBA) {
	lw := max(1, sc(2))
	drawThickLine(rgba, cx-sc(4), cy, cx-sc(1), cy+sc(3), lw, col)
	drawThickLine(rgba, cx-sc(1), cy+sc(3), cx+sc(4), cy-sc(2), lw, col)
}

func absInt(x int) int {
	if x < 0 {
		return -x
	}
	return x
}
