#include "npmstatusbar.h"

#include "src/mainwindow.h"

#include <QProcess>
#include <QVBoxLayout>
#include <QDebug>

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
    this->connect( _btnAdd, SIGNAL(released()), parentWidget(), SIGNAL(npmAddDependency()) );
    this->connect( _btnUpdate, SIGNAL(released()), parentWidget(), SIGNAL(npmUpdateReqested()) );
}

void NpmStatusbar::setProcessing(bool process)
{

}

void NpmStatusbar::setStatus(const QString status)
{

}

void MainWindow::updatePackages()
{
    QProcess *process = new QProcess(this);
    process->setProgram("npm");
    process->setWorkingDirectory( _workingDir );

    process->setArguments(QStringList() << "update");
    process->start(QProcess::ReadOnly);

    QObject::connect(process, &QProcess::readyRead, [process, this]() {
        m_console->appendPlainText( QString(process->readAll()) );
    });

    QObject::connect(process, &QProcess::stateChanged, [process, this](QProcess::ProcessState state) {
        if ( state == QProcess::NotRunning )
        {
            m_console->appendPlainText( "Process finished!\n" );
            process->deleteLater();
        }
    });
}

