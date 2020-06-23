#include "generatorthread.h"
#include <cmath>

GeneratorThread::GeneratorThread(QMutex* mtx):
    threadStatus(true),
    mtx(mtx)
{}

void GeneratorThread::run(){
    qint32 i = 0;
    while(true){
        {
            mtx->lock();
            if(!threadStatus){
                break;
            }
            emit sendPoint(sin(i));
            ++i;
            mtx->unlock();
        }
        usleep(100000);
    }
    mtx->unlock();
}

void GeneratorThread::sleep(qint32 milisec) const{
    usleep(milisec);
}

void GeneratorThread::begin(){
    threadStatus = true;
}

void GeneratorThread::finished(){
    threadStatus = false;
}

QPoint GeneratorThread::sin(qint32 x) const{
    return QPoint ((10 * x) % 1000, static_cast<int>(100 * (1 + std::sin(x / 5.0))));
}
