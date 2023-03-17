#include "helpbrowser.h"

HelpBrowser::HelpBrowser(const QString &strPath, QWidget *pwgt)
    : QWidget(pwgt)
    , hboxLayout(new QHBoxLayout)
    , pressBack(new QPushButton(this))
    , pressForward(new QPushButton(this))
    , pressHome(new QPushButton(this))
{
    txtBrowser = new QTextBrowser(this);
    connect(pressBack, SIGNAL(clicked(bool)), txtBrowser, SLOT(backward()));
    connect(pressForward, SIGNAL(clicked(bool)), txtBrowser, SLOT(forward()));
    connect(pressHome, SIGNAL(clicked(bool)), txtBrowser, SLOT(home()));
    connect(txtBrowser, SIGNAL(backwardAvailable(bool)), pressBack,
            SLOT(setEnabled(bool)));
    connect(txtBrowser, SIGNAL(forwardAvailable(bool)), pressForward,
            SLOT(setEnabled(bool)));

    txtBrowser->setSearchPaths(QStringList() << strPath);

    QVBoxLayout *vboxLayout = new QVBoxLayout(this);

    hboxLayout->addWidget(pressBack);
    hboxLayout->addWidget(pressForward);
    hboxLayout->addWidget(pressHome);
    vboxLayout->addLayout(hboxLayout);
    vboxLayout->addWidget(txtBrowser);
    setLayout(vboxLayout);
    setWindowIcon(QIcon(":/images/icon_64.png"));
}

HelpBrowser::~HelpBrowser() { delete hboxLayout; }

void HelpBrowser::retranslateGUI()
{
    pressBack->setText(tr("Back"));
    pressForward->setText(tr("Forward"));
    pressHome->setText(tr("Home"));

    setWindowTitle(tr("Help"));
}

void HelpBrowser::setSource(QString &source)
{
    txtBrowser->setSource(QString(source));
}
