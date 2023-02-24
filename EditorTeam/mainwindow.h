#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "helpbrowser.h"
#include "filehandler.h"
#include <QMainWindow>
#include <QSharedPointer>
#include <QTextEdit>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private:
    Ui::MainWindow *ui;

  /* Флаг "Содержимое textEdit изменено?" */
  bool isTextModified;

  /*! GubaydullinRG В textEdit загружен новый документ? */
  bool newDataLoaded;

  // Указатель на текущий редактируемый файл
  QSharedPointer<IDevHandler<QString>> srcHandler;

    QSharedPointer<HelpBrowser> hb;

    /*! KuznecovAG
      Переменная для текущего стиля (пока только white и grey) */
    QString currentStyle = "white";
    // Тулбар главной панели
    QToolBar *mainToolBar;

  // Пункты меню
  QMenu *fileMenu;
  QMenu *editMenu;
  QMenu *formatMenu;
  QMenu *settingsMenu;
  QMenu *questionMenu;

  // Вспомогательные методы для выноса части
  // кода за пределы конструктора
  void createAction(QAction **, const QString &, void (MainWindow::*)());
  void createActions();
  void createMenus();

  // Интернационализация приложения
  QTranslator *translator;
  virtual void changeEvent(QEvent *) override;
  void retranslateAction(QAction **, const QPair<const char *, const char *> &);
  void retranslateActions();
  void retranslateMenus();
  void retranslateGUI();

  /*! GubaydullinRG
      Включение/отключение доступности элементов меню 'File' */
  void changeFileMenuAccess(const QString &, bool, bool, bool);

  bool textChangedWarning(); // Окно предупреждения

  // Элементы подменю 'File'
  QAction *newAction;
  QAction *openAction;
  QAction *closeAction;
  QAction *saveAction;
  QAction *saveAsAction;
  QAction *printAction;
  QAction *exitAction;

  // Элементы подменю 'Edit'
  QAction *copyTextFormatAction;
  QAction *applyTextFormatAction;
  QAction *alignTextRightAction;
  QAction *alignTextLeftAction;
  QAction *alignTextCenterAction;
  QAction *switchFontAction;

  // Элементы подменю 'Format'
      QAction *crossedTextFormatAction;

  // Элементы подменю 'Settings'
  QAction *changeLangAction;
  QAction *changeKeyBindAction;
  QAction *changeStyleAction;

  // Поле для размещения редактируемого текста
  QTextEdit *textEdit;

  // Элементы подменю '?'
  QAction *helpAction;
  QAction *aboutAction;

private slots:
  // Основные функции приложения
  void onNew();
  void onOpen();
  void onClose();
  void onSave();
  void onSaveAs();
  void onPrint();
  void onExit();
  void onCopyTextFormat();
  void onApplyTextFormat();
  void onAlignTextRight();
  void onAlignTextLeft();
  void onAlignTextCenter();
  void onSwitchFont();
  void onChangeLang();
  void onChangeKeyBind();
  void onChangeStyle();
  void onHelp();
  void onAbout();
  void onCrossedTextFormat();

    /*! GubaydullinRG
    // Слот действий на случай изменения
    // содержимого textEdit */
    void onTextModified();

    void setMainToolBar();
};
#endif // MAINWINDOW_H
