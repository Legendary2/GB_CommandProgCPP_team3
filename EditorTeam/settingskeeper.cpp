#include "settingskeeper.h"
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>

void SettingsKeeper::save()
{
    settings.setValue(LANG_STR, lang);
    settings.setValue(STYLE_STR, style);
}

void SettingsKeeper::load()
{
    lang = settings.value(LANG_STR, RUS_LANG_STR).toString();
    style = settings.value(STYLE_STR, 0).toInt();

    langComboBox->setCurrentText(lang);
    styleComboBox->setCurrentIndex(style);
}

void SettingsKeeper::setLangAndStyle()
{
    lang = langComboBox->currentText();
    style = styleComboBox->currentIndex();
}

void SettingsKeeper::showEvent(QShowEvent *event)
{
    langComboBox->setCurrentText(lang);
    styleComboBox->setCurrentIndex(style);

    QDialog::showEvent(event);
}

SettingsKeeper::SettingsKeeper(QWidget *parent)
    : QDialog(parent)
    , settings(SETTINGS_STORAGE)
    , langComboBox(new QComboBox(this))
    , styleComboBox(new QComboBox(this))
    , langLabel(new QLabel(this))
    , styleLabel(new QLabel(this))
    , okButton(new QPushButton(QIcon(okIconPath), NULL, this))
    , applyButton(new QPushButton(NULL, this))
    , cancelButton(new QPushButton(QIcon(cancelIconPath), NULL, this))
    , formLayout(new QFormLayout)
    , hboxLayout(new QHBoxLayout)
{

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    langComboBox->addItem(QIcon(russiaIconPath), RUS_LANG_STR);
    langComboBox->addItem(QIcon(usaIconPath), ENG_LANG_STR);

    styleComboBox->addItem(QIcon(whiteStyleIconPath), NULL);
    styleComboBox->addItem(QIcon(greyStyleIconPath), NULL);

    load();

    formLayout->addRow(langLabel, langComboBox);
    formLayout->addRow(styleLabel, styleComboBox);

    connect(applyButton, &QPushButton::clicked,
            [&]()
            {
                setLangAndStyle();
                emit applyButtonClicked();
            });

    connect(cancelButton, &QPushButton::clicked,
            [&]() { emit cancelButtonClicked(); });

    connect(okButton, &QPushButton::clicked,
            [&]()
            {
                setLangAndStyle();
                emit okButtonClicked();
            });

    hboxLayout->addWidget(applyButton);
    hboxLayout->addWidget(cancelButton);
    hboxLayout->addWidget(okButton);

    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(hboxLayout);
}

SettingsKeeper::~SettingsKeeper()
{
    save();
    delete hboxLayout;
    delete formLayout;
}

const QString &SettingsKeeper::getLang() const { return lang; }

const int SettingsKeeper::getStyle() const { return style; }

void SettingsKeeper::retranslateGUI()
{
    langLabel->setText(tr("Language"));
    styleLabel->setText(tr("Style"));

    styleComboBox->setItemText(0, tr("Light theme"));
    styleComboBox->setItemText(1, tr("Dark theme"));

    okButton->setText(tr("OK"));
    okButton->setToolTip(tr("Apply changes and close dialog"));

    applyButton->setText(tr("Apply"));
    applyButton->setToolTip(tr("Apply changes"));

    cancelButton->setText(tr("Cancel"));
    cancelButton->setToolTip(tr("Discard changes and close dialog"));

    setWindowTitle(tr("Settings management"));
}
