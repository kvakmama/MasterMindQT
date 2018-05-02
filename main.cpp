#include <QApplication>
#include <QPushButton>
#include <QDialog>
#include <QGridLayout>
#include "window.h"
#include "button.h"

int main(int argc, char **argv)
{
 QApplication app (argc, argv);

 Window window;
 window.setFixedSize(1000, 1000);

 window.show();
 return app.exec();
}
