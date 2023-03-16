#ifndef CONST_STRINGS_H
#define CONST_STRINGS_H

#include <QBrush>
#include <QMap>
#include <QPair>
#include <QString>

static const int DEFAULT_FONT_SIZE = 12;
static const QString DEFAULT_FONT_FAMILY = "Sans Serif";
static const int MIN_VALUE_VALIDATOR_FONTS_SIZE = 4;
static const int MAX_VALUE_VALIDATOR_FONTS_SIZE = 200;

static const int MIN_VALUE_FONTS_SIZE = 8;
static const int MAX_VALUE_FONTS_SIZE = 50;

static const int STEP_FONT_SIZE = 2;

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
static const QPair<const char *, const char *> OPEN_FILE_READ_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Open file read only"),
    QT_TRANSLATE_NOOP("MainWindow", "Open file read only")};
static const QPair<const char *, const char *> CLOSE_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Close"),
    QT_TRANSLATE_NOOP("MainWindow", "Close a file")};
static const QPair<const char *, const char *> SAVE_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Save"),
    QT_TRANSLATE_NOOP("MainWindow", "Save file")};
static const QPair<const char *, const char *> SAVEAS_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Save as"),
    QT_TRANSLATE_NOOP("MainWindow", "Save file as")};
// LyashenkoAn Save to PDF--------------------------------------------------
static const QPair<const char *, const char *> SAVE_AS_PDF_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Save as PDF"),
    QT_TRANSLATE_NOOP("MainWindow", "Save as PDF")};
static const QPair<const char *, const char *> PRINT_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Print"),
    QT_TRANSLATE_NOOP("MainWindow", "Print file")};
static const QPair<const char *, const char *> EXIT_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Exit"),
    QT_TRANSLATE_NOOP("MainWindow", "Exit application")};

// 'Edit' - menu actions constants
static const QPair<const char *, const char *> SEARCH_TEXT_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Search text"),
    QT_TRANSLATE_NOOP("MainWindow", "Search text")};
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
    CROSSED_TEXT_FORMAT_ACTION_STR_PAIR{
        QT_TRANSLATE_NOOP("MainWindow", "Crossed/normal font"),
        QT_TRANSLATE_NOOP("MainWindow",
                          "Switch between crossed and normal font")};
static const QPair<const char *, const char *>
    UNDERLINE_TEXT_FORMAT_ACTION_STR_PAIR{
        QT_TRANSLATE_NOOP("MainWindow", "Underline/normal font"),
        QT_TRANSLATE_NOOP("MainWindow",
                          "Switch between underline and normal font")};
static const QPair<const char *, const char *> BOLD_TEXT_FORMAT_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Bold/normal font"),
    QT_TRANSLATE_NOOP("MainWindow", "Switch between bold and normal font")};
static const QPair<const char *, const char *>
    ITALIC_TEXT_FORMAT_ACTION_STR_PAIR{
        QT_TRANSLATE_NOOP("MainWindow", "Italic/normal font"),
        QT_TRANSLATE_NOOP("MainWindow",
                          "Switch between italic and normal font")};
static const QPair<const char *, const char *>
    HIGHLIGHT_TEXT_FORMAT_ACTION_STR_PAIR{
        QT_TRANSLATE_NOOP("MainWindow", "Highlight text"),
        QT_TRANSLATE_NOOP("MainWindow", "Text background color")};
static const QPair<const char *, const char *>
    TEXT_COLOR_FORMAT_ACTION_STR_PAIR{
        QT_TRANSLATE_NOOP("MainWindow", "Text color"),
        QT_TRANSLATE_NOOP("MainWindow", "Choose text color")};

// 'Settings' - menu actions constants
static const QPair<const char *, const char *> SETTINGS_ACTION_STR_PAIR{
    QT_TRANSLATE_NOOP("MainWindow", "Settings management"),
    QT_TRANSLATE_NOOP("MainWindow", "Change app settings")};

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
static const char *NEW_DOC_STR{
    QT_TRANSLATE_NOOP("MainWindow", "New document*")};
static const char *NO_FILE_OPENED_STR{
    QT_TRANSLATE_NOOP("MainWindow", "No file opened")};

// Icons
static const QString aboutIconPath{":/images/about.png"};
static const QString alignCenterIconPath{":/images/align_center.png"};
static const QString alignLeftIconPath{":/images/align_left.png"};
static const QString alignRightIconPath{":/images/align_right.png"};
static const QString cancelIconPath{":/images/cancel.png"};
static const QString closeIconPath{":/images/close.png"};
static const QString copyIconPath{":/images/copy.png"};
static const QString copyTextFormatIconPath{":/images/copy_format.png"};
static const QString cutIconPath{":/images/cut.png"};
static const QString exitIconPath{":/images/exit.png"};
static const QString greyStyleIconPath{":/images/grey_style.png"};
static const QString switchFontIconPath{":/images/font.png"};
static const QString helpIconPath{":/images/help.png"};
static const QString newIconPath{":/images/new.png"};
static const QString openIconPath{":/images/open.png"};
static const QString okIconPath{":/images/ok.png"};
static const QString applyTextFormatIconPath{":/images/paste_format.png"};
static const QString printIconPath{":/images/print.png"};
static const QString pasteIconPath{":/images/paste.png"};
static const QString russiaIconPath{":/images/russia.png"};
static const QString saveIconPath{":/images/save.png"};
static const QString saveAsIconPath{":/images/save_as.png"};
static const QString selectAllIconPath{":/images/select_all.png"};
static const QString settingsIconPath{":/images/settings.png"};
static const QString logoIconPath{":/images/icon_64.png"};
static const QString appIconPath{":/images/icon_128.png"};
static const QString boldTextFormatIconPath{":/images/bold.png"};
static const QString crossedTextFormatIconPath{":/images/crossed.png"};
static const QString italicTextFormatIconPath{":/images/italic.png"};
static const QString textColorFormatIconPath{":/images/text_color.png"};
static const QString underlineTextFormatIconPath{":/images/underline.png"};
static const QString usaIconPath{":/images/usa.png"};
static const QString whiteStyleIconPath{":/images/white_style.png"};
static const QString searchTextIconPath{":/images/search.png"};
static const QString highlightStyleIconPath{
    ":/images/text_background_color.png"};
static const QString openReadOnly{":/images/open_read_only.png"};

// LyashenkoAN "SAve to PDF
static const QString savePdfIcon{":/images/save_to_pdf.png"};

// Language
static const QString RUS_LANG_STR{"ru_RU"};
static const QString ENG_LANG_STR{"en_US"};

static const QMap<QString, QString> LANGS_MAP{
    {RUS_LANG_STR, ":/translation/l10n_ru.qm"},
    {ENG_LANG_STR, ":/translation/l10n_en.qm"}};

// Theme
static const QMap<int, QString> STYLES_MAP{{0, ":/themes/white.qss"},
                                           {1, ":/themes/grey.qss"}};

// Settings file name
static const QString SETTINGS_STORAGE{"settings.conf"};

// Setttings dialog GUI
static const char *LANG_STR{"Language"};
static const char *STYLE_STR{"Style"};

// Setttings Search dialog GUI
static const QString SEARCHFORM_TITLE{
    QT_TRANSLATE_NOOP("SearchDialog", "Search text")};
// Особенности шрифта
enum class FontFeature {
  DoesntMatter,
  Bold,
  Crossed,
  FontFamily,
  Italic,
  Size,
  Highlight,
  Underlined,
  ColoredText
};

static const QBrush HIGHLIGHT_COLOR = QBrush("#a5a500");

#endif // CONST_STRINGS_H
