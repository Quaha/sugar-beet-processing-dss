Вот пример документации для Python-модуля, который взаимодействует с C++ DLL, отправляет JSON и получает JSON-ответ. Она включает **формат входных данных**, **ограничения**, и **структуру возвращаемого значения**.

---

## Документация модуля `cpp_bridge`

### Функции

#### `process_json(input_data: dict) -> dict`

Отправляет входные данные в C++ DLL, выполняет серию симуляций и возвращает результат в виде словаря.

---

### Входные данные (`input_data`)

`input_data` должен быть Python словарём, содержащим следующие ключи:

| Поле           | Тип             | Описание                                                | Ограничения                              | Пример |
| -------------- | --------------- | ------------------------------------------------------- | ---------------------------------------- | ------ |
| `t`            | int             | Количество виртуальных экспериментов                    | `t > 0`                                  | 50     |
| `n`            | int             | Количество этапов переработки                           | `n > 0`                                  | 15     |
| `alpha_min`    | float           | Нижняя граница доли полезного ингредиента               | `[0.12, 0.22]`                           | 0.12   |
| `alpha_max`    | float           | Верхняя граница доли полезного ингредиента              | `[0.12, 0.22]`, `alpha_min <= alpha_max` | 0.22   |
| `beta_1`       | float           | Нижняя граница коэффициента деградации                  | `(0.85, 1.0)`                            | 0.86   |
| `beta_2`       | float           | Верхняя граница коэффициента деградации                 | `(0.85, 1.0)`, `beta_1 <= beta_2`        | 0.99   |
| `concentrated` | bool            | Флаг распределения коэффициентов деградации             | —                                        | True   |
| `maturation`   | bool            | Флаг наличия дозаривания                                | —                                        | False  |
| `inorganic`    | bool            | Влияние неорганических веществ                          | —                                        | False  |
| `v`            | int, optional   | Кол-во этапов дозаривания, если `maturation=True`       | `1 <= v <= n`                            | 7      |
| `beta_max`     | float, optional | Верхняя граница коэффициента деградации при дозаривании, если `maturation=True` | `(1.0, 1.15)`                            | 1.05   |

**Пример корректного словаря:**

```python
input_data = {
    "t": 50,
    "n": 15,
    "alpha_min": 0.12,
    "alpha_max": 0.22,
    "beta_1": 0.86,
    "beta_2": 0.99,
    "concentrated": True,
    "maturation": True,
    "inorganic": False,
    "v": 7,
    "beta_max": 1.05
}
```

---

### Возвращаемое значение

Функция возвращает Python словарь, который может быть:

1. **Успешный результат:**

```python
{
    "greedy": {
        "avg_step_ratio": [0.12, 0.14, ..., 0.18],  # длина = n
        "avg_loss": 0.05
    },
    "thrifty": {
        "avg_step_ratio": [...],
        "avg_loss": 0.06
    },
    "greedy_thrifty": {...},
    "thrifty_greedy": {...},
    "median": {...},
    "optimal": {...}
}
```

* `avg_step_ratio` — список чисел типа `float` длиной `n`, средние относительные значения на каждом этапе.
* `avg_loss` — число типа `float`, средняя потеря стратегии относительно оптимальной.

---

2. **Ошибка парсинга или валидации:**

```python
{
    "error_type": "REQUIRED" | "TYPE_MISMATCH" | "INTERVAL" | "PARSING",
    "message": "Описание ошибки"
}
```

Примеры ошибок:

* Отсутствует обязательное поле:

```python
{
    "error_type": "REQUIRED",
    "message": "t"
}
```

* Несоответствие типа:

```python
{
    "error_type": "TYPE_MISMATCH",
    "message": "..."
}
```

* Значение вне допустимого диапазона:

```python
{
    "error_type": "INTERVAL",
    "message": "v must be in [1; n]"
}
```

* Некорректный JSON:

```python
{
    "error_type": "PARSING",
    "message": "..."
}
```

---

### Пример использования

```python
from cpp_bridge import process_json

data = {
    "t": 50,
    "n": 15,
    "alpha_min": 0.12,
    "alpha_max": 0.22,
    "beta_1": 0.86,
    "beta_2": 0.99,
    "concentrated": True,
    "maturation": False,
    "inorganic": False
}

result = process_json(data)

if "error_type" in result:
    print("Ошибка:", result["message"])
else:
    for strategy, stats in result.items():
        print(strategy, stats["avg_loss"], stats["avg_step_ratio"])
```