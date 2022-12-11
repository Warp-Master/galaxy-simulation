#ifndef GALAXY_SIMULATION_MAINWINDOW_HPP
#define GALAXY_SIMULATION_MAINWINDOW_HPP
#include <QElapsedTimer>
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

//    bool ellipse = false;
    const QString textB[2] = {"Stop", "Start"};
    QTimer *timer = new QTimer(this);

    QElapsedTimer elpTimer;

private:
    Ui::MainWindow *ui;

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:

    void buttonText();
};
#endif //GALAXY_SIMULATION_MAINWINDOW_HPP