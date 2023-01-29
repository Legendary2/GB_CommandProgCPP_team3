#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    menuBar()->addMenu(tr("&File"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

