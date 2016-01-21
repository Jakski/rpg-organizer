#ifndef CSV_H
#define CSV_H

#include <QString>
#include <QStringList>
#include <QFile>

#include <QDebug>

class CSV
{
public:
    CSV(QString file);
    QStringList getRow(int n);
    void deleteRow(int n);
    void insertRow(QStringList values);
    int getRowsNum();
    virtual ~CSV();
private:
    QFile mFile;
    QStringList load();
    void save();
};

#endif // CSV_H
