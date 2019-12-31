#include "visualizationdlg.h"
#include "ui_visualizationdlg.h"

VisualizationDlg::VisualizationDlg(QWidget *parent, NewtonSpace *data) :
    QDialog(parent),
    ui(new Ui::VisualizationDlg)
{
    ui->setupUi(this);
    this->data = data;
    this->visualizationGL = new VisGLWidget(this, this->data);
    this->visualizationGL->setObjectName(QString::fromUtf8("visualizationGL"));
    this->visualizationGL->setGeometry(QRect(10, 50, 581, 541));
}

VisualizationDlg::~VisualizationDlg()
{
    delete ui;
}

void VisualizationDlg::on_GInput_editingFinished()
{
    this->visualizationGL->setG(ui->GInput->value());
}

void VisualizationDlg::on_updateSpdInput_editingFinished()
{
    this->visualizationGL->setTime(ui->updateSpdInput->value());
}
