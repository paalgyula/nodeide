#include "mainwindow.h"

#include <QCompleter>
#include <QLineEdit>
#include <QDockWidget>
#include <QTextEdit>
#include <QMenuBar>
#include <QPushButton>
#include <QSpacerItem>
#include <QComboBox>
#include <QScrollArea>
#include <QStatusBar>
#include <QDebug>
#include <QFileInfo>
#include <QLabel>
#include <QVBoxLayout>
#include <QFileIconProvider>
#include <QMimeData>
#include <QMimeDatabase>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileDialog>

#include <src/widgets/codeeditor.h>
#include <src/widgets/projectexplorer.h>
#include <src/widgets/runconfigurationswidget.h>

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerjavascript.h>

#include <src/highlighter/JSLexer.h>
#include <src/mimetypehelper.h>

#define WINDOW_TITLE "KNodeIDE - Paál Gyula (c) 2015"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowIcon(QIcon(":/icons/logo.png"));
    this->setWindowTitle( WINDOW_TITLE );

    this->createMainMenu();
    this->createToolbar();
    this->createProjectExplorer();

    m_documentTabs = new QTabWidget(this);
    m_documentTabs->setTabsClosable(true);

    QFont *font = new QFont();
    font->setBold(true);

    QLabel *tabLabel = new QLabel("<a href=\"http://www.paalgyula.com\">www.paalgyula.com</a> ");
    tabLabel->setTextFormat(Qt::RichText);
    tabLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    tabLabel->setOpenExternalLinks(true);

    m_documentTabs->setCornerWidget(tabLabel);
    this->setCentralWidget( m_documentTabs );

    // Tab close button handler
    connect(m_documentTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(int)));
    // Tab close button handler
    connect(m_documentTabs, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));

    this->setMinimumSize(QSize(700, 400));
}

MainWindow::~MainWindow()
{
}

void MainWindow::createMainMenu()
{
    QMenuBar *mainMenu = new QMenuBar(this);

    // File menu
    QMenu *fileMenu = new QMenu("&File", mainMenu);

    mainMenu->addMenu(fileMenu);
    m_newFileAction = fileMenu->addAction( QIcon::fromTheme("document-new"), tr("&New file..."), this, SLOT(newFile()));
    m_newFileAction->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_N) );

    m_saveFileAction = fileMenu->addAction( QIcon::fromTheme("document-save"), tr("&Save file"), this, SLOT(newFile()));
    m_saveFileAction->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_S) );

    m_openProjectAction = fileMenu->addAction( QIcon::fromTheme("document-open-folder"), tr("Open project"), this, SLOT(openProject()));
    m_openProjectAction->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_O) );

    fileMenu->addSeparator();
    fileMenu->addAction(tr("E&xit"), this, SLOT(close()), QKeySequence( Qt::ALT + Qt::Key_F4 ) );

    // Edit menu
    QMenu *editMenu = new QMenu(tr("Edit"), mainMenu);
    mainMenu->addMenu(editMenu);

    // Window menu
    QMenu *windowMenu = new QMenu(tr("Window"), mainMenu);
    mainMenu->addMenu(windowMenu);

    windowMenu->addAction("Close current tab", this, SLOT(closeCurrentTab()), QKeySequence( Qt::CTRL + Qt::Key_W ));

    mainMenu->addSeparator();

    // About menu
    QMenu *aboutMenu = new QMenu(tr("About"), mainMenu);
    mainMenu->addMenu(aboutMenu);

    this->setMenuBar(mainMenu);
}

void MainWindow::createToolbar() {
    m_toolbar = new QToolBar(this);
    m_toolbar->setMovable(false);
    m_toolbar->addAction( m_newFileAction );
    m_toolbar->addAction( m_saveFileAction );
    m_toolbar->addSeparator();
    m_toolbar->addAction( m_openProjectAction );

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_toolbar->addWidget(spacer);

    QFont *font = new QFont();
    font->setBold(true);
    QLabel *label = new QLabel("KNodeIDE");
    label->setFont(*font);
    m_toolbar->addWidget(label);

    QWidget* spacer2 = new QWidget();
    spacer2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_toolbar->addWidget(spacer2);

    m_runConfig = new RunConfigurationsWidget(this);
    m_toolbar->addWidget(m_runConfig);

    this->addToolBar(Qt::TopToolBarArea, m_toolbar);
}

void MainWindow::createProjectExplorer()
{
    m_projectExplorer = new ProjectExplorer(this, "/home/paalgyula/wspace/tracker");

    QDockWidget *projectExplorerDock = new QDockWidget(tr("Project Explorer"), this);
    projectExplorerDock->setWidget( m_projectExplorer );

    connect(m_projectExplorer, SIGNAL(openFile(QFileInfo*)), this, SLOT(openFile(QFileInfo*)));

    this->addDockWidget(Qt::LeftDockWidgetArea, projectExplorerDock);
}

void MainWindow::newFile()
{
    qWarning() << "NewFile called!";
}

void MainWindow::tabChanged(int currentTab)
{
    CodeEditor *editor = (CodeEditor*)m_documentTabs->widget(currentTab);
    if ( editor != NULL )
        this->setWindowTitle(QString("%1%2 - %3").arg( editor->isModified() ? "*" : "", editor->documentName(), WINDOW_TITLE ) );
    else
        this->setWindowTitle(WINDOW_TITLE);
}

void MainWindow::openFile(QFileInfo *info)
{
    CodeEditor *editor = new CodeEditor(this);
    editor->setDocument(new QFile(info->absoluteFilePath()));
    QIcon icon = NodeIDE::getIconForFile(info);

    int tabIndex = -1;
    if ( icon.isNull() )
        tabIndex = m_documentTabs->addTab( editor, info->fileName() );
    else
        tabIndex = m_documentTabs->addTab( editor, icon, info->fileName() );

    m_documentTabs->setCurrentIndex( tabIndex );
}

void MainWindow::closeFile(int tabIndex)
{
    CodeEditor *editor = (CodeEditor*)(m_documentTabs->widget(tabIndex));
    if ( editor->requestClose() )
        m_documentTabs->removeTab( tabIndex );
}

void MainWindow::openProject()
{
#ifdef QT_DEBUG
    QString selectedDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home/paalgyula/wspace/tracker",
                                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
#else
    QString selectedDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "",
                                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
#endif
    // Cancel
    if (selectedDir.isEmpty())
        return;

    m_runConfig->clear();
    QFile *file = new QFile(QString("%1/package.json").arg(selectedDir));
    if ( file->exists() ) {
        file->open(QFile::ReadOnly);
        QByteArray fileContent = file->readAll();
        QJsonDocument doc = QJsonDocument::fromJson( fileContent );
        QJsonObject obj = doc.object();
        obj = obj["scripts"].toObject();

        foreach(QString key, obj.keys())
        {
            m_runConfig->addScript(key);
        }
    }

    m_projectExplorer->loadProjectDir(selectedDir);
}

void MainWindow::closeCurrentTab()
{
    qWarning() << "Editor close request";
    CodeEditor *editor = (CodeEditor*)m_documentTabs->currentWidget();
    if ( editor != NULL && editor->requestClose())
        m_documentTabs->removeTab( m_documentTabs->currentIndex() );
}
