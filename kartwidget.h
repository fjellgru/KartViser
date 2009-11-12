#ifndef KARTWIDGET_H
#define KARTWIDGET_H

#include <QWidget>

#include "gshhsp.h"

class kartWidget : public QWidget
{
    Q_OBJECT

public:
    kartWidget(QWidget *parent = 0);
    void set_polygon(QVector<gshhsP> &pol)
    {
        polygoner = pol;
    }

protected:
    void paintEvent(QPaintEvent *event);

private:
    QVector<gshhsP> polygoner;
};

#endif // KARTWIDGET_H
