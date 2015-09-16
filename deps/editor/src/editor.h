#ifndef EDITOR_H
#define EDITOR_H

#include <QFileInfo>
#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QTextEdit>

class QCodeEditor : public QPlainTextEdit
{
public:
    explicit QCodeEditor(QWidget *parent);
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    void caretPositionAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    int caretPositionAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

public slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);
    void updateCaretPositionArea(const QRect &rect, int dy);
    void highlightCurrentLine();
    void updateCaretWidget();

private:
    QWidget *lineNumberArea;
    QWidget *caretPositionArea;
    QSyntaxHighlighter *_highlighter;
    QString positionStr;

    QFont caretWidgetFont;
};

#endif // EDITOR_H
