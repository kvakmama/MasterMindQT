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
#include <QMessageBox>
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

//SHUFFLE
    QPushButton* newQuiz = new QPushButton("&Shuffle",this);
    newQuiz->setVisible(true);
    newQuiz->setStyleSheet("color:purple; background-color:white");
    connect(newQuiz, SIGNAL(clicked(bool)), this, SLOT(UpdateRaceColors()));
    QFont font = newQuiz->font();
    font.setPointSize(10);
    newQuiz->setFont(font);
//NEW
    QPushButton* newGame = new QPushButton("&New",this);
    newGame->setVisible(true);
    newGame->setStyleSheet("color:purple; background-color:white");
    connect(newGame, SIGNAL(clicked(bool)), this, SLOT(CreateNewGame()));
    newGame->setFont(font);
//CHECK
    QPushButton* checkGame = new QPushButton("&Check",this);
    checkGame->setVisible(true);
    checkGame->setStyleSheet("color:red; background-color:white");
    connect(checkGame, SIGNAL(clicked(bool)), this, SLOT(ButtonClickedCheck()));
    checkGame->setFont(font);

    gameLabel = new QLabel("Point");
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
    layoutGameMenu->addWidget(newQuiz,0,0);
    layoutGameMenu->addWidget(newGame,0,1);
    layoutGameMenu->addWidget(checkGame,0,2);
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

void Window::CreateNewGame()
{
   Window::UpdateRaceColors();
   Window::UpdatePlayerButtons();
   for (int i = 0; i != 10; ++i)
   {
       playerResultsLabel[i]->setText("new");
   }
}

void Window::ShuffleColors(array<QString,8>& arrayHolder)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(arrayHolder.begin(), arrayHolder.end(), std::default_random_engine(seed));
}

void Window::ButtonClickedCheck()
{
    int i = 0;
    while ((playerResultsLabel[i]->text() != "lofasz") && (playerResultsLabel[i]->text() != "new"))
    {
        ++i;
    }
    playerResultsLabel[i]->setText(CheckColors(buttonsFours, playerButtons[i]));
}

QString Window::CheckColors(lineFours const& rcolor, lineFours const& pcolor)
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

    if ((pcolor[0]->styleSheet() == pcolor[1]->styleSheet()) ||
        (pcolor[0]->styleSheet() == pcolor[2]->styleSheet()) ||
            (pcolor[0]->styleSheet() == pcolor[3]->styleSheet()) ||
            (pcolor[1]->styleSheet() == pcolor[2]->styleSheet()) ||
            (pcolor[1]->styleSheet() == pcolor[3]->styleSheet()) ||
            (pcolor[2]->styleSheet() == pcolor[3]->styleSheet()))
    {
        rv = "color_duplicated";

    }
    if (rv == "bbbb")
    {
        QMessageBox msgBox;
        msgBox.setText("You win!");
        msgBox.exec();
        QString oldPoint;
        oldPoint = gameLabel->text();
        QString aktPoint;
        aktPoint = QString::number(CalculatePoint());
        gameLabel->setText(oldPoint + "\n" + aktPoint);
    }

    return rv;
}

int Window::CalculatePoint()
{
    int point = 1;
    for (int i = 0; i != 10; ++i)
    {
        if ((playerResultsLabel[i]->text() != "new") && (playerResultsLabel[i]->text() != "lofasz"))
        {
           ++point;
        }
    }
    return point;
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



