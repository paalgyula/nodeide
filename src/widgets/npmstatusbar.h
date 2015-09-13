#ifndef NPMSTATUSBAR_H
#define NPMSTATUSBAR_H

#include <QFrame>
#include <QProgressBar>
#include <QPushButton>

class NpmStatusbar : public QFrame
{
    Q_OBJECT
public:
    explicit NpmStatusbar(QWidget *parent = 0);
    void setProcessing(bool process);
    void setStatus(const QString status);
private:
    QPushButton *_btnUpdate;
    QPushButton *_btnAdd;
    QProgressBar *_progressBar;
public slots:
};

#endif // NPMSTATUSBAR_H
