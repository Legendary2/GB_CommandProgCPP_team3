#include "searchform.h"
#include "const_strings.h"

SearchForm::SearchForm(QWidget *parent)
    : QDialog(parent)
    , hboxLayout(new QHBoxLayout)
{
    this->resize(400, 100);
    this->setWindowIcon(QIcon(searchTextIconPath));
    searchButton = new QPushButton(this);
    registerSearch = new QCheckBox(this);
    stringSearch = new QLineEdit(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    hboxLayout->addWidget(stringSearch);
    hboxLayout->addWidget(searchButton);
    mainLayout->addLayout(hboxLayout);
    mainLayout->addWidget(registerSearch);

    stringSearch->setFocus();

    connect(searchButton, &QPushButton::clicked, this,
            &SearchForm::onSearchClicked);

    retranslateGUI();
}

bool SearchForm::isСaseInsensitive()
{
    return registerSearch->isChecked() ? true : false;
}

void SearchForm::onSearchClicked()
{
    emit signalFromSearchText(stringSearch->text());
}

void SearchForm::clearForm()
{
    stringSearch->clear();
    registerSearch->setCheckState(Qt::Unchecked);
    stringSearch->setFocus();
}

void SearchForm::retranslateGUI()
{
    this->setWindowTitle(tr("Search text"));
    searchButton->setText(tr("Search"));
    registerSearch->setText(tr("case insensitive"));
}

SearchForm::~SearchForm() { delete hboxLayout; }
