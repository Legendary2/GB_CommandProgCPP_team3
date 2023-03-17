#include "mainwindow.h"
#include "searchform.h"
#include "ui_mainwindow.h"
#include <QBoxLayout>
#include <QColorDialog>
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
      searchForm(new SearchForm(this)), translator(new QTranslator(this)),
      standardTranslator(new QTranslator(this)), popupMenu(new QMenu(this)) {
  ui->setupUi(this);

  // Заполнение главного меню
  createActions();
  createMenus();

  // Функция настроек и заполнения тулбара
  setMainToolBar();

  onSettingsApplyClicked();

  // Добавление поля для размещения редактируемого текста
  textEdit = new QTextEdit(this);

  QFont qf;
  qf.setPointSize(DEFAULT_FONT_SIZE);
  qf.setFamily(DEFAULT_FONT_FAMILY);
  textEdit->setFont(qf);

  boxLayout->addWidget(textEdit, 0);
  ui->centralwidget->setLayout(boxLayout);
  /*! KuznecovAG
  При сигнале от searchForm о нажатии кнопки вызывается слот
  onSearchFormButtonClicked*/
  connect(searchForm, &SearchForm::signalFromSearchText, this,
          &MainWindow::onSearchFormButtonClicked);

  /*! KuznecovAG
      При сигнале от searchForm о нажатии кнопки вызывается слот
      onSearchFormButtonClicked*/
  connect(searchForm, &SearchForm::signalFromSearchText, this,
          &MainWindow::onSearchFormButtonClicked);

  /*! GubaydullinRG
  Привязка события изменения содержимого textEdit к вызову
  слота onTextModified() */
  connect(textEdit, SIGNAL(textChanged()), this, SLOT(onTextModified()));

  connect(textEdit, &QTextEdit::selectionChanged, this,
          &MainWindow::onSelectionChanged);
  connect(textEdit, &QTextEdit::cursorPositionChanged, this,
          &MainWindow::onSelectionChanged);

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

  searchTextAction->setEnabled(false);

  searchHighLight = new SearchHighLight(textEdit->document());

  connect(textEdit, &QTextEdit::cursorPositionChanged, this,
          &MainWindow::clearHighLight);
  this->resize(860, 600);
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
  // LyashenkoAN---------------------------------------------------------
  // File open read
  createAction(&openForRead, openReadOnly, &MainWindow::openFileToRead);
  //--------------------------------------------------------------------
  createAction(&closeAction, closeIconPath, &MainWindow::onClose);
  createAction(&saveAction, saveIconPath, &MainWindow::onSave);
  createAction(&saveAsAction, saveAsIconPath, &MainWindow::onSaveAs);
  createAction(&savePdfAction, savePdfIcon,
               &MainWindow::onSavePdf); // Add LyashenkoAN
  createAction(&printAction, printIconPath, &MainWindow::onPrint);
  createAction(&exitAction, exitIconPath, &MainWindow::onExit);

  // 'Edit'
  createAction(&searchTextAction, searchTextIconPath,
               &MainWindow::onSearchText);
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
  createAction(&highlightTextFormatAction, highlightStyleIconPath,
               &MainWindow::onHighlightTextFormat);
  createAction(&textColorFormatAction, textColorFormatIconPath,
               &MainWindow::onTextColorFormat);

  // 'Settings'
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
  openAction->setShortcut(QKeySequence("CTRL+O"));
  fileMenu->addAction(openForRead);
  openForRead->setShortcut(QKeySequence("CTRL+R"));
  openAction->setShortcut(QKeySequence("CTRL+O"));
  fileMenu->addAction(openForRead);
  openForRead->setShortcut(QKeySequence("CTRL+R"));
  fileMenu->addAction(closeAction);
  closeAction->setShortcut(QKeySequence("ESC"));
  closeAction->setShortcut(QKeySequence("ESC"));
  closeAction->setEnabled(false); // На старте нам нечего закрывать
  fileMenu->addSeparator();
  fileMenu->addAction(saveAction);
  saveAction->setShortcut(QKeySequence("CTRL+S"));
  saveAction->setShortcut(QKeySequence("CTRL+S"));
  saveAction->setEnabled(false); // На старте нам некуда сохранять
  fileMenu->addAction(saveAsAction);
  saveAsAction->setShortcut(QKeySequence("CTRL+S"));
  //-----------------------------------
  fileMenu->addAction(savePdfAction); // Add LyashenkoAN
  savePdfAction->setShortcut(QKeySequence("CTRL+T"));
  //-----------------------------------
  fileMenu->addSeparator();
  fileMenu->addAction(printAction);
  printAction->setShortcut(QKeySequence("CTRL+P"));
  fileMenu->addSeparator();
  fileMenu->addAction(exitAction);
  exitAction->setShortcut(QKeySequence("CTRL+Q"));
  exitAction->setShortcut(QKeySequence("CTRL+Q"));

  // 'Edit'
  editMenu = new QMenu(this);
  menuBar()->addMenu(editMenu);
  editMenu->addAction(searchTextAction);
  searchTextAction->setShortcut(QKeySequence("CTRL+F"));
  editMenu->addSeparator();
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
  formatMenu->addAction(highlightTextFormatAction);
  formatMenu->addAction(textColorFormatAction);

  // 'Settings'
  settingsMenu = new QMenu(this);
  menuBar()->addMenu(settingsMenu);
  settingsMenu->addSeparator();
  settingsMenu->addAction(settingsAction);

  // '?'
  questionMenu = new QMenu(this);
  menuBar()->addMenu(questionMenu);
  questionMenu->addAction(helpAction);
  helpAction->setShortcut(QKeySequence("F1"));
  helpAction->setShortcut(QKeySequence("F1"));
  questionMenu->addSeparator();
  questionMenu->addAction(aboutAction);
  aboutAction->setShortcut(QKeySequence("F11"));
  aboutAction->setShortcut(QKeySequence("F11"));

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
  retranslateAction(&openForRead, OPEN_FILE_READ_ACTION_STR_PAIR);
  retranslateAction(&openForRead, OPEN_FILE_READ_ACTION_STR_PAIR);
  retranslateAction(&closeAction, CLOSE_ACTION_STR_PAIR);
  retranslateAction(&saveAction, SAVE_ACTION_STR_PAIR);
  retranslateAction(&saveAsAction, SAVEAS_ACTION_STR_PAIR);
  retranslateAction(&savePdfAction, SAVE_AS_PDF_ACTION_STR_PAIR);
  retranslateAction(&savePdfAction, SAVE_AS_PDF_ACTION_STR_PAIR);
  retranslateAction(&printAction, PRINT_ACTION_STR_PAIR);
  retranslateAction(&exitAction, EXIT_ACTION_STR_PAIR);

  // 'Edit'
  retranslateAction(&searchTextAction, SEARCH_TEXT_ACTION_STR_PAIR);
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
  retranslateAction(&highlightTextFormatAction,
                    HIGHLIGHT_TEXT_FORMAT_ACTION_STR_PAIR);
  retranslateAction(&textColorFormatAction, TEXT_COLOR_FORMAT_ACTION_STR_PAIR);

  // 'Settings'
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

  QPair<QString, QString> translatorPair = LANGS_MAP[settingsKeeper->getLang()];

  std::ignore = translator->load(translatorPair.first);
  std::ignore =
      standardTranslator->load(translatorPair.second, ":/translation");

  QApplication::installTranslator(translator);
  QApplication::installTranslator(standardTranslator);

  retranslateMenus();
  retranslateActions();

  if (titleHasCertainString(true))
    setWindowTitle(QString(tr(NEW_DOC_STR)));
  if (titleHasCertainString(false))
    setWindowTitle(QString(tr(NO_FILE_OPENED_STR)));

  settingsKeeper->retranslateGUI();
  hb->retranslateGUI();
  searchForm->retranslateGUI();
}

bool MainWindow::titleHasCertainString(bool newDoc) const {

  QString currentWindowTitle = windowTitle();

  const char *inputStr = newDoc ? NEW_DOC_STR : NO_FILE_OPENED_STR;

  QTranslator localRUTranslator;
  if (!localRUTranslator.load(LANGS_MAP[RUS_LANG_STR].first))
    return false;
  QString testStrRU = localRUTranslator.translate("MainWindow", inputStr);

  QTranslator localENTranslator;
  if (!localENTranslator.load(LANGS_MAP[ENG_LANG_STR].first))
    return false;
  QString testStrEN = localENTranslator.translate("MainWindow", inputStr);

  return (currentWindowTitle == testStrRU || currentWindowTitle == testStrEN);
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
  } else {
    selectAllAction->setEnabled(true);
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
    return charFormatFirst.font().family() == charFormatSecond.font().family();
  case FontFeature::Italic:
    return charFormatFirst.fontItalic() == charFormatSecond.fontItalic();
  case FontFeature::Underlined:
    return charFormatFirst.fontUnderline() == charFormatSecond.fontUnderline();
  case FontFeature::Size:
    return charFormatFirst.fontPointSize() == charFormatSecond.fontPointSize();
  case FontFeature::Highlight:
    return charFormatFirst.background().color() ==
           charFormatSecond.background().color();
  case FontFeature::ColoredText:
    return charFormatFirst.foreground().color() ==
           charFormatSecond.foreground().color();

  default:
    return false;
  }

  return false;
}

void MainWindow::onSave() {
  if (srcHandler->save(textEdit->toHtml())) {
    isTextModified = false;

    ui->statusbar->showMessage(srcHandler->getSourceName() + " " +
                               tr("has been saved."));
    saveAction->setEnabled(false);
    setWindowTitle(srcHandler->getSourceName());
  } else
    ui->statusbar->showMessage(tr("Can't save file."));
}

void MainWindow::onSaveAs() {
  if (srcHandler->saveAs(textEdit->toHtml())) {
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
  QFont font =
      QFontDialog::getFont(&ok, textEdit->currentFont(), this,
                           tr("Change font"), QFontDialog::DontUseNativeDialog);
  if (ok) {
    QTextCharFormat charFormat;
    charFormat.setFont(font);

    if (textEdit->textCursor().hasSelection())
      textEdit->textCursor().mergeCharFormat(charFormat);
    else
      textEdit->mergeCurrentCharFormat(charFormat);
  }
}

void MainWindow::onChangeStyle() {
  QFile qss(STYLES_MAP[settingsKeeper->getStyle()]);
  if (!qss.open(QIODevice::ReadOnly))
    return;

  qApp->setStyleSheet(qss.readAll());
  qss.close();
}

void MainWindow::onNew() {
  textEdit->setReadOnly(false);
  onClose();
  changeFileMenuAccess(tr(NEW_DOC_STR), false, true, false);
  saveAction->setEnabled(false);
  isTextModified = false;
  newDataLoaded = true;
  copyTextFormatAction->setEnabled(true);
}

void MainWindow::onOpen() {
  textEdit->setReadOnly(false);
  if (isTextModified) {
    if (textChangedWarning()) {
      onSave();
    }
  }

  if (srcHandler->open()) {
    newDataLoaded = true;
    changeFileMenuAccess(srcHandler->getSourceName(), false, true, true);
    QFileInfo qfi(srcHandler->getSourceName());
    if (qfi.suffix() == "tha") {
      textEdit->setHtml(srcHandler->getData());
    } else {
      textEdit->setPlainText(srcHandler->getData());
    }
    saveAction->setEnabled(false);
    isTextModified = false;
    copyTextFormatAction->setEnabled(true);
  }
}

void MainWindow::onClose() {
  textEdit->setReadOnly(false);
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
  searchTextAction->setEnabled(false);
}

void MainWindow::onHelp() {
  hb->resize(700, 600);
  hb->show();
}

void MainWindow::onAbout() {
  QMessageBox msgBox;
  msgBox.setWindowTitle(tr("About THare"));
  msgBox.setIconPixmap(appIconPath);
  msgBox.setInformativeText(tr("THare v 1.0.0 \n\n"
                               "Command N 3\n\n"
                               "© 2023 All rights reserved.\n\n"));
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
        setWindowTitle(QString(tr(NEW_DOC_STR)));
    } else {
      saveAction->setEnabled(true);
      setWindowTitle(srcName.append("*"));
    }
    closeAction->setEnabled(true);
    isTextModified = true;
  }
  newDataLoaded = false;

  textEdit->document()->characterCount() > 1
      ? searchTextAction->setEnabled(true)
      : searchTextAction->setEnabled(false);
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
  std::optional<QTextCharFormat> charFormatStorage =
      getCurrentCharFormat(FontFeature::Crossed);

  QTextCharFormat charFormat;

  if (charFormatStorage.has_value() &&
      charFormatStorage.value().fontStrikeOut())
    charFormat.setFontStrikeOut(false);
  else
    charFormat.setFontStrikeOut(true);

  if (textEdit->textCursor().hasSelection())
    textEdit->textCursor().mergeCharFormat(charFormat);
  else
    textEdit->mergeCurrentCharFormat(charFormat);
}

void MainWindow::inflatePopupMenu() {
  textEdit->setContextMenuPolicy(Qt::CustomContextMenu);

  connect(textEdit, SIGNAL(customContextMenuRequested(QPoint)), this,
          SLOT(onPopupMenuCalled(QPoint)));

  popupMenu->addAction(copyAction);
  popupMenu->addAction(cutAction);
  popupMenu->addAction(pasteAction);
  popupMenu->addSeparator();
  popupMenu->addAction(selectAllAction);
}

void MainWindow::onUnderlineTextFormat() {
  std::optional<QTextCharFormat> charFormatStorage =
      getCurrentCharFormat(FontFeature::Underlined);
  QTextCharFormat charFormat;

  if (charFormatStorage.has_value() &&
      charFormatStorage.value().fontUnderline())
    charFormat.setFontUnderline(false);
  else
    charFormat.setFontUnderline(true);

  if (textEdit->textCursor().hasSelection())
    textEdit->textCursor().mergeCharFormat(charFormat);
  else
    textEdit->mergeCurrentCharFormat(charFormat);
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

void MainWindow::onHighlightTextFormat() {
  QTextCharFormat charFormat;
  QColor color;
  QBrush hlBrush = Qt::white;

  // Проверяем направление выделения и отличия в цвете
  std::optional<QTextCharFormat> charFormatStorage =
      getCurrentCharFormat(FontFeature::Highlight);

  if (charFormatStorage.has_value())
    color = charFormatStorage->background().color();
  else
    hlBrush = Qt::black;

  // Определяем цвет кисти для палитры диалога
  if (textEdit->textCursor().hasSelection()) {
    if (hlBrush == Qt::black)
      hlBrush = Qt::white;
    else {
      if (color == Qt::black)
        color = Qt::white;

      hlBrush = color;
    }
  } else {
    hlBrush = textEdit->textCursor().charFormat().background().color();
  }

  QColor chosenColor =
      QColorDialog::getColor(hlBrush.color(), this, tr("Highlight text format"),
                             QColorDialog::DontUseNativeDialog);
  // Если цвет выбран, то красим фон текст
  if (chosenColor.isValid()) {
    charFormat.setBackground(chosenColor);
    if (textEdit->textCursor().hasSelection())
      textEdit->textCursor().mergeCharFormat(charFormat);
    else
      textEdit->mergeCurrentCharFormat(charFormat);
  }
}

void MainWindow::onTextColorFormat() {
  QTextCharFormat charFormat;
  QColor color;
  QBrush brush = Qt::black; // Кисть для цвета текста

  // Проверяем направление выделения и отличия в цвете
  std::optional<QTextCharFormat> charFormatStorage =
      getCurrentCharFormat(FontFeature::ColoredText);

  if (charFormatStorage.has_value()) {
    color = charFormatStorage->foreground().color();
  } else {
    brush = Qt::white;
  }

  // Определяем цвет кисти для палитры диалога
  if (textEdit->textCursor().hasSelection()) {
    if (brush != Qt::white)
      brush = color;
  } else {
    brush = textEdit->textCursor().charFormat().foreground();
  }

  QColor chosenColor =
      QColorDialog::getColor(brush.color(), this, tr("Change text color"),
                             QColorDialog::DontUseNativeDialog);
  // Если цвет выбран, то красим текст
  if (chosenColor.isValid()) {
    charFormat.setForeground(chosenColor);
    if (textEdit->textCursor().hasSelection())
      textEdit->textCursor().mergeCharFormat(charFormat);
    else
      textEdit->mergeCurrentCharFormat(charFormat);
  }
}

void MainWindow::setMainToolBar() // Установка настроек и иконок тулбара
{
  /* Создаем ComboBox для изменения размера шрифта */
  fontSizeComboBox = new QComboBox(this);
  fontSizeComboBox->setEditable(true);
  fontSizeComboBox->setValidator(new QIntValidator(
      MIN_VALUE_VALIDATOR_FONTS_SIZE, MAX_VALUE_VALIDATOR_FONTS_SIZE, this));
  fontSizeComboBox->view()->setAutoScroll(true);
  for (int i = MIN_VALUE_FONTS_SIZE; i <= MAX_VALUE_FONTS_SIZE;
       i += STEP_FONT_SIZE) {
    fontSizeComboBox->addItem(QString::number(i));
  }
  fontSizeComboBox->setCurrentText(QString::number(DEFAULT_FONT_SIZE));
  fontSizeComboBox->setCurrentIndex(
      fontSizeComboBox->findText(QString::number(DEFAULT_FONT_SIZE)));
  connect(fontSizeComboBox, SIGNAL(currentIndexChanged(int)),
          SLOT(onfontSizeComboBoxChanged(int)));

  /* Создаем ComboBox для изменения шрифта */
  fontFamiliesComboBox = new QComboBox(this);
  fontFamiliesComboBox->setEditable(true);
  fontFamiliesComboBox->lineEdit()->setReadOnly(true);
  fontFamiliesComboBox->view()->setAutoScroll(true);
  auto qsl = QFontDatabase::families();
  for (auto i = 0; i < qsl.size(); i++) {
    fontFamiliesComboBox->addItem(qsl[i]);
  }
  fontFamiliesComboBox->setCurrentText(DEFAULT_FONT_FAMILY);
  fontFamiliesComboBox->setCurrentIndex(
      fontFamiliesComboBox->findText(DEFAULT_FONT_FAMILY));
  connect(fontFamiliesComboBox, SIGNAL(currentIndexChanged(int)),
          SLOT(onfontFamiliesComboBoxChanged(int)));

  /* Создаем ToolBar */
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
  mainToolBar->addSeparator();
  mainToolBar->addWidget(fontFamiliesComboBox);
  mainToolBar->addWidget(fontSizeComboBox);
  mainToolBar->addAction(boldTextFormatAction);
  mainToolBar->addAction(italicTextFormatAction);
  mainToolBar->addAction(underlineTextFormatAction);
  mainToolBar->addAction(crossedTextFormatAction);
  mainToolBar->addSeparator();
  mainToolBar->addAction(textColorFormatAction);
  mainToolBar->addAction(highlightTextFormatAction);
}

void MainWindow::onPopupMenuCalled(QPoint pos) {
  changePopupMenuAccess();
  popupMenu->exec(mapToGlobal(pos));
}

void MainWindow::onfontSizeComboBoxChanged(int /* index */) {
  QTextCharFormat textCharFormat;
  textCharFormat.setFontPointSize(fontSizeComboBox->currentText().toDouble());
  textEdit->textCursor().mergeCharFormat(textCharFormat);
  if (!(textEdit->textCursor().hasSelection())) {
    textEdit->setFontPointSize(fontSizeComboBox->currentText().toDouble());
  }
}

void MainWindow::onfontFamiliesComboBoxChanged(int /* index */) {
  QTextCharFormat textCharFormat;
  QStringList temp;
  temp.append(fontFamiliesComboBox->currentText());

  textCharFormat.setFontFamilies(temp);
  textEdit->textCursor().mergeCharFormat(textCharFormat);
  if (!(textEdit->textCursor().hasSelection())) {
    textEdit->setFontFamily(fontFamiliesComboBox->currentText());
  }
}

void MainWindow::onCopy() { textEdit->copy(); }

void MainWindow::onCut() { textEdit->cut(); }

void MainWindow::onPaste() {
  if (textEdit->canPaste())
    textEdit->paste();
}

void MainWindow::onSelectAll() { textEdit->selectAll(); }

void MainWindow::onSearchText() { searchForm->exec(); }

void MainWindow::clearHighLight() {
  textEdit->blockSignals(true);
  ui->statusbar->clearMessage();
  searchHighLight->clearText();
  textEdit->blockSignals(false);
}

void MainWindow::onSearchFormButtonClicked(QString searchString) {
  textEdit->blockSignals(true);
  searchHighLight->searchText(searchString, searchForm->isСaseInsensitive());
  searchForm->reject();
  searchForm->clearForm();

  if (!searchHighLight->coutResult()) {
    ui->statusbar->showMessage(tr("No matches found"));
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(searchTextIconPath));
    msgBox.setWindowTitle(tr("Results"));
    msgBox.setInformativeText(tr("No matches found"));
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
  } else {
    QString qs =
        QString::number(searchHighLight->coutResult()) + tr(" matches found");
    ui->statusbar->showMessage(qs);
  }
  textEdit->blockSignals(false);
}

void MainWindow::onSelectionChanged() {
  std::optional<QTextCharFormat> charFormatStorage =
      getCurrentCharFormat(FontFeature::Size);

  if (charFormatStorage.has_value()) {
    QFont qf = charFormatStorage->font();
    fontSizeComboBox->setCurrentText(QString::number(qf.pointSize()));
    fontSizeComboBox->setCurrentIndex(
        fontSizeComboBox->findText(QString::number(qf.pointSize())));
  } else {
    fontSizeComboBox->setCurrentText("");
  }

  charFormatStorage = getCurrentCharFormat(FontFeature::FontFamily);

  if (charFormatStorage.has_value()) {
    QFont qf = charFormatStorage->font();
    fontFamiliesComboBox->setCurrentText(qf.family());
    fontFamiliesComboBox->setCurrentIndex(
        fontFamiliesComboBox->findText(qf.family()));
  } else {
    fontFamiliesComboBox->setCurrentText("");
  }

  if (textEdit->document()->characterCount() <= 1) {
    fontSizeComboBox->setCurrentText(QString::number(DEFAULT_FONT_SIZE));
    fontSizeComboBox->setCurrentIndex(
        fontSizeComboBox->findText(QString::number(DEFAULT_FONT_SIZE)));

    fontFamiliesComboBox->setCurrentText(DEFAULT_FONT_FAMILY);
    fontFamiliesComboBox->setCurrentIndex(
        fontFamiliesComboBox->findText(DEFAULT_FONT_FAMILY));

    QFont qf;
    qf.setPointSize(DEFAULT_FONT_SIZE);
    qf.setFamily(DEFAULT_FONT_FAMILY);
    textEdit->setFont(qf);
  }
}

void MainWindow::openFileToRead() {

  onClose();
  changeFileMenuAccess(tr(NEW_DOC_STR), false, true, false);
  saveAction->setEnabled(false);
  isTextModified = false;
  newDataLoaded = true;
  copyTextFormatAction->setEnabled(true);

  QFile file;
  file.setFileName(QFileDialog::getOpenFileName(0, "Открыть", "", "*.txt"));
  if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {
    textEdit->setText(file.readAll());
    textEdit->setReadOnly(true);
    file.close();
    closeAction->setEnabled(true);
  }
}

void MainWindow::onSavePdf() // запись содержимого экрана в ПДФ
{

  QTextDocument doc;
  doc.setHtml(textEdit->toHtml());

  QPdfWriter pdfWriter(
      QFileDialog::getSaveFileName(this, tr("Save *.pdf"), "", "*.pdf"));

  QPainter painter(&pdfWriter);
  painter.scale(20.0, 20.0); // Под А4.
  doc.drawContents(&painter);
}

void MainWindow::closeEvent(QCloseEvent *event) {
  event->accept();
  qApp->quit();
}
