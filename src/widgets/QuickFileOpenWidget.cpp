#include <src/mainwindow.h>

#include <QVBoxLayout>
#include <QLineEdit>

#include "QuickFileOpenWidget.h"

QuickFileOpenWidget::QuickFileOpenWidget(QWidget *parent) : QFrame(parent)
{
  QVBoxLayout *layout = new QVBoxLayout();
  layout->setSpacing(0);
  layout->setMargin(0);
  
  QLineEdit *finder = new QLineEdit(this);
  finder->setMinimumWidth( 250 );
  
  m_fileListWidget = new QListWidget(this);
  
  layout->addWidget(finder);
  layout->addWidget(m_fileListWidget);
  layout->addWidget( new QPushButton("Anyad", this ) );
  
  this->setLayout(layout);
  this->setFixedSize(QSize(400,250));
  this->setAutoFillBackground(true);
  finder->setFocus();
  
}

void QuickFileOpenWidget::setFileList(const QStringList fileList)
{
  m_fileListWidget->clear();
  m_fileListWidget->addItems(fileList);
}

void MainWindow::showQuickOpenPopup()
{
  if ( m_quickOpen )
    m_quickOpen->deleteLater();
  
  m_quickOpen = new QuickFileOpenWidget(this);
  m_quickOpen->move(QPoint(40, 40));
  m_quickOpen->setFileList(*_projectFiles);
  m_quickOpen->show();
}
