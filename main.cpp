#include <QApplication>

#include "mainwindow.hh"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QFile styleFile(":/styles.qss");
  styleFile.open(QFile::ReadOnly);

  QString style(styleFile.readAll());
  a.setStyleSheet(style);

  MainWindow w;
  w.show();

  return a.exec();
}
