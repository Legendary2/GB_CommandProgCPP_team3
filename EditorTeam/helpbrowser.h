#ifndef HELPBROWSER_H
#define HELPBROWSER_H

#include <QApplication>
#include <QtWidgets>

class HelpBrowser : public QWidget {
  Q_OBJECT

private:
  QHBoxLayout *hboxLayout;

public:
  HelpBrowser(const QString &strPath, const QString &strFileName,
              QWidget *pwgt = 0);
  ~HelpBrowser();
};

#endif // HELPBROWSER_H
