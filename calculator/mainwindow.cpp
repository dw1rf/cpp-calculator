#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <cmath>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    SetText("0");
    ui->l_memory->clear();
    ui->l_formula->clear();

    for (auto* button : findChildren<QPushButton*>()) {
        connect(button, &QPushButton::clicked, this, [this, button] {
            HandleButton(button->text());
        });
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetText(const QString& text) {
    input_number_ = text;
    ui->l_result->setText(text);
}

void MainWindow::AddText(const QString& suffix) {
    if (start_new_input_) {
        if (operation_.isEmpty()) {
            ui->l_formula->clear();
        }
        SetText(suffix);
        start_new_input_ = false;
    } else {
        SetText(input_number_ + suffix);
    }

    if (!operation_.isEmpty()) {
        has_second_operand_ = true;
    }
}

QString MainWindow::FormatNumber(double value) const {
    if (std::isfinite(value)
        && std::abs(value) < 9e15
        && std::abs(value - std::round(value)) < 1e-10) {
        return QString::number(std::round(value), 'f', 0);
    }
    return QString::number(value, 'g', 15);
}

void MainWindow::SelectOperation(const QString& text) {
    if (operation_.isEmpty()) {
        left_text_ = input_number_;
    } else if (has_second_operand_) {
        const double result = calculator_.Calculate(operation_, input_number_.toDouble());
        left_text_ = FormatNumber(result);
        SetText(left_text_);
    }

    calculator_.SetLeft(left_text_.toDouble());
    operation_ = text;
    start_new_input_ = true;
    has_second_operand_ = false;

    const QString displayed_operation = operation_ == "xʸ" ? "^" : operation_;
    ui->l_formula->setText(left_text_ + " " + displayed_operation);
}

void MainWindow::Calculate() {
    if (operation_.isEmpty()) {
        return;
    }

    const QString right_text = has_second_operand_ ? input_number_ : left_text_;
    const double result = calculator_.Calculate(operation_, right_text.toDouble());
    const QString displayed_operation = operation_ == "xʸ" ? "^" : operation_;
    ui->l_formula->setText(left_text_ + " " + displayed_operation + " " + right_text + " =");

    SetText(FormatNumber(result));
    left_text_ = input_number_;
    calculator_.SetLeft(result);
    operation_.clear();
    start_new_input_ = true;
    has_second_operand_ = false;
}

void MainWindow::HandleButton(const QString& text) {
    if (text.size() == 1 && text[0].isDigit()) {
        AddText(text);
        return;
    }

    if (text == ".") {
        if (start_new_input_) {
            AddText("0.");
        } else if (!input_number_.contains('.')) {
            AddText(".");
        }
        return;
    }

    if (text == "±") {
        if (start_new_input_) {
            return;
        }
        if (input_number_.toDouble() == 0.0) {
            SetText("0");
        } else if (input_number_.startsWith("-")) {
            SetText(input_number_.mid(1));
        } else {
            SetText("-" + input_number_);
        }
        return;
    }

    if (text == "⌫") {
        if (!start_new_input_) {
            QString shortened_number = input_number_;
            shortened_number.chop(1);
            if (shortened_number.isEmpty()
                || shortened_number == "-"
                || shortened_number == "-0") {
                shortened_number = "0";
            }
            SetText(shortened_number);
        }
        return;
    }

    if (text == "C") {
        SetText("0");
        left_text_.clear();
        operation_.clear();
        ui->l_formula->clear();
        start_new_input_ = true;
        has_second_operand_ = false;
        return;
    }

    if (text == "MC") {
        has_memory_ = false;
        ui->l_memory->clear();
        return;
    }

    if (text == "MS") {
        memory_ = input_number_.toDouble();
        has_memory_ = true;
        ui->l_memory->setText("M");
        return;
    }

    if (text == "MR") {
        if (has_memory_) {
            if (operation_.isEmpty()) {
                ui->l_formula->clear();
            } else {
                has_second_operand_ = true;
            }
            SetText(FormatNumber(memory_));
            start_new_input_ = true;
        }
        return;
    }

    if (text == "=") {
        Calculate();
        return;
    }

    if (text == "+" || text == "−" || text == "×" || text == "÷" || text == "xʸ") {
        SelectOperation(text);
    }
}
