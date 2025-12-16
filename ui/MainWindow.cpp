#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QHeaderView>
#include <fstream>

MainWindow::MainWindow(Service& service, QWidget* parent)
    : QMainWindow(parent), service(service) {
    setupUI();
    populateTable();
}

void MainWindow::setupUI() {
    QWidget* centralWidget = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;

    // Input fields
    QHBoxLayout* formLayout = new QHBoxLayout;
    nameEdit = new QLineEdit;
    typeEdit = new QLineEdit;
    durationEdit = new QLineEdit;
    dateEdit = new QLineEdit;
    effortCombo = new QComboBox;
    effortCombo->addItems({"easy", "medium", "hard"});
    //etichete corespunzatoare

    formLayout->addWidget(new QLabel("Name:")); formLayout->addWidget(nameEdit);
    formLayout->addWidget(new QLabel("Type:")); formLayout->addWidget(typeEdit);
    formLayout->addWidget(new QLabel("Duration:")); formLayout->addWidget(durationEdit);
    formLayout->addWidget(new QLabel("Date:")); formLayout->addWidget(dateEdit);
    formLayout->addWidget(new QLabel("Effort:")); formLayout->addWidget(effortCombo);

    // Buttons - two rows
    QHBoxLayout* row1 = new QHBoxLayout;
    QHBoxLayout* row2 = new QHBoxLayout;

    addButton = new QPushButton("Add");
    removeButton = new QPushButton("Remove");
    updateButton = new QPushButton("Update");
    filterButton = new QPushButton("Filter");
    undoButton = new QPushButton("Undo");
    redoButton = new QPushButton("Redo");
    saveButton = new QPushButton("Save CSV");

    row1->addWidget(addButton);
    row1->addWidget(removeButton);
    row1->addWidget(updateButton);
    row2->addWidget(filterButton);
    row2->addWidget(undoButton);
    row2->addWidget(redoButton);
    row2->addWidget(saveButton);

    // Table
    table = new QTableWidget;
    table->setColumnCount(5);
    QStringList headers{"Name", "Type", "Duration", "Date", "Effort"};
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    layout->addLayout(formLayout);
    layout->addLayout(row1);
    layout->addLayout(row2);
    layout->addWidget(table);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Button styles
    QString pinkStyle = "QPushButton { background-color: pink; border-radius: 10px; padding: 6px; }";
    for (auto btn : {addButton, removeButton, updateButton, filterButton, undoButton, redoButton, saveButton})
        btn->setStyleSheet(pinkStyle); //pink

    // Connections between functions and buttons
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addActivity);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeActivity);
    connect(updateButton, &QPushButton::clicked, this, &MainWindow::updateActivity);
    connect(undoButton, &QPushButton::clicked, this, &MainWindow::undo);
    connect(redoButton, &QPushButton::clicked, this, &MainWindow::redo);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveToCSV);

    connect(filterButton, &QPushButton::clicked, this, [this]() {
        QString type = typeEdit->text();
        QString effort = effortCombo->currentText();

        std::shared_ptr<FilterStrategy> strategy;

        if (!type.isEmpty() && !effort.isEmpty()) {
            strategy = std::make_shared<AndFilter>(
                std::make_shared<TypeFilter>(type.toStdString()),
                std::make_shared<EffortFilter>(effort.toStdString())
                );
        } else if (!type.isEmpty()) {
            strategy = std::make_shared<TypeFilter>(type.toStdString());
        } else if (!effort.isEmpty()) {
            strategy = std::make_shared<EffortFilter>(effort.toStdString());
        } else {
            populateTable();
            return;
        }
        //aplicam filtrul si afisam in tabel

        auto filtered = service.filter(strategy);
        table->setRowCount(filtered.size());

        for (int i = 0; i < filtered.size(); ++i) {
            const auto& a = filtered[i];
            table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(a.getName())));
            table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(a.getType())));
            table->setItem(i, 2, new QTableWidgetItem(QString::number(a.getDuration())));
            table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(a.getDate())));
            table->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(a.getEffort())));
        }
    });

    // Select row → fill fields
    connect(table, &QTableWidget::cellClicked, this, [this](int row, int) {
        nameEdit->setText(table->item(row, 0)->text());
        typeEdit->setText(table->item(row, 1)->text());
        durationEdit->setText(table->item(row, 2)->text());
        dateEdit->setText(table->item(row, 3)->text());
        effortCombo->setCurrentText(table->item(row, 4)->text());
    });
}

void MainWindow::populateTable() {
    auto all = service.getAllActivities();
    table->setRowCount(all.size());

    for (int i = 0; i < all.size(); ++i) {
        const auto& a = all[i];
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(a.getName())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(a.getType())));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(a.getDuration())));
        table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(a.getDate())));
        table->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(a.getEffort())));
    }
}

void MainWindow::addActivity() {
    try {
        service.addActivity(Activity(
            nameEdit->text().toStdString(),
            typeEdit->text().toStdString(),
            durationEdit->text().toInt(),
            dateEdit->text().toStdString(),
            effortCombo->currentText().toStdString()
            ));
        populateTable();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::removeActivity() {
    try {
        service.removeActivity(nameEdit->text().toStdString());
        populateTable();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::updateActivity() {
    try {
        service.updateActivity(Activity(
            nameEdit->text().toStdString(),
            typeEdit->text().toStdString(),
            durationEdit->text().toInt(),
            dateEdit->text().toStdString(),
            effortCombo->currentText().toStdString()
            ));
        populateTable();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::undo() {
    try {
        service.undo();
        populateTable();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Undo Error", e.what());
    }
}

void MainWindow::redo() {
    try {
        service.redo();
        populateTable();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Redo Error", e.what());
    }
}

void MainWindow::saveToCSV() {
    std::ofstream fout("activities.csv");
    for (const auto& a : service.getAllActivities()) {
        fout << a.getName() << "," << a.getType() << ","
             << a.getDuration() << "," << a.getDate() << ","
             << a.getEffort() << "\n";
    }
    QMessageBox::information(this, "Saved", "Activities saved to activities.csv");
}
