#ifndef DISK_H
#define DISK_H

#include <QWidget>
//#include "pole.h"
class Disk : public QWidget
{
    Q_OBJECT
    int size;
    int height=10;
    //Pole *on;


public:
    int getSize();
    Disk* operator=(Disk* d);
    explicit Disk(QWidget *parent = 0);
    void Draw();
    Disk(int size);

signals:

public slots:

};



#endif // DISK_H
