#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "visualizationdlg.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(600,500);

    // attributes
    ui->particalsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->particalsTable->setShowGrid(true);
    ui->particalsTable->horizontalHeader()->setVisible(true);
    ui->particalsTable->verticalHeader()->setVisible(true);

    // setup table header
    QStringList tableHeader;
    tableHeader << tr("Mass") << tr("x") << tr("y") << tr("dx") << tr("dy");
    ui->particalsTable->setColumnCount(5);
    ui->particalsTable->setHorizontalHeaderLabels(tableHeader);
}

MainWindow::~MainWindow()
{
    delete data;
    delete ui;
}

void MainWindow::on_addBtn_clicked()
{
    // Get the results
    double mass = ui->massInput->value();
    Point pos(ui->xInput->value(), ui->yInput->value());
    Point d(ui->dxInput->value(), ui->dyInput->value());
    // Add to the list
    this->data->addPartical(Partical(mass,pos,d));
    // Show in the table
    ui->particalsTable->setRowCount(this->data->getLen());
    ui->particalsTable->setItem(this->data->getLen()-1,0,new QTableWidgetItem(QString::number(mass)));
    ui->particalsTable->setItem(this->data->getLen()-1,1,new QTableWidgetItem(QString::number(pos.x)));
    ui->particalsTable->setItem(this->data->getLen()-1,2,new QTableWidgetItem(QString::number(pos.y)));
    ui->particalsTable->setItem(this->data->getLen()-1,3,new QTableWidgetItem(QString::number(d.x)));
    ui->particalsTable->setItem(this->data->getLen()-1,4,new QTableWidgetItem(QString::number(d.y)));
    // Set to 0
    ui->massInput->setValue(.0);
    ui->xInput->setValue(.0);
    ui->yInput->setValue(.0);
    ui->dxInput->setValue(.0);
    ui->dyInput->setValue(.0);
}

void MainWindow::on_startBtn_clicked()
{
   if(this->data->getLen()==0)return;
   VisualizationDlg vis(nullptr, this->data);
   vis.exec();
}
