#ifndef HANOIWINDOW_H
#define HANOIWINDOW_H

#include <QMainWindow>
#include "pole.h"
#include "move.h"
#include <stack>
#include <queue>
#include <QPushButton>
namespace Ui {
class HanoiWindow;
}

class HanoiWindow : public QMainWindow
{
    Q_OBJECT
    Pole *left;
    Pole *center;
    Pole *right;
    bool moving = false;
    std::stack<Move*> playerMoves;//size is going to be roughly (int)pow(2,numDisks+1)
    Pole *source;
    Pole *dest;
    std::queue<Move*> autoMoves;
    QTimer *timer;

    void autoPlayHanoi(int disk,Pole *source, Pole *dest, Pole *spare);
    void paintDisk(Pole *p, int diskIndex, QPushButton *b);
    void paintHover(Pole *p, int diskIndex, QPushButton *b);
    void paintAllDisks(Pole *p, QPushButton *b);
    int getWidth(int width, int size);
    void reset();
public:

    explicit HanoiWindow(QWidget *parent = 0);
    void click(Pole *p);
    ~HanoiWindow();
protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private slots:
    void undo();

    void delay();

    void on_btnLeft_clicked();

    void on_btnCenter_clicked();

    void on_btnRight_clicked();

    void on_actionUndo_Move_triggered();

    void on_actionReset_Game_triggered();

    void on_actionSet_Disks_triggered();

    void on_actionNew_Game_triggered();

    void on_actionExit_triggered();

    void on_actionAuto_Play_triggered();

    void on_actionUndo_All_triggered();

private:
    Ui::HanoiWindow *ui;
};

#endif // HANOIWINDOW_H
