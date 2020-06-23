#ifndef GENERATORTHREAD_H
#define GENERATORTHREAD_H

#include <QThread>
#include <QMutex>
#include <QPoint>

class GeneratorThread : public QThread{
    Q_OBJECT

public:
    GeneratorThread(QMutex* mtx);
    void run();
    void sleep(qint32 milisec = 500000) const;  //make to sleep the main thread

signals:
    void sendPoint(QPoint point);

private slots:
    void begin();                               //turn on a child thread
    void finished();                            //turn off a child thread

private:
    QPoint sin(qint32 x) const;                 //generate function

    bool threadStatus;                          //thread control
    QMutex* mtx;
};


#endif // GENERATORTHREAD_H
