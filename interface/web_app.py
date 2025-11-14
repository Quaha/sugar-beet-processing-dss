import os
import sys

from PyQt6.QtWidgets import QApplication, QMainWindow
from PyQt6.QtWebEngineWidgets import QWebEngineView
from PyQt6.QtGui import QIcon
from PyQt6.QtCore import QUrl



class WebApp(QMainWindow):
    def __init__(
        self,
        title="App",
        width=1280,
        height=720,
        favicon=None
    ):
        super().__init__()

        self.setWindowTitle(title)
        self.resize(width, height)

        if favicon and os.path.exists(favicon):
            self.setWindowIcon(QIcon(favicon))

        self.view = QWebEngineView()
        self.setCentralWidget(self.view)

    def load_local(self, relative_path):
        abs_path = os.path.abspath(relative_path)
        url = QUrl.fromLocalFile(abs_path)
        self.view.setUrl(url)

    def start(self):
        self.show()
