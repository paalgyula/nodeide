#ifndef STDAFX_H
#define STDAFX_H

#if defined __cplusplus

#include <QCompleter>
#include <QLineEdit>
#include <QDockWidget>
#include <QTextEdit>
#include <QMenuBar>
#include <QPushButton>
#include <QSpacerItem>
#include <QComboBox>
#include <QScrollArea>
#include <QStatusBar>
#include <QDebug>
#include <QFileInfo>
#include <QLabel>
#include <QVBoxLayout>
#include <QFileIconProvider>
#include <QMimeData>
#include <QMimeDatabase>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileDialog>
#include <QDirIterator>
#include <QToolButton>
#include <QSettings>

#include <src/widgets/codeeditor.h>
#include <src/widgets/ProjectExplorer.h>
#include <src/widgets/runconfigurationswidget.h>
#include <src/widgets/directorytreewidgetitem.h>
#include <src/widgets/npmstatusbar.h>
#include <src/widgets/QuickFileOpenWidget.h>
#include <src/widgets/lists/FileTreeWidgetItem.h>
#include <src/widgets/lists/QuickSearchItem.h>

#include <src/caretpositionwidget.h>
#include <src/linenumberwidget.h>

#include <src/QCodeEditor.h>
#include <src/mainwindow.h>
#include <src/mimetypehelper.h>

// Highlighters
#include <src/highlighter/NodeHighlighter.h>

#include <src/highlighter/JavaScriptHighlight.h>
#include <src/highlighter/JadeHighlight.h>

#endif

#endif // STDAFX_H

