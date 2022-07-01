/*
    Actually I copyed it from https://github.com/ThisIsClark/Qt-MultiSelectComboBox and only
    1)changed separator to '/'
    2)added function currentStringText() to return just QString instead of QStringList
*/

#pragma once

#include <QComboBox>
#include <QListWidget>

class MultiSelectComboBox : public QComboBox
{
    Q_OBJECT

public:
    MultiSelectComboBox(QWidget* aParent = Q_NULLPTR);
    void addItem(const QString& aText, const QVariant& aUserData = QVariant());
    void addItems(const QStringList& aTexts);
    QStringList currentText();
    QString currentStringText();
    int count() const;
    void hidePopup() override;
    void SetSearchBarPlaceHolderText(const QString& aPlaceHolderText);
    void SetPlaceHolderText(const QString& aPlaceHolderText);
    void ResetSelection();

signals:
    void selectionChanged();

public slots:
    void clear();
    void setCurrentText(const QString& aText);
    void setCurrentText(const QStringList& aText);

protected:
    void wheelEvent(QWheelEvent* aWheelEvent) override;
    bool eventFilter(QObject* aObject, QEvent* aEvent) override;
    void keyPressEvent(QKeyEvent* aEvent) override;

private:
    void stateChanged(int aState);
    void onSearch(const QString& aSearchString);
    void itemClicked(int aIndex);

    QListWidget* mListWidget;
    QLineEdit* mLineEdit;
    QLineEdit* mSearchBar;
};
