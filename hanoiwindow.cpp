#include "hanoiwindow.h"
#include "ui_hanoiwindow.h"
#include "disk.h"
#include "pole.h"
#include "move.h"
#include "math.h"
#include <stack>

#include "QtWidgets"
HanoiWindow::HanoiWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HanoiWindow)
{
    /*
    Pole *left;
    Pole *center;
    Pole *right;
    bool moving = false;
    std::stack<Move> playerMoves;
    Pole *source;
    Pole *dest;
    */
    ui->setupUi(this);
    ui->sbNumDisks->hide(); //initially hides spinbox
    int numDisks = ui->sbNumDisks->value();
    left = new Pole(numDisks);
    center = new Pole(numDisks);
    right = new Pole(numDisks);
    for(int i = numDisks; i >0; i--){
        left->addDisk(new Disk(i));
    }
    //initial setup done

}
void HanoiWindow::paintDisk(Pole *p, int diskIndex, QPushButton *b){
    QPainter painter(this);
    int width = b->width();
    int center = b->x()+width/2;
    QPoint c(center,b->height()-diskIndex*10);
    painter.drawEllipse(c,
                        p->stack[diskIndex].getSize(),
                        p->stack[diskIndex].getSize()/2);

}
void HanoiWindow::paintHover(Pole *p, int diskIndex, QPushButton *b){
    QPainter painter(this);
    int width = b->width();
    int center = b->x()+width/2;
    QPoint c(center,b->height()*.3-diskIndex*10);
    painter.drawEllipse(c,
                        p->stack[diskIndex].getSize(),
                        p->stack[diskIndex].getSize()/2);
}
void HanoiWindow::paintAllDisks(Pole *p, QPushButton *b){
    for(int i = 0; i < p->numDisks; i++){
        if(p->hover && (i == p->numDisks-1)){
            paintHover(p,i,b);
        }
        else{
            paintDisk(p,i,b);
        }
    }
}

void HanoiWindow::paintEvent(QPaintEvent *event){


    //elipse
    //square
    //elipse
    int x = ui->btnLeft->x();
    x = ui->btnCenter->x();
    x = ui->btnRight->x();
    paintAllDisks(left,ui->btnLeft);
    paintAllDisks(center,ui->btnCenter);
    paintAllDisks(right,ui->btnRight);
        /*&static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -40)
    };
    static const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };

    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 191);

    int side = qMin(width(), height());
    QTime time = QTime::currentTime();
//! [10]

//! [11]
    QPainter painter(this);
//! [11] //! [12]
    painter.setRenderHint(QPainter::Antialiasing);
//! [12] //! [13]
    painter.translate(width() / 2, height() / 2);
//! [13] //! [14]
    painter.scale(side / 200.0, side / 200.0);
//! [9] //! [14]

//! [15]
    painter.setPen(Qt::NoPen);
//! [15] //! [16]
    painter.setBrush(hourColor);
//! [16]

//! [17] //! [18]
    painter.save();
//! [17] //! [19]
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();
//! [18] //! [19]

//! [20]
    painter.setPen(hourColor);
//! [20] //! [21]

    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }
//! [21]

//! [22]
    painter.setPen(Qt::NoPen);
//! [22] //! [23]
    painter.setBrush(minuteColor);

//! [24]
    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();
//! [23] //! [24]

//! [25]
    painter.setPen(minuteColor);
//! [25] //! [26]

//! [27]
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }
    */
}

HanoiWindow::~HanoiWindow()
{
    delete ui;
}

void HanoiWindow::on_btnLeft_clicked()
{
    click(left);
}

void HanoiWindow::on_btnCenter_clicked()
{
    click(center);
}

void HanoiWindow::on_btnRight_clicked()
{
    click(right);
}

void HanoiWindow::click(Pole *p){
    if(moving){
        dest = p;
        Move *m;
        if(m->isValidMove(source,dest)){
            m = new Move(source,dest);
            playerMoves.push(m);
            source->hover = false;
            moving = false;
            m->move();
        }
        else{
            source = nullptr;
            dest = nullptr;
            moving = false;
            p->hover = false;
        }
    }
    else{
        if(p->numDisks == 0)return;
        source = p;
        p->hover = true;
        moving = true;
    }
}

//grab size and location of button
//resize elipse and square
