//
// Created by w on 2022/12/22.
//

#ifndef STUDENTSYSTEM_STUDENTMODEL_H
#define STUDENTSYSTEM_STUDENTMODEL_H

#include "QString"

class StudentModel {
public:
    QString id;
    QString name;
    double math;
    double english;
    double compute;
    double average = 0.0;

public:
    double getAverage();

    double getSum();

    StudentModel(QString id, QString name, double math, double english, double compute);

    StudentModel();
};

#endif //STUDENTSYSTEM_STUDENTMODEL_H
