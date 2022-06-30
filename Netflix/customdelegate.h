#pragma once
#include "filmmodel.h"
#include "genresmodel.h"
#include "multiselectcombobox.h"
#include <QColor>
#include <QComboBox>
#include <QIntValidator>
#include <QLineEdit>
#include <QPainter>
#include <QRegExp>
#include <QRegExpValidator>
#include <QStyledItemDelegate>

class GenreSetter;
class CustomDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    CustomDelegate(GenresModel* _genresModel, QObject* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

private:
    GenresModel* genresModel = nullptr;
    friend class GenreSetter;
};
