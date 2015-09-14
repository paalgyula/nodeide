#include <src/mainwindow.h>

#include <QVBoxLayout>
#include <QLineEdit>
#include <QDebug>
#include <QDialog>
#include <src/widgets/lists/QuickSearchItem.h>

#include "QuickFileOpenWidget.h"

QuickFileOpenWidget::QuickFileOpenWidget(QWidget *parent) : QFrame(parent)
{
  QVBoxLayout *layout = new QVBoxLayout();
  layout->setSpacing(0);
  layout->setMargin(0);
  
  m_finder = new QLineEdit(this);
  m_finder->setMinimumWidth( 250 );
  
  m_fileListView = new QListView(this);
  m_fileListView->viewport()->setAutoFillBackground(true);
  m_fileListView->setItemDelegate(new QuickSearchItem(m_fileListView));

  m_model = new QStandardItemModel(this);
  m_fileListView->setModel(m_model);

  layout->addWidget(m_finder);
  layout->addWidget(m_fileListView);

  this->setLayout(layout);
  this->setFixedSize(QSize(400,250));
  this->setAutoFillBackground(false);
  m_finder->setFocus();

  connect( m_finder, &QLineEdit::textChanged, this, &QuickFileOpenWidget::filterChanged);
}

void QuickFileOpenWidget::filterChanged(QString filterText)
{
    m_model->clear();
    m_model->setColumnCount(3);

    QStringList matchList;

    for (int i=0; i<m_listFile->count(); i++ )
    {
        QString filepath = m_listFile->at(i);
        if ( filepath.contains(filterText, Qt::CaseInsensitive) )
        {
            matchList << filepath;
        }
    }

    m_model->setRowCount(matchList.size() < 10 ? matchList.size() : 10);

    for(int row = 0; row < matchList.count(); row++)
    {
        QString fileName = matchList.at(row);
        QFileInfo *info = new QFileInfo(fileName);

        QIcon icon = Tools::getInstance().getIconForFile(info);

        m_model->setData(m_model->index(row, 0), fileName);
        m_model->setData(m_model->index(row, 1), icon);
        m_model->setData(m_model->index(row, 2), filterText);
    }

    m_fileListView->setCurrentIndex(m_model->index(0,0));
}

void QuickFileOpenWidget::setFileList(QStringList fileList)
{
    m_listFile = &fileList;
    m_finder->setText("");
    filterChanged("");
}

void MainWindow::showQuickOpenPopup()
{
  if ( m_quickOpen )
    m_quickOpen->deleteLater();

  QDialog *dialog = new QDialog(this);
  dialog->setWindowIcon( QIcon(":/icons/shock.png") );
  dialog->setWindowTitle(tr("Quick open.."));
  
  m_quickOpen = new QuickFileOpenWidget(dialog);
  //m_quickOpen->move(QPoint(40, 40));
  m_quickOpen->setFileList(*_projectFiles);

  QHBoxLayout *layout = new QHBoxLayout();
  layout->setMargin(0);
  layout->setSpacing(2);
  layout->addWidget(m_quickOpen);

  dialog->setLayout(layout);
  dialog->exec();
}
