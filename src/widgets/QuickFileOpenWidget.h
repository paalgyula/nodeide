#ifndef QUICKFILEOPENWIDGET_H
#define QUICKFILEOPENWIDGET_H

#include <QFrame>
#include <QPoint>
#include <QStringList>
#include <QListWidget>

class QuickFileOpenWidget : public QFrame
{
public:
  QuickFileOpenWidget(QWidget *parent = 0);
  void setPosition( QPoint position );
  void setFileList( const QStringList fileList );
private:
  QListWidget *m_fileListWidget;
};

#endif // QUICKFILEOPENWIDGET_H
