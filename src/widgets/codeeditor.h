#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QFile>
#include <QLabel>
#include <QWidget>

#include <Qsci/qsciscintilla.h>

class CodeEditor : public QWidget
{
    Q_OBJECT
public:
    explicit CodeEditor(QWidget *parent = 0);
    void setDocument(QFile *file);
    bool requestClose();
    void reformat();
    void getCursorPosition(int &line, int &col);
    QString documentName();
    bool isModified();
private:
    QsciScintilla *m_editor;
    QFile *m_file;
    QLabel *m_cursorPositionLabel;
    int pos_line;
    int pos_col;
signals:
    void cursorPosChanged(int line, int col);
public slots:

private slots:
    void cursorPositionChanged(int line, int col);

};

#endif // CODEEDITOR_H
