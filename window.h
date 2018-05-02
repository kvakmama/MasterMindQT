#ifndef WINDOW_H
#define WINDOW_H
#include <QPushButton>
#include <QWidget>
#include "game.h"
#include "button.h"
#include <array>
#include <QLabel>

class Window : public QWidget
{
    Q_OBJECT
    // storing the current game state
    game mGame;
    // holding the buttons matching the game state
    typedef std::array<QPushButton*,4> Line;
    std::array<Line,10> mButtons;
    std::array<QLabel*,10> mResults;
    QPushButton* mButtons2[1][8];
    Line mButtons3;

    QPushButton* newGame;

    QString mSelectedStyleSheet;
    void UpdateUI();
    void UpdateUI2();

    QString CheckGame(const Line &pcolor, const Line &rcolor);
public:
    explicit Window(QWidget *parent = nullptr);

private slots:
    void buttonClickedGet();
    void buttonClickedSet();
    void RColor(std::array<QString,8>& arrayHolder);
    void UpdateUI3();

    void CheckButtonClicked();
};

#endif // WINDOW_H
//QString a,QString b,QString c
