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

    this->rePaintTimer = startTimer(1);
}

VisualizationDlg::~VisualizationDlg()
{
    delete ui;
}

void VisualizationDlg::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == this->rePaintTimer) {
        this->data->update(ui->GInput->value(), ui->updateSpdInput->value());
        this->visualizationGL->update();

        this->rePaintTimer = startTimer(1);
    }
}
