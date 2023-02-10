#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpbrowser.h"
#include <QBoxLayout>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Заполнение главного меню
  createActions();
  createMenus();

  //Добавление поля для размещения редактируемого текста
  QBoxLayout *boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
  textEdit = new QTextEdit(this);
  boxLayout->addWidget(textEdit, 0);
  ui->centralwidget->setLayout(boxLayout);
}

MainWindow::~MainWindow(){ delete ui; }

void MainWindow::createAction(QAction** action, const QString& actionTitle,
    const QString& statusTitle, void (MainWindow::*funcSlot)())
{
   *action = new QAction(actionTitle, this);

   (*action)->setStatusTip(statusTitle);

   connect(*action, &QAction::triggered, this, funcSlot);
}

void MainWindow::createActions() {
  // 'File'
  createAction(&newAction, tr("New"), tr("Create new file"),
               &MainWindow::onNew);
  createAction(&openAction, tr("Open"), tr("Open a file"), &MainWindow::onOpen);
  createAction(&closeAction, tr("Close"), tr("Close a file"),
               &MainWindow::onClose);
  createAction(&saveAction, tr("Save"), tr("Save a file"), &MainWindow::onSave);
  createAction(&saveAsAction, tr("Save as"), tr("Save file as"),
               &MainWindow::onSaveAs);
  createAction(&printAction, tr("Print"), tr("Print a file"),
               &MainWindow::onPrint);
  createAction(&exitAction, tr("Exit"), tr("Exit application"),
               &MainWindow::onExit);

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
  createAction(&switchFontAction, tr("Switch font"), tr("Switch font to other"),
               &MainWindow::onSwitchFont);

  // 'Settings'
  createAction(&changeLangAction, tr("Language"),
               tr("Change application language"), &MainWindow::onChangeLang);
  createAction(&changeKeyBindAction, tr("Key bindings"),
               tr("Edit key bindings settings"), &MainWindow::onChangeKeyBind);
  createAction(&changeStyleAction, tr("Change style"),
               tr("Change application style"), &MainWindow::onChangeStyle);

  // '?'
  createAction(&helpAction, tr("Help"), tr("Show application manual"),
               &MainWindow::onHelp);
  createAction(&aboutAction, tr("About"), tr("Short info about application"),
               &MainWindow::onAbout);
}

void MainWindow::createMenus() {
  // 'File'
  fileMenu = menuBar()->addMenu(tr("&File"));
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

void MainWindow::onClose() {}

void MainWindow::onSave() {}

void MainWindow::onSaveAs() {}

void MainWindow::onPrint() {}

void MainWindow::onExit() { QApplication::exit(0); }

void MainWindow::onCopyTextFormat() {}

void MainWindow::onApplyTextFormat() {}

void MainWindow::onAlignTextRight() {}

void MainWindow::onAlignTextLeft() {}

void MainWindow::onAlignTextCenter() {}

void MainWindow::onSwitchFont() {}

void MainWindow::onChangeLang() {}

void MainWindow::onChangeKeyBind() {}

void MainWindow::onChangeStyle() {
  QString newStyle = "white";
  if (currentStyle == newStyle) {
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
    fileName = QFileDialog::getOpenFileName(this, tr("Open Document"),
    QDir::currentPath(), "All files (*.*) ;; Document files (*.txt)");
    if(fileName == "file.txt")
        {
            return;
        }
        else
        {
            QFile file(fileName);
            if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
            {
             QMessageBox::warning(this,tr("Error"),tr("Open failed"));
    return;
    }
    else
    {
    if(!file.isReadable())
    {
    QMessageBox::warning(this,tr("Error"),tr("The file is not read"));
    }
    else
    {
    QTextStream textStream(&file);
    while(!textStream.atEnd())
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

void MainWindow::onHelp()
{
    HelpBrowser helpbrowser(":/helpfiles", "index.htm");
    helpbrowser.resize(400, 400);
    helpbrowser.show();
    helpbrowser.activateWindow();
}

void MainWindow::onAbout()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("О программе");
    msgBox.setIconPixmap(QPixmap(":/images/about.png"));

    msgBox.setInformativeText(" ПО Текстовый редактор v 0.0 \n\n"

                              "  GB_CommandProgCPP_team3\n\n"

                              "© 2008-2022 The Qt Company Ltd.\n "
                              "     Все права защищены.\n\n");
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}
