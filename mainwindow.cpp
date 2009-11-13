#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <proj_api.h>

#include "gshhspolygons.h"

#include "kartwidget.h"

#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    view = new QGraphicsView;

    view->setScene(scene);

    //    kart = new kartWidget;

    projPJ fra_proj = pj_init_plus("+proj=latlon +ellps=WGS84 +datum=WGS84 +units=km");
    projPJ til_proj = pj_init_plus("+proj=aitoff +ellps=WGS84 +datum=WGS84 +units=km");
    //projPJ til_proj = pj_init_plus("+proj=stere +lon_0=0 +lat_0=90 +lat_ts=60 +units=km +ellps=WGS84 +datum=WGS84");

    double x = 60.*DEG_TO_RAD;
    double y = 10.*DEG_TO_RAD;
    double z = 0. *DEG_TO_RAD;
    pj_transform(fra_proj, til_proj, 1, 0, &x, &y, &z);

    qDebug(QString::number(x).toAscii() + " - " + QString::number(y).toAscii() + " - " + QString::number(z).toAscii());

    polys.read_gshhs_files();
    qDebug("Før transform");
    polys.transform(fra_proj,til_proj);
    qDebug("Etter transform");

    QVector<gshhsP> p = polys.get_polygoner();
    qDebug("1Antall polygoner: " + QString::number(p.size()).toAscii());
    //kart->set_polygon(p);
    qDebug("2Antall polygoner: " + QString::number(p.size()).toAscii());
    //ui->gridLayout->addWidget(scene);
    ui->gridLayout->addWidget(view);

    QColor orange(255,127,0);
    QColor blaa(0,0,255);
    QColor lys_blaa(200,255,200);

    int flag = 0;
    for(int i=0;i < p.size(); i++)
    {
        //scene->addPolygon(p.at(i).pj_points);
        //p.at(i).pj_path.setFillRule(Qt::WindingFill);
        //p.at(i).pj_path.
        flag = p.at(i).flag & 255;
        //qDebug("flag:" + QString::number(flag).toAscii());
        if ( flag == 1 || flag == 3 )
            scene->addPath(p.at(i).pj_path,QPen(),QBrush(orange));
        else
            scene->addPath(p.at(i).pj_path,QPen(),QBrush(lys_blaa));
        //scene->update();
    }
    qDebug("3Antall polygoner: " + QString::number(p.size()).toAscii());

    view->scale(.08,-.08);
    //view->translate(180.,0.);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->setBackgroundBrush(QBrush(blaa));
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete ui;
}
