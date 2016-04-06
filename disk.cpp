#include "disk.h"
#include "pole.h"
Disk::Disk(QWidget *parent) : QWidget(parent)
{
    //int size;
    //int height;
    //Pole *on; //why need this?

}
Disk* Disk::operator=(Disk *d){
    this->size = d->size;
    this->height = d->height;
    //this->on = d->on;
    return this;
}
Disk::Disk(int size){
    this->size = size;
}

int Disk::getSize(){
    return size;
}

void Disk::Draw(){

}
