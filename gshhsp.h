#ifndef GSHHSP_H
#define GSHHSP_H

#include <QPolygonF>

class gshhsP
{
public:
    gshhsP();

public:
    QPolygonF points;
    int id;
    int n;
    int flag;
    int west;
    int east;
    int south;
    int north;
    int area;
    int area_full;
    int container;
    int ancestor;
};

#endif // GSHHSP_H
