#include "hanoiwindow.h"
#include "ui_hanoiwindow.h"
#include "disk.h"
#include "pole.h"
#include "move.h"
#include "math.h"
#include <stack>
//#include <iostream>
#include <queue>

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
    std::stack<Move*> playerMoves;
    std::queue<Move*> autoMoves;
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
    QColor outerDisk(43,207,255);
    QColor innerDisk(0,100,100);
    QColor pole(128,64,64);

    QPainter painter(this);
    int diskWidth = getWidth(b->width(),p->stack[diskIndex].getSize());
    int diskHeight = std::min((b->height()/2)/ui->sbNumDisks->value(),ui->sbNumDisks->value()*9/4);
    int center = b->x()+b->width()/2;
    int yAxis = b->height()*3/4;

    int elipseHeight = diskWidth*4/9;

    QPoint c(center,yAxis-diskHeight*diskIndex);
    //20+

    painter.drawEllipse(c,diskWidth,elipseHeight);
    //QBrush *b = new QBrush(QColor(Qt::red));
    //painter.

}
int HanoiWindow::getWidth(int width, int size){
    int w = width*8/10;
    int min = 20;
    double factor = (w-min)/ui->sbNumDisks->value();
    return (int)(size*factor/2);
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

HanoiWindow::~HanoiWindow(){
    delete ui;
}

void HanoiWindow::on_btnLeft_clicked(){
    click(left);
}

void HanoiWindow::on_btnCenter_clicked(){
    click(center);
}

void HanoiWindow::on_btnRight_clicked(){
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
            source = 0;//nullptr;
            dest = 0;//nullptr;
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
void HanoiWindow::reset(){
    ui->btnCenter->show();
    ui->btnLeft->show();
    ui->btnRight->show();
    left->numDisks = 0;
    center->numDisks = 0;
    right->numDisks = 0;
    for(int i = ui->sbNumDisks->value(); i > 0; i--){
        left->addDisk(new Disk(i));
    }
    repaint();
}
void HanoiWindow::on_actionUndo_Move_triggered()
{
    left->hover = false;
    center->hover = false;
    right->hover = false;
    moving = false;
    if(playerMoves.empty())return;
    Move *m = playerMoves.top();
    m->reverseMove();
    playerMoves.pop();
    repaint();

}

void HanoiWindow::on_actionReset_Game_triggered()
{
    reset();
}


void HanoiWindow::on_actionSet_Disks_triggered()
{
    ui->btnCenter->hide();
    ui->btnLeft->hide();
    ui->btnRight->hide();
    left->numDisks = 0;
    center->numDisks = 0;
    right->numDisks = 0;
    ui->sbNumDisks->show();
}

void HanoiWindow::on_actionNew_Game_triggered()
{
    reset();
    ui->sbNumDisks->hide();

}

void HanoiWindow::on_actionExit_triggered()
{
    exit(0);
}
void HanoiWindow::delay(){
    if(autoMoves.empty()){
        timer->stop();
    }
    else{
        Move *m = autoMoves.front();
        m->move();
        autoMoves.pop();
        repaint();
    }
}
void HanoiWindow::on_actionAuto_Play_triggered()
{
    autoPlayHanoi(ui->sbNumDisks->value(),left,center,right);
    reset();
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(delay()));
    //connect(timer,SIGNAL(timeout()),this,SLOT())
    timer->start(5);

}
void HanoiWindow::autoPlayHanoi(int disk,Pole *source, Pole *dest, Pole *spare){
    Move *m;
    if(disk == 1){
        m = new Move(source,dest);
        autoMoves.push(m);
        m->move();
    }
    else{
        autoPlayHanoi(disk-1,source,spare,dest);
        m = new Move(source,dest);
        autoMoves.push(m);
        m->move();
        autoPlayHanoi(disk-1,spare,dest,source);
    }
}
void HanoiWindow::undo(){
    if(!playerMoves.empty()){
        Move *m = playerMoves.top();
        m->reverseMove();
        playerMoves.pop();
    }
    else{
        timer->stop();
    }
}

void HanoiWindow::on_actionUndo_All_triggered()
{
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(undo()));

    //connect(timer,SIGNAL(timeout()),this,SLOT())
    timer->start(50);
}
