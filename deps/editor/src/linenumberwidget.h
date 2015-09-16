#ifndef LINENUMBERWIDGET
#define LINENUMBERWIDGET

#include "QCodeEditor.h"

#include <QWidget>

class LineNumberWidget : public QWidget
{
public:
    LineNumberWidget(QCodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    QCodeEditor *codeEditor;
};

#endif // LINENUMBERWIDGET

