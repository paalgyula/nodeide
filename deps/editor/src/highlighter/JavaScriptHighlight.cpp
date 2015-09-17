#include "JavaScriptHighlight.h"

JavaScriptHighlight::JavaScriptHighlight(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(QColor("#BEE5FF"));

    QStringList keywordPatterns;
    keywordPatterns = QString("break case class catch const continue "
            "debugger default delete do else export "
            "extends finally for function if import "
            "in instanceof let new return super switch "
            "this throw try typeof var void while with yield "
            "null true false")
            .split(" ");

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(QString("\\b%1\\b").arg(pattern));
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // Formats
    //classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    /*functionFormat.setFontItalic(true);
    functionFormat.setForeground(QColor("#BEE5FF"));
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);*/

    // operators
    operatorFormat.setForeground(QColor("#FFD14D"));
    rule.pattern = QRegExp("[&{}\\(\\)\\[\\]\\!\\?%\\|<>=:;,\\.-\\*]");
    rule.format = operatorFormat;
    highlightingRules.append(rule);

    numberFormat.setForeground(QColor("#FFA09E"));
    rule.pattern = QRegExp("(\\b[0-9]+\\b)");
    rule.format = numberFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(QColor("#C6F079"));
    rule.pattern = QRegExp("(\"[^\"]+\")|(\'[^\']+\')");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    QTextCharFormat commentFormat;
    commentFormat.setForeground(Qt::gray);
    rule.pattern = QRegExp("[^:]//.*$");
    rule.format = commentFormat;
    highlightingRules.append(rule);
}

void JavaScriptHighlight::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }


    QTextCharFormat multiLineCommentFormat;
    multiLineCommentFormat.setForeground( Qt::gray );

    QRegExp startExpression("/\\*");
    QRegExp endExpression("\\*/");

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(startExpression);

    while (startIndex >= 0) {
       int endIndex = text.indexOf(endExpression, startIndex);
       int commentLength;
       if (endIndex == -1) {
           setCurrentBlockState(1);
           commentLength = text.length() - startIndex;
       } else {
           commentLength = endIndex - startIndex
                           + endExpression.matchedLength();
       }
       setFormat(startIndex, commentLength, multiLineCommentFormat);
       startIndex = text.indexOf(startExpression,
                                 startIndex + commentLength);
    }
}
