#pragma once
#include "calculator.h"
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void SetText(const QString& text);
    void AddText(const QString& suffix);
    void HandleButton(const QString& text);
    void SelectOperation(const QString& text);
    void Calculate();
    QString FormatNumber(double value) const;
    Ui::MainWindow* ui;
    Calculator calculator_;
    QString input_number_ = "0";
    QString left_text_;
    QString operation_;
    bool start_new_input_ = true;
    bool has_second_operand_ = false;
    bool has_memory_ = false;
    double memory_ = 0.0;
};
