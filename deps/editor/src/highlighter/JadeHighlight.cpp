#include "JadeHighlight.h"
#include <QDebug>

JadeHighlight::JadeHighlight(QTextDocument *parent = 0) : NodeHighlighter(parent)
{
    HighlightingRule rule;

    // operators
    QTextCharFormat operatorFormat;
    operatorFormat.setForeground(QColor("#FFD14D"));
    rule.pattern = QRegExp("[&{}\\(\\)\\[\\]\\!\\?%\\|<>=:;,\\.-\\*]");
    rule.format = operatorFormat;
    highlightingRules.append(rule);

    QTextCharFormat tagFormat;
    tagFormat.setForeground(QColor("#FFA09E"));
    tagFormat.setAnchor(true);
    rule.pattern = QRegExp("(^[\\ ]+[a-zA-Z0-9-_]+\\b)|(^[a-zA-Z0-9-_]+\\b)");
    rule.format = tagFormat;
    highlightingRules.append(rule);

    QTextCharFormat variableFormat;
    variableFormat.setForeground(QColor("#BEE5FF"));
    variableFormat.setAnchor(true);
    rule.pattern = QRegExp("#\\{[^\\}]+\\}");
    rule.format = variableFormat;
    highlightingRules.append(rule);

    QTextCharFormat quotationFormat;
    quotationFormat.setForeground(QColor("#C6F079"));
    rule.pattern = QRegExp("(\"[^\"]+\")|(\'[^\']+\')");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    QTextCharFormat commentFormat;
    commentFormat.setForeground(Qt::gray);
    rule.pattern = QRegExp("//.*$");
    rule.format = commentFormat;
    highlightingRules.append(rule);
}

void JadeHighlight::highlightBlock(const QString &text)
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

    QRegExp expression("[a-zA-Z0-9-_]+\\((.*)\\)");
    int index = expression.indexIn(text);
    if ( index > 0 )
    {

        qWarning() << expression.cap(1);
    }
}
