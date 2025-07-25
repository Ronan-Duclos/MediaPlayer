#include "mainwindow.hpp"
#include "../ui_mainwindow.h"

#include <QLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *cw = ui->centralwidget;
    this->setFixedHeight(this->height());
    this->setFixedWidth(this->width());
    cw->setFixedHeight(this->height());
    cw->setFixedWidth(this->width());
    m_controller = std::make_unique<MediaPlayerC>(cw);
    this->setWindowIcon(QIcon("img/CanaSky.ico"));
    this->setWindowTitle("CanaSky Player");
}

MainWindow::~MainWindow()
{
    delete ui;
}
