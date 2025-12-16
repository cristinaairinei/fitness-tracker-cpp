#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include "../controller/Service.h"

class MainWindow : public QMainWindow { //permite conectarea butoanelor la sloturi
    Q_OBJECT

private:
    Service& service;

    QLineEdit *nameEdit, *typeEdit, *durationEdit, *dateEdit;
    QComboBox *effortCombo;
    QPushButton *addButton, *removeButton, *updateButton, *filterButton, *undoButton, *redoButton, *saveButton;
    QTableWidget *table;

    void setupUI();
    void populateTable();

private slots://actiuni cand apasam butoanele
    void addActivity();
    void removeActivity();
    void updateActivity();
    void undo();
    void redo();
    void saveToCSV();

public:
    MainWindow(Service& service, QWidget* parent = nullptr);//constructor
};
