#include "QCodeEditor.h"
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
#include <QDirIterator>
#include <QToolButton>
#include <QSettings>

#include <src/widgets/codeeditor.h>
#include <src/widgets/ProjectExplorer.h>
#include <src/widgets/runconfigurationswidget.h>

#include <src/mimetypehelper.h>

#define WINDOW_TITLE "NodeIDE - Paál Gyula (c) 2015"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowIcon(QIcon(":/icons/logo.png"));
    this->setWindowTitle( WINDOW_TITLE );

    this->createMainMenu();
    this->createToolbar();
    this->createProjectExplorer();

    m_quickOpen = NULL;
    _projectFiles = new QStringList();
      
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
    connect(m_documentTabs, &QTabWidget::tabCloseRequested, this, &MainWindow::closeCurrentTab);
    // Tab close button handler
    connect(m_documentTabs, &QTabWidget::currentChanged, this, &MainWindow::tabChanged);

    this->setMinimumSize(QSize(700, 400));

    QSettings settings;
    QString lastProjectDir = settings.value("lastProjectDir").toString();
    if ( !lastProjectDir.isEmpty() )
    {
        openProject( lastProjectDir );
    }
}

MainWindow::~MainWindow()
{
}

/**
 * @brief MainWindow::createMainMenu
 * creates main menu
 */
void MainWindow::createMainMenu()
{
    QMenuBar *mainMenu = new QMenuBar(this);

    // File menu
    QMenu *fileMenu = new QMenu("&File", mainMenu);

    mainMenu->addMenu(fileMenu);
    m_actionNewFile = fileMenu->addAction( QIcon(":/icons/document_new.png"), tr("&New file..."), this, SLOT(newFile()));
    m_actionNewFile->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_N) );

    m_actionSaveFile = fileMenu->addAction( QIcon(":/icons/document_save.png"), tr("&Save file"), this, SLOT(saveFile()));
    m_actionSaveFile->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_S) );

    m_actionOpenProject = fileMenu->addAction( QIcon(":/icons/document_open.png"), tr("Open project"), this, SLOT(openProject()));
    m_actionOpenProject->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_O) );

    fileMenu->addSeparator();
    fileMenu->addAction(tr("E&xit"), this, SLOT(close()), QKeySequence( Qt::ALT + Qt::Key_F4 ) );

    // Edit menu
    QMenu *editMenu = new QMenu(tr("Edit"), mainMenu);
    mainMenu->addMenu(editMenu);

    // Window menu
    QMenu *windowMenu = new QMenu(tr("Window"), mainMenu);
    mainMenu->addMenu(windowMenu);

    windowMenu->addAction("Close current tab", this, SLOT(closeCurrentTab()), QKeySequence( Qt::CTRL + Qt::Key_W ));
    m_actionQuickOpen = windowMenu->addAction( QIcon(":/icons/shock.png"), "Quick open file...", this, SLOT(showQuickOpenPopup()), QKeySequence( Qt::CTRL + Qt::Key_P ));

    // TODO: impelment a bugReport form
    QToolButton *bugButton = new QToolButton(this);
    bugButton->setFocusPolicy(Qt::ClickFocus);
    bugButton->setAutoRaise(true);
    bugButton->setIcon(QIcon(":/icons/bug.png"));

    mainMenu->setCornerWidget(bugButton);

    this->setMenuBar(mainMenu);
}

void MainWindow::createToolbar() {
    m_toolbar = new QToolBar(this);
    m_toolbar->setMovable(false);
    m_toolbar->addAction( m_actionNewFile );
    m_toolbar->addAction( m_actionSaveFile );
    m_toolbar->addSeparator();
    m_toolbar->addAction( m_actionOpenProject );
    m_toolbar->addAction( m_actionQuickOpen );

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_toolbar->addWidget(spacer);

    // Decoration :)
    QLabel *iconLabel = new QLabel("", this);
    iconLabel->setPixmap(QPixmap(":/icons/nodejs.png"));
    iconLabel->setFixedSize(QSize(32,32));

    QFont *font = new QFont();
    font->setBold(true);
    QLabel *label = new QLabel("NodeIDE");
    label->setFont(*font);

    m_toolbar->addWidget(iconLabel);
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
    projectExplorerDock->setTitleBarWidget(new QFrame(this));
    projectExplorerDock->setWidget( m_projectExplorer );

    connect(m_projectExplorer, SIGNAL(openFile(QFileInfo*)), this, SLOT(openFile(QFileInfo*)));
    connect(m_projectExplorer, SIGNAL(npmUpdateReqested()), this, SLOT(updatePackages()));

    this->addDockWidget(Qt::LeftDockWidgetArea, projectExplorerDock);

    // Console:
    m_console = new QCodeEditor(this);
    m_console->setReadOnly(true);
    QDockWidget *consoleDockWidget = new QDockWidget(tr("Console"), this);
    consoleDockWidget->setWidget( m_console );

    this->addDockWidget(Qt::BottomDockWidgetArea, consoleDockWidget);
}

void MainWindow::newFile()
{
    qWarning() << "NewFile called!";
}

void MainWindow::tabChanged(int currentTab)
{
    CodeEditor *editor = (CodeEditor*)m_documentTabs->widget(currentTab);
    if ( editor != NULL )
    {
        this->setWindowTitle(QString("%1%2 - %3").arg( editor->isModified() ? "*" : "", editor->documentName(), WINDOW_TITLE ) );
        editor->setFocus();
    } else
        this->setWindowTitle(WINDOW_TITLE);
}

void MainWindow::openFile(QFileInfo *info)
{
    for( int i=0; i<m_documentTabs->count(); i++ )
    {
        CodeEditor *editor = (CodeEditor*)m_documentTabs->widget(i);
        if ( editor->documentPath() == info->absoluteFilePath() )
        {
            m_documentTabs->setCurrentIndex(i);
            return;
        }
    }

    CodeEditor *editor = new CodeEditor(this);
    editor->loadFile(*info);
    QIcon icon = Tools::getInstance().getIconForFile(info);

    int tabIndex = -1;
    if ( icon.isNull() )
        tabIndex = m_documentTabs->addTab( editor, info->fileName() );
    else
        tabIndex = m_documentTabs->addTab( editor, icon, info->fileName() );

    connect(editor, SIGNAL(modificationChanged(bool, CodeEditor*)), this, SLOT(fileModificationChanged(bool, CodeEditor*)));

    m_documentTabs->setCurrentIndex( tabIndex );
    editor->setFocus();
}

void MainWindow::closeFile(int tabIndex)
{
    CodeEditor *editor = (CodeEditor*)(m_documentTabs->widget(tabIndex));
    if ( editor->requestClose() ) {
        m_documentTabs->removeTab( tabIndex );
        delete editor;
    }
}

void MainWindow::openProject(QString selectedDir)
{
    if ( selectedDir.isEmpty() )
    {
#ifdef QT_DEBUG
    selectedDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home/paalgyula/wspace/tracker",
                                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
#else
    selectedDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "",
                                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
#endif
    }
    // Cancel
    if (selectedDir.isEmpty())
        return;
    
    _workingDir = selectedDir;
    _projectFiles->clear();
    QDirIterator it(_workingDir, QStringList() << "*", QDir::Files | QDir::Hidden, QDirIterator::Subdirectories);
    while (it.hasNext()) {
      QString path = it.next().replace( _workingDir, "" );
      if ( path.startsWith("/node_modules/") ||
	path.startsWith("/public/bower_components/"))
	continue;
      
      *_projectFiles << path;
    }

    // HAX :D
    m_runConfig->clear();
    QFile *file = new QFile(QString("%1/package.json").arg(_workingDir));
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

    m_projectExplorer->loadProjectDir( _workingDir );
    QSettings settings;
    settings.setValue("lastProjectDir", _workingDir);
}

void MainWindow::closeCurrentTab()
{
    CodeEditor *editor = (CodeEditor*)m_documentTabs->currentWidget();
    if ( editor != NULL && editor->requestClose()) {
        m_documentTabs->removeTab( m_documentTabs->currentIndex() );
        editor->deleteLater();
    }
}

void MainWindow::fileModificationChanged(bool modified, CodeEditor* editor)
{
    int index = m_documentTabs->indexOf( editor );
    m_documentTabs->setTabText(index, QString("%1%2").arg(modified ? "*" : "", editor->documentName()));
    this->tabChanged(index);
}

void MainWindow::saveFile()
{
    CodeEditor *editor = (CodeEditor*)m_documentTabs->currentWidget();
    editor->save();
}
