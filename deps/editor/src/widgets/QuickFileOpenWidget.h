#ifndef QUICKFILEOPENWIDGET_H
#define QUICKFILEOPENWIDGET_H

#include <QFrame>
#include <QPoint>
#include <QStringList>
#include <QListView>
#include <QStandardItemModel>
#include <QLineEdit>

class QuickFileOpenWidget : public QFrame
{
public:
  QuickFileOpenWidget(QWidget *parent = 0);
  void setPosition( QPoint position );
  void setFileList( QStringList fileList );
public slots:
  void filterChanged(QString text);
private:
  QStringList *m_listFile;
  QLineEdit *m_finder;
  QListView *m_fileListView;
  QStandardItemModel *m_model;
};

#endif // QUICKFILEOPENWIDGET_H
