#include "hanoiwindow.h"
#include "ui_hanoiwindow.h"
#include "disk.h"
#include "pole.h"
#include "move.h"
#include "math.h"
#include <stack>
HanoiWindow::HanoiWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HanoiWindow)
{
    /*
    Pole *left;
    Pole *center;
    Pole *right;
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
    std::stack<Move> playerMoves;//((int)pow(2,numDisks+1));



}

HanoiWindow::~HanoiWindow()
{
    delete ui;
}

void HanoiWindow::on_btnLeft_clicked()
{
    left->hover = true;
}

void HanoiWindow::on_btnCenter_clicked()
{

}

void HanoiWindow::on_btnRight_clicked()
{

}
