#ifndef THREADS_H
#define THREADS_H
#include <QtCore>


class Threads : public QThread
{
public:
    Threads();
    void run();
};

#endif // THREADS_H
