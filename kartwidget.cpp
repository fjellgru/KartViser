#include "kartwidget.h"

#include <QPainter>

#include "gshhsp.h"

kartWidget::kartWidget(QWidget *parent)
        : QWidget(parent)
{
}

void kartWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.scale(5.,5.);
    //QVector<gshhsP> pp = polygoner.get_polygoner();
    for(QVector<gshhsP>::iterator it=polygoner.begin();
        it != polygoner.end();
        ++it)
        p.drawPolygon(it->points);
}
