#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBoxLayout>
#include "const_strings.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      translator(new QTranslator(this))
{
    ui->setupUi(this);

    // Заполнение главного меню
    createActions();
    createMenus();

    retranslateGUI();

    //Добавление поля для размещения редактируемого текста
    QBoxLayout * boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    textEdit = new QTextEdit(this);
    boxLayout->addWidget(textEdit, 0);
    ui->centralwidget->setLayout(boxLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createAction(QAction** action,
    void (MainWindow::*funcSlot)())
{
   *action = new QAction(this);

   connect(*action, &QAction::triggered, this, funcSlot);
}

void MainWindow::createActions()
{
    // 'File'
    createAction(&newAction, &MainWindow::onNew);
    createAction(&openAction, &MainWindow::onOpen);
    createAction(&closeAction, &MainWindow::onClose);
    createAction(&saveAction, &MainWindow::onSave);
    createAction(&saveAsAction, &MainWindow::onSaveAs);
    createAction(&printAction, &MainWindow::onPrint);
    createAction(&exitAction, &MainWindow::onExit);

    // 'Edit'
    createAction(&copyTextFormatAction, &MainWindow::onCopyTextFormat);
    createAction(&applyTextFormatAction, &MainWindow::onApplyTextFormat);
    createAction(&alignTextRightAction, &MainWindow::onAlignTextRight);
    createAction(&alignTextLeftAction, &MainWindow::onAlignTextLeft);
    createAction(&alignTextCenterAction, &MainWindow::onAlignTextCenter);
    createAction(&switchFontAction, &MainWindow::onSwitchFont);

    // 'Settings'
    createAction(&changeLangAction, &MainWindow::onChangeLang);
    createAction(&changeKeyBindAction, &MainWindow::onChangeKeyBind);
    createAction(&changeStyleAction, &MainWindow::onChangeStyle);

    // '?'
    createAction(&helpAction, &MainWindow::onHelp);
    createAction(&aboutAction, &MainWindow::onAbout);
}

void MainWindow::createMenus()
{
    // 'File'
    fileMenu = new QMenu(this);
    menuBar()->addMenu(fileMenu);
    fileMenu->addAction(newAction);
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

void MainWindow::retranslateAction(QAction **action,
    const QPair<const char*, const char*> &strPair)
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
    retranslateAction(&applyTextFormatAction, APPLY_TEXT_FORMAT_ACTION_STR_PAIR);
    retranslateAction(&alignTextRightAction, ALIGN_TEXT_RIGHT_ACTION_STR_PAIR);
    retranslateAction(&alignTextLeftAction, ALIGN_TEXT_LEFT_ACTION_STR_PAIR);
    retranslateAction(&alignTextCenterAction, ALIGN_TEXT_CENTER_ACTION_STR_PAIR);
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
    if(translator->language() == "ru_RU")
        translator->load(":/l10n_en.qm");
    else
        translator->load(":/l10n_ru.qm");

    QApplication::installTranslator(translator);

    retranslateMenus();
    retranslateActions();
}

void MainWindow::onNew()
{

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
    retranslateGUI();
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





