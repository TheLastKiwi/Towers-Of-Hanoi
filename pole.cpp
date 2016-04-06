#include "pole.h"
#include "disk.h"
/*
    int numDisks;
    Disk *stack;
    bool moving;
*/
Pole::Pole(QWidget *parent) : QWidget(parent)
{

}
Pole::Pole(int nDisks){
    numDisks = 0;
    stack = new Disk[nDisks];
    hover = false;
}

void Pole::addDisk(Disk *d){
    stack[numDisks++] = d;
}
Disk* Pole::getTopDisk(){
    return (&stack[numDisks-1]); //added & to make it work
                                 //not sure if it actually does what I want
}

int Pole::getTopSize(){
    return(stack[numDisks-1].getSize());
}
void Pole::removeDisk(){
    numDisks--;
}
