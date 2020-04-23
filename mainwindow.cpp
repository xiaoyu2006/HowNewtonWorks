#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "visualizationdlg.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(600,500);

    ui->startBtn->setDisabled(true);

    // attributes
    ui->particlesTable->setShowGrid(true);
    ui->particlesTable->horizontalHeader()->setVisible(true);
    ui->particlesTable->verticalHeader()->setVisible(true);

    // setup table header
    QStringList tableHeader;
    tableHeader << tr("Mass") << tr("Radius") << tr("x") << tr("y") << tr("dx") << tr("dy");
    ui->particlesTable->setColumnCount(6);
    ui->particlesTable->setHorizontalHeaderLabels(tableHeader);
}

MainWindow::~MainWindow()
{
    delete data;
    delete ui;
}

void MainWindow::on_addBtn_clicked()
{
    ui->startBtn->setDisabled(false);
    // Get the results
    double mass = ui->massInput->value();
    double r = ui->rInput->value();
    Point pos(ui->xInput->value(), ui->yInput->value());
    Point d(ui->dxInput->value(), ui->dyInput->value());
    // Add to the list
    this->data->addParticle(Particle(mass, r, pos, d));
    // Show in the table
    ui->particlesTable->setRowCount(this->data->getLen());
    ui->particlesTable->setItem(this->data->getLen()-1,0,new QTableWidgetItem(QString::number(mass)));
    ui->particlesTable->setItem(this->data->getLen()-1,1,new QTableWidgetItem(QString::number(r)));
    ui->particlesTable->setItem(this->data->getLen()-1,2,new QTableWidgetItem(QString::number(pos.x)));
    ui->particlesTable->setItem(this->data->getLen()-1,3,new QTableWidgetItem(QString::number(pos.y)));
    ui->particlesTable->setItem(this->data->getLen()-1,4,new QTableWidgetItem(QString::number(d.x)));
    ui->particlesTable->setItem(this->data->getLen()-1,5,new QTableWidgetItem(QString::number(d.y)));
    // Set to 0
    ui->massInput->setValue(1.0);
    ui->rInput->setValue(10.0);
    ui->xInput->setValue(250.0);
    ui->yInput->setValue(250.0);
    ui->dxInput->setValue(.0);
    ui->dyInput->setValue(.0);
}

void MainWindow::on_startBtn_clicked()
{
   const int len = this->data->getLen();
   if(len == 0)return;
   VisualizationDlg vis(nullptr, this->data);
   vis.exec();
   int i = 0;
   for(Particle prt : this->data->particles) {
       ui->particlesTable->setItem(i,0,new QTableWidgetItem(QString::number(prt.mass)));
       ui->particlesTable->setItem(i,1,new QTableWidgetItem(QString::number(prt.r)));
       ui->particlesTable->setItem(i,2,new QTableWidgetItem(QString::number(prt.pos.x)));
       ui->particlesTable->setItem(i,3,new QTableWidgetItem(QString::number(prt.pos.y)));
       ui->particlesTable->setItem(i,4,new QTableWidgetItem(QString::number(prt.d.x)));
       ui->particlesTable->setItem(i,5,new QTableWidgetItem(QString::number(prt.d.y)));
       i++;
   }
}

void MainWindow::on_massInput_editingFinished()
{
    ui->rInput->setValue(ui->massInput->value()*2+8);
}

void MainWindow::on_particlesTable_cellChanged(int row, int column)
{
    double it = ui->particlesTable->item(row, column)->text().toDouble();

    switch (column) {
    case 0:
        (this->data->particles)[row].mass = it;
        break;

    case 1:
        (this->data->particles)[row].r = it;
        break;

    case 2:
        (this->data->particles)[row].pos.x = it;
        break;

    case 3:
        (this->data->particles)[row].pos.y = it;
        break;

    case 4:
        (this->data->particles)[row].d.x = it;
        break;

    case 5:
        (this->data->particles)[row].d.y = it;
        break;


    default:
        break;
    }


//    ui->particlesTable->setItem(row, column, new QTableWidgetItem(QString::number(it)));
}
