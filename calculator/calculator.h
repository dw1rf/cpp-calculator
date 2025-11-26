#pragma once

using Number = double;

// Возвращает true, если удалось прочитать число и сохранить его в result.
// В случае неудачи выводит сообщение об ошибке в std::cerr.
bool ReadNumber(Number& result);

// Возвращает true, если работа завершилась штатно командой q.
// В случае ошибки возвращает false.
bool RunCalculatorCycle();