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

    const QString textB[2] = {"Start", "Stop"};
    QTimer *timer = new QTimer(this);
    QElapsedTimer *elpTimer = new QElapsedTimer;

private:
    Ui::MainWindow *ui;

protected:
//    void update(QPaintEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void showMassTable();
    void buttonText();
};
#endif //GALAXY_SIMULATION_MAINWINDOW_HPP