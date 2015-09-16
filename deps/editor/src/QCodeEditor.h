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

    // Tab size
    void setTabSize(int tabSize) { this->_tabSize = tabSize; }
    int tabSize() { return this->_tabSize; }

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

    int _tabSize;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    bool event(QEvent *event) Q_DECL_OVERRIDE;
};

#endif // EDITOR_H
