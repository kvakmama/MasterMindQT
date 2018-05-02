#ifndef BUTTON_H
#define BUTTON_H
#include <QPushButton>

class Button : public QPushButton
{
    Q_OBJECT
public:
    Button(QString text, QWidget*parent);
};

#endif // BUTTON_H
