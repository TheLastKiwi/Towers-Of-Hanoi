#include "hanoiwindow.h"
#include "ui_hanoiwindow.h"
#include "disk.h"
#include "pole.h"
#include "move.h"
#include "math.h"
#include <stack>
#include <iostream>
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
    QColor sideDisk(0,200,255);
    QColor innerDisk(0,100,100);
    QColor pole(128,64,64);
    QBrush brush(Qt::SolidPattern);// = new Brush();
    //brush.setStyle(Qt::SolidPattern);
    QPainter painter(this);
    int diskWidth = std::max(getWidth(b->width(),p->stack[diskIndex].getSize()),5);
    int diskHeight = std::min((b->height()/2)/ui->sbNumDisks->value(),ui->sbNumDisks->value()*9/4);
    int xAxis = b->x()+b->width()/2;
    int yAxis = b->height()*3/4;

    int elipseHeight = diskWidth*4/9;

    QPoint c(xAxis,yAxis-diskHeight*diskIndex);


    brush.setColor(sideDisk);
    painter.setBrush(brush);
    painter.drawEllipse(c,diskWidth,elipseHeight);//bottom Elipse
    brush.setColor(outerDisk);
    painter.setBrush(brush);
    c=QPoint(xAxis,(yAxis-diskHeight*diskIndex)-diskHeight*2/3);
    painter.drawEllipse(c,diskWidth,elipseHeight);//top Elipse

    brush.setColor(innerDisk);
    painter.setBrush(brush);
    painter.drawEllipse(c,3,12/9);//center hole
    //painter.drawRect();//pole

    //QBrush *b = new QBrush(QColor(Qt::red));
    //painter.

}
int HanoiWindow::getWidth(int width, int size){
    int w = width*8/10;
    int min = 10;
    double factor = (w-min)/ui->sbNumDisks->value();
    return (int)(size*factor/2);
}

void HanoiWindow::paintHover(Pole *p, int diskIndex, QPushButton *b){
    QColor outerDisk(43,207,255);
    QColor sideDisk(0,200,255);
    QColor innerDisk(0,100,100);
    QColor pole(128,64,64);
    QBrush brush(Qt::SolidPattern);// = new Brush();
    //brush.setStyle(Qt::SolidPattern);
    QPainter painter(this);
    int diskWidth = std::max(getWidth(b->width(),p->stack[diskIndex].getSize()),5);
    int diskHeight = std::min((b->height()/2)/ui->sbNumDisks->value(),ui->sbNumDisks->value()*9/4);
    int xAxis = b->x()+b->width()/2;
    int yAxis = b->height()*1/4;

    int elipseHeight = diskWidth*4/9;

    QPoint c(xAxis,yAxis+diskHeight);
    //20+

    brush.setColor(sideDisk);
    painter.setBrush(brush);
    painter.drawEllipse(c,diskWidth,elipseHeight);//bottom Elipse
    brush.setColor(outerDisk);
    painter.setBrush(brush);
    c=QPoint(xAxis,(yAxis+diskHeight)-diskHeight*2/3);
    painter.drawEllipse(c,diskWidth,elipseHeight);//top Elipse

    brush.setColor(innerDisk);
    painter.setBrush(brush);
    painter.drawEllipse(c,3,12/9);//center hole
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
            source->hover = false;
            source = 0;//nullptr;
            dest = 0;//nullptr;
            moving = false;

            update();
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
        enableDisableButtons(true);
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
    timer->start(500);
    enableDisableButtons(false);

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
        update();
    }
    else{
        timer->stop();
        enableDisableButtons(true);
    }
}


void HanoiWindow::enableDisableButtons(bool arg){
    ui->btnCenter->setEnabled(arg);
    ui->btnLeft->setEnabled(arg);
    ui->btnRight->setEnabled(arg);
    ui->menuBar->setEnabled(arg);
}

void HanoiWindow::on_actionUndo_All_triggered()
{
    enableDisableButtons(true);
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(undo()));

    //connect(timer,SIGNAL(timeout()),this,SLOT())
    timer->start(500);
}
