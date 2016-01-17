#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_b_add_event_clicked()
{
    ui->t_events->insertRow(ui->t_events->rowCount());
    ui->t_events->setItem(ui->t_events->rowCount() - 1, 0, new QTableWidgetItem(ui->e_event_title->text()));
    ui->t_events->setItem(ui->t_events->rowCount() - 1, 1, new QTableWidgetItem(ui->s_exp->text()));
    ui->e_event_title->clear();
    ui->s_exp->setValue(0);
}
