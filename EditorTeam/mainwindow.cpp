#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    file( new QFile),
    isModified(false)
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

    connect(textEdit, SIGNAL(textChanged()), this, SLOT(onTextModified()));
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
    closeAction->setEnabled(false); //На старте нам нечего закрывать
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    saveAction->setEnabled(false); //На старте нам некуда сохранять
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
    closeAction->setEnabled(true);
    //saveAction->setEnabled(true); //перенёс в onTextModified()
}

void MainWindow::onClose()
{
    //Здесь нужна проверка, изменено ли
    //содержимое textEdit
    //if(isModified)
    //Если true, то спросить у юзера, хочет
    //ли он сохранить текст. Если хочет,
    //то вызвать onSave().

    closeAction->setEnabled(false);
    saveAction->setEnabled(false);
}

void MainWindow::onSave()
{
    if (file->isOpen())
    {
        //Проверим режим открытого файла на возможность записи,
        //если нет, то дадим эту возможность
        if(!(file->openMode() & QFile::WriteOnly))
        {
            file->close();
            if(!file->open(QIODevice::ReadWrite | QIODevice::Text))
            {
                ui->statusbar->showMessage(tr("Can't open "));
                return;
            }
        }

        QTextStream stream(file);
        stream.seek(0);
        stream << textEdit->toPlainText();

        ui->statusbar->showMessage(file->fileName() +
            " " + tr("сохранён."));

        isModified = false;
    }
    else
        //На случай, если никакой файл в textEdit не загружен,
        //но юзер хочет сохранить содержимое textEdit в файл,
    {
        onSaveAs();
    }

    saveAction->setEnabled(false);
}

void MainWindow::onSaveAs()
{
    QString filePath { QFileDialog::getSaveFileName(this,
        tr("Сохранить файл как"), QDir::current().path(),
            tr("Текстовый файл(*.txt)")) };

    if (filePath.length())
    {
        if (file->isOpen()) file->close();

        QString ext { QString { &(filePath.data()
                        [ filePath.length() - 4 ])}};

        file->setFileName(filePath);
        if (file->open(QFile::WriteOnly | QFile::NewOnly))
        {
            QTextStream stream(file);

            stream << textEdit->toPlainText();

            ui->statusbar->showMessage(tr("Файл сохранён как ") + file->fileName() + '.');

            isModified = false;
        }
        else //!open
        {
            QMessageBox::warning(this, tr("Файл не найден"),
                tr("Не могу открыть файл ") + filePath);
        }
    }
}

void MainWindow::onPrint()
{

}

void MainWindow::onExit()
{
    onClose(); //здесь есть проверка на сохранение текста

    QApplication::exit(0);
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

void MainWindow::onTextModified()
{
    isModified = true;
    saveAction->setEnabled(true);
}





