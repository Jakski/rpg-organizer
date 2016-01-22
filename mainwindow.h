#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cmath>

#include "csv.h"

#include <QMainWindow>
#include <QString>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_b_add_event_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_b_event_del_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void showExp();
};

#endif // MAINWINDOW_H
