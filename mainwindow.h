#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "NewtonSpace.cpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addBtn_clicked();

    void on_startBtn_clicked();

    void on_massInput_editingFinished();

    void on_particlesTable_cellChanged(int row, int column);

private:
    Ui::MainWindow *ui;

    NewtonSpace *data = new NewtonSpace();
};
#endif // MAINWINDOW_H
