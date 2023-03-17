#ifndef HELPBROWSER_H
#define HELPBROWSER_H

#include <QApplication>
#include <QtWidgets>

class HelpBrowser : public QWidget
{
    Q_OBJECT

  private:
    QHBoxLayout *hboxLayout;

    QPushButton *pressBack;
    QPushButton *pressForward;
    QPushButton *pressHome;
    QTextBrowser *txtBrowser;

  public:
    HelpBrowser(const QString &strPath, QWidget *pwgt = 0);
    ~HelpBrowser();

    void retranslateGUI();
    void setSource(QString &);
};

#endif // HELPBROWSER_H
