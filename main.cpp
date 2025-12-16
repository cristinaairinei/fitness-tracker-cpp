#include <QApplication>
#include "ui/MainWindow.h"
#include "controller/Service.h"
#include "repository/CSVRepository.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    CSVRepository repo("activities.csv");
    //JSONRepository repo("activities.json");


    Service service(repo);


    MainWindow window(service);
    window.setWindowTitle("Fitness Tracker");
    window.resize(900, 600);
    window.show();

    return app.exec();
}
