#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "idevhandler.h"
#include <QDir>
#include <QFile>
#include <QWidget>

class FileHandler : public QWidget, public IDevHandler<QString>
{
    Q_OBJECT
  private:
    QString fileName;
    QString data;
    QDir tempDir;
    QFileInfo fileInfo;

    void createTempDir();
    void delTempDir();
    bool saveTha(const QString &);
    bool openTha();

  public:
    FileHandler(QWidget *parent = nullptr);

    virtual bool open() override;
    virtual void close() override;

    virtual bool save(const QString &) override;
    virtual bool saveAs(const QString &) override;

    virtual const QString &getSourceName() const override;
    virtual const QString &getData() const override;

    virtual ~FileHandler() override;
};

#endif // FILEHANDLER_H
