#include <QtWidgets>
#include <QTextBrowser>
#include <QBoxLayout>

class helpBrowser : public QWidget
{
    Q_OBJECT

public:
    helpBrowser(const QString &strPath,
                const QString &strFileName,
                QWidget *pwgt = 0) : QWidget(pwgt)
    {
    QPushButton *pressBack = new QPushButton("<<");
    QPushButton *pressForward = new QPushButton(">>");
    QTextBrowser *txtBrowser = new QTextBrowser;


    connect(pressBack, SIGNAL(clicked(bool)), txtBrowser, SLOT(backward()));
    connect(pressForward, SIGNAL(clicked(bool)), txtBrowser, SLOT(forward()));

    txtBrowser->setSearchPaths(QStringList() << strPath);
    txtBrowser->setSource(QString(strFileName));

    QVBoxLayout *vboxLayout = new QVBoxLayout;
    QHBoxLayout *hboxLayout = new QHBoxLayout;

    hboxLayout -> addWidget(pressBack);
    hboxLayout -> addWidget(pressForward);
    vboxLayout -> addLayout(hboxLayout);
    vboxLayout -> addWidget(txtBrowser);
    setLayout(vboxLayout);
    }
};
