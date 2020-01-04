#include "visglwidget.h"

#include <cstdlib>
#include <ctime>

int randInt(int from, int to) {
    return from+rand()%(from-to);
}

VisGLWidget::VisGLWidget(QWidget *parent, NewtonSpace *data)
    : QOpenGLWidget(parent)
{
    if(data == nullptr)throw;

    srand(time(nullptr));
    this->data = data;
    const int len = this->data->getLen();
    for(int _=0; _<len; _++) {
        this->colors.push_back(QColor(
            randInt(0,150), randInt(0,150), randInt(0,150), 100
        ));
    }
}

void VisGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(255,255,255,255);
}

void VisGLWidget::resizeGL(int width, int height)
{
    this->paintGL();
    return;
}

void VisGLWidget::paintGL()
{
    int len = this->data->getLen();

    QPainter painter;
    painter.begin(this);

    for (int i=0; i<len; i++) {
        Point pos = (this->data->particals)[i].pos;
        double mass = (this->data->particals)[i].mass;
        QColor color = (this->colors)[i];
        painter.setPen(QPen(color, 5*mass+15));
        painter.setBrush(QBrush(color));
        painter.drawPoint(pos.x, pos.y);
    }

    painter.end();
}
