#include "filehandler.h"
#include <QFileDialog>
#include <QMessageBox>

FileHandler::FileHandler(QWidget *parent) : QWidget{parent}, file{}, data{} {}

bool FileHandler::open() {

  QString fileName;
  fileName = QFileDialog::getOpenFileName(
      this, tr("Open Document"), QDir::currentPath(),
      tr("All files (*.*) ;; Plain text files (*.txt)"));
  if (fileName.isEmpty()) {
    return false;
  } else {
    if (file.isOpen()) {
      file.close();
    }
    file.setFileName(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
      // if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      //QMessageBox::warning(this, tr("Error"), tr("Open failed"));
      return false;
    } else {
      if (!file.isReadable()) {
        QMessageBox::warning(this, tr("Error"), tr("The file is not readable"));
        return false;
      } else {
        data = QTextStream(&file).readAll();
      }
    }
  }
  return true;
}

void FileHandler::close() {
  if (file.isOpen())
    file.close();
  file.setFileName("");
}

bool FileHandler::save(const QString &inputStr) {
  if (file.isOpen()) {
    // Проверим режим открытого файла на возможность записи,
    // если нет, то дадим эту возможность
    if (!(file.openMode() & QFile::WriteOnly)) {
      file.close();
      if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        return false;
      }
    }

    QTextStream stream(&file);
    stream.seek(0);
    stream << inputStr;

  } else
  // На случай, если никакой файл в textEdit не загружен,
  // но юзер хочет сохранить содержимое textEdit в файл,
  {
    saveAs(inputStr);
  }

  return true;
}

bool FileHandler::saveAs(const QString &inputStr) {
  QString filePath{QFileDialog::getSaveFileName(this, tr("Save file as "),
                                                QDir::current().path(),
                                                tr("Text file(*.txt)"))};

  if (filePath.length()) {
    if (file.isOpen())
      file.close();

    file.setFileName(filePath);
    if (file.open(QFile::WriteOnly)) {
      QTextStream stream(&file);

      stream << inputStr;

      return true;

    } else //! open
    {
      QMessageBox::warning(this, tr("Can't save file"),
                           tr("Cannot save file ") + filePath);
      return false;
    }
  }
  return false;
}

const QString &FileHandler::getData() const { return data; }

const QString FileHandler::getSourceName() const { return file.fileName(); }
