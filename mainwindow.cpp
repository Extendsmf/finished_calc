#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QPixmap"
#include "QtMath"
#include "poland.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800,600);
    button = new QPushButton(this);
    button->setGeometry(width()*0.8625, height()*0.0167, width()*0.125, height()*0.066);
    button->setText("draw");
    ui->label_x->setGeometry(width()*0.8625,60,width()*0.125,20);
    ui->lineEdit_x1->setGeometry(width()*0.8625, 90,40,20);
    ui->lineEdit_x2->setGeometry(width()*0.8625+60, 90,40,20);
    ui->label_y->setGeometry(width()*0.8625,120,width()*0.125,20);
    ui->lineEdit_y1->setGeometry(width()*0.8625, 150,40,20);
    ui->lineEdit_y2->setGeometry(width()*0.8625+60, 150,40,20);
    connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: buttonClicked(){
    ui->label->setGeometry(width()*0.012, height()*0.08, width()*0.8375, height()*0.905);
    ui->label->setStyleSheet("background-color: blue");
    QPixmap pm(ui->label->width(), ui->label->height());
    QPainter painter;
    painter.begin(&pm);
    pm.fill(Qt::black);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(1);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);

    double xmin = -10; double xmax = 10;
    if(ui->lineEdit_x1->text() != "") {
        xmin = ui->lineEdit_x1->text().toDouble();
    }
    if(ui->lineEdit_x2->text() != "") {
        xmax = ui->lineEdit_x2->text().toDouble();
    }

    int xgmin = 0; int xgmax = pm.width();
    int ygmin = 0; int ygmax = pm.height();
    double x, y;
    x = xmin;
    int xg, yg;

    double ymin = -10,  ymax = 10;
    if(ui->lineEdit_y1->text() != "") {
           ymin = ui->lineEdit_y1->text().toDouble();
       }
       if(ui->lineEdit_y2->text() != "") {
           ymax = ui->lineEdit_y2->text().toDouble();
       }
    double kx = (xgmax-xgmin)/(xmax-xmin);
    double ky = (ygmin-ygmax)/(ymax-ymin);
    double x0 = xgmin - kx*xmin;
    double y0 = ygmin - ky*ymax;
    double stepx = (xmax-xmin)/(xgmax-xgmin);
    painter.drawLine(0,y0,pm.width(),y0);
    painter.drawLine(x0,0,x0,pm.height());

    pen.setColor(Qt::yellow);
    QPainterPath path;
    QString fx = ui->lineEdit_fx->text();
    fx.replace("x", "(x)");
    QString tempf = fx;
    QString s1 =QString::number(x);
    tempf.replace("x", s1);
    double ans;
    std::string tempfStd = tempf.toStdString();
    painter.setPen(pen);
    x = xmin;
    int check = 1;
    if (calc(tempfStd, ans) == 0) {
        path.moveTo(x, ans);
    } else {
        check = -1;
    }
    while (x<=xmax){
        QString tempf = fx;
        double ans = 0;
        double clc = 0;
        QString s1 =QString::number(x);
        tempf.replace("x",s1);
        std::string tempfStd = tempf.toStdString();
        clc = calc(tempfStd, ans);
        if (clc == 0) {
            y = ans;
            xg = x0 + kx*x;
            yg = y0 + ky*y;
            if (check == -1) {
                path.moveTo(xg, yg);
                check = 1;
            } else {
                if(y >= ymax || y <= ymin)  {
                    path.moveTo(xg, yg);
                } else {
                     path.lineTo(xg, yg);
                }
            }

        }
        x += stepx;
    }
    painter.drawPath(path);
    ui->label->setPixmap(pm);
    painter.end();
}
