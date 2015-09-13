#include "npmstatusbar.h"

#include <QVBoxLayout>

NpmStatusbar::NpmStatusbar(QWidget *parent) : QFrame(parent)
{
    QSize iconSize(20, 20);
    QSize buttonSize(24, 24);

    _btnAdd = new QPushButton(this);
    _btnAdd->setFlat(true);
    _btnAdd->setIconSize(iconSize);
    _btnAdd->setFixedSize(buttonSize);
    _btnAdd->setIcon(QIcon(":/icons/npm_add.png"));

    _btnUpdate = new QPushButton(this);
    _btnUpdate->setFlat(true);
    _btnUpdate->setIconSize(iconSize);
    _btnUpdate->setFixedSize(buttonSize);
    _btnUpdate->setIcon(QIcon(":/icons/npm_update.png"));

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->addStretch();
    layout->addWidget( _btnAdd );
    layout->addWidget( _btnUpdate );

    this->setLayout( layout );
    this->connect( _btnAdd, SIGNAL(released()), this, SIGNAL(npmAddDependency()) );
    this->connect( _btnUpdate, SIGNAL(released()), this, SIGNAL(npmUpdateReqested()) );
}

void NpmStatusbar::setProcessing(bool process)
{

}

void NpmStatusbar::setStatus(const QString status)
{

}

