//
// Created by w on 2022/12/22.
//

#include <QVariant>
#include "StudentModel.h"

[[maybe_unused]] double StudentModel::getAverage() {
    if (average != 0.0) {
        return average;
    }
    return QString::asprintf("%0.2lf", (math + english + compute) / 3.0).toDouble();
}

StudentModel::StudentModel(QString id, QString name, double math, double english, double compute) {
    this->id = id;
    this->name = name;
    this->math = math;
    this->english = english;
    this->compute = compute;
}

double StudentModel::getSum() {
    return math + english + compute;
}

StudentModel::StudentModel() {

}

QSqlRecord StudentModel::getRecord() {
    QSqlRecord record;
    record.setValue("id", QVariant(id));
    record.setValue("name", QVariant(name));
    record.setValue("math", QVariant(math));
    record.setValue("english", QVariant(english));
    record.setValue("compute", QVariant(compute));
    record.setValue("average", QVariant(getAverage()));
    return record;
}

StudentModel::StudentModel(QString id) {
    this->id = id;
}
