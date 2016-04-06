#ifndef HANOIWINDOW_H
#define HANOIWINDOW_H

#include <QMainWindow>
#include "pole.h"
namespace Ui {
class HanoiWindow;
}

class HanoiWindow : public QMainWindow
{
    Q_OBJECT
    Pole *left;
    Pole *center;
    Pole *right;
public:

    explicit HanoiWindow(QWidget *parent = 0);
    ~HanoiWindow();

private slots:
    void on_btnLeft_clicked();

    void on_btnCenter_clicked();

    void on_btnRight_clicked();

private:
    Ui::HanoiWindow *ui;
};

#endif // HANOIWINDOW_H
