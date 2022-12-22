//
// Created by w on 2022/12/21.
//

#ifndef STUDENTSYSTEM_MAINWINDOW_H
#define STUDENTSYSTEM_MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMap>
#include "StudentModel.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

#pragma execution_character_set("utf-8")

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QSqlTableModel;

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    QMap<QString, QString> courseList = {
            {"math",    "高等数学"},
            {"english", "英语"},
            {"compute", "计算机导论"},
    };

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    const QModelIndex *currentIndex;
    QLabel *statusBarLeft;
    QLabel *statusBarRight;
    QString databaseFileName = "";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    void bindSlot();

    void handle_menu_action_addNewLine();

    void handle_menu_action_showStat();

    void handle_menu_action_openDatabase();

    void handle_menu_action_newDatabase();

    void handle_menu_action_openTestDatabase();

    void handle_menu_action_closeDatabase();

    void initStatusBar();

    void initModel();

    void setScoreInStatusBar(StudentModel *studentModel);

    void refreshUI();

    bool reconnectDatabase(QString &name);

    bool reBuildDatabase(QString &name);

    bool checkDatabase();

private slots:

    [[maybe_unused]] void on_tableView_customContextMenuRequested(const QPoint &pos);

    [[maybe_unused]] void on_tableView_pressed(const QModelIndex &index);

    [[maybe_unused]] void on_pushButton_Save_clicked();

    [[maybe_unused]] void on_pushButton_Revert_clicked();

    [[maybe_unused]] void on_pushButton_Reload_clicked();

    [[maybe_unused]] void on_pushButton_search_clicked();
};


#endif //STUDENTSYSTEM_MAINWINDOW_H
