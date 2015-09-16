#include "codeeditor.h"

#include <QFont>
#include <QTextStream>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QFileInfo>

#include <src/QCodeEditor.h>
#include <src/mimetypehelper.h>

CodeEditor::CodeEditor(QWidget *parent) :
    QWidget(parent)
{
    m_editor = new QCodeEditor(this);

    /*m_editor->setMarginsFont(font);
    m_editor->setMarginWidth(0, 40);
    m_editor->setMarginLineNumbers(0, true);

    m_editor->setAutoIndent(true);

    m_editor->setTabWidth(4);
    m_editor->setCaretLineVisible(false);
    m_editor->setCaretForegroundColor(QColor(255, 255, 255));

    m_editor->setMarginsBackgroundColor(QColor(53, 56, 58));
    m_editor->setMarginsForegroundColor(QColor(173, 176, 178));

    m_editor->setAutoCompletionThreshold(2);
    m_editor->setAutoCompletionSource(QsciScintilla::AcsAPIs);*/

    connect( m_editor, &QCodeEditor::modificationChanged, this, &CodeEditor::edited );

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(2);
    layout->addWidget( m_editor );
    this->setLayout( layout );
}

void CodeEditor::loadFile(const QFileInfo info)
{
    QFile *file = new QFile(info.filePath());

    if (!file->open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file->fileName())
                             .arg(file->errorString()));
        return;
    }

    m_file = file;
    QTextStream in(file);
    m_editor->setPlainText(in.readAll());
    // When load than no modification!
    m_editor->document()->setModified(false);
    file->close();
}

void CodeEditor::save()
{
    if (!m_file->open(QFile::WriteOnly))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(m_file->fileName())
                             .arg(m_file->errorString()));
        return;
    }
    QTextStream out(m_file);
    out << m_editor->toPlainText();
    m_editor->document()->setModified(false);
    m_file->close();
}

bool CodeEditor::requestClose() {
    if ( m_editor->document()->isModified() )
    {
        int answer = QMessageBox::question(this, "Close file", "The file has been changed. Do you want to save changes?",
                                           QMessageBox::Yes |
                                           QMessageBox::No |
                                           QMessageBox::Cancel );
        if (answer == QMessageBox::Cancel)
            return false;
    }

    return true;
}

void CodeEditor::setFocus()
{
    m_editor->setFocus();
}

void CodeEditor::edited(bool modified)
{
    emit modificationChanged(modified, this);
}

CodeEditor::~CodeEditor()
{
    delete m_editor;
    delete m_file;
}
