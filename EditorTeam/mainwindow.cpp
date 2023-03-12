#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QPrintDialog>
#include <QPrinter>
#include <QRegularExpressionValidator>
#include <QStyle>
#include <QTextBlockFormat>
#include <QTextCursor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      boxLayout(new QBoxLayout(QBoxLayout::TopToBottom)),
      settingsKeeper(new SettingsKeeper(this)), isTextModified(false),
      newDataLoaded(false),
      srcHandler(QSharedPointer<IDevHandler<QString>>(new FileHandler(this))),
      hb(QSharedPointer<HelpBrowser>(
          new HelpBrowser(":/helpfiles", "index.htm"))),
      translator(new QTranslator(this)), popupMenu(new QMenu(this)),
      fontSizeLabel(new QLabel(this)), fontSizeComboBox(new QComboBox(this)) {
  ui->setupUi(this);

  // Заполнение главного меню
  createActions();
  createMenus();

  // Функция настроек и заполнения тулбара
  setMainToolBar();

  onSettingsApplyClicked();

  // Добавление поля для размещения редактируемого текста
  textEdit = new QTextEdit(this);
  boxLayout->addWidget(textEdit, 0);
  ui->centralwidget->setLayout(boxLayout);
          
  // Древо каталогов
  teamPath = "C:/";
  dirModel = new QFileSystemModel(this);
  dirModel->setRootPath(teamPath);
  treeView = new QTreeView;
  treeView->setModel(dirModel);
  viewWidget = new QDockWidget{this};
  viewWidget->setWidget(treeView);

  // Окошко поиска и кнопка 'Find'
  searchTreeEdit = new QLineEdit ;
  FindTreeButton = new QPushButton(this);
  FindTreeButton->setText(tr("Find"));
  QWidget *searchArea = new QWidget(this);
  QGridLayout *layout = new QGridLayout(this);
  layout->addWidget(searchTreeEdit, 0, 0, 1, 3);
  layout->addWidget(FindTreeButton, 0, 5);
  searchArea->setLayout(layout);
  viewWidget->setTitleBarWidget(searchArea);
  QString searchedPart = searchTreeEdit->text();
  treeView->keyboardSearch(searchedPart);
  addDockWidget(Qt::LeftDockWidgetArea, viewWidget);
  connect(FindTreeButton, SIGNAL(clicked()), this, SLOT(findFileSlot()));

  /*! GubaydullinRG
  Привязка события изменения содержимого textEdit к вызову
  слота onTextModified() */
  connect(textEdit, SIGNAL(textChanged()), this, SLOT(onTextModified()));

  connect(settingsKeeper, SIGNAL(applyButtonClicked()), this,
          SLOT(onSettingsApplyClicked()));
  connect(settingsKeeper, SIGNAL(cancelButtonClicked()), this,
          SLOT(onSettingsCancelClicked()));
  connect(settingsKeeper, SIGNAL(okButtonClicked()), this,
          SLOT(onSettingsOkClicked()));

  /*! GubaydullinRG
        Заполнение контекстного меню для textEdit */
  inflatePopupMenu();

  /*! GubaydullinRG
   *  На старте приложения создаём пустой документ */
  onNew();
  applyTextFormatAction->setEnabled(false);
}

MainWindow::~MainWindow() {
  delete ui;
  delete boxLayout;
}

void MainWindow::createAction(QAction **action, const QString &iconPath,
                              void (MainWindow::*funcSlot)()) {
  *action = new QAction(this);

  (*action)->setIcon(QIcon(iconPath));

  connect(*action, &QAction::triggered, this, funcSlot);
}

void MainWindow::createActions() {
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

  // 'Format'
  createAction(&underlineTextFormatAction, underlineTextFormatIconPath,
               &MainWindow::onUnderlineTextFormat);
  createAction(&crossedTextFormatAction, crossedTextFormatIconPath,
               &::MainWindow::onCrossedTextFormat);
  createAction(&boldTextFormatAction, boldTextFormatIconPath,
               &MainWindow::onBoldTextFormat);
  createAction(&italicTextFormatAction, italicTextFormatIconPath,
               &MainWindow::onItalicTextFormat);

  // 'Settings'
  createAction(&changeKeyBindAction, keyBindsIconPath,
               &MainWindow::onChangeKeyBind);
  createAction(&settingsAction, settingsIconPath,
               &MainWindow::onSettingsInvoke);

  // '?'
  createAction(&helpAction, helpIconPath, &MainWindow::onHelp);
  createAction(&aboutAction, aboutIconPath, &MainWindow::onAbout);
    
  // popup menu
  createAction(&copyAction, copyIconPath, &MainWindow::onCopy);
  createAction(&cutAction, cutIconPath, &MainWindow::onCut);
  createAction(&pasteAction, pasteIconPath, &MainWindow::onPaste);
  createAction(&selectAllAction, selectAllIconPath, &MainWindow::onSelectAll);
}

void MainWindow::createMenus() {
  // 'File'
  fileMenu = new QMenu(this);
  menuBar()->addMenu(fileMenu);
  fileMenu->addAction(newAction);
  newAction->setShortcut(QKeySequence("CTRL+N"));
  fileMenu->addAction(openAction);
  fileMenu->addAction(closeAction);
  closeAction->setEnabled(false); // На старте нам нечего закрывать
  fileMenu->addSeparator();
  fileMenu->addAction(saveAction);
  saveAction->setEnabled(false); // На старте нам некуда сохранять
  fileMenu->addAction(saveAsAction);
  saveAsAction->setShortcut(QKeySequence("CTRL+S"));
  fileMenu->addSeparator();
  fileMenu->addAction(printAction);
  printAction->setShortcut(QKeySequence("CTRL+P"));
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

  // 'Format'
  formatMenu = new QMenu(this);
  menuBar()->addMenu(formatMenu);
  formatMenu->addAction(underlineTextFormatAction);
  formatMenu->addAction(crossedTextFormatAction);
  formatMenu->addAction(boldTextFormatAction);
  formatMenu->addAction(italicTextFormatAction);

  // 'Settings'
  settingsMenu = new QMenu(this);
  menuBar()->addMenu(settingsMenu);
  settingsMenu->addAction(changeKeyBindAction);
  settingsMenu->addSeparator();
  settingsMenu->addAction(settingsAction);

  // '?'
  questionMenu = new QMenu(this);
  menuBar()->addMenu(questionMenu);
  questionMenu->addAction(helpAction);
  helpAction->setShortcut(QKeySequence("CTRL+H"));
  questionMenu->addSeparator();
  questionMenu->addAction(aboutAction);
  aboutAction->setShortcut(QKeySequence("CTRL+Q"));

  retranslateMenus();
}

void MainWindow::changeEvent(QEvent *event) {
  if (event->type() == QEvent::LanguageChange) {
    retranslateMenus();
    retranslateActions();
  }
  QMainWindow::changeEvent(event);
}

void MainWindow::retranslateAction(
    QAction **action, const QPair<const char *, const char *> &strPair) {
  (*action)->setText(tr(strPair.first));

  (*action)->setStatusTip(tr(strPair.second));
}

void MainWindow::retranslateActions() {
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

  // 'Format'
  retranslateAction(&underlineTextFormatAction,
                    UNDERLINE_TEXT_FORMAT_ACTION_STR_PAIR);
  retranslateAction(&crossedTextFormatAction,
                    CROSSED_TEXT_FORMAT_ACTION_STR_PAIR);
  retranslateAction(&boldTextFormatAction, BOLD_TEXT_FORMAT_ACTION_STR_PAIR);
  retranslateAction(&italicTextFormatAction,
                    ITALIC_TEXT_FORMAT_ACTION_STR_PAIR);

  // 'Settings'
  retranslateAction(&changeKeyBindAction, CHANGE_KEY_BIND_ACTION_STR_PAIR);
  retranslateAction(&settingsAction, SETTINGS_ACTION_STR_PAIR);

  // '?'
  retranslateAction(&helpAction, HELP_ACTION_STR_PAIR);
  retranslateAction(&aboutAction, ABOUT_ACTION_STR_PAIR);

  // popup
  retranslateAction(&copyAction, COPY_ACTION_STR_PAIR);
  retranslateAction(&cutAction, CUT_ACTION_STR_PAIR);
  retranslateAction(&pasteAction, PASTE_ACTION_STR_PAIR);
  retranslateAction(&selectAllAction, SELECT_ALL_ACTION_STR_PAIR);
}

void MainWindow::retranslateMenus() {
  fileMenu->setTitle(tr(FILE_MENU_STR));
  editMenu->setTitle(tr(EDIT_MENU_STR));
  formatMenu->setTitle(tr(FORMAT_MENU_STR));
  settingsMenu->setTitle(tr(SETTINGS_MENU_STR));
  questionMenu->setTitle(tr(QUESTION_MENU_STR));
}

void MainWindow::retranslateGUI() {

  std::ignore = translator->load(LANGS_MAP[settingsKeeper->getLang()]);
  QApplication::installTranslator(translator);

  retranslateMenus();
  retranslateActions();

  fontSizeLabel->setText(tr(POPUP_FONT_SIZE_STR));

  settingsKeeper->retranslateGUI();
}

void MainWindow::changeFileMenuAccess(const QString &winTitle,
                                      bool hideTextEdit, bool enableSaveAs,
                                      bool enableClose) {

  QPair<bool, bool> cachedBoolStats{isTextModified, newDataLoaded};

  setWindowTitle(winTitle);

  textEdit->clear();
  textEdit->setHidden(hideTextEdit);

  saveAsAction->setEnabled(enableSaveAs);
  closeAction->setEnabled(enableClose);

  isTextModified = cachedBoolStats.first;
  newDataLoaded = cachedBoolStats.second;
}

void MainWindow::changePopupMenuAccess() {
  if (textEdit->textCursor().hasSelection()) {
    copyAction->setEnabled(true);
    cutAction->setEnabled(true);
  } else {
    copyAction->setEnabled(false);
    cutAction->setEnabled(false);
  }

  if (textEdit->document()->isEmpty()) {
    selectAllAction->setEnabled(false);
    popupWidgetAction->setEnabled(false);
  } else {
    selectAllAction->setEnabled(true);
    popupWidgetAction->setEnabled(true);
  }
}

const std::optional<QTextCharFormat>
MainWindow::getCurrentCharFormat(const FontFeature fontFeature) const {

  QTextCursor formatsCheckCursor = textEdit->textCursor();
  if (formatsCheckCursor.isNull() || textEdit->isHidden()) {
    return std::nullopt;
  }

  if (!formatsCheckCursor.hasSelection())
    return formatsCheckCursor.charFormat();

  QTextCharFormat charFormat;

  if (textEdit->textCursor().selectionEnd() ==
      textEdit->textCursor().position()) {

    charFormat = textEdit->textCursor().charFormat(); // a

    while (formatsCheckCursor.position() >
           textEdit->textCursor().selectionStart()) {

      if (!fontFeatureEquals(charFormat, formatsCheckCursor.charFormat(),
                             fontFeature))
        return std::nullopt;

      formatsCheckCursor.movePosition(QTextCursor::PreviousCharacter,
                                      QTextCursor::KeepAnchor);
    }

  } else {

    formatsCheckCursor.movePosition(QTextCursor::NextCharacter,
                                    QTextCursor::KeepAnchor);

    charFormat = formatsCheckCursor.charFormat();

    while (formatsCheckCursor.position() <
           textEdit->textCursor().selectionEnd()) {

      formatsCheckCursor.movePosition(QTextCursor::NextCharacter,
                                      QTextCursor::KeepAnchor);

      if (!fontFeatureEquals(charFormat, formatsCheckCursor.charFormat(),
                             fontFeature))
        return {std::nullopt};
    }
  }
  return charFormat;
}

bool MainWindow::fontFeatureEquals(const QTextCharFormat &charFormatFirst,
                                   const QTextCharFormat &charFormatSecond,
                                   const FontFeature fontFeature) const {

  switch (fontFeature) {

  case FontFeature::DoesntMatter:
    return charFormatFirst == charFormatSecond;
  case FontFeature::Bold:
    return charFormatFirst.fontWeight() == charFormatSecond.fontWeight();
  case FontFeature::Crossed:
    return charFormatFirst.fontStrikeOut() == charFormatSecond.fontStrikeOut();
  case FontFeature::FontFamily:
    return charFormatFirst.font() == charFormatSecond.font();
  case FontFeature::Italic:
    return charFormatFirst.fontItalic() == charFormatSecond.fontItalic();
  case FontFeature::Underlined:
    return charFormatFirst.fontUnderline() == charFormatSecond.fontUnderline();
  case FontFeature::Size:
    return charFormatFirst.fontPointSize() == charFormatSecond.fontPointSize();
  default:
    return false;
  }

  return false;
}

void MainWindow::onSave() {
  if (srcHandler->save(textEdit->toPlainText())) {
    isTextModified = false;

    ui->statusbar->showMessage(srcHandler->getSourceName() + " " +
                               tr("has been saved."));
    saveAction->setEnabled(false);
    setWindowTitle(srcHandler->getSourceName());
  } else
    ui->statusbar->showMessage(tr("Can't save file."));
}

void MainWindow::onSaveAs() {
  if (srcHandler->saveAs(textEdit->toPlainText())) {
    isTextModified = false;
    ui->statusbar->showMessage(tr("File saved as ") +
                               srcHandler->getSourceName());
    saveAction->setEnabled(false);
    setWindowTitle(srcHandler->getSourceName());
  } else
    ui->statusbar->showMessage(tr("Can't save file."));
}

void MainWindow::onPrint() {
  QPrinter printer;
  QPrintDialog dlg(&printer, this);
  dlg.setWindowTitle(tr("Print"));
  if (dlg.exec() != QDialog::Accepted)
    return;
  QString printStr = textEdit->toPlainText();
  textEdit->print(&printer);
}

void MainWindow::onExit() {
  if (!textEdit->isHidden())
    onClose();
  QApplication::exit(0);
}

void MainWindow::onCopyTextFormat() {
  std::optional<QTextCharFormat> charFormatStorage =
      getCurrentCharFormat(FontFeature::DoesntMatter);

  if (charFormatStorage.has_value()) {
    copiedTxtFormat = charFormatStorage.value();
    applyTextFormatAction->setEnabled(true);
  }
}

void MainWindow::onApplyTextFormat() {
  if (!copiedTxtFormat.isValid()) {
    applyTextFormatAction->setEnabled(false);
    return;
  }

  textEdit->textCursor().setCharFormat(copiedTxtFormat);
}

void MainWindow::onAlignTextRight() {
  QTextCursor cursor = textEdit->textCursor();
  QTextBlockFormat txtForm = cursor.blockFormat();
  txtForm.setAlignment(Qt::AlignRight);
  cursor.mergeBlockFormat(txtForm);
  textEdit->setTextCursor(cursor);
}

void MainWindow::onAlignTextLeft() {
  QTextCursor cursor = textEdit->textCursor();
  QTextBlockFormat txtForm = cursor.blockFormat();
  txtForm.setAlignment(Qt::AlignLeft);
  cursor.mergeBlockFormat(txtForm);
  textEdit->setTextCursor(cursor);
}

void MainWindow::onAlignTextCenter() {
  QTextCursor center = textEdit->textCursor();
  QTextBlockFormat textBlockFormat = center.blockFormat();
  textBlockFormat.setAlignment(Qt::AlignCenter);
  center.mergeBlockFormat(textBlockFormat);
  textEdit->setTextCursor(center);
}

void MainWindow::onSwitchFont() {
  bool ok;
  QFont font = QFontDialog::getFont(&ok, textEdit->currentFont());
  if (ok) {
    QTextCharFormat textCharFormat;
    textCharFormat.setFont(font);
    textEdit->textCursor().setCharFormat(textCharFormat);
  }
}

void MainWindow::onChangeKeyBind() {}

void MainWindow::onChangeStyle() {
  QFile qss(STYLES_MAP[settingsKeeper->getStyle()]);
  if (!qss.open(QIODevice::ReadOnly))
    return;

  qApp->setStyleSheet(qss.readAll());
  qss.close();
}

void MainWindow::onNew() {
  onClose();
  changeFileMenuAccess(tr(NEW_DOC_STR), false, true, false);
  saveAction->setEnabled(false);
  isTextModified = false;
  newDataLoaded = true;
  copyTextFormatAction->setEnabled(true);
}

void MainWindow::onOpen() {
  if (isTextModified) {
    if (textChangedWarning()) {
      onSave();
    }
  }

  if (srcHandler->open()) {
    newDataLoaded = true;
    changeFileMenuAccess(srcHandler->getSourceName(), false, true, true);
    textEdit->setPlainText(srcHandler->getData());
    saveAction->setEnabled(false);
    isTextModified = false;
    copyTextFormatAction->setEnabled(true);
  }
}

void MainWindow::onClose() {
  if (isTextModified) {
    if (textChangedWarning()) { // Юзер согласился сохраниться
      onSave();
    }
  }

  srcHandler->close();
  saveAction->setEnabled(false);

  isTextModified = false;
  newDataLoaded = false;

  changeFileMenuAccess(tr(NO_FILE_OPENED_STR), true, false, false);
  copyTextFormatAction->setEnabled(false);
  applyTextFormatAction->setEnabled(false);
}

void MainWindow::onHelp() {
  hb->resize(600, 400);
  hb->show();
}

void MainWindow::onAbout() {
  QMessageBox msgBox;
  msgBox.setWindowTitle(tr("About THare"));
  msgBox.setIconPixmap(appIconPath);
  msgBox.setInformativeText(tr("THare v 0.5.0 \n\n"
                               "GB_CommandProgCPP_team3\n\n"
                               "© 2023 All rights reserved\n\n"));
  msgBox.setDefaultButton(QMessageBox::Ok);
  msgBox.exec();
}

/*! GubaydullinRG
        Выполнение действий в случае изменения
        содержимого textEdit */
void MainWindow::onTextModified() {

  QString srcName{srcHandler->getSourceName()};

  if (!newDataLoaded) {
    if (srcName.isEmpty()) {
      if (textEdit->isHidden())
        setWindowTitle(QString(NEW_DOC_STR).append("*"));
    } else {
      saveAction->setEnabled(true);
      setWindowTitle(srcName.append("*"));
    }
    closeAction->setEnabled(true);
    isTextModified = true;
  }
  newDataLoaded = false;
}

bool MainWindow::textChangedWarning() {
  QMessageBox choice(this); // Создаём диалоговое окно

  choice.setWindowTitle(tr("Unsaved data could be lost"));
  choice.setText(tr("Do you want to save changes?"));
  choice.addButton(tr("Yes"), QMessageBox::YesRole);
  choice.addButton(tr("No"), QMessageBox::NoRole);

  if (choice.exec() == true) {
    return false;
  } else {
    choice.close();
    return true;
  }
}

void MainWindow::onCrossedTextFormat() {
  QTextCharFormat crossedFormat;
  if (textEdit->textCursor().hasSelection()) {
    if (!textEdit->textCursor().charFormat().fontStrikeOut())
      crossedFormat.setFontStrikeOut(true);
    else
      crossedFormat.setFontStrikeOut(false);
    textEdit->textCursor().mergeCharFormat(crossedFormat);
  }
}

void MainWindow::inflatePopupMenu() {
  textEdit->setContextMenuPolicy(Qt::CustomContextMenu);

  connect(textEdit, SIGNAL(customContextMenuRequested(QPoint)), this,
          SLOT(onPopupMenuCalled(QPoint)));

  popupWidgetAction = new QWidgetAction(popupMenu);

  QWidget *fontSizeWidget = new QWidget(popupMenu);

  QHBoxLayout *fontSizeLayout = new QHBoxLayout(popupMenu);

  for (int i = 10; i <= 50; i += 10)
    fontSizeComboBox->addItem(QString::number(i));

  fontSizeComboBox->setEditable(true);

  fontSizeComboBox->setValidator(new QRegularExpressionValidator(
      QRegularExpression("^([8-9]|[1-4]\\d|50)$"), popupMenu));

  connect(fontSizeComboBox, SIGNAL(currentIndexChanged(int)),
          SLOT(onPopupComboBoxIndexChanged(int)));

  fontSizeLayout->addWidget(fontSizeLabel);
  fontSizeLayout->addWidget(fontSizeComboBox);

  fontSizeWidget->setLayout(fontSizeLayout);

  popupWidgetAction->setDefaultWidget(fontSizeWidget);

  popupMenu->addAction(copyAction);
  popupMenu->addAction(cutAction);
  popupMenu->addAction(pasteAction);
  popupMenu->addSeparator();
  popupMenu->addAction(selectAllAction);
  popupMenu->addSeparator();
  popupMenu->addAction(popupWidgetAction);
}

void MainWindow::onUnderlineTextFormat() {
  QTextCharFormat chFormat;
  if (textEdit->textCursor().hasSelection()) {
    if (!textEdit->textCursor().charFormat().fontUnderline())
      chFormat.setFontUnderline(true);
    else
      chFormat.setFontUnderline(false);
    textEdit->textCursor().mergeCharFormat(chFormat);
  }
}

void MainWindow::onBoldTextFormat() {

  std::optional<QTextCharFormat> charFormatStorage =
      getCurrentCharFormat(FontFeature::Bold);

  QTextCharFormat charFormat;

  if (charFormatStorage.has_value() &&
      charFormatStorage.value().fontWeight() == QFont::Bold)
    charFormat.setFontWeight(QFont::Normal);
  else
    charFormat.setFontWeight(QFont::Bold);

  if (textEdit->textCursor().hasSelection())
    textEdit->textCursor().mergeCharFormat(charFormat);
  else
    textEdit->mergeCurrentCharFormat(charFormat);
}

void MainWindow::onItalicTextFormat() {

  std::optional<QTextCharFormat> charFormatStorage =
      getCurrentCharFormat(FontFeature::Italic);

  QTextCharFormat charFormat;

  if (charFormatStorage.has_value() && charFormatStorage.value().fontItalic())
    charFormat.setFontItalic(false);
  else
    charFormat.setFontItalic(true);

  if (textEdit->textCursor().hasSelection())
    textEdit->textCursor().mergeCharFormat(charFormat);
  else
    textEdit->mergeCurrentCharFormat(charFormat);
}

void MainWindow::onSettingsInvoke() { settingsKeeper->exec(); }

void MainWindow::onSettingsApplyClicked() {
  retranslateGUI();
  onChangeStyle();
}

void MainWindow::onSettingsCancelClicked() { settingsKeeper->hide(); }

void MainWindow::onSettingsOkClicked() {
  onSettingsApplyClicked();
  onSettingsCancelClicked();
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

void MainWindow::onPopupMenuCalled(QPoint pos) {

  QTextCharFormat charFormat;
  QTextCursor formatsCheckCursor = textEdit->textCursor();
  bool formatsDiffer{false};

  if (textEdit->textCursor().selectionEnd() ==
      textEdit->textCursor().position()) {
    charFormat = textEdit->textCursor().charFormat();
    while (formatsCheckCursor.position() >
           textEdit->textCursor().selectionStart()) {
      if (charFormat != formatsCheckCursor.charFormat()) {
        formatsDiffer = true;
        break;
      }
      formatsCheckCursor.movePosition(QTextCursor::PreviousCharacter,
                                      QTextCursor::KeepAnchor);
    }
  } else {
    formatsCheckCursor.movePosition(QTextCursor::NextCharacter,
                                    QTextCursor::KeepAnchor);
    charFormat = formatsCheckCursor.charFormat();
    while (formatsCheckCursor.position() <
           textEdit->textCursor().selectionEnd()) {
      formatsCheckCursor.movePosition(QTextCursor::NextCharacter,
                                      QTextCursor::KeepAnchor);
      if (charFormat != formatsCheckCursor.charFormat()) {
        formatsDiffer = true;
        break;
      }
    }
  }

  fontSizeComboBox->setCurrentText(
      formatsDiffer ? "" : QString::number(charFormat.font().pointSize()));

  changePopupMenuAccess();
  popupMenu->exec(mapToGlobal(pos));
}

void MainWindow::onPopupComboBoxIndexChanged(int /* index */) {

  QTextCharFormat textCharFormat = textEdit->textCursor().charFormat();
  textCharFormat.setFontPointSize(fontSizeComboBox->currentText().toDouble());
  textEdit->textCursor().mergeCharFormat(textCharFormat);

  popupMenu->close();
}

void MainWindow::onCopy() { textEdit->copy(); }

void MainWindow::onCut() { textEdit->cut(); }

void MainWindow::onPaste() {
  if (textEdit->canPaste())
    textEdit->paste();
}

void MainWindow::onSelectAll() { textEdit->selectAll(); }
