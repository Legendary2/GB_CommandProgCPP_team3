#ifndef SEARCHHIGHLIGHT_H
#define SEARCHHIGHLIGHT_H

#include <QRegularExpression>
#include <QSyntaxHighlighter>

class SearchHighLight : public QSyntaxHighlighter
{
    Q_OBJECT

  public:
    explicit SearchHighLight(QTextDocument *parent = nullptr);
    ~SearchHighLight();

    void searchText(const QString &, bool isСaseInsensitive = false);
    void clearText();
    int coutResult();

  protected:
    virtual void highlightBlock(const QString &text) override;

  private:
    QRegularExpression patternHighLight;
    QTextCharFormat formatHighLight;
    int count;
};

#endif // SEARCHHIGHLIGHT_H
