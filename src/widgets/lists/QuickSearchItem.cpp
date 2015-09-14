#include "QuickSearchItem.h"
#include <QApplication>
#include <QPainter>
#include <src/mimetypehelper.h>
#include <QDebug>

QuickSearchItem::QuickSearchItem(QWidget *parent) : QStyledItemDelegate(parent)
{
    //m_font()
}

void QuickSearchItem::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyleOptionViewItemV4 opt = option;
    initStyleOption(&opt, index);

    QString fileName = index.model()->data(index.model()->index(index.row(), 0)).toString();
    QString filterText = index.model()->data(index.model()->index(index.row(), 2)).toString();
    QIcon icon = qvariant_cast<QIcon>(index.model()->data(index.model()->index(index.row(), 1)));

    QRect rect = opt.rect;

    // draw correct background
    opt.text = "";
    QStyle *style = opt.widget ? opt.widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, opt.widget);

    QPalette::ColorGroup cg = opt.state & QStyle::State_Enabled ? QPalette::Normal : QPalette::Disabled;
    if (cg == QPalette::Normal && !(opt.state & QStyle::State_Active))
        cg = QPalette::Inactive;

    // set pen color
    if (opt.state & QStyle::State_Selected)
        painter->setPen(opt.palette.color(cg, QPalette::HighlightedText));
    else
        painter->setPen(opt.palette.color(cg, QPalette::Text));

    QFont font = Tools::getInstance().defaultFont();
    painter->setFont(font);

    QString filePart1, filePart2;
    filePart1 = fileName.left( fileName.indexOf(filterText) );
    filePart2 = fileName.right( fileName.length() - filterText.length() - filePart1.length() );

    QFontMetrics metric(font);
    int part1width = metric.width( filePart1 );

    QFont boldFont = Tools::getInstance().defaultFont();
    boldFont.setBold(true);
    QFontMetrics metricBold(boldFont);
    int boldWidth = metricBold.width( filterText );

    int leftPadding = 24;

    painter->drawText(QRect(rect.left() + leftPadding,
                            rect.top(),
                            rect.width(),
                            rect.height()),
                          opt.displayAlignment, filePart1);

    painter->setFont(boldFont);
    painter->drawText(QRect(rect.left() + leftPadding + part1width,
                            rect.top(),
                            rect.width(),
                            rect.height()),
                          opt.displayAlignment, filterText);

    painter->setFont(font);
    painter->drawText(QRect(rect.left() + leftPadding + part1width + boldWidth,
                            rect.top(),
                            rect.width(),
                            rect.height()),
                          opt.displayAlignment, filePart2);

    if ( !icon.isNull() )
    {
        QPixmap pixmap = icon.pixmap(QSize(24,24)).scaled(16, 16,  Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        painter->drawPixmap(rect.left() + 2, rect.top() + 2, pixmap);
    }
}

QSize QuickSearchItem::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QSize result = QStyledItemDelegate::sizeHint(option, index);
    result.setHeight( 20 );
    return result;
}
