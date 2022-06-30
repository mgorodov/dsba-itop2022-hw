#include "filtermodel.h"

FilterModel::FilterModel(QObject* parent,
    QLineEdit* _filterIMDBEditL,
    QLineEdit* _filterIMDBEditR,
    QDateEdit* _filterPremiereEditL,
    QDateEdit* _filterPremiereEditR,
    QLineEdit* _filterRuntimeEditL,
    QLineEdit* _filterRuntimeEditR,
    QLineEdit* _filterGenreEdit,
    QLineEdit* _filterLanguageEdit)
{
    filterIMDBEditL = _filterIMDBEditL;
    filterIMDBEditR = _filterIMDBEditR;
    filterPremiereEditL = _filterPremiereEditL;
    filterPremiereEditR = _filterPremiereEditR;
    filterRuntimeEditL = _filterRuntimeEditL;
    filterRuntimeEditR = _filterRuntimeEditR;
    filterGenreEdit = _filterGenreEdit;
    filterLanguageEdit = _filterLanguageEdit;
}

bool FilterModel::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
    QVariant lhv = left.data(Qt::EditRole);
    QVariant rhv = right.data(Qt::EditRole);
    if (left.column() == static_cast<int>(FilmFields::imdb))
        return lhv.toDouble() < rhv.toDouble();

    if (left.column() == static_cast<int>(FilmFields::premiere))
        return QDate::fromString(lhv.toString(), "dd.MM.yyyy") < QDate::fromString(rhv.toString(), "dd.MM.yyyy");

    if (left.column() == static_cast<int>(FilmFields::runtime))
        return lhv.toDouble() < rhv.toDouble();

    return lhv < rhv;
}

bool FilterModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    QString imdbmin = filterIMDBEditL->text();
    QString imdbmax = filterIMDBEditR->text();
    QDate prmin = filterPremiereEditL->date();
    QDate prmax = filterPremiereEditR->date();
    QString runtimemin = filterRuntimeEditL->text();
    QString runtimemax = filterRuntimeEditR->text();
    QString genreReq = filterGenreEdit->text();
    QString languageReq = filterLanguageEdit->text();

    QModelIndex imdb = sourceModel()->index(sourceRow, static_cast<int>(FilmFields::imdb), sourceParent);
    QModelIndex premiere = sourceModel()->index(sourceRow, static_cast<int>(FilmFields::premiere), sourceParent);
    QModelIndex runtime = sourceModel()->index(sourceRow, static_cast<int>(FilmFields::runtime), sourceParent);
    QModelIndex genre = sourceModel()->index(sourceRow, static_cast<int>(FilmFields::genre), sourceParent);
    QModelIndex language = sourceModel()->index(sourceRow, static_cast<int>(FilmFields::language), sourceParent);
    if (!imdbmin.isEmpty() && sourceModel()->data(imdb).toDouble() < imdbmin.toDouble())
        return false;
    if (!imdbmax.isEmpty() && sourceModel()->data(imdb).toDouble() > imdbmax.toDouble())
        return false;
    if (prmin != QDate(2010, 1, 1) && prmin.isValid() && QDate::fromString(sourceModel()->data(premiere).toString(), "dd.MM.yyyy") < prmin)
        return false;
    if (prmin != QDate(2010, 1, 1) && prmax.isValid() && QDate::fromString(sourceModel()->data(premiere).toString(), "dd.MM.yyyy") > prmax)
        return false;
    if (!runtimemin.isEmpty() && sourceModel()->data(runtime).toDouble() < runtimemin.toDouble())
        return false;
    if (!runtimemax.isEmpty() && sourceModel()->data(runtime).toDouble() > runtimemax.toDouble())
        return false;
    if (!genreReq.isEmpty() && !sourceModel()->data(genre).toString().contains(QRegExp(genreReq, Qt::CaseInsensitive)))
        return false;
    if (!languageReq.isEmpty() && !sourceModel()->data(language).toString().contains(QRegExp(languageReq, Qt::CaseInsensitive)))
        return false;
    return true;
}
