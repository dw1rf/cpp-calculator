#pragma once

#include "enums.h"

#include <QMainWindow>
#include <QPalette>

#include <functional>
#include <optional>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void SetDigitKeyCallback(std::function<void(int)> callback);
    void SetProcessOperationKeyCallback(std::function<void(Operation)> callback);
    void SetProcessControlKeyCallback(std::function<void(ControlKey)> callback);
    void SetControllerCallback(std::function<void(ControllerType)> callback);

    void SetInputText(const std::string& text);
    void SetErrorText(const std::string& text);
    void SetFormulaText(const std::string& text);
    void SetMemText(const std::string& text);
    void SetExtraKey(const std::optional<std::string>& key);

private:
    Ui::MainWindow* ui;
    std::function<void(int)> digit_callback_;
    std::function<void(Operation)> operation_callback_;
    std::function<void(ControlKey)> control_callback_;
    std::function<void(ControllerType)> controller_callback_;
    QPalette normal_palette_;
};
