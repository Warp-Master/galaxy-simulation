#include "mainwindow.h"
#include "math.h"

#include "ui_mainwindow.h"
#include <QPainter>
#include <QTime>
#include <star.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
//    connect(ui->pushButtonStart,  SIGNAL(clicked()), this, SLOT(buttonText()));
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
//    connect(timer, &QTimer::timeout, this, SLOT(myTimer()));
    timer->start(1);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::buttonText(){
    if(ui->pushButtonStart->text()==textB[0]){
        ui->pushButtonStart->setText(textB[1]);
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
    }else{
        ui->pushButtonStart->setText(textB[0]);
        disconnect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
    }
    return;
}

const int topX0 = 100, topY0 = 100, h = 800, length = 800;
galaxy *galactika = new galaxy;

void MainWindow::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e);
  QPainter painter(this);
  QPen pen(Qt::black, 1, Qt::SolidLine);
  painter.setPen(pen);

//  QTime time = QTime::currentTime();
//  int mSec = time.msec();
//  int Sec = time.second();

  QBrush brush;//(Qt::yellow);
  brush.setStyle(Qt::SolidPattern);

  double coefX = length / 2 / 1e12; // system radius
  int centerX = length / 2;
  for(int i = 0; i < galactika->num; ++i){
      if(galactika->stars[i]){
          brush.setColor(galactika->stars[i]->col);
          if(!i) brush.setColor(Qt::yellow);
          painter.setBrush(brush);
          for(int k = 0; k < 2; ++k){
             // условие не рисовать вне квадрата
             /* if(galactika->stars[i]->x[0] * coefX + centerX + topX0 > 0 &&
                 galactika->stars[i]->x[0] * coefX + centerX  < length &&
                 galactika->stars[i]->x[1] * coefX + centerX + topY0 > 0 &&
                 galactika->stars[i]->x[1] * coefX + centerX  < h) */
                    painter.drawEllipse(galactika->stars[i]->x[0] * coefX + centerX + topX0,
                                        galactika->stars[i]->x[1] * coefX + centerX + topY0,
                                        6 + 4 * !i, 6 + 4 * !i);
          }
      }
  }
  galactika->move();

  ui->lineEdit->setText(QString::number(star::starCounter));
  ui->lineEdit_2->setText(QString::number(galactika->stars[0]->m));
  ui->lineEdit_3->setText(QString::number(galactika->stars[0]->x[0]));
}
