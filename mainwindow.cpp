#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->on_tabWidget_currentChanged(0);
    this->showExp();
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
    // events
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
    // skills
    case 1:
    {   
        break;
    }
    // achievments
    case 2:
    {
        ui->li_achieved->clear();
        CSV achieved("achieve.txt");
        for (int i = 0; i < achieved.getRowsNum(); i++) {
            ui->li_achieved->addItem(achieved.getRow(i)[0]);
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
        ui->l_event_dialog->clear();
    } else {
        ui->l_event_dialog->setText("No event selected! Cannot delete.");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    int rowNum = ui->t_events->currentRow();
    if (rowNum != -1) {
        // add to achievments
        CSV events("achieve.txt");
        events.insertRow(QStringList(ui->t_events->item(rowNum, 0)->text()));
        // retrieve current level and experience
        CSV status("status.txt");
        if (status.getRow(0).size() < 1) {
            // file not created. init with 0 experience
            status.insertRow(QStringList("0"));
        }
        // get saved experience
        int exp = status.getRow(0)[0].toInt();
        status.clear();
        // retrieve exp from selected event
        auto nExp = ui->t_events->item(rowNum, 1)->text();
        exp += nExp.toInt();
        // experience needed to pass level is calculated from formula:
        // 10**level + 10**(level-1) + ... + 10**1
        int level = 0;
        int tempExp = exp;
        while (tempExp >= 0) {
            level++;
            tempExp -= pow(10, level);
        }
        // save changes
        status.insertRow(QStringList(QString::number(exp)));
        // use signal to delete selected item from table of events
        this->on_b_event_del_clicked();
        this->showExp();
    } else {
        ui->l_event_dialog->setText("No event selected! Cannot finish.");
    }
}

void MainWindow::on_pushButton_clicked()
{
    CSV achieved("achieve.txt");
    achieved.clear();
    // refresh
    this->on_tabWidget_currentChanged(2);
}

void MainWindow::showExp()
{
    CSV status("status.txt");
    if (status.getRow(0).size() < 1) {
        // file not created. init with 0 experience
        status.insertRow(QStringList("0"));
    }
    // get saved experience
    int exp = status.getRow(0)[0].toInt();
    // experience needed to pass level is calculated from formula:
    // 10**level + 10**(level-1) + ... + 10**1
    int level = 0;
    int tempExp = exp;
    while (tempExp >= 0) {
        level++;
        tempExp -= pow(10, level);
    }
    // show changes on UI
    ui->lcd_level->display(level);
}
