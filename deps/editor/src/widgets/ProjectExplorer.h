#ifndef PROJECTEXPLORER_H
#define PROJECTEXPLORER_H

#include "npmstatusbar.h"

#include <QTreeWidget>
#include <QWidget>
#include <QFileInfo>
#include <QMimeDatabase>
#include <src/mimetypehelper.h>

class ProjectExplorer : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectExplorer(QWidget *parent = 0, QString projectDirectory = "");
    void loadProjectDir(const QString projectDirectory);
private:
    QTreeWidget *m_tree;
    QString m_projectDir;
    NpmStatusbar *m_statusbar;

signals:
    void openFile(QFileInfo *fileInfo);
    void npmUpdateReqested();
    void npmAddDependency();

public slots:
    void itemClicked(QTreeWidgetItem* item, int index);
private slots:
    void expanded(QTreeWidgetItem *widgetItem);
};

#endif // PROJECTEXPLORER_H
