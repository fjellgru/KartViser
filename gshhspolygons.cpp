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
    QPointF tmp_pkt;
    QFile gshhs_fil("C:/3party/gshhs/gshhs_l.b");
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
                tmp_pkt.setX(lon/1000000.0);
                tmp_pkt.setY(lat/1000000.0);
                polygon.points.push_back(tmp_pkt);
                //polygon.pj_points.push_back(tmp_pkt);
                //std::cout << lon << " " << lat << std::endl;
            }
            polygoner.push_back(polygon);
            polygon.points.clear();
            //polygon.pj_points.clear();
            //qDebug("her");
            //qDebug("id: " + QString::number(polygon.id).toAscii() + " n: " + QString::number(polygon.n).toAscii());
            //break;
        }
        //qDebug("Ferdig while");
        gshhs_fil.close();
    }
}

void gshhsPolygons::transform(projPJ from, projPJ to)
{
    qDebug("Transform");
    double x = 0.;
    double y = 0.;
    double z = 0.;
    double prev_x = 0.;
    double prev_y = 0.;
    //double z = 0.;
    int pj_err = 0;
    bool first_point = true;
    double jump_limit = 1000.;
    if ( pj_polys.size() == 0 )
    {
        for(QVector<gshhsP>::iterator it=polygoner.begin();
        it != polygoner.end();
        ++it)
        {
            first_point = true;
            //QPolygonF::iterator it_pj_p=it->pj_points.begin();
            for(QPolygonF::iterator it_p=it->points.begin();
                it_p != it->points.end();
                ++it_p)
                //, ++it_pj_p)
                {
                    x = it_p->x()*DEG_TO_RAD;
                    y = it_p->y()*DEG_TO_RAD;
                    z = 0.*DEG_TO_RAD;
                    //qDebug(QString::number(it_p->x()).toAscii());
                    pj_err = pj_transform(from,to,1,0,&x,&y,&z);
                    //qDebug(QString::number(x).toAscii());

                    if ( first_point )
                    {
                        it->pj_path.moveTo(x,y);
                        first_point = false;
                    }
                    else
                    {
                        if ( it->id != 4 && (
                             fabs(prev_x - x) > jump_limit ||
                             fabs(prev_y - y) > jump_limit) )
                        {
                            it->pj_path.moveTo(x,y);
                            /*
                                qDebug("her" + QString::number(it->id).toAscii());
                                qDebug("prev: " + QString::number(prev_x).toAscii() + " " + QString::number(prev_y).toAscii());
                                qDebug("this: " + QString::number(x).toAscii() + " " + QString::number(y).toAscii());
                                */
                        }
                        else
                        {
                            it->pj_path.lineTo(x,y);
                        }
                    }
                    prev_x = x;
                    prev_y = y;
                    /*
                        it_pj_p->setX(x);
                        it_pj_p->setY(y);
                     */
                }
            /*
                if ( it->id != 4 )
                it->pj_path.closeSubpath();
            */
        }
    }
}
