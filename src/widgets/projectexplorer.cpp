#include "directorytreewidgetitem.h"
#include "projectexplorer.h"

#include <QDirModel>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDirIterator>
#include <QFileInfoList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

ProjectExplorer::ProjectExplorer(QWidget *parent, QString projectDirectory) : QWidget(parent), m_projectDir(projectDirectory)
{
    m_tree = new QTreeWidget(this);
    m_tree->setHeaderHidden(true);

    connect( m_tree, SIGNAL(itemActivated(QTreeWidgetItem*,int)), this, SLOT(itemClicked(QTreeWidgetItem*,int)) );

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(2);
    layout->setSpacing(0);
    this->setLayout(layout);

    layout->addWidget( m_tree );
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
    m_tree->clear();

    QTreeWidgetItem *root = new QTreeWidgetItem(0);
    root->setText(0, "Project root");
    root->setIcon(0, QIcon(":/icons/nodejs.png"));

    m_tree->addTopLevelItem( root );
    m_tree->setRootIsDecorated(false);

    m_projectDir = projectDirectory;
    QDir *projectDir = new QDir(m_projectDir);
    QFileInfoList files = projectDir->entryInfoList(QDir::NoFilter, QDir::DirsFirst);

    for (int i = 0; i < files.size(); ++i) {
        QFileInfo info = files.at(i);

        if ( info.isDir() )
        {
            if ( info.fileName() != "." && info.fileName() != ".." )
                root->addChild( new DirectoryTreeWidgetItem(info) );
        }
        else
        {
            QTreeWidgetItem *item = new QTreeWidgetItem(0);
            item->setText(0, info.fileName() );
            item->setWhatsThis(0, info.absoluteFilePath());
            root->addChild(item);

            item->setIcon(0, NodeIDE::getIconForFile(&info));
        }
    }

    root->setExpanded(true);
}
