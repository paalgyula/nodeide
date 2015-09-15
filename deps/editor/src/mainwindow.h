#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMimeDatabase>
#include <QToolBar>

#include <src/widgets/codeeditor.h>
#include <src/widgets/ProjectExplorer.h>
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
    QAction *m_actionNewFile;
    QAction *m_actionSaveFile;
    QAction *m_actionOpenProject;
    QAction *m_actionQuickOpen;
    
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
    void openProject(QString selectedDir = "");
    void tabChanged(int currentTab);
    void closeCurrentTab();
    void saveFile();

    void updatePackages();
private slots:
    void fileModificationChanged(bool modified, CodeEditor *editor);    
    void showQuickOpenPopup();
};

#endif // MAINWINDOW_H
