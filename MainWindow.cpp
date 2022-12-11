#include "MainWindow.hpp"
#include <cmath>

#include "build/ui_MainWindow.h"
#include <QPainter>
#include <QTime>
#include "Star.hpp"
#include "Galaxy.hpp"
#include "constants.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->pushButtonStart,  SIGNAL(clicked()), this, SLOT(buttonText()));
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
//    connect(timer, &QTimer::timeout, this, SLOT(myTimer()));
    timer->start(0);
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
    for (Star *star: *galaxy) {
        if (!star) continue;
        brush.setColor(star->col);
        painter.setBrush(brush);

        int x = floor(star->x[0] * coefX + centerX + topX0 - star->size * 0.5);
        int y = floor(star->x[1] * coefX + centerX + topY0 - star->size * 0.5);
        // условие не рисовать вне квадрата
//        if((0 < x && x < length) && (0 < y && y < h))
            painter.drawEllipse(x, y, star->size, star->size);
    }
    galaxy->update();
    ui->lineEdit->setText(QString::number(galaxy->star_cnt));
    ui->lineEdit_2->setText(QString::number(galaxy->central_star->m));
    ui->lineEdit_3->setText(QString::number(galaxy->central_star->x[0]));
}
