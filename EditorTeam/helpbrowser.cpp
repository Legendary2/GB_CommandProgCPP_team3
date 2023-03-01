#include "helpbrowser.h"

HelpBrowser::HelpBrowser(const QString &strPath, const QString &strFileName,
                         QWidget *pwgt)
    : QWidget(pwgt) {
  QPushButton *pressBack = new QPushButton("Back", this);
  QPushButton *pressForward = new QPushButton("Forward", this);
  QPushButton *pressHome = new QPushButton("Home", this);
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
  QHBoxLayout *hboxLayout = new QHBoxLayout(this);

  hboxLayout->addWidget(pressBack);
  hboxLayout->addWidget(pressForward);
  hboxLayout->addWidget(pressHome);
  vboxLayout->addLayout(hboxLayout);
  vboxLayout->addWidget(txtBrowser);
  setLayout(vboxLayout);
}
