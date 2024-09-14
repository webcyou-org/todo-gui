import TkEasyGUI as eg
layout = [
    [eg.Text("Hello, World!")],
    [eg.Button("OK")]
]

with eg.Window("Hello App", layout) as window:
    for event, values in window.event_iter():
        if event == "OK":
            eg.print("Thank you.")
            break