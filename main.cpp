#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"
#include "test_data.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    if (!createConnection())
        return 1;
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}
