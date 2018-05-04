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
 window.setFixedSize(500, 500);

 window.show();
 return app.exec();
}
