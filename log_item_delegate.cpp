#include "log_item_delegate.h"

#include <QPainter>

LogItemDelegate::LogItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

void LogItemDelegate::paint(QPainter *painter,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index) const {
    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, QColor(236, 226, 192));
    else
        painter->fillRect(option.rect, QColor(206, 176, 84));

    QPoint pos = (option.rect.topLeft() + option.rect.bottomLeft()) / 2;
    QString txt = index.data(Qt::DisplayRole).toString();

    QFont font("Microsoft YAHEI", 9);
    QFontMetrics fm(font);
    int h = fm.xHeight();
    pos += QPoint(0, h / 2);

    painter->setFont(font);
    painter->drawText(pos, txt);
}

QSize LogItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                const QModelIndex &index) const {
    return QSize(0, 32);
}