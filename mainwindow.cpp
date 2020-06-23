#include "mainwindow.h"
#include <QGraphicsItem>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene()),
    firstExec(true)
{
    thread = new GeneratorThread(&mtx);
    ui->setupUi(this);

    QTransform transform(1, 0, 0, 0, -1, 0, 0, 0);                                          //setting up the graphicView
    ui->graphicsView->setTransform(transform);
    ui->graphicsView->setScene(scene);

    QRect sceneRect(0, 0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20); //setting up the scene
    scene->setSceneRect(sceneRect);
    xAxis = new AxisItem(ui->graphicsView->width() - 50, 0);
    yAxis = new AxisItem(0, ui->graphicsView->height() - 50, Y_axis);
    scene->addItem(xAxis->getItem());
    scene->addItem(yAxis->getItem());

    ui->playButton->setIcon(QIcon("play.png"));                                             //setting up buttones
    ui->playButton->setIconSize(QSize(30, 30));
    ui->playButton->setFixedSize(QSize(32, 32));
    ui->pauseButton->setIcon(QIcon("pause.png"));
    ui->pauseButton->setIconSize(QSize(30, 30));
    ui->pauseButton->setFixedSize(QSize(32, 32));
    ui->stopButton->setIcon(QIcon("stop.png"));
    ui->stopButton->setIconSize(QSize(30, 30));
    ui->stopButton->setFixedSize(QSize(32, 32));

    connect(ui->playButton, SIGNAL(clicked()), SLOT(playButton_clicked()));     //buttons and thread signals connection
    connect(ui->pauseButton, SIGNAL(clicked()), SLOT(pauseButton_clicked()));
    connect(ui->stopButton, SIGNAL(clicked()), SLOT(stopButton_clicked()));
    connect(thread, SIGNAL(sendPoint(QPoint)), SLOT(addPoint(QPoint)));
    connect(this, SIGNAL(finished()), thread, SLOT(finished()));
    connect(this, SIGNAL(begin()), thread, SLOT(begin()));
}

void MainWindow::playButton_clicked(){
    if(firstExec){
        emit begin();
        thread->start();
        firstExec = false;
    }
    mtx.unlock();
}

void MainWindow::pauseButton_clicked(){
    mtx.try_lock();
}

void MainWindow::stopButton_clicked(){
    QGraphicsScene* clearScene = new QGraphicsScene();              //for faster clean (to user)
    ui->graphicsView->setScene(clearScene);

    emit finished();
    firstExec = true;
    mtx.unlock();

    scene->clear();
    xAxis = new AxisItem(ui->graphicsView->width() - 50, 0);
    yAxis = new AxisItem(0, ui->graphicsView->height() - 50, Y_axis);
    scene->addItem(xAxis->getItem());
    scene->addItem(yAxis->getItem());

    ui->graphicsView->setScene(scene);
    delete clearScene;
}

void MainWindow::addPoint(QPoint point){
    int r = 5;
    QColor color(40, 120, 200);
    QPen pen(Qt::black);
    QBrush brush(color);
    QRect circle(point.x(), point.y(), r, r);
    scene->addEllipse(circle, pen, brush);
}

void MainWindow::resizeEvent(QResizeEvent* event){
    QMainWindow::resizeEvent(event);

    QRect graphicField(20, 20, this->width() - 40, this->height() - 100);
    QRect playField(20, this->height() - 60, 40, 40);
    QRect pauseField(90, this->height() - 60, 40, 40);
    QRect stopField(160, this->height() - 60, 40, 40);
    ui->graphicsView->setGeometry(graphicField);
    ui->playButton->setGeometry(playField);
    ui->pauseButton->setGeometry(pauseField);
    ui->stopButton->setGeometry(stopField);

    QRect sceneRect(0, 0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
    scene->setSceneRect(sceneRect);
    xAxis->resize(ui->graphicsView->width() - 50, 0);
    yAxis->resize(0, ui->graphicsView->height() - 50);
}

void MainWindow::closeEvent(QCloseEvent* event){
    stopButton_clicked();
    if(thread->isRunning() && !thread->isFinished())
        thread->sleep();                                        //time for child thread to kill himself
    QMainWindow::closeEvent(event);
}

MainWindow::~MainWindow()
{
    delete thread;
    delete scene;
    delete ui;
}
