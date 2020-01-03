#ifndef VISUALIZATIONDLG_H
#define VISUALIZATIONDLG_H

#include <QDialog>
#include <QTimerEvent>

#include "NewtonSpace.cpp"

#include "visglwidget.h"

namespace Ui {
class VisualizationDlg;
}

class VisualizationDlg : public QDialog
{
    Q_OBJECT

public:
    explicit VisualizationDlg(QWidget *parent = nullptr, NewtonSpace *data = nullptr);
    ~VisualizationDlg();

    NewtonSpace *data;

protected:
    void timerEvent(QTimerEvent *event);

private:
    Ui::VisualizationDlg *ui;
    VisGLWidget *visualizationGL;

    int rePaintTimer;
};

#endif // VISUALIZATIONDLG_H
