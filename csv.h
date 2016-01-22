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
    void clear();
    virtual ~CSV();
private:
    QFile mFile;
};

#endif // CSV_H
