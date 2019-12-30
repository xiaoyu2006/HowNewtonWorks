#include "visualizationdlg.h"
#include "ui_visualizationdlg.h"

VisualizationDlg::VisualizationDlg(QWidget *parent, NewtonSpace *data) :
    QDialog(parent),
    ui(new Ui::VisualizationDlg)
{
    ui->setupUi(this);
    this->data = data;
    // for the missing piece...
    ui->visualizationGL->setData(this->data);
    ui->visualizationGL->setTime(.0001);
    ui->visualizationGL->setG(.1);
}

VisualizationDlg::~VisualizationDlg()
{
    delete ui;
}

void VisualizationDlg::on_GInput_editingFinished()
{
    ui->visualizationGL->setG(ui->GInput->value());
}

void VisualizationDlg::on_updateSpdInput_editingFinished()
{
    ui->visualizationGL->setTime(ui->updateSpdInput->value());
}
