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
    for(int i=0;i < p.size(); i++)
    {
        //scene->addPolygon(p.at(i).pj_points);
        //p.at(i).pj_path.setFillRule(Qt::WindingFill);
        //p.at(i).pj_path.
        scene->addPath(p.at(i).pj_path,QPen(),QBrush(QColor(255,127,0)));

        //scene->update();
    }
    qDebug("3Antall polygoner: " + QString::number(p.size()).toAscii());

    view->scale(.03,-.03);
    //view->translate(180.,0.);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
}

MainWindow::~MainWindow()
{
    delete ui;
}
