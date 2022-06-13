/***************************************************************************************************

  Class FilterModel, derived from QSortFilterProxyModel implements sorting and filtering of data,
  according to corresponding user-input queries

***************************************************************************************************/

#pragma once

#include "filmmodel.h"
#include <QDate>
#include <QDateEdit>
#include <QLineEdit>
#include <QSortFilterProxyModel>

class FilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    FilterModel(QObject* parent = nullptr,
        QLineEdit* _filterIMDBEditL = nullptr,
        QLineEdit* _filterIMDBEditR = nullptr,
        QDateEdit* _filterPremiereEditL = nullptr,
        QDateEdit* _filterPremiereEditR = nullptr,
        QLineEdit* _filterRuntimeEditL = nullptr,
        QLineEdit* _filterRuntimeEditR = nullptr,
        QLineEdit* _filterGenreEdit = nullptr,
        QLineEdit* _filterLanguageEdit = nullptr);

protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
    virtual bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;

private:
    QLineEdit* filterIMDBEditL = nullptr;
    QLineEdit* filterIMDBEditR = nullptr;
    QDateEdit* filterPremiereEditL = nullptr;
    QDateEdit* filterPremiereEditR = nullptr;
    QLineEdit* filterRuntimeEditL = nullptr;
    QLineEdit* filterRuntimeEditR = nullptr;
    QLineEdit* filterGenreEdit = nullptr;
    QLineEdit* filterLanguageEdit = nullptr;
};
