/*
      Delegate used for wrapping cells in table on main page derived from QTableView.
      This delegate creates two types of editors: MultiSelectComboBox and QLineEdit as well as validators for them
*/

#pragma once
#include "filmmodel.h"
#include "gigamodel.h"
#include "multiselectcombobox.h"
#include <QColor>
#include <QComboBox>
#include <QIntValidator>
#include <QLineEdit>
#include <QPainter>
#include <QRegExp>
#include <QRegExpValidator>
#include <QStyledItemDelegate>

class GigaSetter;
class CustomDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    CustomDelegate(GigaModel* _genresModel, GigaModel* _languagesModel, QObject* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

private:
    GigaModel* genresModel = nullptr;
    GigaModel* languagesModel = nullptr;
    friend class GigaSetter;
};
