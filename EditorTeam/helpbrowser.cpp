#include "helpbrowser.h"

HelpBrowser::HelpBrowser(const QString &strPath, const QString &strFileName,
                         QWidget *pwgt)
    : QWidget(pwgt), hboxLayout(new QHBoxLayout),
      pressBack(new QPushButton(this)), pressForward(new QPushButton(this)),
      pressHome(new QPushButton(this)) {
  QTextBrowser *txtBrowser = new QTextBrowser(this);
  connect(pressBack, SIGNAL(clicked(bool)), txtBrowser, SLOT(backward()));
  connect(pressForward, SIGNAL(clicked(bool)), txtBrowser, SLOT(forward()));
  connect(pressHome, SIGNAL(clicked(bool)), txtBrowser, SLOT(home()));
  connect(txtBrowser, SIGNAL(backwardAvailable(bool)), pressBack,
          SLOT(setEnabled(bool)));
  connect(txtBrowser, SIGNAL(forwardAvailable(bool)), pressForward,
          SLOT(setEnabled(bool)));

  txtBrowser->setSearchPaths(QStringList() << strPath);
  txtBrowser->setSource(QString(strFileName));

  QVBoxLayout *vboxLayout = new QVBoxLayout(this);

  hboxLayout->addWidget(pressBack);
  hboxLayout->addWidget(pressForward);
  hboxLayout->addWidget(pressHome);
  vboxLayout->addLayout(hboxLayout);
  vboxLayout->addWidget(txtBrowser);
  setLayout(vboxLayout);
}

HelpBrowser::~HelpBrowser() { delete hboxLayout; }

void HelpBrowser::retranslateGUI() {
  pressBack->setText(tr("Back"));
  pressForward->setText(tr("Forward"));
  pressHome->setText(tr("Home"));

  setWindowTitle(tr("Help"));
}
