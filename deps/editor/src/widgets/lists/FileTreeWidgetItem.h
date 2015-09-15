#ifndef FILETREEWIDGETITEM_H
#define FILETREEWIDGETITEM_H

#include <QFileInfo>
#include <QTreeWidgetItem>

class FileTreeWidgetItem : public QTreeWidgetItem
{
public:
    FileTreeWidgetItem(const QFileInfo info);
private:
    const QFileInfo _info;
};

#endif // FILETREEWIDGETITEM_H
