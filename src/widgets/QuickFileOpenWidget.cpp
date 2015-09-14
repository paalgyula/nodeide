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
  
  QLineEdit *finder = new QLineEdit(this);
  finder->setMinimumWidth( 250 );
  
  m_fileListView = new QListView(this);
  m_fileListView->viewport()->setAutoFillBackground(true);
  m_fileListView->setItemDelegate(new QuickSearchItem(m_fileListView));

  m_model = new QStandardItemModel(this);
  m_fileListView->setModel(m_model);

  layout->addWidget(finder);
  layout->addWidget(m_fileListView);

  this->setLayout(layout);
  this->setFixedSize(QSize(400,250));
  this->setAutoFillBackground(false);
  finder->setFocus();
}

void QuickFileOpenWidget::setFileList(const QStringList fileList)
{
    //m_model = new QStandardItemModel(this);
    m_model->clear();
    m_model->setColumnCount(2);
    m_model->setRowCount(fileList.count());

    for(int row = 0; row < fileList.count(); row++)
    {
        QString fileName = fileList.at(row);
        QFileInfo *info = new QFileInfo(fileName);

        QIcon icon = Tools::getInstance().getIconForFile(info);

        m_model->setData(m_model->index(row, 0), fileList.at(row));
        m_model->setData(m_model->index(row, 1), icon);
    }
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
