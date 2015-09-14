#include "ProjectExplorer.h"

#include "directorytreewidgetitem.h"

#include <QDirModel>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDirIterator>
#include <QFileInfoList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include <src/widgets/lists/FileTreeWidgetItem.h>

ProjectExplorer::ProjectExplorer(QWidget *parent, QString projectDirectory) : QWidget(parent), m_projectDir(projectDirectory)
{
    m_tree = new QTreeWidget(this);
    m_tree->setHeaderHidden(true);

    m_statusbar = new NpmStatusbar(this);

    connect( m_tree, SIGNAL(itemActivated(QTreeWidgetItem*,int)), this, SLOT(itemClicked(QTreeWidgetItem*,int)) );

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(2);
    layout->setSpacing(0);
    this->setLayout(layout);

    layout->addWidget( m_tree );
    layout->addWidget( m_statusbar );
}

void ProjectExplorer::itemClicked(QTreeWidgetItem *item, int index)
{
    Q_UNUSED(index)

    QFileInfo *info = new QFileInfo( item->whatsThis(0) );

    if ( info->isFile() )
        emit openFile( info );
}

void ProjectExplorer::loadProjectDir(const QString projectDirectory)
{
    m_projectDir = projectDirectory;
    m_tree->clear();

    QFileInfo rootInfo(projectDirectory);
    DirectoryTreeWidgetItem *root = new DirectoryTreeWidgetItem(rootInfo);
    root->setText(0, QString("Project - %1").arg(rootInfo.fileName()) );
    root->setIcon(0, QIcon(":/icons/nodejs.png"));

    m_tree->addTopLevelItem( root );
    m_tree->setRootIsDecorated(false);
    root->reload();
    root->setExpanded(true);

    connect(m_tree, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(expanded(QTreeWidgetItem*)));
}

void ProjectExplorer::expanded(QTreeWidgetItem *widgetItem)
{
    DirectoryTreeWidgetItem *item = (DirectoryTreeWidgetItem*)widgetItem;
    item->reload();
}
