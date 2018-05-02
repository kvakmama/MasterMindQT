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

void Window::buttonClickedGet()
{
    QPushButton* pb(qobject_cast<QPushButton*>(sender()));
    if (pb)
    {
        mSelectedStyleSheet = pb->styleSheet();
    }
}

void Window::buttonClickedSet()
{
    QPushButton* pb(qobject_cast<QPushButton*>(sender()));
    if (pb)
    {
        pb->setStyleSheet(mSelectedStyleSheet);
    }
}

Window::Window(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* hblayout(new QHBoxLayout);
    QVBoxLayout* vblayout(new QVBoxLayout);

    QGridLayout* layout(new QGridLayout);
    for (int i = 0; i != 10; ++i)
    {
       for (int j = 0; j != 4; ++j)
       {
            QPushButton* pb = new QPushButton;
            pb->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
            pb->setFixedSize(33,33);
            layout->addWidget(pb,i,j);
            connect(pb, SIGNAL(clicked(bool)), this, SLOT(buttonClickedSet()));
            QFont font = pb->font();
            font.setPointSize(33);
            pb->setFont(font);
            mButtons[i][j]=pb;
       }
       QLabel* labelCheck(new QLabel("lofasz"));
       layout->addWidget(labelCheck,i,4);
       mResults[i] = labelCheck;
    }
    UpdateUI();

    QGridLayout* layout2(new QGridLayout);
    for (int i = 0; i != 1; ++i)
    {
       for (int j = 0; j != 8; ++j)
       {
            QPushButton* pb = new QPushButton;
            pb->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
            layout2->addWidget(pb,i,j);
            connect(pb, SIGNAL(clicked(bool)), this, SLOT(buttonClickedGet()));
            QFont font = pb->font();
            font.setPointSize(33);
            pb->setFont(font);
            mButtons2[i][j]=pb;
       }
    }
    UpdateUI2();

    QGridLayout* layout3(new QGridLayout);
    for (int j = 0; j != 4; ++j)
    {
        QPushButton* pb = new QPushButton;
        pb->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        layout3->addWidget(pb,1,j);
        connect(pb, SIGNAL(clicked(bool)), this, SLOT(buttonClickedGet()));
        QFont font = pb->font();
        font.setPointSize(33);
        pb->setFont(font);
        mButtons3[j]=pb;
    }
    UpdateUI3();

    QPushButton* newGame = new QPushButton("&New",this);
    newGame->setVisible(true);
    newGame->setStyleSheet("color:black; background-color:red");
    connect(newGame, SIGNAL(clicked(bool)), this, SLOT(UpdateUI3()));
    QFont font = newGame->font();
    font.setPointSize(33);
    newGame->setFont(font);

    QPushButton* checkGame = new QPushButton("&Check",this);
    checkGame->setVisible(true);
    checkGame->setStyleSheet("color:black; background-color:red");
    connect(checkGame, SIGNAL(clicked(bool)), this, SLOT(CheckButtonClicked()));
    checkGame->setFont(font);

    QLabel* label(new QLabel("lofasz"));
    label->setVisible(true);
    label->setStyleSheet("QLabel {background-color : grey;}");
    label->setAutoFillBackground(true);

    layout2->addWidget(newGame,4,1);
    layout2->addWidget(label,1,0);
    layout2->setRowStretch(1,1);

    layout3->setRowStretch(1,1);


    hblayout->addLayout(layout);
    vblayout->addLayout(layout3);
    vblayout->addLayout(layout2);
    hblayout->addLayout(vblayout);

    setLayout(hblayout);
}

void Window::UpdateUI()
{
    for (int i = 0; i != 10; ++i)
    {
       for (int j = 0; j != 4; ++j)
       {
            QPushButton* pb = mButtons[i][j];
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

void Window::UpdateUI2()
{
    QString paletta_color []={"white","yellow","orange","red","pink","green","blue","black"};
    for (int i = 0; i != 8; ++i)
    {
         QPushButton* pb = mButtons2[0][i];
         int state = mGame.get_elem(game::input{0,i});
         QString color;
         if (state == 0)
         {
             pb->setEnabled(true);
             pb->setText("");
             color = paletta_color[i];
         }
         pb->setStyleSheet("color:black; background-color:"+color);
    }
}

void Window::UpdateUI3()
{
    array<QString,8> paletta_color={"white","yellow","orange","red","pink","green","blue","black"};
    RColor(paletta_color);
    for (int i = 0; i != 4; ++i)
    {
         QPushButton* pb = mButtons3[i];
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
             color = paletta_color[i];
         }
         pb->setStyleSheet("color:black; background-color:"+color);
    }
}

void Window::RColor(array<QString,8>& arrayHolder)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(arrayHolder.begin(), arrayHolder.end(), std::default_random_engine(seed));
}

void Window::CheckButtonClicked()
{
    mResults[0]->setText(CheckGame(mButtons3, mButtons[0]));
}

QString Window::CheckGame(Line const& pcolor, Line const& rcolor)
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

