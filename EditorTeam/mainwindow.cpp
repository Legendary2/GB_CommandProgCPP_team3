#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug> //

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

void MainWindow::createAction(QAction** action, const QString& actionTitle,
                    const QString& statusTitle, void (MainWindow::*funcSlot)())
{
   *action = new QAction(actionTitle, this);

   (*action)->setStatusTip(statusTitle);

   connect(*action, &QAction::triggered, this, funcSlot);
}

void MainWindow::createActions()
{
    // 'File'
    createAction(&openAction, QString(tr("Open")),
        QString(tr("Open a file")), &MainWindow::onOpen);
    createAction(&closeAction, QString(tr("Close")),
        QString(tr("Close a file")), &MainWindow::onClose);
    createAction(&saveAction, QString(tr("Save")),
        QString(tr("Save a file")), &MainWindow::onSave);
    createAction(&saveAsAction, QString(tr("Save as")),
        QString(tr("Save file as")), &MainWindow::onSaveAs);
    createAction(&printAction, QString(tr("Print")),
        QString(tr("Print a file")), &MainWindow::onPrint);
    createAction(&exitAction, QString(tr("Exit")),
        QString(tr("Exit application")), &MainWindow::onExit);

    // 'Edit'
    createAction(&copyTextFormatAction, QString(tr("Copy text format")),
        QString(tr("Copy text format")), &MainWindow::onCopyTextFormat);
    createAction(&applyTextFormatAction, QString(tr("Apply text format")),
        QString(tr("Apply text format")), &MainWindow::onApplyTextFormat);
    createAction(&alignTextRightAction, QString(tr("Align text right")),
        QString(tr("Align text right")), &MainWindow::onAlignTextRight);
    createAction(&alignTextLeftAction, QString(tr("Align text left")),
        QString(tr("Align text left")), &MainWindow::onAlignTextLeft);
    createAction(&switchFontAction, QString(tr("Switch font")),
        QString(tr("Switch font to other")), &MainWindow::onSwitchFont);

    // 'Settings'
    createAction(&changeLangAction, QString(tr("Language")),
        QString(tr("Change application language")), &MainWindow::onChangeLang);
    createAction(&changeKeyBindAction, QString(tr("Key bindings")),
        QString(tr("Edit key bindings settings")), &MainWindow::onChangeKeyBind);
    createAction(&changeStyleAction, QString(tr("Change style")),
        QString(tr("Change application style")), &MainWindow::onChangeStyle);

    // '?'
    createAction(&helpAction, QString(tr("Help")),
        QString(tr("Show application manual")), &MainWindow::onHelp);
    createAction(&aboutAction, QString(tr("About")),
        QString(tr("Short info about application")), &MainWindow::onAbout);
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





