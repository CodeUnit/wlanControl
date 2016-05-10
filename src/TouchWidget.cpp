#include "TouchWidget.h"

#define TCRAD 8

TouchWidget::TouchWidget(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("border: 2px solid red");
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setMinimumSize(100,100);
    qDebug() << "Test";

    x = 0;
    y = 0;
    firstRun = true;
}

void TouchWidget::resizeEvent(QResizeEvent *e)
{
    x = width() / 2;
    y = height() / 2;
}

void TouchWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.drawRect(0, 0, this->width() -1, this->height() -1);


    if (firstRun)
    {
        firstRun = false;
        x = this->width() / 2;
        y = this->height() / 2;
    }

    QPainter painterElli(this);
    painterElli.drawEllipse(x - TCRAD, y - TCRAD, TCRAD * 2, TCRAD * 2);

//    QWidget::paintEvent(e);
}

void TouchWidget::mouseMoveEvent(QMouseEvent *e)
{
    x =  e->pos().x();
    y =  e->pos().y();

    int xMax = this->size().width();
    int yMax = this->size().height();

    if (x >= xMax)
        x = xMax;
    if (y >=yMax)
        y = yMax;

    if (x <= 0)
        x = 0;
    if (y <= 0)
        y = 0;


    update();

    int transX = (float) 25 / this->width() * x;
    int transY = (float) 25 / this->height() * y;

    qDebug() << transX << transY;

}

void TouchWidget::mousePressEvent(QMouseEvent *e)
{
    x = e->x();
    y = e->y();

    update();
}

void TouchWidget::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    x = width() / 2;
    y = height() / 2;

    update();
}
