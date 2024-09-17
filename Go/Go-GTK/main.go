package main

import "github.com/mattn/go-gtk/gtk"

func main() {
    gtk.Init(nil)
    win := gtk.NewWindow(gtk.WINDOW_TOPLEVEL)
    win.SetTitle("ToDo")
    win.SetSizeRequest(400, 300)
    win.Connect("destroy", gtk.MainQuit)

    lab := gtk.NewLabel("ToDo Application")
    win.Add(lab)

    win.ShowAll()
    gtk.Main()
}

