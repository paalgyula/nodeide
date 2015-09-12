#include "directorytreewidgetitem.h"

DirectoryTreeWidgetItem::DirectoryTreeWidgetItem(QFileInfo info) :
    QTreeWidgetItem(UserType),
    m_info(info)
{
    setIcon(0, QIcon(":/icons/folder.png"));
    setText(0, m_info.baseName());
    setExpanded(false);

    if ( m_info.baseName().toLower() == "bin" )
    {
        setIcon(0, QIcon(":/icons/terminal.png"));
    }
}

