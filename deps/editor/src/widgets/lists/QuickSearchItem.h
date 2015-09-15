#ifndef QUICKSEARCHITEM_H
#define QUICKSEARCHITEM_H

#include <QStyledItemDelegate>

class QuickSearchItem : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit QuickSearchItem(QWidget *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
signals:

public slots:
};

#endif // QUICKSEARCHITEM_H
