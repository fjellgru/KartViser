#include "gshhspolygons.h"

#include <QFile>

#define swabi4(i4) (((i4) >> 24) + (((i4) >> 8) & 65280) + (((i4) & 65280) << 8) + (((i4) & 255) << 24))

gshhsPolygons::gshhsPolygons()
{
}

QVector<gshhsP> &gshhsPolygons::get_polygoner()
{
    return polygoner;
}

void gshhsPolygons::read_gshhs_files()
{
    gshhsP::gshhsP polygon;
    register int lon, lat;
    register int val;
    QFile gshhs_fil("C:/3party/gshhs/gshhs_c.b");
    if ( gshhs_fil.open(QIODevice::ReadOnly) )
    {
        while ( not gshhs_fil.atEnd() )
        {
            gshhs_fil.read((char*)&val,sizeof(val));
            polygon.id = swabi4((unsigned int)val);
            gshhs_fil.read((char*)&val,sizeof(val));
            polygon.n = swabi4((unsigned int)val);
            gshhs_fil.read((char*)&val,sizeof(val));
            polygon.flag = swabi4((unsigned int)val);
            gshhs_fil.read((char*)&val,sizeof(val));
            polygon.west = swabi4((unsigned int)val);
            gshhs_fil.read((char*)&val,sizeof(val));
            polygon.east = swabi4((unsigned int)val);
            gshhs_fil.read((char*)&val,sizeof(val));
            polygon.south = swabi4((unsigned int)val);
            gshhs_fil.read((char*)&val,sizeof(val));
            polygon.north = swabi4((unsigned int)val);
            gshhs_fil.read((char*)&val,sizeof(val));
            polygon.area = swabi4((unsigned int)val);
            gshhs_fil.read((char*)&val,sizeof(val));
            polygon.area_full = swabi4((unsigned int)val);
            gshhs_fil.read((char*)&val,sizeof(val));
            polygon.container = swabi4((unsigned int)val);
            gshhs_fil.read((char*)&val,sizeof(val));
            polygon.ancestor = swabi4((unsigned int)val);

            for(int i=0; i < polygon.n;i++)
            {

                gshhs_fil.read((char*)&lon,sizeof(lon));
                lon = swabi4((unsigned int)lon);
                //if ( lon > 180000000 ) lon -=180000000;
                gshhs_fil.read((char*)&lat,sizeof(lon));
                lat = swabi4((unsigned int)lat);
                polygon.points.push_back(QPointF(lon/1000000.0, lat/1000000.0));
                //std::cout << lon << " " << lat << std::endl;
            }
            polygoner.push_back(polygon);
            polygon.points.clear();
            //qDebug("her");
            //qDebug("id: " + QString::number(polygon.id).toAscii() + " n: " + QString::number(polygon.n).toAscii());
            //break;
        }
        //qDebug("Ferdig while");
        gshhs_fil.close();
    }
}
