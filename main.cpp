#include <QApplication>
#include <QLabel>
#include "lib/mainwindow.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  MainWindow *w = new MainWindow();
  w->show();

  return app.exec();
}
