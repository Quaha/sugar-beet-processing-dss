import sys

from PyQt6.QtWidgets import QApplication
from web_app import WebApp
from cpp_bridge import process_json

def main():

    # C++ communication example
    data = {"value": 42}

    # Just eho function
    result = process_json(data)
    print(result)

    # Interface
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
