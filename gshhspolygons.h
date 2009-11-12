#ifndef GSHHSPOLYGONS_H
#define GSHHSPOLYGONS_H

#include <gshhsP.h>

class gshhsPolygons
{
public:
    gshhsPolygons();

    void read_gshhs_files();
    QVector<gshhsP> &get_polygoner();

private:

    QVector<gshhsP> polygoner;
};

#endif // GSHHSPOLYGONS_H
