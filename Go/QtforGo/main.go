package main

import (
    "os"

    "github.com/therecipe/qt/widgets"
)

func main() {
    // QApplicationを作成
    app := widgets.NewQApplication(len(os.Args), os.Args)

    // QMainWindowを作成
    window := widgets.NewQMainWindow(nil, 0)
    window.SetWindowTitle("ToDo Application")
    window.SetMinimumSize2(400, 300)

    // ウィンドウを表示
    window.Show()

    // イベントループを開始
    app.Exec()
}
