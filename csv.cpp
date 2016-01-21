#include "csv.h"

CSV::CSV(QString file) :
    mFile(file)
{
    mFile.open(QIODevice::ReadWrite);
}

QStringList CSV::getRow(int n) {
    QString row;
    for (int i = 0; i <= n; i++) {
        row = QString(mFile.readLine());
    }
    row.chop(1);
    mFile.reset();
    return row.split(";");
}

void CSV::deleteRow(int n) {
    QFile tmp("tmp" + mFile.fileName());
    tmp.open(QIODevice::WriteOnly);
    for (int i = 0; i < this->getRowsNum(); i++) {
        if (i == n) {continue;}
        QString row = this->getRow(i).join(";").append("\n");
        tmp.write(row.toUtf8());
    }
    // replace old file with updated one
    QString fileName = mFile.fileName();
    mFile.remove();
    mFile.close();
    tmp.rename(fileName);
    tmp.close();
    mFile.setFileName(fileName);
    mFile.open(QIODevice::ReadWrite);
}

void CSV::insertRow(QStringList values) {
    // validate input
    for (int i = 0; i < values.count(); i++) {
        values[i] = values[i].replace("\n", "NL").replace(";", ",");
    }
    // go to end of file
    mFile.seek(mFile.size());
    QString row = values.join(";").append("\n");
    mFile.write(row.toUtf8());
    mFile.reset();
}

int CSV::getRowsNum() {
    int num = QString(mFile.readAll()).count("\n");
    mFile.reset();
    return num;
}

CSV::~CSV() {
    mFile.close();
}
