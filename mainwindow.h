#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
