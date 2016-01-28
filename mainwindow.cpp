#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->on_tabWidget_currentChanged(0);
    // load skill points and experience
    CSV status("status.txt");
    if (status.getRow(0).size() < 2) {
        status.insertRow(QStringList("0") << "0");
    }
    int exp = status.getRow(0)[0].toInt();
    int skillPoints = status.getRow(0)[1].toInt();
    ui->lcd_level->display(this->getLevel(exp));
    ui->lcd_skill->display(skillPoints);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getLevel(int exp)
{
    // experience needed to pass level is calculated from formula:
    // exp(level) = 10**level + 10**(level-1) + ... + 10**1
    int level = 0;
    int tempExp = exp;
    while (tempExp >= 0) {
        level++;
        tempExp -= pow(10, level);
    }
    return level;
}

// event insert
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

// tab switch
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
        CSV skills("skills.txt");
        for (int i = ui->t_skills->rowCount(); i > -1; i--) {
            ui->t_skills->removeRow(i);
        }
        for (int i = 0; i < skills.getRowsNum(); i++) {
            ui->t_skills->insertRow(ui->t_skills->rowCount());
            auto row = skills.getRow(i);
            ui->t_skills->setItem(ui->t_skills->rowCount() - 1, 0, new QTableWidgetItem(row[0]));
            ui->t_skills->setItem(ui->t_skills->rowCount() - 1, 1, new QTableWidgetItem(row[1]));
        }
        CSV mastered("mastered.txt");
        ui->li_mastered->clear();
        for (int i = 0; i < mastered.getRowsNum(); i++) {
            ui->li_mastered->addItem(mastered.getRow(i)[0]);
        }
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

// event delete
void MainWindow::on_b_event_del_clicked()
{
    int rowNum = ui->t_events->currentRow();
    if (rowNum != -1) {
        ui->t_events->removeRow(rowNum);
        CSV events("events.txt");
        events.deleteRow(rowNum);
        ui->l_event_dialog->clear();
    } else {
        ui->l_event_dialog->setText("No event selected!");
    }
}

// event finish
void MainWindow::on_pushButton_2_clicked()
{
    int rowNum = ui->t_events->currentRow();
    if (rowNum != -1) {
        CSV events("achieve.txt");
        events.insertRow(QStringList(ui->t_events->item(rowNum, 0)->text()));
        CSV status("status.txt");
        int skillPoints = status.getRow(0)[1].toInt();
        int exp = status.getRow(0)[0].toInt();
        status.clear();
        int level = this->getLevel(exp);
        exp += ui->t_events->item(rowNum, 1)->text().toInt();
        if (level < this->getLevel(exp)) {
            skillPoints += (this->getLevel(exp) - level) * 10;
        }
        status.insertRow(QStringList(QString::number(exp)) << QString::number(skillPoints));
        this->on_b_event_del_clicked();
        ui->lcd_level->display(this->getLevel(exp));
        ui->lcd_skill->display(skillPoints);
    } else {
        ui->l_event_dialog->setText("No event selected!");
    }
}

// archive clear
void MainWindow::on_pushButton_clicked()
{
    CSV achieved("achieve.txt");
    achieved.clear();
    this->on_tabWidget_currentChanged(2);
}

// skill insert
void MainWindow::on_pushButton_5_clicked()
{
    QString req(ui->s_skill->text()),
            skill(ui->l_skill->text());
    ui->t_skills->insertRow(ui->t_skills->rowCount());
    ui->t_skills->setItem(ui->t_skills->rowCount() - 1, 0, new QTableWidgetItem(ui->l_skill->text().replace(";", ",")));
    ui->t_skills->setItem(ui->t_skills->rowCount() - 1, 1, new QTableWidgetItem(ui->s_skill->text().replace(";", ",")));
    ui->l_skill->clear();
    ui->s_skill->setValue(0);
    CSV skills("skills.txt");
    skills.insertRow(QStringList() << skill << req);
}

// skill delete
void MainWindow::on_pushButton_4_clicked()
{
    int rowNum = ui->t_skills->currentRow();
    if (rowNum != -1) {
        ui->t_skills->removeRow(rowNum);
        CSV skills("skills.txt");
        skills.deleteRow(rowNum);
        ui->l_skill_dialog->clear();
    } else {
        ui->l_skill_dialog->setText("No skill selected!");
    }
}

// skill learn
void MainWindow::on_pushButton_3_clicked()
{
    int rowNum = ui->t_skills->currentRow();
    if (rowNum != -1) {
        CSV skills("skills.txt");
        auto skill = skills.getRow(rowNum);
        if (skill[1].toInt() <= ui->lcd_skill->value()) {
            ui->t_skills->removeRow(rowNum);
            skills.deleteRow(rowNum);
            CSV status("status.txt");
            auto stats = status.getRow(0);
            status.clear();
            stats[1] = QString::number(stats[1].toInt() - skill[1].toInt());
            ui->lcd_skill->display(stats[1].toInt());
            status.insertRow(stats);
            CSV mastered("mastered.txt");
            mastered.insertRow(QStringList(skill[0]));
            this->on_tabWidget_currentChanged(1);
            ui->l_skill_dialog->clear();
        } else {
            ui->l_skill_dialog->setText("Not enough skill points!");
        }
    } else {
        ui->l_skill_dialog->setText("No skill selected!");
    }
}

// mastered clear
void MainWindow::on_pushButton_6_clicked()
{
    CSV mastered("mastered.txt");
    mastered.clear();
    this->on_tabWidget_currentChanged(1);
}
