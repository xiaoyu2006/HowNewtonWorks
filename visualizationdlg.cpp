#include "visualizationdlg.h"
#include "ui_visualizationdlg.h"

VisualizationDlg::VisualizationDlg(QWidget *parent, NewtonSpace *data) :
    QDialog(parent),
    ui(new Ui::VisualizationDlg)
{
    ui->setupUi(this);
    this->data = data;
    ui->visualizationGL->setData(this->data);
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
