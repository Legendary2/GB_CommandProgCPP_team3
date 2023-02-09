#ifndef HELPBROWSER_H
#define HELPBROWSER_H



//#include <QWidget>
#include <QtWidgets>
//#include <QPushButton>
//#include <QTextBrowser>
//#include <QBoxLayout>

namespace Ui {
class helpbrowser;
}

class helpbrowser : public QWidget
{
    Q_OBJECT

public:
    explicit helpbrowser(QWidget *parent = nullptr);
    ~helpbrowser();

    helpbrowser(const QString &strPath,
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


private:
    Ui::helpbrowser *ui;
};

#endif // HELPBROWSER_H
