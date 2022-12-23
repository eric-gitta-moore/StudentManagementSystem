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
#include "QItemSelectionModel"
#include "utils/tools.hpp"
#include "map"
#include "QSqlTableModel"

#pragma execution_character_set("utf-8")

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    /// 课程列表
    QVector<std::tuple<QString, QString>> courseList = {
            {"math",    "高等数学"},
            {"english", "英语"},
            {"compute", "计算机导论"}
    };

    /// 表头信息
    QVector<std::tuple<QString, QString>> tableHeaderList = {
            {"id",      "学号"},
            {"name",    "姓名"},
            {"math",    "高等数学"},
            {"english", "英语"},
            {"compute", "计算机导论"},
            {"average", "平均成绩"}
    };

private:
    /// UI窗口指针
    Ui::MainWindow *ui;

    /// 数据模型
    QSqlTableModel *model;

    /// 状态栏左侧通知
    QLabel *statusBarLeft = nullptr;

    /// 状态栏右侧通知
    QLabel *statusBarRight = nullptr;

    /// 当前打开的数据库文件名
    QString databaseFileName = "";

    /// 数据库句柄
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    /// QTableView选择模型
    QItemSelectionModel *itemSelectionModel;

    /// 批量绑定所有信号槽
    void bindSlot();

    /// 在底部添加新行
    void handle_menu_action_addNewLine();

    /// 删除当前行
    void handle_menu_action_removeLine();

    /// 显示统计信息
    void handle_menu_action_showStat();

    /// 打开现有数据库文件
    void handle_menu_action_openDatabase();

    /// 创建新数据库文件
    void handle_menu_action_newDatabase();

    /// 打开测试数据库
    void handle_menu_action_openTestDatabase();

    /// 关闭当前数据库
    void handle_menu_action_closeDatabase();

    /// 导出当前表格和统计信息到Excel
    void handle_menu_action_exportExcel();

    /// 监听模型修改
    void
    handle_model_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

    /// 初始化状态栏
    void initStatusBar();

    /// 重新计算给定行的平均成绩
    void reCalcAverage(const QModelIndex &index);

    /// 刷新状态栏显示
    void refreshStatusBar();

    /// 初始化表格数据模型
    void initModel(QString &table);

    void initModel();

    /// 设置状态栏分数显示
    void setScoreInStatusBar(StudentModel *studentModel);

    /// 刷新UI显示
    void refreshUI();

    /// 重新连接数据库
    bool reconnectDatabase(QString &name);

    /// 重建数据库
    bool reBuildDatabase(QString &name);

    /// 检查数据库可用性
    bool checkDatabase();

private slots:

    /// 监听tableView右键
    [[maybe_unused]] void on_tableView_customContextMenuRequested(const QPoint &pos);

    /// 监听tableView鼠标按下
    [[maybe_unused]] void on_tableView_pressed(const QModelIndex &index);

    /// 保存按钮被点击
    [[maybe_unused]] void on_pushButton_Save_clicked();

    /// 还原修改按钮被点击
    [[maybe_unused]] void on_pushButton_Revert_clicked();

    /// 重新载入数据库按钮被点击
    [[maybe_unused]] void on_pushButton_Reload_clicked();

    /// 搜索按钮被点击
    [[maybe_unused]] void on_pushButton_search_clicked();
};


#endif //STUDENTSYSTEM_MAINWINDOW_H
