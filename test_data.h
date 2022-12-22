//
// Created by w on 2022/12/21.
//

#ifndef STUDENTSYSTEM_TEST_DATA_H
#define STUDENTSYSTEM_TEST_DATA_H

#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QSqlRecord>
#include "QDebug"
#include "StudentModel.h"
#include "QVariantList"

static bool createConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/test.dat");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                              QObject::tr("Unable to establish a database connection.\n"
                                          "This example needs SQLite support. Please read "
                                          "the Qt SQL driver documentation for information how "
                                          "to build it.\n\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query(db);
    bool test = query.exec(
            "create table student\n"
            "(\n"
            "    id      varchar(255) not null\n"
            "        constraint student_pk\n"
            "            primary key,\n"
            "    name    varchar(255) not null,\n"
            "    math    double       not null,\n"
            "    english double       not null,\n"
            "    compute double       not null,\n"
            "    average double       not null\n"
            ")"
    );
    qDebug() << "[createConnection] query: " << test << " ,error: " << query.lastError();
    QVector<StudentModel*> vector;
    vector.push_back(new StudentModel(QString("001"), QString("张磊"), 80, 73, 90));
    vector.push_back(new StudentModel(QString("002"), QString("王鹏"), 76, 69, 70));
    vector.push_back(new StudentModel(QString("003"), QString("黎明"), 60, 78, 69));
    vector.push_back(new StudentModel(QString("004"), QString("黎明"), 66, 44, 55));

    for (auto item: vector) {
        query.prepare("insert into student values(?,?,?,?,?,?)");
        query.addBindValue(item->id);
        query.addBindValue(item->name);
        query.addBindValue(item->math);
        query.addBindValue(item->english);
        query.addBindValue(item->compute);
        query.addBindValue(item->getAverage());
        query.exec();
    }
    return true;
}

#endif //STUDENTSYSTEM_TEST_DATA_H

