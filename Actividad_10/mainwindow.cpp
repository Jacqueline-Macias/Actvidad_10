#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPushButton *ordenarPorIdButton = new QPushButton("Ordenar por ID", this);
QPushButton *ordenarPorVoltajeButton = new QPushButton("Ordenar por Voltaje", this);

connect(ordenarPorIdButton, &QPushButton::clicked, this, &MainWindow::ordenarNeuronasPorId);
connect(ordenarPorVoltajeButton, &QPushButton::clicked, this, &MainWindow::ordenarNeuronasPorVoltaje);
