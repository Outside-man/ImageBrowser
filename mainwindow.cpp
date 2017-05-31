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
#include <qdebug.h>
#include <string>


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

    Num = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_action_N_triggered()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("Open Image"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    if(fileDialog->exec() == QDialog::Accepted) {
         for(QString path : fileDialog->selectedFiles()){
             qDebug()<<path<<endl;
             QImage img;
             img.load(path);
             QStringList  s = path.split(".");
             qDebug()<<s.last()<<endl;
             QLabel *q = new QLabel;
             q->setPixmap(QPixmap::fromImage(img));
             QString title ;
             title = "Unnamed" + QString::number(Num) + "." + s.last();
             Label.insert(make_pair(title, q));
             Img.insert(make_pair(title, img));
             q->setWindowTitle(title);
             qDebug()<<title<<endl;
             qDebug()<<Num<<endl;
             Num++;
             ui->mdiArea->addSubWindow(q);
             q->setScaledContents(true);
             q->resize(q->width(),q->height());
             q->show();
         }
    }
}

void MainWindow::on_pushButton_clicked(){
    QMdiSubWindow *ql = ui->mdiArea->activeSubWindow();
    qDebug()<<ql->windowTitle()<<endl;
    QString title = ql->windowTitle();
    if(Img.find(title)==Img.end())return;
    QImage before_img = Img[title];
    QImage blur_img = Img[title];
    //模糊
    QRgb grb;
    int green1,red1,blue1;
    int height=before_img.height();
    int width=before_img.width();
    for(int i=1;i<height-1;i++){
        for(int j=1;j<width-1;j++){
            int mohur=0,mohug=0,mohub=0;
            for(int k=i-1;k<=i+1;k++){
                for(int l=j-1;l<=j+1;l++){
                    grb = before_img.pixel(l,k);
                    red1 = qRed(grb);
                    green1 = qGreen(grb);
                    blue1 = qBlue(grb);
                    mohur+=red1;
                    mohug+=green1;
                    mohub+=blue1;
                }
            }
            blur_img.setPixel(j,i,qRgb(mohur/9,mohug/9,mohub/9));
        }
    }
    QLabel *q = Label[title];
    q->setPixmap(QPixmap::fromImage(blur_img));
    Img[title] = blur_img;
    q->setScaledContents(true);
    q->show();
}

//灰度化
void MainWindow::on_pushButton_2_clicked(){
    //QMdiSubWindow
    QMdiSubWindow *ql = ui->mdiArea->activeSubWindow();
    QString title = ql->windowTitle();
    if(Img.find(title)==Img.end())return;
    QImage before_img = Img[title];
    QImage grey_img = Img[title];
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
           grey_img.setPixel(j,i,qRgb(gray,gray,gray));
        }
    }
    QLabel *q = Label[title];
    q->setPixmap(QPixmap::fromImage(grey_img));
    Img[title] = grey_img;
    q->setScaledContents(true);
    q->resize(q->width(),q->height());
    q->show();
}
