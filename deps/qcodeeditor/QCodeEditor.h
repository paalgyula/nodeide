#ifndef QCODEEDITOR_H
#define QCODEEDITOR_H

#include <QTextEdit>
#include <QWidget>

class QCodeEditor : public QTextEdit
{
    Q_OBJECT
public:
    explicit QCodeEditor(QWidget *parent);
};

#endif // QCODEEDITOR_H
