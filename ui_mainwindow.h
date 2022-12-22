/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_addNewLine;
    QAction *action_openDatabase;
    QAction *action_saveFile;
    QAction *action_exportExcel;
    QAction *action_showStat;
    QAction *action_newDatabase;
    QAction *action_openTestDatabase;
    QAction *action_closeDatabase;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLineEdit *lineEdit_searchValue;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_search;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_Reload;
    QPushButton *pushButton_Save;
    QPushButton *pushButton_Revert;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(715, 475);
        action_addNewLine = new QAction(MainWindow);
        action_addNewLine->setObjectName(QString::fromUtf8("action_addNewLine"));
        action_openDatabase = new QAction(MainWindow);
        action_openDatabase->setObjectName(QString::fromUtf8("action_openDatabase"));
        action_saveFile = new QAction(MainWindow);
        action_saveFile->setObjectName(QString::fromUtf8("action_saveFile"));
        action_exportExcel = new QAction(MainWindow);
        action_exportExcel->setObjectName(QString::fromUtf8("action_exportExcel"));
        action_showStat = new QAction(MainWindow);
        action_showStat->setObjectName(QString::fromUtf8("action_showStat"));
        action_newDatabase = new QAction(MainWindow);
        action_newDatabase->setObjectName(QString::fromUtf8("action_newDatabase"));
        action_openTestDatabase = new QAction(MainWindow);
        action_openTestDatabase->setObjectName(QString::fromUtf8("action_openTestDatabase"));
        action_closeDatabase = new QAction(MainWindow);
        action_closeDatabase->setObjectName(QString::fromUtf8("action_closeDatabase"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setContextMenuPolicy(Qt::CustomContextMenu);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSortingEnabled(true);

        horizontalLayout->addWidget(tableView);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setMinimumSize(QSize(200, 150));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(label);

        lineEdit_searchValue = new QLineEdit(groupBox_3);
        lineEdit_searchValue->setObjectName(QString::fromUtf8("lineEdit_searchValue"));

        verticalLayout_3->addWidget(lineEdit_searchValue);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        pushButton_search = new QPushButton(groupBox_3);
        pushButton_search->setObjectName(QString::fromUtf8("pushButton_search"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_search->sizePolicy().hasHeightForWidth());
        pushButton_search->setSizePolicy(sizePolicy2);

        verticalLayout_3->addWidget(pushButton_search);


        verticalLayout_2->addWidget(groupBox_3);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        groupBox->setMinimumSize(QSize(200, 0));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_Reload = new QPushButton(groupBox);
        pushButton_Reload->setObjectName(QString::fromUtf8("pushButton_Reload"));

        verticalLayout->addWidget(pushButton_Reload);

        pushButton_Save = new QPushButton(groupBox);
        pushButton_Save->setObjectName(QString::fromUtf8("pushButton_Save"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButton_Save->sizePolicy().hasHeightForWidth());
        pushButton_Save->setSizePolicy(sizePolicy4);
        pushButton_Save->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(pushButton_Save);

        pushButton_Revert = new QPushButton(groupBox);
        pushButton_Revert->setObjectName(QString::fromUtf8("pushButton_Revert"));

        verticalLayout->addWidget(pushButton_Revert);


        verticalLayout_2->addWidget(groupBox);


        horizontalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 715, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(action_openDatabase);
        menu->addAction(action_newDatabase);
        menu->addAction(action_closeDatabase);
        menu->addAction(action_openTestDatabase);
        menu->addAction(action_exportExcel);
        menu_2->addAction(action_addNewLine);
        menu_3->addAction(action_showStat);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_addNewLine->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\344\270\200\350\241\214", nullptr));
        action_openDatabase->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\225\260\346\215\256\345\272\223", nullptr));
        action_saveFile->setText(QCoreApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272", nullptr));
        action_exportExcel->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272Excel", nullptr));
        action_showStat->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\347\273\237\350\256\241\347\273\223\346\236\234", nullptr));
        action_newDatabase->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\346\225\260\346\215\256\345\272\223", nullptr));
        action_openTestDatabase->setText(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\346\265\213\350\257\225\346\225\260\346\215\256\345\272\223", nullptr));
        action_closeDatabase->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\346\225\260\346\215\256\345\272\223", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\255\246\345\217\267\346\210\226\345\247\223\345\220\215\357\274\232", nullptr));
        pushButton_search->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234\346\240\217", nullptr));
        pushButton_Reload->setText(QCoreApplication::translate("MainWindow", "\351\207\215\346\226\260\345\212\240\350\275\275\346\225\260\346\215\256\345\272\223", nullptr));
        pushButton_Save->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\344\277\256\346\224\271", nullptr));
        pushButton_Revert->setText(QCoreApplication::translate("MainWindow", "\350\277\230\345\216\237\344\277\256\346\224\271", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\347\273\237\350\256\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
