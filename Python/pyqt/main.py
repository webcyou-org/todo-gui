import sys
from PyQt6.QtWidgets import QApplication,QWidget

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('ToDo')
        self.setGeometry(200,200,400,400)

qAp = QApplication(sys.argv)
mainWindow = MainWindow()
mainWindow.show()
qAp.exec()
