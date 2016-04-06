#ifndef MOVE_H
#define MOVE_H

#include <QWidget>
#include "pole.h"

class Move : public QWidget
{
    Q_OBJECT

    Pole *from = nullptr;
    Pole *to = nullptr;

public:
    explicit Move(QWidget *parent = 0);
    Move(Pole *from, Pole *to);
    void reverseMove();
    bool isValidMove();
    bool isValidMove(Pole *f, Pole *t);
    void move();
signals:

public slots:
};

#endif // MOVE_H
