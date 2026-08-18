#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QLabel>
#include <QPushButton>

#include <array>
#include <utility>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    normal_palette_ = ui->l_result->palette();

    const std::array<QPushButton*, 10> digit_buttons{
        ui->tb_0,
        ui->tb_1,
        ui->tb_2,
        ui->tb_3,
        ui->tb_4,
        ui->tb_5,
        ui->tb_6,
        ui->tb_7,
        ui->tb_8,
        ui->tb_9,
    };
    for (std::size_t digit = 0; digit < digit_buttons.size(); ++digit) {
        connect(digit_buttons[digit], &QPushButton::clicked, this, [this, digit] {
            if (digit_callback_) {
                digit_callback_(static_cast<int>(digit));
            }
        });
    }

    const auto connect_operation = [this](QPushButton* button, Operation operation) {
        connect(button, &QPushButton::clicked, this, [this, operation] {
            if (operation_callback_) {
                operation_callback_(operation);
            }
        });
    };
    connect_operation(ui->tb_add, Operation::ADDITION);
    connect_operation(ui->tb_sub, Operation::SUBTRACTION);
    connect_operation(ui->tb_mul, Operation::MULTIPLICATION);
    connect_operation(ui->tb_div, Operation::DIVISION);
    connect_operation(ui->tb_pow, Operation::POWER);

    const auto connect_control = [this](QPushButton* button, ControlKey control_key) {
        connect(button, &QPushButton::clicked, this, [this, control_key] {
            if (control_callback_) {
                control_callback_(control_key);
            }
        });
    };
    connect_control(ui->tb_equals, ControlKey::EQUALS);
    connect_control(ui->tb_clear, ControlKey::CLEAR);
    connect_control(ui->tb_ms, ControlKey::MEM_SAVE);
    connect_control(ui->tb_mr, ControlKey::MEM_LOAD);
    connect_control(ui->tb_mc, ControlKey::MEM_CLEAR);
    connect_control(ui->tb_sign, ControlKey::PLUS_MINUS);
    connect_control(ui->tb_back, ControlKey::BACKSPACE);
    connect_control(ui->tb_extra, ControlKey::EXTRA_KEY);

    connect(ui->cmb_controller,
            qOverload<int>(&QComboBox::currentIndexChanged),
            this,
            [this](int index) {
                if (controller_callback_) {
                    controller_callback_(static_cast<ControllerType>(index));
                }
            });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetDigitKeyCallback(std::function<void(int)> callback) {
    digit_callback_ = std::move(callback);
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation)> callback) {
    operation_callback_ = std::move(callback);
}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey)> callback) {
    control_callback_ = std::move(callback);
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType)> callback) {
    controller_callback_ = std::move(callback);
}

void MainWindow::SetInputText(const std::string& text) {
    ui->l_result->setStyleSheet("");
    ui->l_result->setPalette(normal_palette_);
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text) {
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string& text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    ui->tb_extra->setVisible(key.has_value());
    if (key) {
        ui->tb_extra->setText(QString::fromStdString(*key));
    }
}
