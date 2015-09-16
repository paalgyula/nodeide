#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QFile>
#include <QFileInfo>
#include <QLabel>
#include <QWidget>

#include <Qsci/qsciscintilla.h>

#include <src/editor.h>

class CodeEditor : public QWidget
{
    Q_OBJECT
public:
    explicit CodeEditor(QWidget *parent = 0);
    void loadFile(const QFileInfo info);
    void save();
    bool requestClose();
    void reformat();
    void getCursorPosition(int &line, int &col);
    QString documentName() { return QFileInfo(*m_file).fileName(); }
    QString documentPath() { return QFileInfo(*m_file).absoluteFilePath(); }
    bool isModified() { return m_editor->document()->isModified(); }
    void setFocus();
    ~CodeEditor();

private:
    QCodeEditor *m_editor;
    QFile *m_file;
signals:
    void cursorPosChanged(int line, int col);
    void modificationChanged(bool modified, CodeEditor*);
public slots:

private slots:
    void edited(bool modified);
};

#endif // CODEEDITOR_H
