#ifndef JADEHIGHLIGHT_H
#define JADEHIGHLIGHT_H

#include "NodeHighlighter.h"

#include <QSyntaxHighlighter>
#include <QTextDocument>

class JadeHighlight : public NodeHighlighter
{
public:
    JadeHighlight(QTextDocument *parent);
protected:
    void highlightBlock(const QString &text);
};

#endif // JADEHIGHLIGHT_H
