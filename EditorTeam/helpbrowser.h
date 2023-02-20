#ifndef HELPBROWSER_H
#define HELPBROWSER_H

#include <QApplication>
#include <QtWidgets>

class HelpBrowser : public QWidget {
  Q_OBJECT

public:
  HelpBrowser(const QString &strPath, const QString &strFileName,
              QWidget *pwgt = 0);
};

#endif // HELPBROWSER_H
