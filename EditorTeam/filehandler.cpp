#include "filehandler.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QTextDocumentFragment>

FileHandler::FileHandler(QWidget *parent)
    : QWidget{parent}
    , fileName{}
    , data{}
    , fileInfo{}
{
    createTempDir();
}

FileHandler::~FileHandler() { delTempDir(); }

void FileHandler::createTempDir()
{
    QDir qd;
    qd.setPath(QDir::tempPath());
    qd.mkdir(".thare");
    qd.cd(".thare");
    tempDir = qd.absolutePath();
    qd.removeRecursively();
    qd.mkdir(tempDir.absolutePath());
    qd.setPath(tempDir.absolutePath());
    qd.mkdir("images");
}

void FileHandler::delTempDir()
{
    QDir qd;
    qd.setPath(tempDir.absolutePath());
    qd.removeRecursively();
}

bool FileHandler::open()
{

    QFile file;
    QString filePath = QFileDialog::getOpenFileName(
        this, tr("Open Document"), QDir::currentPath(),
        tr("All files (*) ;; THare files (*.tha) ;;"
           " Plain text files (*.txt)"));
    if (filePath.isEmpty())
    {
        return false;
    }
    else
    {
        if (file.isOpen())
        {
            file.close();
        }
        file.setFileName(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return false;
        }
        else
        {
            fileInfo.setFile(file);
            if (!file.isReadable())
            {
                QMessageBox::warning(this, tr("Error"),
                                     tr("The file is not readable"));
                return false;
            }
            else
            {
                if (fileInfo.suffix() == "tha")
                {
                    openTha();
                }
                else
                {
                    data = QTextStream(&file).readAll();
                }
            }
        }
        fileName = QFileInfo(filePath).fileName();
        fileInfo.setFile(filePath);
        file.close();
    }

    return true;
}

void FileHandler::close()
{
    createTempDir();
    fileName = "";
    fileInfo.setFile("");
}

bool FileHandler::save(const QString &inputStr)
{
    if (fileName.isEmpty())
    {
        saveAs(inputStr);
    }
    else
    {
        QFile file(fileInfo.absoluteFilePath());

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return false;
        }
        else
        {
            if (fileInfo.suffix() == "tha")
            {
                file.close();
                saveTha(inputStr);
            }
            else
            {
                QTextDocumentFragment qtdf;
                QTextStream stream(&file);
                stream.seek(0);
                stream << qtdf.fromHtml(inputStr).toPlainText();
                file.close();
            }
        }
    }

    return true;
}

bool FileHandler::saveAs(const QString &inputStr)
{
    QString filePath;
    QFileDialog dialog(this, tr("Save as"),
                       fileInfo.path().isEmpty() ? QDir::homePath()
                                                 : fileInfo.path(),
                       tr("THare files (*.tha);;"
                          "Plain text files (*.txt);;"
                          "All files (*)"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec())
    {
        filePath = dialog.selectedFiles().at(0);
        QFileInfo fi(filePath);
        if (fi.suffix().isEmpty())
        {
            if (dialog.selectedNameFilter().contains("tha"))
            {
                filePath.append(".tha");
            }
            else if (dialog.selectedNameFilter().contains("txt"))
            {
                filePath.append(".txt");
            }
        }
    }
    if (filePath.length())
    {

        QFile file(filePath);
        if (file.open(QFile::WriteOnly))
        {
            fileInfo.setFile(file);
            if (fileInfo.suffix() == "tha")
            {
                file.close();
                saveTha(inputStr);
                fileName = QFileInfo(filePath).fileName();
                fileInfo.setFile(filePath);
            }
            else
            {

                QTextStream stream(&file);
                QTextDocumentFragment qtdf;
                stream << qtdf.fromHtml(inputStr).toPlainText();
                fileName = QFileInfo(filePath).fileName();
                fileInfo.setFile(filePath);
                file.close();
            }
            return true;
        }
        else //! open
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

bool FileHandler::saveTha(const QString &inputStr)
{
    QString tempPath = tempDir.absoluteFilePath("main.html");
    QFile fileTha(tempPath);
    if (!fileTha.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }
    else
    {
        QTextStream streamTha(&fileTha);
        streamTha.seek(0);
        streamTha << inputStr;
        fileTha.close();

        QProcess fileProcess;
        QStringList arguments;
        QString command;
        fileProcess.setWorkingDirectory(tempDir.path());

        QDir qdl;
        qdl.setPath(QDir::currentPath());
        qdl.cd("arch");

#ifdef Q_OS_WIN
        command = qdl.absoluteFilePath("7za.exe");
#endif
#ifdef Q_OS_LINUX
        command = qdl.absoluteFilePath("7zzs");
#endif

        arguments << "a" << fileInfo.completeBaseName() + ".tha"
                  << "*";

        fileProcess.start(command, arguments);

        if (!fileProcess.waitForStarted() || !fileProcess.waitForFinished())
        {
            return false;
        }
        QFileInfo qfi;
        qfi.setFile(tempDir, fileInfo.fileName());
        fileTha.remove(fileInfo.absoluteFilePath());
        fileTha.copy(qfi.absoluteFilePath(), fileInfo.absoluteFilePath());
        fileTha.remove(qfi.absoluteFilePath());
        return true;
    }
    return true;
}

bool FileHandler::openTha()
{
    createTempDir();

    QString tempPath = tempDir.absoluteFilePath("main.html");
    QFile fileTha(tempPath);
    QFileInfo qfi;
    qfi.setFile(tempDir, fileInfo.fileName());
    fileTha.copy(fileInfo.absoluteFilePath(), qfi.absoluteFilePath());

    QProcess fileProcess;
    QStringList arguments;
    QString command;
    fileProcess.setWorkingDirectory(tempDir.path());

    QDir qdl;
    qdl.setPath(QDir::currentPath());
    qdl.cd("arch");

#ifdef Q_OS_WIN
    command = qdl.absoluteFilePath("7za.exe");
#endif
#ifdef Q_OS_LINUX
    command = qdl.absoluteFilePath("7zzs");
#endif

    arguments << "e" << fileInfo.completeBaseName() + ".tha";

    fileProcess.start(command, arguments);

    if (!fileProcess.waitForStarted() || !fileProcess.waitForFinished())
    {
        return false;
    }

    fileTha.remove(qfi.absoluteFilePath());

    if (fileTha.isOpen())
    {
        fileTha.close();
    }
    if (!fileTha.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }
    else
    {
        if (!fileTha.isReadable())
        {
            QMessageBox::warning(this, tr("Error"),
                                 tr("The file is not readable"));
            return false;
        }
        else
        {
            data = QTextStream(&fileTha).readAll();
        }
    }
    return true;
}
