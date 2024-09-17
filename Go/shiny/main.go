package main

import (
    "golang.org/x/exp/shiny/screen"
    "golang.org/x/exp/shiny/driver/gldriver"
    "golang.org/x/image/colornames"
    "golang.org/x/mobile/event/lifecycle"
    "golang.org/x/mobile/event/size"
    "golang.org/x/mobile/event/paint"
    "image"
)

func main() {
    gldriver.Main(func(s screen.Screen) {
        w, err := s.NewWindow(&screen.NewWindowOptions{
            Width:  800,
            Height: 600,
            Title:  "ToDo Application",
        })
        if err != nil {
            panic(err)
        }
        defer w.Release()

        var sz size.Event

        for {
            e := w.NextEvent()
            switch e := e.(type) {
            case lifecycle.Event:
                if e.To == lifecycle.StageDead {
                    return
                }
            case size.Event:
                sz = e
            case paint.Event:
                // ウィンドウのサイズに基づいて描画
                w.Fill(image.Rect(0, 0, sz.WidthPx, sz.HeightPx), colornames.Skyblue, screen.Src)
                w.Publish()
            }
        }
    })
}
