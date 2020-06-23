#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "generatorthread.h"
#include "axis.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void begin();                                       //signal for begining a child thread
    void finished();                                    //signal for killing a child thread

private slots:
    void playButton_clicked();
    void pauseButton_clicked();
    void stopButton_clicked();
    void addPoint(QPoint point);                        //add generated point to the scene

private:
    void resizeEvent(QResizeEvent* event);              //for windoe resize
    void closeEvent(QCloseEvent* event);                //kill a thread before closing the window

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    AxisItem* xAxis;
    AxisItem* yAxis;

    GeneratorThread* thread;
    QMutex mtx;
    bool firstExec;                                     //buttons control
};

#endif // MAINWINDOW_H
