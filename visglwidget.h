#ifndef VISGLWIDGET_H
#define VISGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <QPainter>

#include "NewtonSpace.cpp"

class VisGLWidget : public QOpenGLWidget,
                    protected QOpenGLFunctions
{
    Q_OBJECT
public:
    VisGLWidget(QWidget *parent = nullptr, NewtonSpace *data = nullptr);
    void setData(NewtonSpace *data);
    void setG(double G);
    void setTime(double time);

    void update();

    NewtonSpace *data;
    double G, step;

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    std::vector<QColor> colors;
};

#endif // VISGLWIDGET_H
