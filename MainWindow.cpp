#include "MainWindow.hpp"
#include <cmath>

#include "build/ui_mainwindow.h"
#include <QPainter>
#include <QTime>
#include "Star.hpp"
#include "Galaxy.hpp"
#include "constants.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
//    connect(ui->pushButtonStart,  SIGNAL(clicked()), this, SLOT(buttonText()));
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
//    connect(timer, &QTimer::timeout, this, SLOT(myTimer()));
    timer->start(1);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::buttonText() {
    if (ui->pushButtonStart->text() == textB[0]) {
        ui->pushButtonStart->setText(textB[1]);
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
    } else {
        ui->pushButtonStart->setText(textB[0]);
        disconnect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
    }
}

const int topX0 = 100, topY0 = 100, h = 800, length = 800;
Galaxy *galaxy = new Galaxy(numStars);

void MainWindow::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);
    QPainter painter(this);
    QPen pen(Qt::black, 1, Qt::SolidLine);
    painter.setPen(pen);

//  QTime time = QTime::currentTime();
//  int mSec = time.msec();
//  int Sec = time.second();

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    double coefX = length / 2 / 1e12; // system radius
    int centerX = length / 2;
    for (Star *star_i: galaxy->stars) {
        brush.setColor(star_i->col);
        painter.setBrush(brush);
        // условие не рисовать вне квадрата
        /* if(galactika->stars[i]->x[0] * coefX + centerX + topX0 > 0 &&
            galactika->stars[i]->x[0] * coefX + centerX  < length &&
            galactika->stars[i]->x[1] * coefX + centerX + topY0 > 0 &&
            galactika->stars[i]->x[1] * coefX + centerX  < h) */
        painter.drawEllipse(floor(star_i->x[0] * coefX + centerX + topX0),
                            floor(star_i->x[1] * coefX + centerX + topY0),
                            6, 6);
    }
    galaxy->update();

    ui->lineEdit->setText(QString::number(galaxy->stars.size()));
    ui->lineEdit_2->setText(QString::number(galaxy->central_star->m));
    ui->lineEdit_3->setText(QString::number(galaxy->central_star->x[0]));
}
