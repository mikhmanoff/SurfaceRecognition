# Triangulation


## Описание
Проект `Triangulation` предназначен для выполнения триангуляции Делоне для набора точек в трехмерном пространстве. Проект использует библиотеки CGAL (Computational Geometry Algorithms Library) и Boost (в частности, Boost.Program_options для обработки командной строки).

## Зависимости
### CGAL
Установите CGAL в соответствии с инструкциями на [официальном сайте CGAL](https://www.cgal.org/download.html).

### Boost
Установите Boost, следуя инструкциям на [официальном сайте Boost](https://www.boost.org/).

## Установка и Конфигурация
1. **Установка CGAL и Boost:**
   - Для установки CGAL и Boost следуйте инструкциям на официальных сайтах библиотек.
   - Убедитесь, что библиотеки доступны для вашего компилятора.

2. **Клонирование репозитория:**
   ```bash
   git clone https://github.com/mikhmanoff/Triangulation.git
   
   cd Triangulation

2. **Компиляция и запуск:**
   ```bash
   cmake .

   make

   ./my_app -i [путь к входному файлу] -o [путь к выходному файлу]
