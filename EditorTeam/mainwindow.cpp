#include "mainwindow.h"
#include "const_strings.h"
#include "ui_mainwindow.h"
#include <QBoxLayout>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QStyle>
#include <QPrinter>
#include <QPrintDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isModified(false)
    , file(new QFile(this))
    , hb(QSharedPointer<HelpBrowser>(
          new HelpBrowser(":/helpfiles", "index.htm")))
    , translator(new QTranslator(this))
{
    setWindowIcon(QIcon(logoIconPath));
    ui->setupUi(this);

    // Заполнение главного меню
    createActions();
    createMenus();

    // Функция настроек и заполнения тулбара
    setMainToolBar();

    retranslateGUI();

    // Добавление поля для размещения редактируемого текста
    QBoxLayout *boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    textEdit = new QTextEdit(this);
    boxLayout->addWidget(textEdit, 0);
    ui->centralwidget->setLayout(boxLayout);

    /*! GubaydullinRG
    Привязка события изменения содержимого textEdit к вызову
    слота onTextModified() */
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(onTextModified()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::createAction(QAction **action, const QString &iconPath,
                              void (MainWindow::*funcSlot)())
{
    *action = new QAction(this);

    (*action)->setIcon(QIcon(iconPath));

    connect(*action, &QAction::triggered, this, funcSlot);
}

void MainWindow::createActions()
{
    // 'File'
    createAction(&newAction, newIconPath, &MainWindow::onNew);
    createAction(&openAction, openIconPath, &MainWindow::onOpen);
    createAction(&closeAction, closeIconPath, &MainWindow::onClose);
    createAction(&saveAction, saveIconPath, &MainWindow::onSave);
    createAction(&saveAsAction, saveAsIconPath, &MainWindow::onSaveAs);
    createAction(&printAction, printIconPath, &MainWindow::onPrint);
    createAction(&exitAction, exitIconPath, &MainWindow::onExit);

    // 'Edit'
    createAction(&copyTextFormatAction, copyTextFormatIconPath,
                 &MainWindow::onCopyTextFormat);
    createAction(&applyTextFormatAction, applyTextFormatIconPath,
                 &MainWindow::onApplyTextFormat);
    createAction(&alignTextLeftAction, alignLeftIconPath,
                 &MainWindow::onAlignTextLeft);
    createAction(&alignTextCenterAction, alignCenterIconPath,
                 &MainWindow::onAlignTextCenter);
    createAction(&alignTextRightAction, alignRightIconPath,
                 &MainWindow::onAlignTextRight);
    createAction(&switchFontAction, switchFontIconPath,
                 &MainWindow::onSwitchFont);

    // 'Settings'
    createAction(&changeLangAction, changeLanguageIconPath,
                 &MainWindow::onChangeLang);
    createAction(&changeKeyBindAction, keyBindsIconPath,
                 &MainWindow::onChangeKeyBind);
    createAction(&changeStyleAction, changeStyleIconPath,
                 &MainWindow::onChangeStyle);

    // '?'
    createAction(&helpAction, helpIconPath, &MainWindow::onHelp);
    createAction(&aboutAction, aboutIconPath, &MainWindow::onAbout);
}

void MainWindow::createMenus()
{
    // 'File'
    fileMenu = new QMenu(this);
    menuBar()->addMenu(fileMenu);
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(closeAction);
    closeAction->setEnabled(false); // На старте нам нечего закрывать
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    saveAction->setEnabled(false); // На старте нам некуда сохранять
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // 'Edit'
    editMenu = new QMenu(this);
    menuBar()->addMenu(editMenu);
    editMenu->addAction(copyTextFormatAction);
    editMenu->addAction(applyTextFormatAction);
    editMenu->addSeparator();
    editMenu->addAction(alignTextRightAction);
    editMenu->addAction(alignTextLeftAction);
    editMenu->addAction(alignTextCenterAction);
    editMenu->addSeparator();
    editMenu->addAction(switchFontAction);

    // 'Settings'
    settingsMenu = new QMenu(this);
    menuBar()->addMenu(settingsMenu);
    settingsMenu->addAction(changeLangAction);
    settingsMenu->addSeparator();
    settingsMenu->addAction(changeKeyBindAction);
    settingsMenu->addSeparator();
    settingsMenu->addAction(changeStyleAction);

    // '?'
    questionMenu = new QMenu(this);
    menuBar()->addMenu(questionMenu);
    questionMenu->addAction(helpAction);
    questionMenu->addSeparator();
    questionMenu->addAction(aboutAction);

    retranslateMenus();
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        retranslateMenus();
        retranslateActions();
    }
    QMainWindow::changeEvent(event);
}

void MainWindow::retranslateAction(
    QAction **action, const QPair<const char *, const char *> &strPair)
{
    (*action)->setText(tr(strPair.first));

    (*action)->setStatusTip(tr(strPair.second));
}

void MainWindow::retranslateActions()
{
    // 'File'
    retranslateAction(&newAction, NEW_ACTION_STR_PAIR);
    retranslateAction(&openAction, OPEN_ACTION_STR_PAIR);
    retranslateAction(&closeAction, CLOSE_ACTION_STR_PAIR);
    retranslateAction(&saveAction, SAVE_ACTION_STR_PAIR);
    retranslateAction(&saveAsAction, SAVEAS_ACTION_STR_PAIR);
    retranslateAction(&printAction, PRINT_ACTION_STR_PAIR);
    retranslateAction(&exitAction, EXIT_ACTION_STR_PAIR);

    // 'Edit'
    retranslateAction(&copyTextFormatAction, COPY_TEXT_FORMAT_ACTION_STR_PAIR);
    retranslateAction(&applyTextFormatAction,
                      APPLY_TEXT_FORMAT_ACTION_STR_PAIR);
    retranslateAction(&alignTextRightAction, ALIGN_TEXT_RIGHT_ACTION_STR_PAIR);
    retranslateAction(&alignTextLeftAction, ALIGN_TEXT_LEFT_ACTION_STR_PAIR);
    retranslateAction(&alignTextCenterAction,
                      ALIGN_TEXT_CENTER_ACTION_STR_PAIR);
    retranslateAction(&switchFontAction, SWITCH_FONT_ACTION_STR_PAIR);

    // 'Settings'
    retranslateAction(&changeLangAction, CHANGE_LANG_ACTION_STR_PAIR);
    retranslateAction(&changeKeyBindAction, CHANGE_KEY_BIND_ACTION_STR_PAIR);
    retranslateAction(&changeStyleAction, CHANGE_STYLE_ACTION_STR_PAIR);

    // '?'
    retranslateAction(&helpAction, HELP_ACTION_STR_PAIR);
    retranslateAction(&aboutAction, ABOUT_ACTION_STR_PAIR);
}

void MainWindow::retranslateMenus()
{
    fileMenu->setTitle(tr(FILE_MENU_STR));
    editMenu->setTitle(tr(EDIT_MENU_STR));
    settingsMenu->setTitle(tr(SETTINGS_MENU_STR));
    questionMenu->setTitle(tr(QUESTION_MENU_STR));
}

void MainWindow::retranslateGUI()
{
    if (translator->language() == "ru_RU")
        translator->load(":/translation/l10n_en.qm");
    else
        translator->load(":/translation/l10n_ru.qm");

    QApplication::installTranslator(translator);

    retranslateMenus();
    retranslateActions();
}

void MainWindow::onSave()
{
    if (file->isOpen())
    {
        // Проверим режим открытого файла на возможность записи,
        // если нет, то дадим эту возможность
        if (!(file->openMode() & QFile::WriteOnly))
        {
            file->close();
            if (!file->open(QIODevice::ReadWrite | QIODevice::Text))
            {
                ui->statusbar->showMessage(tr("Can't save file."));
                return;
            }
        }

        QTextStream stream(file);
        stream.seek(0);
        stream << textEdit->toPlainText();

        ui->statusbar->showMessage(file->fileName() + " " +
                                   tr("has been saved."));

        isModified = false;
    }
    else
    // На случай, если никакой файл в textEdit не загружен,
    // но юзер хочет сохранить содержимое textEdit в файл,
    {
        onSaveAs();
    }

    saveAction->setEnabled(false);
}

void MainWindow::onSaveAs()
{
    QString filePath{QFileDialog::getSaveFileName(this, tr("Save file as "),
                                                  QDir::current().path(),
                                                  tr("Text file(*.txt)"))};

    if (filePath.length())
    {
        if (file->isOpen())
            file->close();

        file->setFileName(filePath);
        if (file->open(QFile::WriteOnly))
        {
            QTextStream stream(file);

            stream << textEdit->toPlainText();

            ui->statusbar->showMessage(tr("File saved as ") + file->fileName() +
                                       '.');

            isModified = false;
        }
        else //! open
        {
            QMessageBox::warning(this, tr("Can't save file"),
                                 tr("Cannot save file ") + filePath);
        }
    }
}

void MainWindow::onPrint()
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle(tr("Print"));
    if (dlg.exec() != QDialog::Accepted)
        return;
    QString printStr = textEdit->toPlainText();
    textEdit->print(&printer);
}

void MainWindow::onExit()
{
    if (!isTextModified)
        MainWindow::close();
    else if (warningWindow())
        MainWindow::close();
}

void MainWindow::onCopyTextFormat() {}

void MainWindow::onApplyTextFormat() {}

void MainWindow::onAlignTextRight() {}

void MainWindow::onAlignTextLeft() {}

void MainWindow::onAlignTextCenter() {}

void MainWindow::onSwitchFont() {}

void MainWindow::onChangeLang() { retranslateGUI(); }

void MainWindow::onChangeKeyBind() {}

void MainWindow::onChangeStyle()
{
    QString newStyle = "white";
    if (currentStyle == newStyle)
    {
        newStyle = "grey";
    }
    QFile qss(":/themes/" + newStyle + ".qss");
    if (!qss.open(QIODevice::ReadOnly))
        return;

    qApp->setStyleSheet(qss.readAll());
    qss.close();
    currentStyle = newStyle;
}

void MainWindow::onNew()
{
    textEdit->clear();
    textEdit->setHidden(false);
    lastFilename = "file.txt";
}

void MainWindow::onOpen()
{

    QString fileName;
    fileName = QFileDialog::getOpenFileName(
        this, tr("Open Document"), QDir::currentPath(),
        "All files (*.*) ;; Document files (*.txt)");
    if (fileName == "file.txt")
    {
        return;
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Error"), tr("Open failed"));
            return;
        }
        else
        {
            if (!file.isReadable())
            {
                QMessageBox::warning(this, tr("Error"),
                                     tr("The file is not read"));
            }
            else
            {
                QTextStream textStream(&file);
                while (!textStream.atEnd())
                {
                    textEdit->setPlainText(textStream.readAll());
                }
                textEdit->show();
                file.close();
                lastFilename = fileName;
            }
        }
    }
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

void MainWindow::onHelp()
{
    hb->resize(600, 400);
    hb->show();
}

void MainWindow::onAbout()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("О программе");
    msgBox.setIconPixmap(appIconPath);

    msgBox.setInformativeText(" ПО Текстовый редактор v 0.0 \n\n"

                              "  GB_CommandProgCPP_team3\n\n"

                              "© 2008-2022 The Qt Company Ltd.\n "
                              "     Все права защищены.\n\n");
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

/*! GubaydullinRG
        Выполнение действий в случае изменения
        содержимого textEdit */
void MainWindow::onTextModified()
{
    isModified = true;
    saveAction->setEnabled(true);
}

bool MainWindow::warningWindow()
{
    QMessageBox choice; // Создаём диалоговое окно
    choice.setWindowTitle(tr("Вы уверены?"));
    choice.setText(tr("Все несохраненные данные будут утеряны!"));
    choice.addButton(tr("Да"), QMessageBox::YesRole);
    choice.addButton(tr("Нет"), QMessageBox::NoRole);
    if (choice.exec() == false)
    {
        return true;
    }
    else
    {
        choice.close();
        return false;
    }
}

void MainWindow::changeEnableActions() // Переключение активности режима кнопки
{
    isTextModified = true;
    closeAction->setEnabled(true);
}

void MainWindow::setMainToolBar() // Установка настроек и иконок тулбара
{
    mainToolBar = addToolBar("");
    mainToolBar->setFloatable(false);
    mainToolBar->setMovable(false);
    mainToolBar->setContextMenuPolicy(Qt::CustomContextMenu);

    mainToolBar->addAction(newAction);
    mainToolBar->addAction(openAction);
    mainToolBar->addAction(saveAction);
    mainToolBar->addAction(saveAsAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(printAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(copyTextFormatAction);
    mainToolBar->addAction(applyTextFormatAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(alignTextLeftAction);
    mainToolBar->addAction(alignTextCenterAction);
    mainToolBar->addAction(alignTextRightAction);
}
