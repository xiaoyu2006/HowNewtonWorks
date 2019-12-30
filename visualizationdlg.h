#ifndef VISUALIZATIONDLG_H
#define VISUALIZATIONDLG_H

#include <QDialog>

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

private slots:
    void on_GInput_editingFinished();

    void on_updateSpdInput_editingFinished();

private:
    Ui::VisualizationDlg *ui;
};

#endif // VISUALIZATIONDLG_H
