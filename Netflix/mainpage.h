#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QVariant>

class FilmModel;
enum class FilmFields
{
    title, genre, premiere, runtime, imdb, language, COUNT
};

struct Film
{
    std::array<QVariant, static_cast<int> (FilmFields::COUNT)> data;
};

class FilterModel;

class MainPage : public QWidget
{
    Q_OBJECT
public:
    explicit MainPage(QWidget *parent = nullptr);
private:
    void setupUI();
    std::vector<Film> loadData(const QString &dir);
public slots:
    void loadDataTrigger();

};

#endif // MAINPAGE_H
