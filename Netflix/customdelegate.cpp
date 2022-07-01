#include "customdelegate.h"

CustomDelegate::CustomDelegate(GigaModel* _genresModel, GigaModel* _languagesModel, QObject* parent)
    : QStyledItemDelegate(parent)
    , genresModel(_genresModel)
    , languagesModel(_languagesModel)
{
}

inline QColor redToGreen(double x)
{
    if (x <= 3)
        return QColor::fromRgb(255, 0, 0);
    if (x >= 8)
        return QColor::fromRgb(0, 255, 0);
    if (x < 6)
        return QColor::fromRgb(255, 85 * (x - 3), 0);
    return QColor::fromRgb(255 - 127.5 * (x - 6), 255, 0);
}

void CustomDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (static_cast<FilmFields>(index.column()) == FilmFields::imdb)
    {
        bool ok = false;
        double rate = index.data().toDouble(&ok);
        if (ok)
            painter->fillRect(option.rect, QBrush(redToGreen(rate)));
    }
    QStyledItemDelegate::paint(painter, option, index);
}

QWidget* CustomDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex& index) const
{
    if (static_cast<FilmFields>(index.column()) == FilmFields::genre)
    {
        MultiSelectComboBox* editor = new MultiSelectComboBox(parent);
        editor->setFrame(false);
        for (const QString& g : genresModel->m_data)
            editor->addItem(g);

        return editor;
    }
    if (static_cast<FilmFields>(index.column()) == FilmFields::language)
    {
        MultiSelectComboBox* editor = new MultiSelectComboBox(parent);
        editor->setFrame(false);
        for (const QString& g : languagesModel->m_data)
            editor->addItem(g);

        return editor;
    }
    QLineEdit* editor = new QLineEdit(parent);
    if (static_cast<FilmFields>(index.column()) == FilmFields::runtime)
        editor->setValidator(new QIntValidator(1, 300));
    if (static_cast<FilmFields>(index.column()) == FilmFields::imdb)
        editor->setValidator(new QDoubleValidator(0, 10, 1));
    if (static_cast<FilmFields>(index.column()) == FilmFields::premiere)
        editor->setValidator(new QRegExpValidator(QRegExp("(0[1-9]|[12][0-9]|3[01]).(0[1-9]|[1][0-2]).(19[0-9][0-9]|20[0-9][0-9])")));
    return editor;
}

void CustomDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    QVariant value = index.model()->data(index, Qt::EditRole);

    MultiSelectComboBox* comboBox = dynamic_cast<MultiSelectComboBox*>(editor);
    QLineEdit* lineEdit = dynamic_cast<QLineEdit*>(editor);
    if (comboBox)
        comboBox->setCurrentText(value.toString().split('/'));
    if (lineEdit)
        lineEdit->setText(value.toString());
}

void CustomDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    MultiSelectComboBox* comboBox = dynamic_cast<MultiSelectComboBox*>(editor);
    QLineEdit* lineEdit = dynamic_cast<QLineEdit*>(editor);

    if (comboBox)
        model->setData(index, comboBox->currentStringText(), Qt::EditRole);
    if (lineEdit)
        model->setData(index, lineEdit->text(), Qt::EditRole);
}

void CustomDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& /* index */) const
{
    editor->setGeometry(option.rect);
}
