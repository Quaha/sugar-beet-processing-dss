import sys

from PyQt6.QtWidgets import QApplication

from web_app import WebApp



def main():
    app_qt = QApplication(sys.argv)

    app = WebApp(
        title="Cards",
        width=1280,
        height=720,
        favicon="website/assets/icon.ico"
    )

    app.load_local("website/index.html")
    app.start()

    sys.exit(app_qt.exec())


if __name__ == "__main__":
    main()
