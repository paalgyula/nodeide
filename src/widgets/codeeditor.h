#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QFile>
#include <QFileInfo>
#include <QLabel>
#include <QWidget>

#include <Qsci/qsciscintilla.h>

class CodeEditor : public QWidget
{
    Q_OBJECT
public:
    explicit CodeEditor(QWidget *parent = 0);
    void setDocument(const QFileInfo info);
    void save();
    bool requestClose();
    void reformat();
    void getCursorPosition(int &line, int &col);
    QString documentName() { return QFileInfo(*m_file).fileName(); }
    QString documentPath() { return QFileInfo(*m_file).absoluteFilePath(); }
    bool isModified() { return m_editor->isModified(); }
    void setFocus();
    ~CodeEditor();

private:
    QsciScintilla *m_editor;
    QFile *m_file;
    QLabel *m_cursorPositionLabel;
    int pos_line;
    int pos_col;
signals:
    void cursorPosChanged(int line, int col);
    void modificationChanged(bool modified, CodeEditor*);
public slots:

private slots:
    void cursorPositionChanged(int line, int col);

    void edited(bool modified);
};

#endif // CODEEDITOR_H
