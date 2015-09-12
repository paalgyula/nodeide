#ifndef DIRECTORYTREEWIDGETITEM_H
#define DIRECTORYTREEWIDGETITEM_H

#include <QFileInfoList>
#include <qtreewidget.h>

class DirectoryTreeWidgetItem : public QTreeWidgetItem
{
public:
    DirectoryTreeWidgetItem(QFileInfo info);
private:
    const QFileInfo m_info;
};

#endif // DIRECTORYTREEWIDGETITEM_H
