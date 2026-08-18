#pragma once
#include "enums.h"
#include <QMainWindow>
#include <functional>
#include <optional>
#include <string>
QT_BEGIN_NAMESPACE
namespace Ui{class MainWindow;}
QT_END_NAMESPACE
class MainWindow:public QMainWindow{Q_OBJECT
public:
 explicit MainWindow(QWidget* p=nullptr);~MainWindow();
 void SetDigitKeyCallback(std::function<void(int)> f){digit_=std::move(f);}
 void SetProcessOperationKeyCallback(std::function<void(Operation)> f){operation_=std::move(f);}
 void SetProcessControlKeyCallback(std::function<void(ControlKey)> f){control_=std::move(f);}
 void SetControllerCallback(std::function<void(ControllerType)> f){controller_=std::move(f);}
 void SetInputText(const std::string&);void SetErrorText(const std::string&);void SetFormulaText(const std::string&);void SetMemText(const std::string&);void SetExtraKey(std::optional<std::string>);
private:Ui::MainWindow* ui;std::function<void(int)> digit_;std::function<void(Operation)> operation_;std::function<void(ControlKey)> control_;std::function<void(ControllerType)> controller_;QPalette normal_palette_;};
