import os
import sys

from pathlib import Path
from PyQt6.QtWidgets import QApplication, QMainWindow
from PyQt6.QtWebEngineWidgets import QWebEngineView
from PyQt6.QtGui import QIcon
from PyQt6.QtCore import QUrl, QObject, pyqtSlot
from PyQt6.QtWebChannel import QWebChannel


class WebApp(QMainWindow):
    def __init__(
        self,
        title="App",
        width=1280,
        height=720,
        favicon=None,
        js_api=None
    ):
        super().__init__()

        self.setWindowTitle(title)
        self.resize(width, height)

        if favicon and os.path.exists(favicon):
            self.setWindowIcon(QIcon(favicon))

        self.view = QWebEngineView()
        self.setCentralWidget(self.view)

        if js_api:
            self.channel = QWebChannel()
            self.channel.registerObject("backend", js_api)
            self.view.page().setWebChannel(self.channel)

    def load_local(self, file_path: Path):
        url = QUrl.fromLocalFile(str(file_path.absolute()))
        self.view.setUrl(url)

    def start(self):
        self.show()
