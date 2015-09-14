#ifndef QUICKFILEOPENWIDGET_H
#define QUICKFILEOPENWIDGET_H

#include <QFrame>
#include <QPoint>
#include <QStringList>
#include <QListView>
#include <QStandardItemModel>

class QuickFileOpenWidget : public QFrame
{
public:
  QuickFileOpenWidget(QWidget *parent = 0);
  void setPosition( QPoint position );
  void setFileList( const QStringList fileList );
private:
  QStringList *m_listFile;
  QListView *m_fileListView;
  QStandardItemModel *m_model;
};

#endif // QUICKFILEOPENWIDGET_H
