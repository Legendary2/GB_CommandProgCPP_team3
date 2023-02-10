#include <QtWidgets>
#include <QApplication>

class HelpBrowser : public QWidget
{
    Q_OBJECT

public:
    HelpBrowser(const QString &strPath,
                const QString &strFileName,
                QWidget *pwgt = 0) : QWidget(pwgt)
    {
    QPushButton *pressBack = new QPushButton("Back");
    QPushButton *pressForward = new QPushButton("Forward");
    QPushButton *pressHome = new QPushButton("Home");
    QTextBrowser *txtBrowser = new QTextBrowser;


    connect(pressBack, SIGNAL(clicked(bool)), txtBrowser, SLOT(backward()));
    connect(pressForward, SIGNAL(clicked(bool)), txtBrowser, SLOT(forward()));
    connect(pressHome, SIGNAL(clicked(bool)), txtBrowser, SLOT(home()));
    connect(txtBrowser, SIGNAL(backwardAvailable(bool)), pressBack, SLOT(setEnabled(bool)));
    connect(txtBrowser, SIGNAL(forwardAvailable(bool)), pressForward, SLOT(setEnabled(bool)));

    txtBrowser->setSearchPaths(QStringList() << strPath);
    txtBrowser->setSource(QString(strFileName));

    QVBoxLayout *vboxLayout = new QVBoxLayout;
    QHBoxLayout *hboxLayout = new QHBoxLayout;

    hboxLayout -> addWidget(pressBack);
    hboxLayout -> addWidget(pressForward);
    hboxLayout -> addWidget(pressHome);
    vboxLayout -> addLayout(hboxLayout);
    vboxLayout -> addWidget(txtBrowser);
    setLayout(vboxLayout);
    }

};
