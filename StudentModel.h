//
// Created by w on 2022/12/22.
//

#ifndef STUDENTSYSTEM_STUDENTMODEL_H
#define STUDENTSYSTEM_STUDENTMODEL_H

#include "QString"
#include "QSqlRecord"

class StudentModel {
public:
    QString id = "000";
    QString name = "[no name]";
    double math = 0.0;
    double english = 0.0;
    double compute = 0.0;
    double average = 0.0;

public:
    double getAverage();

    double getSum();

    QSqlRecord getRecord();

    StudentModel(QString id, QString name, double math, double english, double compute);

    StudentModel();

    StudentModel(QString id);
};

#endif //STUDENTSYSTEM_STUDENTMODEL_H
