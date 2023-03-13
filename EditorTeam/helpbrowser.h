#ifndef HELPBROWSER_H
#define HELPBROWSER_H

#include <QApplication>
#include <QtWidgets>

class HelpBrowser : public QWidget {
  Q_OBJECT

private:
  QHBoxLayout *hboxLayout;

  QPushButton *pressBack;
  QPushButton *pressForward;
  QPushButton *pressHome;

public:
  HelpBrowser(const QString &strPath, const QString &strFileName,
              QWidget *pwgt = 0);
  ~HelpBrowser();

  void retranslateGUI();
};

#endif // HELPBROWSER_H
