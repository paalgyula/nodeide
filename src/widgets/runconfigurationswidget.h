#ifndef RUNCONFIGURATIONSWIDGET_H
#define RUNCONFIGURATIONSWIDGET_H

#include <QComboBox>
#include <QPushButton>
#include <QWidget>

class RunConfigurationsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RunConfigurationsWidget(QWidget *parent = 0);
    void addScript(const QString script);
    void clear();
private:
    QComboBox *_comboConfigSelect;
    QPushButton *_btnStop;
    QPushButton *_btnStart;
signals:

public slots:
private slots:
    void start();
};

#endif // RUNCONFIGURATIONSWIDGET_H
