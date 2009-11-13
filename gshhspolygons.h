#ifndef GSHHSPOLYGONS_H
#define GSHHSPOLYGONS_H

#include <gshhsP.h>

#include <proj_api.h>

class gshhsPolygons
{
public:
    gshhsPolygons();

    void read_gshhs_files();
    void transform(projPJ, projPJ);

    QVector<gshhsP> &get_polygoner();

private:

    QVector<gshhsP> polygoner;
    QVector<gshhsP> pj_polys;
};

#endif // GSHHSPOLYGONS_H
