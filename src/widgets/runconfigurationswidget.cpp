#include "runconfigurationswidget.h"

#include <QVBoxLayout>

RunConfigurationsWidget::RunConfigurationsWidget(QWidget *parent) : QWidget(parent)
{
    _comboConfigSelect = new QComboBox(this);
    _comboConfigSelect->setFixedWidth(100);
    _comboConfigSelect->setFocusPolicy(Qt::ClickFocus);

    _btnStart = new QPushButton(this);
    _btnStop = new QPushButton(this);

    QSize iconSize = QSize(20, 20);

    _btnStop->setIconSize(iconSize);
    _btnStart->setIconSize(iconSize);

    _btnStop->setFixedSize(32, 32);
    _btnStart->setFixedSize(32, 32);

    _btnStop->setFlat(true);
    _btnStart->setFlat(true);

    _btnStop->setIcon(QIcon(":/icons/stop.png"));
    _btnStart->setIcon(QIcon(":/icons/play.png"));

    _btnStop->setEnabled(false);
    _btnStart->setEnabled(false);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(_comboConfigSelect);
    layout->addWidget(_btnStart);
    layout->addWidget(_btnStop);
    layout->setSpacing(0);
    layout->setMargin(0);

    this->setLayout(layout);

    this->clear();
}

void RunConfigurationsWidget::clear()
{
    for (int i=_comboConfigSelect->count();i<0;i--)
    {
        _comboConfigSelect->removeItem(0);
    }

    _comboConfigSelect->setEnabled(false);
}

void RunConfigurationsWidget::addScript(const QString script)
{
    _comboConfigSelect->addItem(script);
    if ( !_comboConfigSelect->isEnabled() ) {
        _comboConfigSelect->setEnabled(true);
        _btnStart->setEnabled(true);
    }
}

void RunConfigurationsWidget::start()
{

}
