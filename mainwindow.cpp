//
// Created by w on 2022/12/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "qdebug.h"
#include "QtSql/QtSql"
#include "utils/ReadOnlyDelegate.h"
#include "QTableWidget"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    currentIndex = new QModelIndex;
    bindSlot();

    model = new QSqlTableModel(this);
    model->setTable("student");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, "学号");
    model->setHeaderData(1, Qt::Horizontal, "姓名");
    model->setHeaderData(2, Qt::Horizontal, courseList.value("math", "高等数学"));
    model->setHeaderData(3, Qt::Horizontal, courseList.value("english", "英语"));
    model->setHeaderData(4, Qt::Horizontal, courseList.value("compute", "计算机导论"));
    model->setHeaderData(5, Qt::Horizontal, "平均成绩");
    ui->tableView->setItemDelegateForColumn(5, new ReadOnlyDelegate);

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    initStatusBar();
}

void MainWindow::initStatusBar() {
    statusBarLeft = new QLabel("欢迎使用学生成绩管理系统");
    ui->statusbar->addWidget(statusBarLeft);
    statusBarRight = new QLabel(QString("总人数：%1").arg(model->rowCount()));
    ui->statusbar->addPermanentWidget(statusBarRight);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::bindSlot() {
    connect(ui->action_addNewLine, &QAction::triggered, this, &MainWindow::handle_menu_addNewLine);
    connect(ui->action_showStat, &QAction::triggered, this, &MainWindow::handle_menu_showStat);
}

[[maybe_unused]] void MainWindow::on_tableView_customContextMenuRequested(const QPoint &pos) {
    QMenu menu;
    //添加右键菜单的选项
    menu.addAction("添加一行", this, &MainWindow::handle_menu_addNewLine);
    //显示menu菜单并设置其显示位置为鼠标位置
    menu.exec(QCursor::pos());
}

[[maybe_unused]] void MainWindow::on_tableView_pressed(const QModelIndex &index) {
    currentIndex = &index;

    auto record = model->record(index.row());

    setScoreInStatusBar(new StudentModel(record.value("id").toString(),
                                         record.value("name").toString(),
                                         record.value("math").toDouble(),
                                         record.value("english").toDouble(),
                                         record.value("compute").toDouble()
    ));
}

void MainWindow::setScoreInStatusBar(StudentModel *studentModel) {
    auto str = QString::asprintf("[%s]%s 总成绩：%0.2lf 平均：%0.2lf", studentModel->id.toStdString().c_str(),
                                 studentModel->name.toStdString().c_str(),
                                 studentModel->getSum(), studentModel->getAverage());
    statusBarLeft->setText(str);
}

void MainWindow::handle_menu_addNewLine() {
    model->insertRow(model->rowCount());
    qDebug() << "handle_menu_addNewLineAtRear";
    refreshUI();
}

[[maybe_unused]] void MainWindow::on_pushButton_Save_clicked() {
    model->database().transaction();
    if (model->submitAll()) {
        model->database().commit();
        QMessageBox::information(this, "提示", "保存成功");
    } else {
        model->database().rollback();
        QMessageBox::warning(this, "错误", model->lastError().text());
    }
}

void MainWindow::on_pushButton_search_clicked() {
    QString searchValue = ui->lineEdit_searchValue->text();
    model->setFilter(QString::asprintf("name like '%%%s%%' or id like '%%%s%%'", searchValue.toStdString().c_str(),
                                       searchValue.toStdString().c_str()));
}

[[maybe_unused]] void MainWindow::on_pushButton_Revert_clicked() {
    model->revertAll();
    model->revertAll();
    QMessageBox::information(this, "提示", "已还原修改");
}

[[maybe_unused]] void MainWindow::on_pushButton_Reload_clicked() {
    ui->tableView->sortByColumn(-1, Qt::SortOrder::AscendingOrder);
    ui->tableView->update();
    ui->tableView->repaint();
}

void MainWindow::refreshUI() {
    initStatusBar();
}

void MainWindow::handle_menu_showStat() {
    QTableWidget *tableWidget = new QTableWidget();
    tableWidget->setAlternatingRowColors(true);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectItems);
    tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setWindowTitle("统计结果");
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setSortingEnabled(true);

    QStringList headerList;
    headerList << "课程名" << "平均成绩" << "最高分" << "最低分" << "不及格" << "60-69分" << "70-79分" << "80-89分"
               << "90分以上";
    tableWidget->setColumnCount(headerList.count());
    tableWidget->setHorizontalHeaderLabels(headerList);
    tableWidget->setRowCount(courseList.count());
    tableWidget->resize(
            tableWidget->horizontalHeader()->defaultSectionSize() * (tableWidget->horizontalHeader()->count() + 0) +
            tableWidget->horizontalHeader()->minimumSectionSize(),
            tableWidget->verticalHeader()->defaultSectionSize() * (tableWidget->verticalHeader()->count() + 1));

    auto it = courseList.begin();
    for (int row = 0; it != courseList.end(); it++, row++) {
        tableWidget->setItem(row, 0, new QTableWidgetItem(it.value()));

        QSqlQuery query(model->database());
        QString sql = QString("select avg(%1)                                     as avg,\n"
                              "       max(%1)                                     as max,\n"
                              "       min(%1)                                     as min,\n"
                              "       (select count() from student where %1 < 60) as fail,\n"
                              "       (select count() from student where 60 <= %1 and %1 <= 69) as s60,\n"
                              "       (select count() from student where 70 <= %1 and %1 <= 79) as s70,\n"
                              "       (select count() from student where 80 <= %1 and %1 <= 89) as s80,\n"
                              "       (select count() from student where 90 <= %1) as s90\n"
                              "from student").arg(it.key());
        query.exec(sql);
        query.next();
        qDebug() << "query.value(\"avg\") " << query.value("avg").toString();

        QString avg = query.value("avg").toString();
        QString max = query.value("max").toString();
        QString min = query.value("min").toString();
        QString fail = query.value("fail").toString();
        QString s60 = query.value("s60").toString();
        QString s70 = query.value("s70").toString();
        QString s80 = query.value("s80").toString();
        QString s90 = query.value("s90").toString();
        tableWidget->setItem(row, 1, new QTableWidgetItem(avg));
        tableWidget->setItem(row, 2, new QTableWidgetItem(max));
        tableWidget->setItem(row, 3, new QTableWidgetItem(min));
        tableWidget->setItem(row, 4, new QTableWidgetItem(fail));
        tableWidget->setItem(row, 5, new QTableWidgetItem(s60));
        tableWidget->setItem(row, 6, new QTableWidgetItem(s70));
        tableWidget->setItem(row, 7, new QTableWidgetItem(s80));
        tableWidget->setItem(row, 8, new QTableWidgetItem(s90));
    }
    model->database().exec().exec();
    tableWidget->show();
}
