#ifndef HANOIWINDOW_H
#define HANOIWINDOW_H

#include <QMainWindow>
#include "pole.h"
#include "move.h"
#include <stack>
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
    void paintDisk(Pole *p, int diskIndex, QPushButton *b);
    void paintHover(Pole *p, int diskIndex, QPushButton *b);
    void paintAllDisks(Pole *p, QPushButton *b);
public:

    explicit HanoiWindow(QWidget *parent = 0);
    void click(Pole *p);
    ~HanoiWindow();
protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private slots:
    void on_btnLeft_clicked();

    void on_btnCenter_clicked();

    void on_btnRight_clicked();

    void on_actionUndo_Move_triggered();

private:
    Ui::HanoiWindow *ui;
};

#endif // HANOIWINDOW_H
