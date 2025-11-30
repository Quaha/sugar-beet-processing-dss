import sys

from pathlib import Path
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
        title="СППР - Оптимизация переработки свеклы",
        width=1280,
        height=720,
        favicon="interface/website/assets/icon.ico"
    )

    path_to_html = Path(__file__).parent / "website" / "index.html"
    app.load_local(str(path_to_html))

    app.start()
    sys.exit(app_qt.exec())


if __name__ == "__main__":
    main()
