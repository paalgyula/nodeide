#include "runconfigurationswidget.h"

#include <QVBoxLayout>
#include <QDebug>

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

    connect(_btnStart, &QPushButton::clicked, this, &RunConfigurationsWidget::startRequest);
    connect(_btnStop, &QPushButton::clicked, this, &RunConfigurationsWidget::startRequest);

    this->setStatus(NotRunning);

    this->setLayout(layout);
    this->clear();
}

void RunConfigurationsWidget::clear()
{
    _comboConfigSelect->clear();
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

void RunConfigurationsWidget::setStatus(ExecutionStatus status)
{
    this->_status = status;

    if ( _comboConfigSelect->count() > 0 )
    {
        if ( this->_status == Running ) {
            _btnStart->setEnabled(false);
            _btnStop->setEnabled(true);
        }
        else
        {
            _btnStart->setEnabled(true);
            _btnStop->setEnabled(false);
        }
    }
}

const QString RunConfigurationsWidget::script()
{
    return _comboConfigSelect->currentText();
}
