#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include <QGraphicsScene>
#include <QGraphicsView>

#include <gshhspolygons.h>

namespace Ui
{
    class MainWindow;
}

class kartWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    gshhsPolygons::gshhsPolygons polys;

    QGraphicsScene *scene;
    QGraphicsView  *view;

    kartWidget *kart;
};

#endif // MAINWINDOW_H
