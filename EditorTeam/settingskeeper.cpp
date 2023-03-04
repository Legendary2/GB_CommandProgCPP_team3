#include "settingskeeper.h"
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>

void SettingsKeeper::save() {
  settings.setValue(LANG_STR, lang);
  settings.setValue(STYLE_STR, style);
}

void SettingsKeeper::load() {
  lang = settings.value(LANG_STR, RUS_LANG_STR).toString();
  style = settings.value(STYLE_STR, WHITE_STYLE_STR).toString();

  langComboBox->setCurrentText(lang);
  styleComboBox->setCurrentText(style);
}

void SettingsKeeper::setLangAndStyle() {
  lang = langComboBox->currentText();
  style = styleComboBox->currentText();
}

void SettingsKeeper::showEvent(QShowEvent *event) {
  langComboBox->setCurrentText(lang);
  styleComboBox->setCurrentText(style);

  QDialog::showEvent(event);
}

SettingsKeeper::SettingsKeeper(QWidget *parent)
    : QDialog(parent), settings(SETTINGS_STORAGE),
      langComboBox(new QComboBox(this)), styleComboBox(new QComboBox(this)),
      keyBindActionComboBox(new QComboBox(this)),
      keyBindModComboBox(new QComboBox(this)),
      keyBindKeyComboBox(new QComboBox(this)), langLabel(new QLabel(this)),
      styleLabel(new QLabel(this)), keyBindActionLabel(new QLabel(this)),
      keyBindModLabel(new QLabel(this)), keyBindKeyLabel(new QLabel(this)),
      okButton(
          new QPushButton(QIcon(okIconPath), OK_SETTINGS_BTN_PAIR.first, this)),
      applyButton(new QPushButton(QIcon(okIconPath),
                                  APPLY_SETTINGS_BTN_PAIR.first, this)),
      cancelButton(new QPushButton(QIcon(cancelIconPath),
                                   CANCEL_SETTINGS_BTN_PAIR.first, this)),
      formLayout(new QFormLayout), hboxLayout(new QHBoxLayout),
      keyBindsGroupBox(new QGroupBox(this)) {

  QVBoxLayout *mainLayout = new QVBoxLayout(this);

  langComboBox->addItem(QIcon(russiaIconPath), RUS_LANG_STR);
  langComboBox->addItem(QIcon(usaIconPath), ENG_LANG_STR);

  styleComboBox->addItem(QIcon(whiteStyleIconPath), WHITE_STYLE_STR);
  styleComboBox->addItem(QIcon(greyStyleIconPath), GRAY_STYLE_STR);

  load();

  formLayout->addRow(langLabel, langComboBox);
  formLayout->addRow(styleLabel, styleComboBox);

  connect(applyButton, &QPushButton::clicked, [&]() {
    setLangAndStyle();
    emit applyButtonClicked();
  });

  connect(cancelButton, &QPushButton::clicked,
          [&]() { emit cancelButtonClicked(); });

  connect(okButton, &QPushButton::clicked, [&]() {
    setLangAndStyle();
    emit okButtonClicked();
  });

  hboxLayout->addWidget(applyButton);
  hboxLayout->addWidget(cancelButton);
  hboxLayout->addWidget(okButton);

  QFormLayout *keyBindLayout = new QFormLayout(keyBindsGroupBox);

  keyBindLayout->addRow(keyBindActionLabel, keyBindActionComboBox);
  keyBindLayout->addRow(keyBindModLabel, keyBindModComboBox);
  keyBindLayout->addRow(keyBindKeyLabel, keyBindKeyComboBox);

  mainLayout->addLayout(formLayout);
  mainLayout->addWidget(keyBindsGroupBox);
  mainLayout->addLayout(hboxLayout);

  retranslateGUI();
}

SettingsKeeper::~SettingsKeeper() {
  save();
  delete hboxLayout;
  delete formLayout;
}

const QString &SettingsKeeper::getLang() const { return lang; }

const QString &SettingsKeeper::getStyle() const { return style; }

void SettingsKeeper::retranslateGUI() {
  langLabel->setText(LANG_STR);
  styleLabel->setText(STYLE_STR);

  keyBindsGroupBox->setTitle(KEYBINDS_GROUPBOX_STR); // to retranslateGUI

  keyBindActionLabel->setText(KEYBINDS_ACTION_LABEL_STR);
  keyBindModLabel->setText(KEYBINDS_MOD_LABEL_STR);
  keyBindKeyLabel->setText(KEYBINDS_KEY_LABEL_STR);

  okButton->setText(OK_SETTINGS_BTN_PAIR.first);
  okButton->setToolTip(OK_SETTINGS_BTN_PAIR.second);

  applyButton->setText(APPLY_SETTINGS_BTN_PAIR.first);
  applyButton->setToolTip(APPLY_SETTINGS_BTN_PAIR.second);

  cancelButton->setText(CANCEL_SETTINGS_BTN_PAIR.first);
  cancelButton->setToolTip(CANCEL_SETTINGS_BTN_PAIR.second);
}
