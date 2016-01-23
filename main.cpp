#include "mainwindow.h"
#include "csv.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    //CSV csv("lol.txt");
    //csv.insertRow(QStringList("ssfsf"));
    //qDebug() << csv.getRow(1);
    //csv.deleteRow(1);
    //csv.insertRow(QStringList("ssfs124f"));
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("RPG Organizer");
    w.show();

    return a.exec();
}
