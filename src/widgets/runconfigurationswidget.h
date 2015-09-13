#ifndef RUNCONFIGURATIONSWIDGET_H
#define RUNCONFIGURATIONSWIDGET_H

#include <QComboBox>
#include <QPushButton>
#include <QWidget>

class RunConfigurationsWidget : public QWidget
{
    Q_OBJECT
public:
    enum ExecutionStatus {
        Running,
        NotRunning
    };

    explicit RunConfigurationsWidget(QWidget *parent = 0);
    void addScript(const QString script);
    void clear();
    const QString script();
    void setStatus(ExecutionStatus status);
private:
    QComboBox *_comboConfigSelect;
    QPushButton *_btnStop;
    QPushButton *_btnStart;

    ExecutionStatus _status;
signals:
    void startRequest();
    void stopRequest();

public slots:
private slots:
};

#endif // RUNCONFIGURATIONSWIDGET_H
