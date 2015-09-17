#ifndef JAVASCRIPTHIGHLIGHT_H
#define JAVASCRIPTHIGHLIGHT_H

#include <QSyntaxHighlighter>

class JavaScriptHighlight : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    JavaScriptHighlight(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;

    QTextCharFormat operatorFormat;
    QTextCharFormat numberFormat;
};

#endif // JAVASCRIPTHIGHLIGHT_H
