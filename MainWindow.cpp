#include <iostream>
#include <QPainter>
#include <QTableWidget>
#include <QTime>
#include <cmath>

#include "MainWindow.hpp"
#include "build/ui_MainWindow.h"
#include "Star.hpp"
#include "Galaxy.hpp"


Galaxy *galaxy = new Galaxy(numStars);


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->pushButtonStart,  SIGNAL(clicked()), this, SLOT(buttonText()));
    connect(ui->massTopButton, SIGNAL(clicked()), this, SLOT(showMassTable()));
    if (ui->pushButtonStart->text() == textB[0]) {
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
    }

    timer->start(10);
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

void MainWindow::showMassTable() {
    int rows = ui->spinBox->value();
    auto table = new QTableWidget(rows, 1);
    table->setWindowTitle("Top Stars");
    table->setHorizontalHeaderLabels({"Mass"});
    auto top_it = galaxy->getTopKMass(rows);
    int row = 0;
    for (auto it = top_it.first; it < top_it.second; ++it) {
        table->setItem(row++, 0, new QTableWidgetItem(QString::number((*it)->m)));
    }
    table->show();
}

void MainWindow::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e)

    QPen pen{Qt::black, 1, Qt::SolidLine};
    QBrush brush{Qt::SolidPattern};
    QPainter painter{this};

    painter.setPen(pen);

    for (Star *star: *galaxy) {
        if (!star) continue;
        brush.setColor(star->col);
        painter.setBrush(brush);

        int x = std::floor(star->x[0] * coefX + centerX + topX0 - star->size * 0.5);
        int y = std::floor(star->x[1] * coefX + centerX + topY0 - star->size * 0.5);
        painter.drawEllipse(x, y, star->size, star->size);
    }

    elpTimer->start();
    galaxy->update();
    ui->lineEdit->setText(QString::number(galaxy->size()));
    ui->lineEdit_2->setText(QString::number(galaxy->centralStar->m));
    ui->lineEdit_3->setText(QString::number(1e9 / (double)elpTimer->nsecsElapsed()));
}
