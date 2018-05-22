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
    typedef std::array<QPushButton*,4> lineFours;
    std::array<lineFours,10> playerButtons;
    std::array<QLabel*,10> playerResultsLabel;
    QPushButton* paletteButtons[1][8];
    lineFours buttonsFours;
    QLabel* gameLabel;

    QPushButton* newGame;

    QString selectedStyleSheet;
    void UpdatePlayerButtons();
    void UpdatePalette();
    QString CheckColors(const lineFours &pcolor, const lineFours &rcolor);

public:
    explicit Window(QWidget *parent = nullptr);

private slots:
    void ButtonClickedGet();
    void ButtonClickedSet();
    void ButtonClickedCheck();
    void ShuffleColors(std::array<QString,8>& arrayHolder);
    void UpdateRaceColors();
    void CreateNewGame();
    int CalculatePoint();
};

#endif // WINDOW_H
//QString a,QString b,QString c
