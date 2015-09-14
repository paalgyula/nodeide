#include "FileTreeWidgetItem.h"

#include <src/mimetypehelper.h>

FileTreeWidgetItem::FileTreeWidgetItem(const QFileInfo info) :
    QTreeWidgetItem(UserType),
    _info(info)
{
    this->setText(0, info.fileName() );
    this->setWhatsThis(0, info.absoluteFilePath());
    this->setIcon(0, Tools::getInstance().getIconForFile(&_info));
}

