#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "idevhandler.h"
#include <QFile>
#include <QWidget>

class FileHandler : public QWidget, public IDevHandler<QString> {
  Q_OBJECT
private:
  QString fileName;
  QString data;

public:
  FileHandler(QWidget *parent = nullptr);

  virtual bool open() override;
  virtual void close() override;

  virtual bool save(const QString &) override;
  virtual bool saveAs(const QString &) override;

  virtual const QString &getSourceName() const override;
  virtual const QString &getData() const override;

  virtual ~FileHandler() = default;
};

#endif // FILEHANDLER_H
