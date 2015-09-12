#ifndef MIMETYPEHELPER
#define MIMETYPEHELPER

#include <QFile>
#include <QIcon>
#include <QMimeDatabase>

namespace NodeIDE {
    static QIcon getIconForFile(QFileInfo *info)
    {
        QMimeDatabase db;
        QMimeType type = db.mimeTypeForFile(info->fileName());

        QIcon mimeIcon;

#ifdef __linux__
        QString filePath = QString("/usr/share/icons/oxygen/16x16/mimetypes/%1.png")
                .arg(type.name()
                     .replace("/", "-"));
        QFile iconFile(filePath);
        if ( !iconFile.exists() )
            mimeIcon = QIcon();
        else
            mimeIcon = QIcon(iconFile.fileName());
#else
        mimeIcon = QIcon(":/icons/mime/text.png");
#endif

        if ( mimeIcon.isNull() ) {
            QString icon = "text";
            QString suffix = info->suffix().toLower().trimmed();
            if ( suffix == "json" )
                icon = "json";
            else if (suffix == "js")
                icon = "javascript";
            else if (suffix == "jade")
                icon = "jade";
            else if (suffix == "htm")
                icon = "html";
            else if (suffix == "html")
                icon = "html";

            mimeIcon = QIcon(QString(":/icons/mime/%1.png").arg(icon));
        }

        return mimeIcon;
    }
}

#endif // MIMETYPEHELPER

