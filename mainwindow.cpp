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
#include "QFileDialog"
#include "test_data.h"
#include <QtConcurrent/QtConcurrent>
#include "libs/BasicExcel.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowTitle("学生成绩管理系统");
    initModel();
    refreshStatusBar();
    bindSlot();
}

void MainWindow::initModel() {
    QString table = QString("student");
    initModel(table);
}

void MainWindow::initModel(QString &table) {
    model = new QSqlTableModel(this);
    model->setTable(table);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    for (int i = 0; i < tableHeaderList.size(); ++i) {
        model->setHeaderData(i, Qt::Horizontal, std::get<1>(tableHeaderList[i]));
    }
    ui->tableView->setItemDelegateForColumn(5, new ReadOnlyDelegate);

    ui->tableView->setModel(model);
    connect(model, &QSqlTableModel::dataChanged, this, &MainWindow::handle_model_dataChanged);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

//    itemSelectionModel = new QItemSelectionModel(model);
//    connect(itemSelectionModel, &QItemSelectionModel::currentChanged, this, &MainWindow::handle_model_dataChanged);
//    ui->tableView->setSelectionModel(itemSelectionModel);

    refreshUI();
}

void MainWindow::handle_model_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                                          const QVector<int> &roles) {
    Q_UNUSED(bottomRight)
    Q_UNUSED(roles)
    qDebug() << QString::asprintf("handle_model_dataChanged [%d,%d]", topLeft.row(), topLeft.column());
    reCalcAverage(topLeft);
}

void MainWindow::reCalcAverage(const QModelIndex &index) {
    auto record = model->record(index.row());
    StudentModel studentModel(record.value("id").toString(),
                              record.value("name").toString(),
                              record.value("math").toDouble(),
                              record.value("english").toDouble(),
                              record.value("compute").toDouble());
    if (record.value("average").toDouble() != studentModel.getAverage()) {
        qDebug() << record.value("average").toDouble() << " " << studentModel.getAverage();
        model->setData(model->index(index.row(), record.indexOf("average")), studentModel.getAverage());
    }
}

void MainWindow::initStatusBar() {
    if (statusBarLeft == nullptr) {
        statusBarLeft = new QLabel("欢迎使用学生成绩管理系统");
        ui->statusbar->addWidget(statusBarLeft);
    }
    if (statusBarRight == nullptr) {
        statusBarRight = new QLabel(QString("总人数：%1").arg(model->rowCount()));
        ui->statusbar->addPermanentWidget(statusBarRight);
    }
}

void MainWindow::refreshStatusBar() {
    if (statusBarLeft == nullptr) {
        statusBarLeft = new QLabel("欢迎使用学生成绩管理系统");
        ui->statusbar->addWidget(statusBarLeft);
    }
    if (statusBarRight == nullptr) {
        statusBarRight = new QLabel(QString("总人数：0"));
        ui->statusbar->addPermanentWidget(statusBarRight);
    }
    statusBarLeft->setText("欢迎使用学生成绩管理系统");
    statusBarRight->setText(QString("总人数：%1").arg(model->rowCount()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::bindSlot() {
    connect(ui->action_addNewLine, &QAction::triggered, this, &MainWindow::handle_menu_action_addNewLine);
    connect(ui->action_showStat, &QAction::triggered, this, &MainWindow::handle_menu_action_showStat);
    connect(ui->action_newDatabase, &QAction::triggered, this, &MainWindow::handle_menu_action_newDatabase);
    connect(ui->action_openDatabase, &QAction::triggered, this, &MainWindow::handle_menu_action_openDatabase);
    connect(ui->action_openTestDatabase, &QAction::triggered, this, &MainWindow::handle_menu_action_openTestDatabase);
    connect(ui->action_closeDatabase, &QAction::triggered, this, &MainWindow::handle_menu_action_closeDatabase);
    connect(ui->action_exportExcel, &QAction::triggered, this, &MainWindow::handle_menu_action_exportExcel);
}

[[maybe_unused]] void MainWindow::on_tableView_customContextMenuRequested(const QPoint &pos) {
    QMenu menu;
    //添加右键菜单的选项
    menu.addAction("添加一行", this, &MainWindow::handle_menu_action_addNewLine);
    menu.addAction("删除行", this, &MainWindow::handle_menu_action_removeLine);
    //显示menu菜单并设置其显示位置为鼠标位置
    menu.exec(QCursor::pos());
}

void MainWindow::handle_menu_action_removeLine() {
    QModelIndex index = ui->tableView->currentIndex();
    model->removeRow(index.row());
}

[[maybe_unused]] void MainWindow::on_tableView_pressed(const QModelIndex &index) {
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

void MainWindow::handle_menu_action_addNewLine() {
    if (!checkDatabase())return;
//    StudentModel studentModel(QString(model->rowCount()));
//    model->insertRecord(model->rowCount(), studentModel.getRecord());

    model->insertRow(model->rowCount());
    int row = model->rowCount() - 1;
    int colLast = model->columnCount() - 1;
    QModelIndex index =
            model->index(model->rowCount() - 1, model->columnCount() - 1);
    qDebug() << "handle_menu_action_addNewLine " << index.row() << "," << index.column();
    model->setData(model->index(row, 0), QVariant(QString::asprintf("%03d", row + 1)));
    model->setData(model->index(row, 1), QVariant("[no name]"));
    model->setData(model->index(row, 2), QVariant(0));
    model->setData(model->index(row, 3), QVariant(0));
    model->setData(model->index(row, 4), QVariant(0));
    model->setData(model->index(row, colLast), QVariant(0));
    refreshUI();
}

[[maybe_unused]] void MainWindow::on_pushButton_Save_clicked() {
    if (!checkDatabase())return;
    model->database().transaction();
    if (model->submitAll()) {
        model->database().commit();
        QMessageBox::information(this, "提示", "保存成功");
    } else {
        model->database().rollback();
        QMessageBox::critical(this, "错误", "数据错误，请检查数据后重试");
        qDebug() << "on_pushButton_Save_clicked " << model->lastError().text();
    }
}

void MainWindow::on_pushButton_search_clicked() {
    if (!checkDatabase())return;
    QString searchValue = ui->lineEdit_searchValue->text();
    model->setFilter(QString::asprintf("name like '%%%s%%' or id like '%%%s%%'", searchValue.toStdString().c_str(),
                                       searchValue.toStdString().c_str()));
}

[[maybe_unused]] void MainWindow::on_pushButton_Revert_clicked() {
    if (!checkDatabase())return;
    model->revertAll();
    model->revertAll();
    QMessageBox::information(this, "提示", "已还原修改");
}

[[maybe_unused]] void MainWindow::on_pushButton_Reload_clicked() {
    if (!checkDatabase())return;
    ui->tableView->sortByColumn(-1, Qt::SortOrder::AscendingOrder);
    ui->tableView->update();
    ui->tableView->repaint();
}

void MainWindow::refreshUI() {
    refreshStatusBar();
}

void MainWindow::handle_menu_action_showStat() {
    // 检查数据库是否可用
    if (!checkDatabase())return;
    // 构造窗体
    QTableWidget *tableWidget = new QTableWidget();
    tableWidget->setAlternatingRowColors(true);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectItems);
    tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setWindowTitle("统计结果");
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setSortingEnabled(true);

    // 构造表头
    QStringList headerList;
    headerList << "课程名" << "平均成绩" << "最高分" << "最低分" << "不及格" << "60-69分" << "70-79分" << "80-89分"
               << "90分以上";
    tableWidget->setColumnCount(headerList.count());
    tableWidget->setHorizontalHeaderLabels(headerList);
    tableWidget->setRowCount(courseList.count());

    // 设置合适大小
    tableWidget->resize(
            tableWidget->horizontalHeader()->defaultSectionSize() * (tableWidget->horizontalHeader()->count() + 0) +
            tableWidget->horizontalHeader()->minimumSectionSize(),
            tableWidget->verticalHeader()->defaultSectionSize() * (tableWidget->verticalHeader()->count() + 1));

    // 计算并添加统计数据
    for (int row = 0; row < courseList.count(); row++) {
        tableWidget->setItem(row, 0, new QTableWidgetItem(std::get<1>(courseList[row])));

        QSqlQuery query(model->database());
        QString sql = QString("select avg(%1)                                     as avg,\n"
                              "       max(%1)                                     as max,\n"
                              "       min(%1)                                     as min,\n"
                              "       (select count() from student where %1 < 60) as fail,\n"
                              "       (select count() from student where 60 <= %1 and %1 <= 69) as s60,\n"
                              "       (select count() from student where 70 <= %1 and %1 <= 79) as s70,\n"
                              "       (select count() from student where 80 <= %1 and %1 <= 89) as s80,\n"
                              "       (select count() from student where 90 <= %1) as s90\n"
                              "from student").arg(std::get<0>(courseList[row]));
        query.exec(sql);
        query.next();
        qDebug() << "query.value(\"avg\") " << query.value("avg").toString();

        QString avg = QString::asprintf("%0.2lf", query.value("avg").toDouble());
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

void MainWindow::handle_menu_action_openTestDatabase() {
    QString dbName(":memory:");
    if (!reBuildDatabase(dbName)) {
        QMessageBox::critical(this, "错误", "打开测试数据库失败");
        return;
    }
    setWindowTitle(QString("当前操作数据库：%1").arg("测试数据库:memory:"));
    initModel();
}

void MainWindow::handle_menu_action_openDatabase() {
    QString fileName = QFileDialog::getOpenFileName(this, "请选择数据库", ".", "SQLite 文件 (*.dat *.sqlite)");
    if (fileName.isEmpty()) {
        return;
    }
    databaseFileName = fileName;
    reconnectDatabase(fileName);
}

bool MainWindow::reconnectDatabase(QString &name) {
    db.close();
    db.setDatabaseName(name);
    if (!db.open()) {
        qDebug() << "reconnectDatabase: " << db.lastError();
        QMessageBox::critical(this, "错误",
                              "无法打开数据库", QMessageBox::Cancel);
        return false;
    }
    initModel();
    setWindowTitle(QString("当前操作数据库：%1").arg(name));
    return true;
}

void MainWindow::handle_menu_action_newDatabase() {
    QString fileName = QFileDialog::getSaveFileName(this, "请选择数据库保存位置", "./database.dat",
                                                    "SQLite 文件 (*.dat *.sqlite)");
    qDebug() << "handle_menu_action_newDatabase " << fileName;
    if (fileName.isEmpty())
        return;
    if (reBuildDatabase(fileName)) {
        reconnectDatabase(fileName);
    }
}

bool MainWindow::reBuildDatabase(QString &name) {
    db.close();
    db.setDatabaseName(name);
    if (!db.open())
        return false;

    QSqlQuery query(db);
    query.exec("drop table student");
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
    qDebug() << "[reBuildDatabase] query: " << test << " ,error: " << query.lastError();
    QVector<StudentModel *> vector;
    vector.push_back(new StudentModel(QString("001"), QString("张磊"), 80, 73, 90));
    vector.push_back(new StudentModel(QString("002"), QString("王鹏"), 76, 69, 70));
    vector.push_back(new StudentModel(QString("003"), QString("黎明"), 60, 78, 69));
    vector.push_back(new StudentModel(QString("004"), QString("刘鹏"), 55, 66, 60));
    vector.push_back(new StudentModel(QString("005"), QString("李四"), 78, 70, 80));
    vector.push_back(new StudentModel(QString("006"), QString("张佳"), 43, 50, 60));
    vector.push_back(new StudentModel(QString("007"), QString("赵平"), 89, 85, 79));
    vector.push_back(new StudentModel(QString("008"), QString("高洁"), 90, 89, 70));

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
    return test;
}

void MainWindow::handle_menu_action_closeDatabase() {
    db.close();
    QString table = "";
    initModel(table);
    setWindowTitle("学生成绩管理系统");
}

bool MainWindow::checkDatabase() {
    QSqlQuery query(db);
    query.exec("select count(*) from student");
    if (!query.next()) {
        QMessageBox::warning(this, "警告", "无可操作数据库");
        return false;
    }
    return true;
}

void MainWindow::handle_menu_action_exportExcel() {
//    QtConcurrent::run([&]() {
    // 准备Excel
    YExcel::BasicExcel e;
    e.New(1);
    QVector<std::tuple<QString, QString>> rankList = courseList;
    rankList.push_back({"average", "平均成绩"});

    /**
     * 复制tableView的表头到Sheet表头
     */
    auto insertTableHeaderRow = [&](YExcel::BasicExcelWorksheet *sheet) {
        for (int col = 0; col < model->columnCount(); ++col) {
            auto headerData = model->headerData(col, Qt::Horizontal);
            sheet->Cell(0, col)->SetWString(QString2Wchar(headerData.toString()));
        }
    };

    YExcel::BasicExcelWorksheet *sheet1 = e.GetWorksheet(0ULL);
    if (!sheet1)
        return;
    insertTableHeaderRow(sheet1);
    for (int row = 0; row < model->rowCount(); row++) {
        auto recordItem = model->record(row);
        for (int col = 0; col < recordItem.count(); ++col) {
            auto value = recordItem.value(col);
            sheet1->Cell(row + 1, col)->SetWString(QString2Wchar(value.toString()));
        }
    }

    for (const auto &rankItem: rankList) {
        YExcel::BasicExcelWorksheet *worksheet = e.AddWorksheet(
                QString2Wchar(QString("%1排名").arg(std::get<1>(rankItem))));
        if (!worksheet)
            continue;
        insertTableHeaderRow(worksheet);

        // 添加数据到Excel
        QSqlQuery query(db);
        query.exec(QString("select *\n"
                           "from student\n"
                           "order by %1 desc;").arg(std::get<0>(rankItem)));
        for (int row = 1; query.next(); row++) {
            QSqlRecord record = query.record();
            for (int col = 0; col < record.count(); col++) {
                worksheet->Cell(row, col)->SetWString(QString2Wchar(record.value(col).toString()));
            }
        }
    }

    // 保存Excel
    QString saveFileName = QFileDialog::getSaveFileName(this, "请选择保存路径", ".", "Excel (*.xls)");
    if (saveFileName.isEmpty())
        return;
    QFile file(saveFileName);
    if (file.exists() && !file.remove()) {
        QMessageBox::critical(this, "警告", QString("%1文件被占用，无法删除").arg(saveFileName));
        return;
    }
    bool result = e.SaveAs(saveFileName.toStdString().c_str());
    if (result) {
        QMessageBox::information(this, "提示", "保存成功");
    } else {
        QMessageBox::critical(this, "警告", "保存失败");
    }
//    });
}
