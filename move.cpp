#include "move.h"
#include "pole.h"


bool Move::isValidMove(){
    if (to->getTopSize() > from->getTopSize()) return false;
    return true;
}

bool Move::isValidMove(Pole *f, Pole *t){
    if (t->getTopSize() > f->getTopSize()) return false;
    return true;
}

Move::Move(Pole *from, Pole *to){
    this->from = from;
    this->to = to;
}

void Move::move(){
    to->addDisk(from->getTopDisk());
    from->removeDisk();
}
void Move::reverseMove(){
    from->addDisk(to->getTopDisk());
    to->removeDisk();
}

