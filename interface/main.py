# python interface/main.py

import sys
import json

from pathlib import Path
from PyQt6.QtWidgets import QApplication
from PyQt6.QtCore import QObject, pyqtSlot
from PyQt6.QtGui import QIcon
from web_app import WebApp
from cpp_bridge import process_json


class Api(QObject):
    @pyqtSlot(str, result=str)
    def run_simulation(self, params_json_str):
        print(f"Python получил данные от JS: {params_json_str}")
        try:
            params_dict = json.loads(params_json_str)
            result_dict = process_json(params_dict)
            print("--- ШАГ 2: Python получил ответ от C++ ---")
            print(result_dict) 
            response_json_str = json.dumps(result_dict)
            print("--- ШАГ 3: Python отправляет ответ в JS ---")
            print(response_json_str)
            return response_json_str
        except Exception as e:
            print(f"Возникла ошибка: {e}")
            return json.dumps({"error": str(e)})


def main():
    app_qt = QApplication(sys.argv)

    path_to_project = Path(__file__).parent
    path_to_icon = path_to_project / "website" / "assets" / "icon.ico"
    app_qt.setWindowIcon(QIcon(str(path_to_icon)))
    
    api_bridge = Api()

    path_to_html = path_to_project / "website" / "index.html"

    app = WebApp(
        title="СППР - Оптимизация переработки свеклы",
        width=1280,
        height=720,
        favicon=str(path_to_icon),   # <-- ВАЖНО: абсолютный путь!
        js_api=api_bridge
    )

    app.load_local(path_to_html)
    app.start()
    
    sys.exit(app_qt.exec())


if __name__ == "__main__":
    main()
