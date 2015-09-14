#include "codeeditor.h"

#include <QFont>
#include <QTextStream>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QFileInfo>

#include <Qsci/qsciscintilla.h>
#include <Qsci/qsciabstractapis.h>
#include <Qsci/qsciapis.h>

#include <src/highlighter/JSLexer.h>
#include <src/mimetypehelper.h>

CodeEditor::CodeEditor(QWidget *parent) :
    QWidget(parent),
    pos_col(0),
    pos_line(0)
{
    m_editor = new QsciScintilla;

    QFont font = Tools::getInstance().monoFont();

    m_cursorPositionLabel = new QLabel(this);
    m_cursorPositionLabel->setText("Line: 1, Col: 1");

    m_editor->setMarginsFont(font);
    m_editor->setMarginWidth(0, 40);
    m_editor->setMarginLineNumbers(0, true);

    JSLexer *lexer = new JSLexer(m_editor);
    lexer->setDefaultFont(font);
    lexer->setDefaultPaper( QColor(73, 76, 78) );

    m_editor->setLexer(lexer);
    m_editor->setAutoIndent(true);

    m_editor->setTabWidth(4);
    m_editor->setCaretLineVisible(false);
    m_editor->setCaretForegroundColor(QColor(255, 255, 255));

    m_editor->setMarginsBackgroundColor(QColor(53, 56, 58));
    m_editor->setMarginsForegroundColor(QColor(173, 176, 178));

    m_editor->setAutoCompletionThreshold(2);
    m_editor->setAutoCompletionSource(QsciScintilla::AcsAPIs);

    connect( m_editor, SIGNAL(cursorPositionChanged(int,int)), this, SLOT(cursorPositionChanged(int,int)) );
    connect( m_editor, SIGNAL(modificationChanged(bool)), this, SLOT(edited(bool)) );

    QHBoxLayout *lineNumberLayout = new QHBoxLayout();
    lineNumberLayout->addStretch();
    lineNumberLayout->setMargin(0);
    lineNumberLayout->addWidget(m_cursorPositionLabel);

    QFrame *statusFrame = new QFrame(this);
    //statusFrame->setFrameShape(QFrame::StyledPanel);
    statusFrame->setLayout( lineNumberLayout );

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(2);
    layout->addWidget( m_editor );
    layout->addWidget( statusFrame );

    this->setLayout( layout );
}

void CodeEditor::setDocument(QFile *file)
{
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
    m_editor->setText(in.readAll());
    // When load than no modification!
    m_editor->setModified(false);
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
    out << m_editor->text();
    m_editor->setModified(false);
    m_file->close();
}

bool CodeEditor::requestClose() {
    if ( m_editor->isModified() )
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

void CodeEditor::reformat()
{

}

void CodeEditor::cursorPositionChanged(int line, int col)
{
    this->pos_line = line;
    this->pos_col = col;

    this->m_cursorPositionLabel->setText(
                QString("Line: %1, col: %2").arg(
                    QString::number(line + 1),
                    QString::number(col + 1))
                );

    emit cursorPosChanged(line, col);
}

void CodeEditor::getCursorPosition(int &line, int &col)
{
    line = this->pos_line + 1;
    col = this->pos_col + 1;
}

QString CodeEditor::documentName()
{
    return QFileInfo(*m_file).fileName();
}

bool CodeEditor::isModified()
{
    return m_editor->isModified();
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
    delete m_cursorPositionLabel;
}
