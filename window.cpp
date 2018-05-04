#include "window.h"
#include <QPushButton>
#include <iostream>
#include <QGridLayout>
#include <QMessageBox>
#include <QPalette>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
using namespace std;

Window::Window(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* hblayout(new QHBoxLayout);
    QVBoxLayout* vblayout(new QVBoxLayout);
    QGridLayout* layoutGameMenu(new QGridLayout);

    QGridLayout* layoutPlayerButtons(new QGridLayout);
    for (int i = 0; i != 10; ++i)
    {
       for (int j = 0; j != 4; ++j)
       {
            QPushButton* pb = new QPushButton;
            pb->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
            pb->setFixedSize(33,33);
            layoutPlayerButtons->addWidget(pb,i,j);
            connect(pb, SIGNAL(clicked(bool)), this, SLOT(ButtonClickedSet()));
            QFont font = pb->font();
            font.setPointSize(33);
            pb->setFont(font);
            playerButtons[i][j]=pb;
       }
       QLabel* labelCheck(new QLabel("lofasz"));
       layoutPlayerButtons->addWidget(labelCheck,i,4);
       playerResultsLabel[i] = labelCheck;
    }
    UpdatePlayerButtons();

    QGridLayout* layoutPalette(new QGridLayout);
    for (int i = 0; i != 1; ++i)
    {
       for (int j = 0; j != 8; ++j)
       {
            QPushButton* pb = new QPushButton;
            pb->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
            layoutPalette->addWidget(pb,i,j);
            connect(pb, SIGNAL(clicked(bool)), this, SLOT(ButtonClickedGet()));
            QFont font = pb->font();
            font.setPointSize(33);
            pb->setFont(font);
            paletteButtons[i][j]=pb;
       }
    }
    UpdatePalette();

    QGridLayout* layoutRaceColors(new QGridLayout);
    for (int j = 0; j != 4; ++j)
    {
        QPushButton* pb = new QPushButton;
        pb->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        layoutRaceColors->addWidget(pb,1,j);
        connect(pb, SIGNAL(clicked(bool)), this, SLOT(ButtonClickedGet()));
        QFont font = pb->font();
        font.setPointSize(33);
        pb->setFont(font);
        buttonsFours[j]=pb;
    }
    UpdateRaceColors();

    QPushButton* newGame = new QPushButton("&Shuffle",this);
    newGame->setVisible(true);
    newGame->setStyleSheet("color:purple; background-color:white");
    connect(newGame, SIGNAL(clicked(bool)), this, SLOT(UpdateRaceColors()));
    QFont font = newGame->font();
    font.setPointSize(33);
    newGame->setFont(font);

    QPushButton* checkGame = new QPushButton("&Check",this);
    checkGame->setVisible(true);
    checkGame->setStyleSheet("color:red; background-color:white");
    connect(checkGame, SIGNAL(clicked(bool)), this, SLOT(ButtonClickedCheck()));
    checkGame->setFont(font);

    QLabel* gameLabel(new QLabel("lofasz"));
    gameLabel->setVisible(true);
    gameLabel->setStyleSheet("QLabel {background-color : grey;}");
    gameLabel->setAutoFillBackground(true);

    layoutPalette->setRowStretch(1,1);
    layoutRaceColors->setRowStretch(1,1);
    layoutPlayerButtons->setRowStretch(1,1);

    hblayout->addLayout(layoutPlayerButtons);
    vblayout->addLayout(layoutRaceColors);
    vblayout->addLayout(layoutPalette);
    vblayout->addWidget(gameLabel);
    layoutGameMenu->addWidget(newGame,0,0);
    layoutGameMenu->addWidget(checkGame,0,1);
    vblayout->addLayout(layoutGameMenu);
    hblayout->addLayout(vblayout);
    setLayout(hblayout);
}

void Window::UpdatePlayerButtons()
{
    for (int i = 0; i != 10; ++i)
    {
       for (int j = 0; j != 4; ++j)
       {
            QPushButton* pb = playerButtons[i][j];
            int state = mGame.get_elem(game::input{i,j});
            QString color;
            if (state == 0)
            {
                pb->setEnabled(true);
                pb->setText("");
                color = "white";
            }
            pb->setStyleSheet("color:black; background-color:"+color);
       }
    }
}

void Window::UpdatePalette()
{
    QString paletteColor []={"white","yellow","orange","red","pink","green","blue","black"};
    for (int i = 0; i != 8; ++i)
    {
         QPushButton* pb = paletteButtons[0][i];
         int state = mGame.get_elem(game::input{0,i});
         QString color;
         if (state == 0)
         {
             pb->setEnabled(true);
             pb->setText("");
             color = paletteColor[i];
         }
         pb->setStyleSheet("color:black; background-color:"+color);
    }
}

void Window::UpdateRaceColors()
{
    array<QString,8> paletteColor={"white","yellow","orange","red","pink","green","blue","black"};
    ShuffleColors(paletteColor);
    for (int i = 0; i != 4; ++i)
    {
         QPushButton* pb = buttonsFours[i];
         if (pb==NULL)
         {
             continue;

         }
         int state = mGame.get_elem(game::input{0,i});
         QString color;
         if (state == 0)
         {
             pb->setDisabled(true);
             //pb->setVisible(false);
             pb->setText("");
             color = paletteColor[i];
         }
         pb->setStyleSheet("color:black; background-color:"+color);
    }
}

void Window::ShuffleColors(array<QString,8>& arrayHolder)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(arrayHolder.begin(), arrayHolder.end(), std::default_random_engine(seed));
}

void Window::ButtonClickedCheck()
{
    playerResultsLabel[0]->setText(CheckColors(buttonsFours, playerButtons[0]));
}

QString Window::CheckColors(lineFours const& pcolor, lineFours const& rcolor)
{
    QString rv;
    QStringList rcolorsStyles;

    for (int i = 0; i != 4; ++i)
    {
        rcolorsStyles<<rcolor[i]->styleSheet();
    }

    for (int i = 0; i != 4; ++i)
    {
        if (pcolor[i]->styleSheet() == rcolor[i]->styleSheet())
        {
            rv = rv+"b";
        }
        else if(rcolorsStyles.contains(pcolor[i]->styleSheet()))
        {
            rv = rv+"w";
        }
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(rv.begin(), rv.end(), std::default_random_engine(seed));

    return rv;
}

void Window::ButtonClickedGet()
{
    QPushButton* pb(qobject_cast<QPushButton*>(sender()));
    if (pb)
    {
        selectedStyleSheet = pb->styleSheet();
    }
}

void Window::ButtonClickedSet()
{
    QPushButton* pb(qobject_cast<QPushButton*>(sender()));
    if (pb)
    {
        pb->setStyleSheet(selectedStyleSheet);
    }
}
