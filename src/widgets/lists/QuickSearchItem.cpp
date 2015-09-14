#include "QuickSearchItem.h"
#include <QApplication>
#include <QPainter>
#include <src/mimetypehelper.h>

QuickSearchItem::QuickSearchItem(QWidget *parent) : QStyledItemDelegate(parent)
{
    //m_font()
}

void QuickSearchItem::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyleOptionViewItemV4 opt = option;
    initStyleOption(&opt, index);

    QString fileName = index.model()->data(index.model()->index(index.row(), 0)).toString();
    QIcon icon = qvariant_cast<QIcon>(index.model()->data(index.model()->index(index.row(), 1)));

    QRect rect = opt.rect;

    // draw correct background
    opt.text = "";
    QStyle *style = opt.widget ? opt.widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, opt.widget);

/*    QPalette::ColorGroup cg = opt.state & QStyle::State_Enabled ? QPalette::Normal : QPalette::Disabled;
    if (cg == QPalette::Normal && !(opt.state & QStyle::State_Active))
        cg = QPalette::Inactive;

    // set pen color
    if (opt.state & QStyle::State_Selected)
        painter->setPen(opt.palette.color(cg, QPalette::HighlightedText));
    else
        painter->setPen(opt.palette.color(cg, QPalette::Text));*/

    QFont font = Tools::getInstance().defaultFont();
    painter->setFont(font);

    QFontMetrics metric(font);
    int width = metric.width( fileName );

    // draw 2 lines of text
    /*painter->drawText(QRect(rect.left() + rect.height() + 5, rect.top() + 2, rect.width(), rect.height()/2),
                      opt.displayAlignment, line0);
    painter->drawText(QRect(rect.left() + rect.height() + 5, rect.top()+rect.height()/2, rect.width(), rect.height()/2),
                      opt.displayAlignment, line1);*/

    painter->drawText(QRect(rect.left() + rect.height() + 5,
                            rect.top(),
                            rect.left() + rect.height() + 5 + width,
                            rect.height()),
                          opt.displayAlignment, fileName);

    painter->drawText(QRect(rect.left() + rect.height() + 5 + width,
                            rect.top(),
                            rect.width(),
                            rect.height()),
                          opt.displayAlignment, "line0");

    painter->drawPixmap(rect.left() + 2, rect.top() + 2, icon.pixmap(QSize(24,24)).scaled(QSize(rect.height()-4,rect.height()-4)));
}

QSize QuickSearchItem::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QSize result = QStyledItemDelegate::sizeHint(option, index);
    result.setHeight( 30 );
    return result;
}
