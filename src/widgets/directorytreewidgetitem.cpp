#include "directorytreewidgetitem.h"

#include <QDir>
#include <QFileInfoList>
#include <QDebug>

#include <src/widgets/lists/FileTreeWidgetItem.h>

DirectoryTreeWidgetItem::DirectoryTreeWidgetItem(QFileInfo info) :
    QTreeWidgetItem(UserType),
    m_info(info)
{
    QString name(m_info.baseName().toLower());
  
    setIcon(0, QIcon(":/icons/folder.png"));
    setText(0, name);
    setExpanded(false);
    setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

    if ( name == "bin" )
    {
        setIcon(0, QIcon(":/icons/terminal.png"));
    } 
    else if ( name == "views" )
    {
        setIcon(0, QIcon(":/icons/bird.png"));
    }
    else if ( name == "models" )
    {
        setIcon(0, QIcon(":/icons/database.png"));
    }
    else if ( name == "public" )
    {
        setIcon(0, QIcon(":/icons/globe.png"));
    }
    else if ( name == "routes" )
    {
        setIcon(0, QIcon(":/icons/route.png"));
    }
    else if ( name == "test" || name == "tests" )
    {
        setIcon(0, QIcon(":/icons/tick.png"));
    }
    else if ( name == "node_modules" )
    {
        setIcon(0, QIcon(":/icons/npm_128.png"));
    }
}

void DirectoryTreeWidgetItem::reload()
{
    foreach (QTreeWidgetItem* widget, takeChildren())
    {
        this->removeChild(widget);
        delete widget;
    }

    QDir actualDir = QDir(m_info.absoluteFilePath());
    QFileInfoList files = actualDir.entryInfoList(QDir::NoFilter, QDir::DirsFirst);

    for (int i = 0; i < files.size(); ++i) {
        QFileInfo fileInfo = files.at(i);

        if ( fileInfo.isDir() )
        {
            // If not parent :)
            if ( fileInfo.fileName() != "." && fileInfo.fileName() != ".." )
                this->addChild( new DirectoryTreeWidgetItem(fileInfo) );
        }
        else
            this->addChild(new FileTreeWidgetItem(fileInfo));
    }
}

