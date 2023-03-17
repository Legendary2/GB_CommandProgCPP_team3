#include "searchhighlight.h"
#include "const_strings.h"

#include <QTextCharFormat>

SearchHighLight::SearchHighLight(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    formatHighLight.setBackground(HIGHLIGHT_COLOR);
}

void SearchHighLight::highlightBlock(const QString &text)
{
    QRegularExpressionMatchIterator matchIterator =
        patternHighLight.globalMatch(text);
    while (matchIterator.hasNext())
    {
        QRegularExpressionMatch match = matchIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(),
                  formatHighLight);
        if (currentBlockState() == -1)
            count++;
    }
}

void SearchHighLight::searchText(const QString &text, bool isСaseInsensitive)
{
    count = 0;
    if (text.isEmpty())
        return;
    patternHighLight = QRegularExpression(text);
    if (isСaseInsensitive)
    {
        patternHighLight.setPatternOptions(
            QRegularExpression::CaseInsensitiveOption);
    }
    else
    {
        patternHighLight.setPatternOptions(QRegularExpression::NoPatternOption);
    }

    rehighlight();
}

void SearchHighLight::clearText()
{
    patternHighLight = QRegularExpression(NULL);
    rehighlight();
    count = 0;
}

int SearchHighLight::coutResult() { return count; }

SearchHighLight::~SearchHighLight() {}
