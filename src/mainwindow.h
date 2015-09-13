#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMimeDatabase>
#include <QToolBar>

#include <src/widgets/codeeditor.h>
#include <src/widgets/projectexplorer.h>
#include <src/widgets/runconfigurationswidget.h>
#include <src/widgets/QuickFileOpenWidget.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    // Actions
    QAction *m_newFileAction;
    QAction *m_saveFileAction;
    QAction *m_openProjectAction;
    
    QuickFileOpenWidget *m_quickOpen;

    QTabWidget *m_documentTabs;

    QToolBar *m_toolbar;
    ProjectExplorer *m_projectExplorer;
    RunConfigurationsWidget *m_runConfig;

    void createMainMenu();
    void createToolbar();
    void createProjectExplorer();

    QStringList *_projectFiles;
    QString _workingDir;
    
public slots:
    void newFile();
    void openFile(QFileInfo *info);
    void closeFile(int tabIndex);
    void openProject();
    void tabChanged(int currentTab);
    void closeCurrentTab();
    void saveFile();

    void updatePackages();
private slots:
    void fileModificationChanged(bool modified, CodeEditor *editor);    
    void showQuickOpenPopup();
};

#endif // MAINWINDOW_H
