#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "filehandler.h"
#include "helpbrowser.h"
#include "searchform.h"
#include "searchhighlight.h"
#include "settingskeeper.h"
#include <QComboBox>
#include <QDockWidget>
#include <QFileSystemModel>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QSharedPointer>
#include <QTextEdit>
#include <QTranslator>
#include <QTreeWidget>

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

    QBoxLayout *boxLayout;

    // Указатель на диалоговое окно настроек
    SettingsKeeper *settingsKeeper;

    // Указатель на окно поиска
    SearchForm *searchForm;
    SearchHighLight *searchHighLight;

    /* Флаг "Содержимое textEdit изменено?" */
    bool isTextModified = false;

    /*! GubaydullinRG В textEdit загружен новый документ? */
    bool newDataLoaded;

    // Указатель на текущий редактируемый файл
    QSharedPointer<IDevHandler<QString>> srcHandler;

    QSharedPointer<HelpBrowser> hb;

    // Тулбар главной панели
    QToolBar *mainToolBar;

    // Пункты меню
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu; // Добавил, чтобы было куда меню делать
    QMenu *settingsMenu;
    QMenu *questionMenu;
    QMenu *treeMenu;

    // Вспомогательные методы для выноса части
    // кода за пределы конструктора
    void createAction(QAction **, const QString &, void (MainWindow::*)());
    void createActions();
    void createMenus();

    // Интернационализация приложения
    QTranslator *translator;
    virtual void changeEvent(QEvent *) override;
    void retranslateAction(QAction **,
                           const QPair<const char *, const char *> &);
    void retranslateActions();
    void retranslateMenus();
    void retranslateGUI();

    /*! GubaydullinRG Переменная, хранящая скопированный функцией
     * onCopyTextFormat() формат выделенного фрагмента текста для передачи его в
     * onApplyTextFormat() */
    QTextCharFormat copiedTxtFormat;

    /*! GubaydullinRG
        Включение/отключение доступности элементов меню */
    void changeFileMenuAccess(const QString &, bool, bool, bool);
    void changePopupMenuAccess();

    const std::optional<QTextCharFormat>
    getCurrentCharFormat(const FontFeature) const;
    bool fontFeatureEquals(const QTextCharFormat &, const QTextCharFormat &,
                           const FontFeature) const;

    bool textChangedWarning(); // Окно предупреждения

    /*! GubaydullinRG
    Контекстное для textEdit меню */
    QMenu *popupMenu;
    QComboBox *fontSizeComboBox;
    QLabel *fontSizeLabel;
    void inflatePopupMenu();

    // Элементы подменю 'File'
    QAction *newAction;
    QAction *openAction;
    QAction *closeAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *printAction;
    QAction *exitAction;

    // Элементы подменю 'Edit'
    QAction *searchTextAction;
    QAction *copyTextFormatAction;
    QAction *applyTextFormatAction;
    QAction *alignTextRightAction;
    QAction *alignTextLeftAction;
    QAction *alignTextCenterAction;
    QAction *switchFontAction;

  // Элементы подменю 'Format'
  QAction *crossedTextFormatAction;
  QAction *underlineTextFormatAction;
  QAction *boldTextFormatAction;
  QAction *italicTextFormatAction;
  QAction *highlightTextFormatAction;
  QAction *textColorFormatAction;

    // Элементы подменю 'Settings'
    // QAction *changeLangAction;
    QAction *changeKeyBindAction;
    QAction *settingsAction;

    // Поле для размещения редактируемого текста
    QTextEdit *textEdit;
    QString lastFilename;

    // Объект хранит в себе скопированный формат текста
    QTextCharFormat textFormat;

    // Элементы подменю '?'
    QAction *helpAction;
    QAction *aboutAction;

    // Элементы древа каталогов
    QString currentFile, teamPath;
    QFileSystemModel *dirModel;
    QPushButton *FindTreeButton;
    QTextEdit *infoText;
    QLabel *statusLabel;
    QLineEdit *searchTreeEdit;
    QTreeView *treeView;
    QDockWidget *viewWidget;

    // popup
    QWidgetAction *popupWidgetAction;
    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *selectAllAction;

    //Добавление Label для вывода пути к файлу
    QLabel *myLabel;

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
    void onChangeKeyBind();
    void onChangeStyle();
    void onHelp();
    void onAbout();
    void onCrossedTextFormat();
    void onUnderlineTextFormat();
    void onBoldTextFormat();
    void onItalicTextFormat();
    void onSettingsInvoke();
    void onSettingsApplyClicked();
    void onSettingsCancelClicked();
    void onSettingsOkClicked();
    void onSearchText();
    void onSearchFormButtonClicked(QString);
    void clearHighLight();
  void onHighlightTextFormat();
  void onTextColorFormat();

    /*! GubaydullinRG
    // Слот действий на случай изменения
    // содержимого textEdit */
    void onTextModified();

    void setMainToolBar();

    /*! GubaydullinRG
    Показ контекстного меню (popupMenu) в textEdit
    и реакция на выбор элемента в popupComboBox */
    void onPopupMenuCalled(QPoint);
    void onPopupComboBoxIndexChanged(int);

    void onCopy();
    void onCut();
    void onPaste();
    void onSelectAll();
};

#endif // MAINWINDOW_H
