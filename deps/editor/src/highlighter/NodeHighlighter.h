#ifndef NODEHIGHLIGHTER
#define NODEHIGHLIGHTER

#include <QSyntaxHighlighter>
#include <QTextDocument>

class NodeHighlighter : public QSyntaxHighlighter
{
public:
    NodeHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {}

protected:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    virtual void loadColors()
    {

    }
};

#endif // NODEHIGHLIGHTER

