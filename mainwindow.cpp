#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->on_tabWidget_currentChanged(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_b_add_event_clicked()
{
    QString exp(ui->s_exp->text()),
            title(ui->e_event_title->text());
    ui->t_events->insertRow(ui->t_events->rowCount());
    ui->t_events->setItem(ui->t_events->rowCount() - 1, 0, new QTableWidgetItem(ui->e_event_title->text().replace(";", ",")));
    ui->t_events->setItem(ui->t_events->rowCount() - 1, 1, new QTableWidgetItem(ui->s_exp->text().replace(";", ",")));
    ui->e_event_title->clear();
    ui->s_exp->setValue(0);
    CSV events("events.txt");
    events.insertRow(QStringList() << title << exp);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch(index) {
    case 0:
    {
        CSV events("events.txt");
        for (int i = ui->t_events->rowCount(); i > -1; i--) {
            ui->t_events->removeRow(i);
        }
        for (int i = 0; i < events.getRowsNum(); i++) {
            ui->t_events->insertRow(ui->t_events->rowCount());
            auto row = events.getRow(i);
            ui->t_events->setItem(ui->t_events->rowCount() - 1, 0, new QTableWidgetItem(row[0]));
            ui->t_events->setItem(ui->t_events->rowCount() - 1, 1, new QTableWidgetItem(row[1]));
        }
        break;
    }
    default:
        qDebug() << "Wrong index: " << index;
        break;
    }
}

void MainWindow::on_b_event_del_clicked()
{
    int rowNum = ui->t_events->currentRow();
    if (rowNum != -1) {
        ui->t_events->removeRow(rowNum);
        CSV events("events.txt");
        events.deleteRow(rowNum);
    }
}
