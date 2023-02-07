<<<<<<< Updated upstream
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Заполнение главного меню
    createActions();
    createMenus();

    //Добавление поля для размещения редактируемого текста
    QBoxLayout * boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    textEdit = new QTextEdit(this);
    boxLayout->addWidget(textEdit, 0);
    ui->centralwidget->setLayout(boxLayout);
    connect(textEdit, &QTextEdit::textChanged, this, &MainWindow::changeCloseAction); //Вызываем функцию при изминении текста
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
    createAction(&newAction, tr("New"),
        tr("Create new file"), &MainWindow::onNew);
    createAction(&openAction, tr("Open"),
        tr("Open a file"), &MainWindow::onOpen);
    createAction(&closeAction, tr("Close"),
        tr("Close a file"), &MainWindow::onClose);
    createAction(&saveAction, tr("Save"),
        tr("Save a file"), &MainWindow::onSave);
    createAction(&saveAsAction, tr("Save as"),
        tr("Save file as"), &MainWindow::onSaveAs);
    createAction(&printAction, tr("Print"),
        tr("Print a file"), &MainWindow::onPrint);
    createAction(&exitAction, tr("Exit"),
        tr("Exit application"), &MainWindow::onExit);

    // 'Edit'
    createAction(&copyTextFormatAction, tr("Copy text format"),
        tr("Copy text format"), &MainWindow::onCopyTextFormat);
    createAction(&applyTextFormatAction, tr("Apply text format"),
        tr("Apply text format"), &MainWindow::onApplyTextFormat);
    createAction(&alignTextRightAction, tr("Align text right"),
        tr("Align text right"), &MainWindow::onAlignTextRight);
    createAction(&alignTextLeftAction, tr("Align text left"),
        tr("Align text left"), &MainWindow::onAlignTextLeft);
    createAction(&alignTextCenterAction, tr("Align text center"),
        tr("Align text center"), &MainWindow::onAlignTextCenter);
    createAction(&switchFontAction, tr("Switch font"),
        tr("Switch font to other"), &MainWindow::onSwitchFont);

    // 'Settings'
    createAction(&changeLangAction, tr("Language"),
        tr("Change application language"), &MainWindow::onChangeLang);
    createAction(&changeKeyBindAction, tr("Key bindings"),
        tr("Edit key bindings settings"), &MainWindow::onChangeKeyBind);
    createAction(&changeStyleAction, tr("Change style"),
        tr("Change application style"), &MainWindow::onChangeStyle);

    // '?'
    createAction(&helpAction, tr("Help"),
        tr("Show application manual"), &MainWindow::onHelp);
    createAction(&aboutAction, tr("About"),
        tr("Short info about application"), &MainWindow::onAbout);
}

void MainWindow::createMenus()
{
    // 'File'
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(closeAction);
    changeCloseAction(); // Переключаем в неактивный режим
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
    editMenu->addAction(alignTextCenterAction);
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

void MainWindow::onNew()
{

}

void MainWindow::onOpen()
{

}

void MainWindow::onClose()
{
    if (!(textEdit->toPlainText().isEmpty()))
    {
        closeAction->setEnabled(true);
        if (warningWindow())
            textEdit->clear();
    }
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
    if (textEdit->toPlainText().isEmpty())
        MainWindow::close();
    else if (warningWindow())
        MainWindow::close();
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

void MainWindow::onAlignTextCenter()
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

bool MainWindow::warningWindow()
{
    QMessageBox choise; // Создаём диалоговое окно
    choise.setWindowTitle(tr("Вы уверены?"));
    choise.setText(tr("Все несохраненные данные будут утеряны!"));
    choise.addButton(tr("Да"), QMessageBox::YesRole);
    choise.addButton(tr("Нет"), QMessageBox::NoRole);
    if (choise.exec() == false){
         return true;
    } else {
        choise.close();
        return false;
    }
}

void MainWindow::changeCloseAction() // Переключение активности режима кнопки
{
    if (closeAction->isEnabled())
        closeAction->setEnabled(false);
    else closeAction->setEnabled(true);
}



=======
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Заполнение главного меню
    createActions();
    createMenus();

    //Добавление поля для размещения редактируемого текста
    QBoxLayout * boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    textEdit = new QTextEdit(this);
    boxLayout->addWidget(textEdit, 0);
    ui->centralwidget->setLayout(boxLayout);
    connect(textEdit, &QTextEdit::textChanged, this, &MainWindow::changeEnableActions); //Вызываем функцию при изминении текста
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
    createAction(&newAction, tr("New"),
        tr("Create new file"), &MainWindow::onNew);
    createAction(&openAction, tr("Open"),
        tr("Open a file"), &MainWindow::onOpen);
    createAction(&closeAction, tr("Close"),
        tr("Close a file"), &MainWindow::onClose);
    createAction(&saveAction, tr("Save"),
        tr("Save a file"), &MainWindow::onSave);
    createAction(&saveAsAction, tr("Save as"),
        tr("Save file as"), &MainWindow::onSaveAs);
    createAction(&printAction, tr("Print"),
        tr("Print a file"), &MainWindow::onPrint);
    createAction(&exitAction, tr("Exit"),
        tr("Exit application"), &MainWindow::onExit);

    // 'Edit'
    createAction(&copyTextFormatAction, tr("Copy text format"),
        tr("Copy text format"), &MainWindow::onCopyTextFormat);
    createAction(&applyTextFormatAction, tr("Apply text format"),
        tr("Apply text format"), &MainWindow::onApplyTextFormat);
    createAction(&alignTextRightAction, tr("Align text right"),
        tr("Align text right"), &MainWindow::onAlignTextRight);
    createAction(&alignTextLeftAction, tr("Align text left"),
        tr("Align text left"), &MainWindow::onAlignTextLeft);
    createAction(&alignTextCenterAction, tr("Align text center"),
        tr("Align text center"), &MainWindow::onAlignTextCenter);
    createAction(&switchFontAction, tr("Switch font"),
        tr("Switch font to other"), &MainWindow::onSwitchFont);

    // 'Settings'
    createAction(&changeLangAction, tr("Language"),
        tr("Change application language"), &MainWindow::onChangeLang);
    createAction(&changeKeyBindAction, tr("Key bindings"),
        tr("Edit key bindings settings"), &MainWindow::onChangeKeyBind);
    createAction(&changeStyleAction, tr("Change style"),
        tr("Change application style"), &MainWindow::onChangeStyle);

    // '?'
    createAction(&helpAction, tr("Help"),
        tr("Show application manual"), &MainWindow::onHelp);
    createAction(&aboutAction, tr("About"),
        tr("Short info about application"), &MainWindow::onAbout);
}

void MainWindow::createMenus()
{
    // 'File'
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(closeAction);
    closeAction->setEnabled(false); // Переключаем в неактивный режим
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
    editMenu->addAction(alignTextCenterAction);
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

void MainWindow::onNew()
{

}

void MainWindow::onOpen()
{

}

void MainWindow::onClose()
{
    if (isTextModified)
    {
        if (warningWindow())
        {
            textEdit->clear();
            isTextModified = false;
            closeAction->setEnabled(false);
        }
    }
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
    if (!isTextModified)
        MainWindow::close();
    else if (warningWindow())
        MainWindow::close();
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

void MainWindow::onAlignTextCenter()
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

bool MainWindow::warningWindow()
{
    QMessageBox choise; // Создаём диалоговое окно
    choise.setWindowTitle(tr("Вы уверены?"));
    choise.setText(tr("Все несохраненные данные будут утеряны!"));
    choise.addButton(tr("Да"), QMessageBox::YesRole);
    choise.addButton(tr("Нет"), QMessageBox::NoRole);
    if (choise.exec() == false){
         return true;
    } else {
        choise.close();
        return false;
    }
}

void MainWindow::changeEnableActions() // Переключение активности режима кнопки
{
    isTextModified = true;
    closeAction->setEnabled(true);
}



>>>>>>> Stashed changes
