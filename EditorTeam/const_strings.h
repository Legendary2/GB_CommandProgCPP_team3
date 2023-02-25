#ifndef CONST_STRINGS_H
#define CONST_STRINGS_H

#include <QPair>
#include <QString>

static const char *FILE_MENU_STR{QT_TRANSLATE_NOOP("MainWindow", "&File")};
static const char *EDIT_MENU_STR{QT_TRANSLATE_NOOP("MainWindow", "&Edit")};
static const char *FORMAT_MENU_STR{QT_TRANSLATE_NOOP("MainWindow", "&Format")};
static const char *SETTINGS_MENU_STR{
    QT_TRANSLATE_NOOP("MainWindow", "&Settings")};
static const char *QUESTION_MENU_STR{QT_TRANSLATE_NOOP("MainWindow", "?")};

// 'File' - menu actions constants
static const QPair<const char *, const char *> NEW_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "New"),
    QT_TRANSLATE_NOOP("MainWindow", "Create new file")};
static const QPair<const char *, const char *> OPEN_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Open"),
    QT_TRANSLATE_NOOP("MainWindow", "Open a file")};
static const QPair<const char *, const char *> CLOSE_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Close"),
    QT_TRANSLATE_NOOP("MainWindow", "Close a file")};
static const QPair<const char *, const char *> SAVE_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Save"),
    QT_TRANSLATE_NOOP("MainWindow", "Save file")};
static const QPair<const char *, const char *> SAVEAS_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Save as"),
    QT_TRANSLATE_NOOP("MainWindow", "Save file as")};
static const QPair<const char *, const char *> PRINT_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Print"),
    QT_TRANSLATE_NOOP("MainWindow", "Print file")};
static const QPair<const char *, const char *> EXIT_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Exit"),
    QT_TRANSLATE_NOOP("MainWindow", "Exit application")};

// 'Edit' - menu actions constants
static const QPair<const char *, const char *> COPY_TEXT_FORMAT_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Copy text format"),
    QT_TRANSLATE_NOOP("MainWindow", "Copy text format")};
static const QPair<const char *, const char *>
    APPLY_TEXT_FORMAT_ACTION_STR_PAIR{
        QT_TRANSLATE_NOOP("MainWindow", "Apply text format"),
        QT_TRANSLATE_NOOP("MainWindow", "Apply text format")};
static const QPair<const char *, const char *> ALIGN_TEXT_RIGHT_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Align text right"),
    QT_TRANSLATE_NOOP("MainWindow", "Align text right")};
static const QPair<const char *, const char *> ALIGN_TEXT_LEFT_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Align text left"),
    QT_TRANSLATE_NOOP("MainWindow", "Align text left")};
static const QPair<const char *, const char *>
    ALIGN_TEXT_CENTER_ACTION_STR_PAIR{
        QT_TRANSLATE_NOOP("MainWindow", "Align text center"),
        QT_TRANSLATE_NOOP("MainWindow", "Align text center")};
static const QPair<const char *, const char *> SWITCH_FONT_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Switch font"),
    QT_TRANSLATE_NOOP("MainWindow", "Switch font")};

// 'Format' - menu actions constants
static const QPair<const char *, const char *>
    UNDERLINE_TEXT_FORMAT_ACTION_STR_PAIR{
        QT_TRANSLATE_NOOP("MainWindow", "Underline font"),
        QT_TRANSLATE_NOOP("MainWindow", "Underline font")};

// 'Settings' - menu actions constants
static const QPair<const char *, const char *> CHANGE_LANG_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Language"),
    QT_TRANSLATE_NOOP("MainWindow", "Change application language")};
static const QPair<const char *, const char *> CHANGE_KEY_BIND_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Key bindings"),
    QT_TRANSLATE_NOOP("MainWindow", "Edit key bindings settings")};
static const QPair<const char *, const char *> CHANGE_STYLE_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Change style"),
    QT_TRANSLATE_NOOP("MainWindow", "Change application style")};

// '?' - menu actions constants
static const QPair<const char *, const char *> HELP_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Help"),
    QT_TRANSLATE_NOOP("MainWindow", "Show application manual")};
static const QPair<const char *, const char *> ABOUT_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "About"),
    QT_TRANSLATE_NOOP("MainWindow", "Short info about application")};

// Popup actions
static const QPair<const char *, const char *> COPY_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Copy"),
    QT_TRANSLATE_NOOP("MainWindow", "Copy selected text to clipboard")};
static const QPair<const char *, const char *> CUT_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Cut"),
    QT_TRANSLATE_NOOP("MainWindow", "Cut selected text to clipboard")};
static const QPair<const char *, const char *> PASTE_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Paste"),
    QT_TRANSLATE_NOOP("MainWindow", "Paste from clipboard")};
static const QPair<const char *, const char *> SELECT_ALL_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Select all"),
    QT_TRANSLATE_NOOP("MainWindow", "Select all text")};

// font size on popupMenu
static const char *POPUP_FONT_SIZE_STR{
    QT_TRANSLATE_NOOP("MainWindow", "Choose font size from 8 to 50:"});

// Window title constants
static const char *NEW_DOC_STR{QT_TRANSLATE_NOOP("MainWindow", "New document")};
static const char *NO_FILE_OPENED_STR{
    QT_TRANSLATE_NOOP("MainWindow", "No file opened")};

// Icons
const QString aboutIconPath{":/images/about.png"};
const QString alignCenterIconPath{":/images/align_center.png"};
const QString alignLeftIconPath{":/images/align_left.png"};
const QString alignRightIconPath{":/images/align_right.png"};
const QString closeIconPath{":/images/close.png"};
const QString copyIconPath{":/images/copy.png"};
const QString copyTextFormatIconPath{":/images/copy_format.png"};
const QString cutIconPath{":/images/cut.png"};
const QString exitIconPath{":/images/exit.png"};
const QString switchFontIconPath{":/images/font.png"};
const QString helpIconPath{":/images/help.png"};
const QString keyBindsIconPath{":/images/keybinds.png"};
const QString changeLanguageIconPath{":/images/language.png"};
const QString newIconPath{":/images/new.png"};
const QString openIconPath{":/images/open.png"};
const QString applyTextFormatIconPath{":/images/paste_format.png"};
const QString printIconPath{":/images/print.png"};
const QString pasteIconPath{":/images/paste.png"};
const QString saveIconPath{":/images/save.png"};
const QString saveAsIconPath{":/images/save_as.png"};
const QString selectAllIconPath{":/images/select_all.png"};
const QString changeStyleIconPath{":/images/style.png"};
const QString logoIconPath{":/images/icon_64.png"};
const QString appIconPath{":/images/icon_128.png"};
const QString boldTextFormatIconPath{":/images/bold.png"};
const QString crossedTextFormatIconPath{":/images/crossed.png"};
const QString italicTextFormatIconPath{":/images/italic.png"};
const QString underlineTextFormatIconPath{":/images/underline.png"};

#endif // CONST_STRINGS_H
