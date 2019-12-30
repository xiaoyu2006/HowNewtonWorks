#include "visglwidget.h"

VisGLWidget::VisGLWidget(QWidget *parent, NewtonSpace *data)
    : QOpenGLWidget(parent)
{
    this->data = data;
}

void VisGLWidget::setData(NewtonSpace *data)
{
    this->data = data;
}

void VisGLWidget::setG(double G)
{
    this->G = G;
}

void VisGLWidget::setTime(double time)
{
    this->step = time;
}

void VisGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(255,255,255,0);
}

void VisGLWidget::resizeGL(int width, int height)
{
}

void VisGLWidget::paintGL()
{
}
