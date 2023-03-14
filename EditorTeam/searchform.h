#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include <QtWidgets>

class SearchForm : public QDialog
{
    Q_OBJECT
  public:
    explicit SearchForm(QWidget *parent = nullptr);
    ~SearchForm();

    void clearForm();
    void retranslateGUI();
    bool isСaseInsensitive();

  signals:
    void signalFromSearchText(QString);

  private:
    QHBoxLayout *hboxLayout;
    QPushButton *searchButton;
    QCheckBox *registerSearch;
    QLineEdit *stringSearch;

  private slots:
    void onSearchClicked();
};

#endif // SEARCHFORM_H
