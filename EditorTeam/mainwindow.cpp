#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Заполнение главного меню
    createActions();
    createMenus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    // 'File'

    openAction = new QAction(tr("Open"), this);
    openAction->setStatusTip(tr("Open a file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::onOpen);

    closeAction = new QAction(tr("Close"), this);
    closeAction->setStatusTip(tr("Close a file"));
    connect(closeAction, &QAction::triggered, this, &MainWindow::onClose);

    saveAction = new QAction(tr("Save"), this);
    saveAction->setStatusTip(tr("Save a file"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::onSave);

    saveAsAction = new QAction(tr("Save as"), this);
    saveAsAction->setStatusTip(tr("Save file as"));
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::onSaveAs);

    printAction = new QAction(tr("Print"), this);
    printAction->setStatusTip(tr("Print a file"));
    connect(printAction, &QAction::triggered, this, &MainWindow::onPrint);

    exitAction = new QAction(tr("Exit"), this);
    exitAction->setStatusTip(tr("Exit application"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExit);

    // 'Edit'

    copyTextFormatAction = new QAction(tr("Copy text format"), this);
    copyTextFormatAction->setStatusTip(tr("Copy text format"));
    connect(copyTextFormatAction, &QAction::triggered, this, &MainWindow::onCopyTextFormat);

    applyTextFormatAction = new QAction(tr("Apply text format"), this);
    applyTextFormatAction->setStatusTip(tr("Apply text format"));
    connect(applyTextFormatAction, &QAction::triggered, this, &MainWindow::onApplyTextFormat);

    alignTextRightAction = new QAction(tr("Align text right"), this);
    alignTextRightAction->setStatusTip(tr("Align text right"));
    connect(alignTextRightAction, &QAction::triggered, this, &MainWindow::onAlignTextRight);

    alignTextLeftAction = new QAction(tr("Align text left"), this);
    alignTextLeftAction->setStatusTip(tr("Align text left"));
    connect(alignTextLeftAction, &QAction::triggered, this, &MainWindow::onAlignTextLeft);

    switchFontAction = new QAction(tr("Switch font"), this);
    switchFontAction->setStatusTip(tr("Swith font to other"));
    connect(switchFontAction, &QAction::triggered, this, &MainWindow::onSwitchFont);

    // 'Settings'

    changeLangAction = new QAction(tr("Language"), this);
    changeLangAction->setStatusTip(tr("Change application language"));
    connect(changeLangAction, &QAction::triggered, this, &MainWindow::onChangeLang);

    changeKeyBindAction = new QAction(tr("Key bindings"), this);
    changeKeyBindAction->setStatusTip(tr("Edit key bindings settings"));
    connect(changeKeyBindAction, &QAction::triggered, this, &MainWindow::onChangeKeyBind);

    changeStyleAction = new QAction(tr("Change style"), this);
    changeStyleAction->setStatusTip(tr("Change application style"));
    connect(changeStyleAction, &QAction::triggered, this, &MainWindow::onChangeStyle);

    // '?'

    helpAction = new QAction(tr("Help"), this);
    helpAction->setStatusTip(tr("Show application manual"));
    connect(helpAction, &QAction::triggered, this, &MainWindow::onHelp);

    aboutAction = new QAction(tr("About"), this);
    aboutAction->setStatusTip(tr("Short info about application"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAbout);
}

void MainWindow::createMenus()
{
    // 'File'
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(closeAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // 'Edit'
    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(copyTextFormatAction);
    editMenu->addAction(applyTextFormatAction);
    editMenu->addSeparator();
    editMenu->addAction(alignTextRightAction);
    editMenu->addAction(alignTextLeftAction);
    editMenu->addSeparator();
    editMenu->addAction(switchFontAction);

    // 'Settings'
    settingsMenu = menuBar()->addMenu((tr("&Settings")));
    settingsMenu->addAction(changeLangAction);
    settingsMenu->addSeparator();
    settingsMenu->addAction(changeKeyBindAction);
    settingsMenu->addSeparator();
    settingsMenu->addAction(changeStyleAction);

    // '?'
    questionMenu = menuBar()->addMenu("?");
    questionMenu->addAction(helpAction);
    questionMenu->addSeparator();
    questionMenu->addAction(aboutAction);

}

void MainWindow::onOpen()
{

}

void MainWindow::onClose()
{

}

void MainWindow::onSave()
{

}

void MainWindow::onSaveAs()
{

}

void MainWindow::onPrint()
{

}

void MainWindow::onExit()
{

}

void MainWindow::onCopyTextFormat()
{

}

void MainWindow::onApplyTextFormat()
{

}

void MainWindow::onAlignTextRight()
{

}

void MainWindow::onAlignTextLeft()
{

}

void MainWindow::onSwitchFont()
{

}

void MainWindow::onChangeLang()
{

}

void MainWindow::onChangeKeyBind()
{

}

void MainWindow::onChangeStyle()
{

}

void MainWindow::onHelp()
{

}

void MainWindow::onAbout()
{

}





