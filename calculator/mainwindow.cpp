#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
MainWindow::MainWindow(QWidget*p):QMainWindow(p),ui(new Ui::MainWindow){ui->setupUi(this);normal_palette_=ui->l_result->palette();
 for(auto*b:findChildren<QPushButton*>()){QString t=b->text();if(t.size()==1&&t[0].isDigit())connect(b,&QPushButton::clicked,this,[this,t]{if(digit_)digit_(t.toInt());});}
 auto op=[this](const char*name,Operation v){auto*b=findChild<QPushButton*>(name);connect(b,&QPushButton::clicked,this,[this,v]{if(operation_)operation_(v);});};
 op("tb_add",Operation::ADDITION);op("tb_sub",Operation::SUBTRACTION);op("tb_mul",Operation::MULTIPLICATION);op("tb_div",Operation::DIVISION);op("tb_pow",Operation::POWER);
 auto ctl=[this](const char*name,ControlKey v){auto*b=findChild<QPushButton*>(name);connect(b,&QPushButton::clicked,this,[this,v]{if(control_)control_(v);});};
 ctl("tb_equals",ControlKey::EQUALS);ctl("tb_clear",ControlKey::CLEAR);ctl("tb_ms",ControlKey::MEM_SAVE);ctl("tb_mr",ControlKey::MEM_LOAD);ctl("tb_mc",ControlKey::MEM_CLEAR);ctl("tb_sign",ControlKey::PLUS_MINUS);ctl("tb_back",ControlKey::BACKSPACE);ctl("tb_extra",ControlKey::EXTRA_KEY);
 connect(ui->cmb_controller,qOverload<int>(&QComboBox::currentIndexChanged),this,[this](int i){if(controller_)controller_(static_cast<ControllerType>(i));});}
MainWindow::~MainWindow(){delete ui;}
void MainWindow::SetInputText(const std::string&s){ui->l_result->setStyleSheet("");ui->l_result->setPalette(normal_palette_);ui->l_result->setText(QString::fromStdString(s));}
void MainWindow::SetErrorText(const std::string&s){ui->l_result->setStyleSheet("color: red;");ui->l_result->setText(QString::fromStdString(s));}
void MainWindow::SetFormulaText(const std::string&s){ui->l_formula->setText(QString::fromStdString(s));}
void MainWindow::SetMemText(const std::string&s){ui->l_memory->setText(QString::fromStdString(s));}
void MainWindow::SetExtraKey(std::optional<std::string>s){ui->tb_extra->setVisible(s.has_value());if(s)ui->tb_extra->setText(QString::fromStdString(*s));}
