//
// Created by w on 2022/12/22.
//

#ifndef STUDENTSYSTEM_READONLYDELEGATE_H
#define STUDENTSYSTEM_READONLYDELEGATE_H

#include "QItemDelegate"

class ReadOnlyDelegate : public QItemDelegate {

public:
    ReadOnlyDelegate(QWidget *parent = NULL) : QItemDelegate(parent) {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override //final
    {
        Q_UNUSED(parent)
        Q_UNUSED(option)
        Q_UNUSED(index)
        return NULL;
    }
};

#endif //STUDENTSYSTEM_READONLYDELEGATE_H
