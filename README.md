
# Поиск комбинаций для получения определенного результата

Этот проект решает задачу поиска всех возможных комбинаций математических выражений с использованием знаков (+, -, или ничего) между числами от 9 до 0, чтобы получить определенный результат. В данном случае, мы ищем комбинации, результат которых равен 200.

## Описание задачи

Имеется набор чисел от 9 до 0. Наша задача - найти все возможные комбинации математических выражений, в которых между этими числами будут использованы знаки "+" и "-" (или ничего), чтобы результат выражения равнялся 200.

## Как работает решение

Программа использует рекурсивный подход для перебора различных комбинаций знаков между числами от 9 до 0. Для каждого числа выполняются три действия: сложение (+), вычитание (-) или оставление числа без знака (ничего). Программа рекурсивно вызывает себя для всех комбинаций, пока не будет найдено выражение, результат которого равен 200.

## Использование

Проект содержит файлы:

- `expression_finder.py`: решение задачи на языке Python с использованием рекурсии.

Для запуска решения на языке Python, выполните:
```
python expression_finder.py
```


## Важно

Это одно из возможных решений для задачи поиска комбинаций математических выражений. Решение не является оптимальным и может быть улучшено в зависимости от требований и ограничений задачи.
