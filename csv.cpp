#include "csv.h"

CSV::CSV(QString file) :
    mFile(file)
{
    mFile.open(QIODevice::ReadWrite | QIODevice::Append);
}

QStringList CSV::getRow(int n) {
    QString row;
    for (int i = 0; i <= n; i++) {
        row = QString(mFile.readLine());
    }
    mFile.reset();
    return row.split(";");
}

void CSV::deleteRow(int n) {

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
    // adding 1 probably, because last endline is ignored
    int num = QString(mFile.readAll()).count("\n") + 1;
    mFile.reset();
    return num;
}

QStringList CSV::load() {
    QString buffer = mFile.readAll();
    mFile.reset();
    return buffer.split("\n");
}

void CSV::save() {

}

CSV::~CSV() {
    mFile.close();
}
