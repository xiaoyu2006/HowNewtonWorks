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
    ui->particalsTable->setShowGrid(true);
    ui->particalsTable->horizontalHeader()->setVisible(true);
    ui->particalsTable->verticalHeader()->setVisible(true);

    // setup table header
    QStringList tableHeader;
    tableHeader << tr("Mass") << tr("Radius") << tr("x") << tr("y") << tr("dx") << tr("dy");
    ui->particalsTable->setColumnCount(6);
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
    double r = ui->rInput->value();
    Point pos(ui->xInput->value(), ui->yInput->value());
    Point d(ui->dxInput->value(), ui->dyInput->value());
    // Add to the list
    this->data->addPartical(Partical(mass, r, pos, d));
    // Show in the table
    ui->particalsTable->setRowCount(this->data->getLen());
    ui->particalsTable->setItem(this->data->getLen()-1,0,new QTableWidgetItem(QString::number(mass)));
    ui->particalsTable->setItem(this->data->getLen()-1,1,new QTableWidgetItem(QString::number(r)));
    ui->particalsTable->setItem(this->data->getLen()-1,2,new QTableWidgetItem(QString::number(pos.x)));
    ui->particalsTable->setItem(this->data->getLen()-1,3,new QTableWidgetItem(QString::number(pos.y)));
    ui->particalsTable->setItem(this->data->getLen()-1,4,new QTableWidgetItem(QString::number(d.x)));
    ui->particalsTable->setItem(this->data->getLen()-1,5,new QTableWidgetItem(QString::number(d.y)));
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
   for(Partical prt : this->data->particals) {
       ui->particalsTable->setItem(i,0,new QTableWidgetItem(QString::number(prt.mass)));
       ui->particalsTable->setItem(i,1,new QTableWidgetItem(QString::number(prt.r)));
       ui->particalsTable->setItem(i,2,new QTableWidgetItem(QString::number(prt.pos.x)));
       ui->particalsTable->setItem(i,3,new QTableWidgetItem(QString::number(prt.pos.y)));
       ui->particalsTable->setItem(i,4,new QTableWidgetItem(QString::number(prt.d.x)));
       ui->particalsTable->setItem(i,5,new QTableWidgetItem(QString::number(prt.d.y)));
       i++;
   }
}

void MainWindow::on_massInput_editingFinished()
{
    ui->rInput->setValue(ui->massInput->value()*2+8);
}

void MainWindow::on_particalsTable_cellEntered(int row, int column)
{
    QTableWidgetItem it = *(ui->particalsTable->item(row, column));

    double reset;

    switch (column) {
    case 0:
        (this->data->particals)[row].mass = reset = it.text().toDouble();
        break;

    case 1:
        (this->data->particals)[row].r = reset = it.text().toDouble();
        break;

    case 2:
        (this->data->particals)[row].pos.x = reset = it.text().toDouble();
        break;

    case 3:
        (this->data->particals)[row].pos.y = reset = it.text().toDouble();
        break;

    case 4:
        (this->data->particals)[row].d.x = reset = it.text().toDouble();
        break;

    case 5:
        (this->data->particals)[row].d.y = reset = it.text().toDouble();
        break;


    default:
        reset = -1;
        break;
    }


    ui->particalsTable->setItem(row, column, new QTableWidgetItem(QString::number(reset)));
}
