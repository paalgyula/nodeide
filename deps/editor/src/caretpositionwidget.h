#ifndef CARETPOSITIONWIDGET
#define CARETPOSITIONWIDGET

#include "QCodeEditor.h"

#include <QWidget>

class CaretPositionWidget : public QWidget
{
public:
    CaretPositionWidget(QCodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(codeEditor->caretPositionAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
        codeEditor->caretPositionAreaPaintEvent(event);
    }

private:
    QCodeEditor *codeEditor;
};

#endif // CARETPOSITIONWIDGET

