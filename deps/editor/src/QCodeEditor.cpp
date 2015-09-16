#include "QCodeEditor.h"

#include "caretpositionwidget.h"
#include "highlighter.h"
#include "linenumberwidget.h"

#include <QPainter>
#include <QTextStream>

#include <QTextDocumentFragment>
#include <QDebug>

QCodeEditor::QCodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Base, QColor(73, 76, 78));
    palette.setColor(QPalette::Text, QColor(Qt::white));
    this->setPalette(palette);

    QFont font;
    font.setFamily("Monospace");
    font.setFixedPitch(true);
    font.setPointSize(10);

    _highlighter = new Highlighter(document());

    this->setFont(font);

    // Slots
    lineNumberArea = new LineNumberWidget(this);
    caretPositionArea = new CaretPositionWidget(this);

    connect(this, &QPlainTextEdit::blockCountChanged, this, &QCodeEditor::updateLineNumberAreaWidth);
    connect(this, &QPlainTextEdit::updateRequest, this, &QCodeEditor::updateLineNumberArea);
    connect(this, &QPlainTextEdit::cursorPositionChanged, this, &QCodeEditor::highlightCurrentLine);
    connect(this, &QPlainTextEdit::cursorPositionChanged, this, &QCodeEditor::updateCaretWidget);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();

    positionStr = QString("Line: 1, col: 1");
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setWordWrapMode(QTextOption::NoWrap);

    caretWidgetFont.setFamily(caretWidgetFont.defaultFamily());
    caretWidgetFont.setPointSize(8);
    caretWidgetFont.setFixedPitch(false);

    _tabSize = 2;

    QTextOption textOption = document()->defaultTextOption();
    //textOption.setFlags(QTextOption::ShowTabsAndSpaces | QTextOption::ShowLineAndParagraphSeparators);
    document()->setDefaultTextOption(textOption);
}

int QCodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    // TODO: implement more icon - 16x16 + 2 padding
    int space = 17 + fontMetrics().width(QLatin1Char('9')) * digits + 3 + 1 + 16;

    return space;
}

int QCodeEditor::caretPositionAreaWidth()
{
    QFontMetrics metric(caretWidgetFont);
    return metric.width(positionStr) + 8;
}

void QCodeEditor::updateCaretWidget()
{
    positionStr = QString("Line: %1, col: %2").arg(
        QString::number(textCursor().blockNumber()+1),
        QString::number(textCursor().positionInBlock()+1)
        );

    QRect cr = viewport()->geometry();

    int caretWidgetHeight = 16;
    caretPositionArea->setGeometry( QRect(
                                        cr.right() - caretPositionAreaWidth(),
                                        cr.bottom() - caretWidgetHeight,
                                        caretPositionAreaWidth(),
                                        caretWidgetHeight)
                                    );
    caretPositionArea->update();
}

void QCodeEditor::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Tab)
    {
        //int cursorPosition = cur.position();
        QTextCursor cur = textCursor();
        if (!cur.hasSelection())
        {
            cur.insertText(QString("%1").arg(" ", _tabSize));
        }
        else // Ident selection
        {
            QTextCursor *helper = new QTextCursor(document());
            helper->setPosition(cur.anchor());
            // selection row number
            int startSelection = helper->blockNumber();
            helper->setPosition(cur.position());
            int endSelection = helper->blockNumber();

            helper->beginEditBlock();
            {
                for ( ;; )
                {
                    helper->movePosition(QTextCursor::StartOfLine);
                    helper->insertText(QString("%1").arg(" ", _tabSize));

                    if ( startSelection == helper->blockNumber() )
                        break;
                    helper->movePosition( startSelection > endSelection ? QTextCursor::Down : QTextCursor::Up);
                };
            }
            helper->endEditBlock();
            delete helper;
        }

    }
    else if (event->key() == Qt::Key_Backtab) // Shift + Tab
    {
        QTextCursor cur = textCursor();
        QTextCursor helper = textCursor();
        QRegExp unidentRegexp(QString("^[\\ ]{0,%1}").arg(QString::number(_tabSize)));

        if (!cur.hasSelection())
        {
            helper.movePosition(QTextCursor::StartOfLine);

            for (int i=0;i<_tabSize;i++)
            {
                if (helper.block().text().startsWith(" "))
                {
                    helper.clearSelection();
                    helper.deleteChar();
                }
            }
        }
        else // Ident selection
        {
            QTextCursor *helper = new QTextCursor(document());
            helper->setPosition(cur.anchor());
            // selection row number
            int startSelection = helper->blockNumber();
            helper->setPosition(cur.position());
            int endSelection = helper->blockNumber();

            helper->beginEditBlock();
            {
                for ( ;; )
                {
                    helper->movePosition(QTextCursor::StartOfLine);

                    for (int i=0;i<_tabSize;i++)
                    {
                        if (helper->block().text().startsWith(" "))
                        {
                            helper->clearSelection();
                            helper->deleteChar();
                        }
                    }

                    if ( startSelection == helper->blockNumber() )
                        break;

                    helper->movePosition( startSelection > endSelection ? QTextCursor::Down : QTextCursor::Up);
                };
            }
            helper->endEditBlock();
            delete helper;
        }

    }
    else
        QPlainTextEdit::keyPressEvent(event);
}

bool QCodeEditor::event(QEvent *event)
{
    if ( event->type() == QEvent::KeyPress )
    {
        QKeyEvent *ke = static_cast<QKeyEvent*>(event);
        if (ke->key() == Qt::Key_Tab || ke->key() == Qt::Key_Backtab) {
            QCodeEditor::keyPressEvent(ke);
            return true;
        }
    }

    return QPlainTextEdit::event(event);
}

void QCodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void QCodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void QCodeEditor::updateCaretPositionArea(const QRect &rect, int dy)
{
    if (dy)
        caretPositionArea->scroll(0, dy);
    else
        caretPositionArea->update(0, rect.y(), caretPositionArea->width(), rect.height());
}

void QCodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));

    this->updateCaretWidget();
}

void QCodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(QColor(73, 76, 78)).darker(110);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void QCodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    //m_editor->setMarginsBackgroundColor(QColor(53, 56, 58));
    //m_editor->setMarginsForegroundColor(QColor(173, 176, 178));

    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor(53, 56, 58));

    // Git line
    QRect lineRect, rect = event->rect();
    lineRect = QRect(rect.right()- 3 - 16,
    //                             ^   ^   ^
    //                             |   |   |
    //             line width -----/ padd  \----- icon size
                     rect.top(),
                     3,
                     rect.bottom());
    painter.fillRect( lineRect, Qt::darkGreen );

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor(173, 176, 178));

            if ( blockNumber == textCursor().blockNumber() )
                painter.setPen(Qt::white);

            // -20 is a padding
            painter.drawText(16, top +1, lineNumberArea->width() - 16 - 16 - 3 - 2, fontMetrics().height(),
                             Qt::AlignRight, number);

            /*QPixmap pixmap(":/icons/stop.png");
            pixmap = pixmap.scaled(QSize(16, 16), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            painter.drawPixmap(lineNumberArea->width() - 17, top, pixmap);*/
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void QCodeEditor::caretPositionAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(caretPositionArea);
    painter.setFont(caretWidgetFont);
    painter.setOpacity(0.5);

    QRect rc = event->rect();

    QBrush brush(QColor(53, 56, 58));
    painter.setBrush(brush);

    QRect rect = QRect(rc.left(), rc.top(), rc.height() , rc.height());
    painter.drawEllipse(rect);

    painter.fillRect(QRect(
                         rc.left() + rc.height() / 2,
                         rc.top(),
                         rc.width() - rc.height() / 2,
                         rc.height()
                         ), QColor(53, 56, 58));

    painter.setPen(QColor("#ffffff"));
    painter.setOpacity(1);
    painter.drawText(QRect(
                         rc.left(),
                         rc.top() + 2,
                         rc.width(),
                         rc.height() - 2
                         ), Qt::AlignRight, positionStr);

}

Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(QColor("#BEE5FF"));

    QStringList keywordPatterns;
    keywordPatterns = QString("break case class catch const continue "
            "debugger default delete do else export "
            "extends finally for function if import "
            "in instanceof let new return super switch "
            "this throw try typeof var void while with yield null")
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

void Highlighter::highlightBlock(const QString &text)
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

//////////////////////////////////////////////////////////////////////////////////
