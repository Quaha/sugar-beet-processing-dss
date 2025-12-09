# Лабораторная работа по курсу "Численные методы"

## Описание проекта

Данная лабораторная работа посвящена разработке **системы поддержки принятия решений**, предназначенной для рекомендаций оптимальных стратегий решения задачи о назначениях (в модифицированном виде).

В рамках работы проводится серия вычислительных экспериментов, направленных на анализ эффективности различных стратегий и их статистическую оценку.

---

## Состав группы

- **Артем Романов** (*Quaha*)
- **Алексей Гутянский** (*AlexixRugis*)
- **Семён Константинов** (*Projectius*)
- **Вячеслав Долов** (*slaver07*)
- **Валентин Кутергин** (*VALancaster*)

---

## Постановка задачи

Постановка задачи описана в `docs/task.md`.

---

# Разработка

Идея заключается в том, чтобы сделать `webview` приложение, которое будет брать данные с `C++ core` частью посредством `dll` файла.

## FAQ

### Как склонировать репозиторий (main ветку)?
`git clone --recurse-submodules https://github.com/Quaha/sugar-beet-processing-dss`

### Как склонировать репозиторий (свою ветку)?
`git clone --recurse-submodules https://github.com/Quaha/sugar-beet-processing-dss -b "<name_of_branch>"`

### Необходимые `python` зависимости:
- `pip install PyQt6 PyQt6-WebEngine`
- `pip install pyinstaller`

### Как собрать и открыть `core` часть для доработки (Microsoft Visual Studio)?
- Удалить папку `/core/build_static`, если она есть
- В папке `/core` в консоли прописать `cmake -S . -B build_static -DBUILD_FOR_DLL=OFF`
- Открыть `.sln` файл с помощью Microsoft Visual Studio

### Как запустисть тесты (Microsoft Visual Studio)
- Собрать сервеную часть для доработки
- Открыть `.sln` файл с помощью Microsoft Visual Studio
- Выбрать `core_tests` в качестве запускаемого проекта
- Запустить код

### Как собрать `dll` файл
- Удалить папку `/core/build_dll`, если она есть
- В папке `/core` прописать `cmake -S . -B build_dll -DBUILD_FOR_DLL=ON`
- В папке `/core` прописать `cmake --build build_dll --config Release`

.dll файл будет лежать в `core/build_dll/Release`

### Как собрать `.exe` приложение
- Убедиться что в папке `core/build_dll/Release` лежит актуальная собранная версия `core_library.dll`
- В папке `/interface` выполнить команду `pyinstaller --onefile --windowed  --add-data "website;website" --add-data "cpp_bridge.py;." --add-data "web_app.py;." --add-binary "../core/build_dll/Release/core_library.dll;."--hidden-import PyQt6.sip --icon "website/assets/icon.ico" --name "Sugar beet processing DSS"  main.py`

.exe файл будет лежать в папке `/interface/dist`
