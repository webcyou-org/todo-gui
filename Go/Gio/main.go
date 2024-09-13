package main

import (
    "gioui.org/app"
)

func main() {
    go func() {
        w := new(app.Window)

        for {
            w.Event()
        }
    }()
    app.Main()
}

