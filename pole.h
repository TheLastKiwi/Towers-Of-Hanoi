#ifndef POLE_H
#define POLE_H

#include <QWidget>
#include "disk.h"
class Pole : public QWidget
{
    Q_OBJECT



public:
    int numDisks;
    Disk *stack;
    bool hover;
    explicit Pole(QWidget *parent = 0);
    Pole(int);

    Disk* getTopDisk();
    void addDisk(Disk* d);
    void removeDisk();
    int getTopSize();
signals:

public slots:
};

#endif // POLE_H
