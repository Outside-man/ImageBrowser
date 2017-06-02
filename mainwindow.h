#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <map>
#include <QCloseEvent>
#include <QApplication>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    map<QString, QImage> Img;
    map<QString, QLabel*> Label;
    int Num;
    bool trans;
    //void closeEvent(QCloseEvent *event);


private slots:
    void on_action_N_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_action_L_triggered();

    void on_action_R_triggered();

    void on_actioninfo_I_triggered();

    void on_actiontranslate_T_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
