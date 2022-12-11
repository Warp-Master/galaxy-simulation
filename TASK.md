# Курсовая по программированию 3 семестр
Используя представленный в приложении прототип программы расчета движения объектов под действием гравитации, студент должен изменить его в соответствии со своим вариантом. (Номер варианта соответствует номеру в группе в официальном списке из деканата)

## Тесты программы
1. 100 объектов со случайными координатами и скоростями не превышающими 30 км/с. Со случайными массами в диапазоне от Меркурия до Земли. В центре Солнце с координатами и скоростями (0,0)
2. 5 объектов с массами и на орбитах (добавить константы любым удобным способом) соответствующим Солнечной системе + Солнце.
3. Необязательный тест: продублировать Солнечную систему из пункта No2 и направить их друг на друга с небольшой скоростью и **НЕ**центральным столкновением. Это сложно, поэтому этот тест необязателен.

## Задания
1. Создать систему из объектов в количестве: номер варианта х 2000, со случайными координатами и скоростями не превышающими 30 км/с. Со случайными массами в диапазоне от Меркурия до Земли. В центре Солнце с координатами и скоростями (0,0).
2. Сделать окна для вывода текущего времени и текущего шага расчета в системе.
3. Сделать функцию член класса star которая меняет цвет объекта в зависимости от изменения массы, предусмотреть 10 градаций цвета.
4. Перегрузить оператор + для класса star для слияния двухобъектов, которые оказались на расстоянии менее чем 1000 км, координаты, скорость и масса объекта должны соответствовать.
5. Сделать функцию член класса star которая меняет размер изображения объекта (эллипса) в зависимости от изменения массы. Размер долженбыть разумным, не в масштабе области). Вероятно
лучше менять его ступенчато на 1 пиксель при переходе через границы в массиве масс.
6. Перегрузить операторы << для вывода состояния системы в файл и >> для ввода исходных данных (количество объектов, размер области, расстояние) из файла.
7. Сделать окна для вывода общей массы системы, массы, координат и скоростей трех (для тех, кто умеет динамически делать окна, то N) самых массивных объектов. (Лишние окна из образца убрать)
8. Сделать окна для вывода общей массы системы, импульса, момента импульса, потенциальной, кинетической и полной энергии системы. (Лишние окна из образца убрать. Потенциальную энергию объекта на бесконечности приравнять 0)
9. Сделать окна для ввода начального количества объектов, размера области их начального расположения, расстояния слияния. Естественно, что можно убрать соответствующие константы из программы.

## Необязательные задания
* сделать завершение расчетов с записью в файл состояния и рестарт при котором это состояние считывается из файла.
* заменить массив указателей на объекты на список объектов (можно из библиотеки шаблонов) сравнить быстродействие для систем из разного количества объектов.
* заменить массив указателей на объекты на vector (из библиотеки шаблонов и уменьшать его размер при слиянии объектов) сравнить быстродействие для систем из разного количества объектов.
* Сделать вывод характеристик объекта при наведении на него курсора. В статические или динамические окна, можно в появляющиеся. См.: 
  * <https://doc.qt.io/qt-5/qmouseevent.html> 
  * [QPoint QCursor::pos()](https://doc.qt.io/qt-5/qcursor.html#pos) - returns the position of the cursor (hot spot) in global screen coordinates. 
  * [QWidget::mapFromGlobal()](https://doc.qt.io/qt-6/qwidget.html#mapFromGlobal-1) to translate it to widget coordinates. See also:
    * [QCursor::setPos()](https://doc.qt.io/qt-5/qcursor.html#setPos)
    * [QWidget::mapToGlobal()](https://doc.qt.io/qt-6/qwidget.html#mapToGlobal-1)

## Приложение
Прототип программы starsCreation:
<https://www.dropbox.com/sh/r5p66pxlea3zm6u/AADw4kAtMH5TYpjklPXx3Ca0a?dl=0>