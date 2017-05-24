#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QImage before_img,gery_img,blur_img1,blur_img2;
    QLabel *blur_label;
    bool blur_flag,gery_flag;
    ~MainWindow();

private slots:
    void on_action_N_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void close_gery();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
