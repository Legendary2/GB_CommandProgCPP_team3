#include "filehandler.h"
#include <QFileDialog>
#include <QMessageBox>

FileHandler::FileHandler(QWidget *parent)
    : QWidget{parent}, fileName{}, data{} {}

bool FileHandler::open() {

  QFile file;
  QString filePath = QFileDialog::getOpenFileName(
      this, tr("Open Document"), QDir::currentPath(),
      tr("All files (*) ;; Plain text files (*.txt) ;;"
         " XML files (*.xml) ;; CPP files (*.cpp) ;; Header files (*.h "
         "*.hpp) ;; SHELL files (*.sh) ;; CONF files (*.conf) ;; INI files "
         "(*.ini)"));
  if (filePath.isEmpty()) {
    return false;
  } else {
    if (file.isOpen()) {
      file.close();
    }
    file.setFileName(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      return false;
    } else {
      if (!file.isReadable()) {
        QMessageBox::warning(this, tr("Error"), tr("The file is not readable"));
        return false;
      } else {
        data = QTextStream(&file).readAll();
      }
    }
    fileName = QFileInfo(filePath).fileName();
    file.close();
  }

  return true;
}

void FileHandler::close() { fileName = ""; }

bool FileHandler::save(const QString &inputStr) {
  if (fileName.isEmpty()) {
    saveAs(inputStr);
  } else {
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      return false;
    } else {
      QTextStream stream(&file);
      stream.seek(0);
      stream << inputStr;
      file.close();
    }
  }

  return true;
}

bool FileHandler::saveAs(const QString &inputStr) {
  QString filePath{QFileDialog::getSaveFileName(
      this, tr("Save file as "), QDir::current().path(),
      tr("All files (*) ;; Plain text files (*.txt) ;;"
         " XML files (*.xml) ;; CPP files (*.cpp) ;; Header files (*.h "
         "*.hpp) ;; SHELL files (*.sh) ;; CONF files (*.conf) ;; INI files "
         "(*.ini)"))};

  if (filePath.length()) {

    QFile file(filePath);
    if (file.open(QFile::WriteOnly)) {
      QTextStream stream(&file);

      stream << inputStr;

      fileName = QFileInfo(filePath).fileName();
      file.close();

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

const QString &FileHandler::getSourceName() const { return fileName; }
