#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolButton>
#include <QSpinBox>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QImage>
#include <QTextEdit>
#include <QLabel>
#include <QRgb>
#include <QDebug>
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QToolButton *toolBtn = new QToolButton(this);
    toolBtn->setText(tr("颜色"));
    QMenu *colorMenu = new QMenu(this);
    colorMenu->addAction(tr("红色"));
    colorMenu->addAction(tr("绿色"));
    toolBtn->setMenu(colorMenu);
    toolBtn->setPopupMode(QToolButton::MenuButtonPopup);
    ui->mainToolBar->addWidget(toolBtn);
    QSpinBox *spinBox = new QSpinBox(this);
    ui->mainToolBar->addWidget(spinBox);
    blur_label=new QLabel;
    blur_flag = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_action_N_triggered()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("Open Image"));
    if(fileDialog->exec() == QDialog::Accepted) {
        gery_flag = false;
         QString path = fileDialog->selectedFiles()[0];
         before_img.load(path);
         before_img = before_img.scaled(before_img.width()*0.5,before_img.height()*0.5);
         blur_img1.load(path);
         blur_img1 = blur_img1.scaled(blur_img1.width()*0.5,blur_img1.height()*0.5);
         blur_img2.load(path);
         blur_img2 = blur_img2.scaled(blur_img2.width()*0.5,blur_img2.height()*0.5);
         QLabel *q = new QLabel;
         q->setPixmap(QPixmap::fromImage(before_img));
         q->setWindowTitle(path+"原图");
         ui->mdiArea->addSubWindow(q);
         q->setScaledContents(true);
         q->resize(q->width(),q->height());
         q->show();
    }
}

void MainWindow::on_pushButton_clicked(){
    //模糊
    QRgb grb;
    int green1,red1,blue1;
    int height=blur_img1.height();
    int width=blur_img1.width();
    for(int i=1;i<height-1;i++){
        for(int j=1;j<width-1;j++){
            int mohur=0,mohug=0,mohub=0;
            for(int k=i-1;k<=i+1;k++){
                for(int l=j-1;l<=j+1;l++){
                    grb = blur_img1.pixel(l,k);
                    red1 = qRed(grb);
                    green1 = qGreen(grb);
                    blue1 = qBlue(grb);
                    mohur+=red1;
                    mohug+=green1;
                    mohub+=blue1;
                }
            }
            grb = blur_img1.pixel(j,i);
            blur_img2.setPixel(j,i,qRgb(mohur/9,mohug/9,mohub/9));
        }
    }
    QLabel *label3=blur_label;
    label3->setPixmap(QPixmap::fromImage(blur_img2));
    if(!blur_flag){
        ui->mdiArea->addSubWindow(label3);
        label3->setScaledContents(true);
        //connect(temp,SIGNAL(destroyed(QObject*)),this,SLOT(close_ruijin()));
    }
    blur_flag = true;
    label3->show();
    blur_img1=blur_img2;
}
void MainWindow::close_gery(){
    gery_flag = false;
}
void MainWindow::on_pushButton_2_clicked(){
    gery_img = before_img;
    QRgb rgb;
    int red,green,blue;
    int height = before_img.height();
    int width = before_img.width();
    for(int i = 0;i<height;i++){
        for(int j = 0;j<width;j++){
           rgb = before_img.pixel(j,i);
           red = qRed(rgb);
           green = qGreen(rgb);
           blue = qBlue(rgb);
           int gray  = (red+green+blue)/3;
           gery_img.setPixel(j,i,qRgb(gray,gray,gray));
        }
    }
    if(!gery_flag){
        gery_flag = true;
        QLabel *q = new QLabel;
        q->setPixmap(QPixmap::fromImage(gery_img));
        q->setWindowTitle("灰度图");
        QMdiSubWindow*tomp= ui->mdiArea->addSubWindow(q);
        connect(tomp,SIGNAL(destroyed(QObject*)),this,SLOT(close_gery()));
        q->setScaledContents(true);
        q->resize(q->width(),q->height());
        q->show();
    }
}
