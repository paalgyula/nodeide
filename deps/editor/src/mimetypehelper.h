#ifndef MIMETYPEHELPER
#define MIMETYPEHELPER

#include <QFile>
#include <QFileIconProvider>
#include <QIcon>
#include <QMimeDatabase>

class Tools
{
private:
    Tools()
    {
    }

public:
    static Tools &getInstance()
    {
          static Tools INSTANCE;
          return INSTANCE;
    }

    QIcon getIconForFile(const QFileInfo *info)
    {
        QIcon mimeIcon;

#ifdef __linux__
        QMimeDatabase db;
        QMimeType type = db.mimeTypeForFile(info->fileName());

        QString filePath = QString("/usr/share/icons/oxygen/16x16/mimetypes/%1.png")
                .arg(type.name()
                     .replace("/", "-"));
        QFile iconFile(filePath);
        if ( !iconFile.exists() )
            mimeIcon = QIcon();
        else
            mimeIcon = QIcon(iconFile.fileName());
#else
        QFileIconProvider *provider = new QFileIconProvider();
        mimeIcon = provider->icon(*info);

        //mimeIcon = QIcon(":/icons/mime/text.png");
#endif

        // Override :D
        QString icon = "";
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

        if ( icon != "" )
            mimeIcon = QIcon(QString(":/icons/mime/%1.png").arg(icon));

        return mimeIcon;
    }

    const QFont monoFont() {
        QFont font;
#ifdef _WIN32
        font.setFamily("Courier");
#else
        font.setFamily("Monospace");
#endif
        font.setFixedPitch(true);
        font.setStyleHint(QFont::Monospace);
        font.setPointSize(10);

        return font;
    }

    const QFont defaultFont() {
        QFont font;
        return font;
    }
};

#endif // MIMETYPEHELPER
