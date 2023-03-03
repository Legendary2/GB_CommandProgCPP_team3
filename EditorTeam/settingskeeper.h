#ifndef SETTINGSKEEPER_H
#define SETTINGSKEEPER_H

#include "const_strings.h"
#include <QComboBox>
#include <QDialog>
#include <QFormLayout> //
#include <QLabel>
#include <QPushButton>
#include <QSettings>

class SettingsKeeper : public QDialog {
  Q_OBJECT

public:
  explicit SettingsKeeper(QWidget *parent = nullptr);
  ~SettingsKeeper();

  const QString &getLang() const;
  const QString &getStyle() const;

  void retranslateGUI();

private:
  QString lang;
  QString style;

  QSettings settings;

  void save();
  void load();

  void setLangAndStyle();

  QComboBox *langComboBox;
  QComboBox *styleComboBox;

  QLabel *langLabel;
  QLabel *styleLabel;

  QPushButton *okButton;
  QPushButton *applyButton;
  QPushButton *cancelButton;

  virtual void showEvent(QShowEvent *) override;

  QFormLayout *formLayout; //
  QHBoxLayout *hboxLayout;

signals:
  void applyButtonClicked();
  void cancelButtonClicked();
  void okButtonClicked();
};

#endif // SETTINGSKEEPER_H
