#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    //scene->addText("hello world");
    robot = new Robot("walk.gif");
    scene->addItem(robot);

    ui->progressBar->setValue(robot->hp);

    leftMove = new GameTimer();
    rightMove = new GameTimer();
    gameLoop = new GameTimer();

    connect(leftMove, SIGNAL(signalFromThread()), this, SLOT(onLeft()));

    connect(rightMove, SIGNAL(signalFromThread()), this, SLOT(onRight()));

    connect(gameLoop, SIGNAL(signalFromThread()), this, SLOT(onGameLoop()));
    gameLoop->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRight()
{
    if(robot->hp > 0)
    {
        robot->move(3);
    }
}

void MainWindow::onLeft() {

    if(robot->hp > 0)
    {
        robot->move(1);
    }
}

void MainWindow::onGameLoop() {
    robot->checkHp();
    ui->progressBar->setValue(robot->hp);

    robot->standStill();
}

void MainWindow::on_pushButton_pressed()
{
    leftMove->start();
}

void MainWindow::on_pushButton_released()
{
    leftMove->terminate();
    robot->standStill();
}

void MainWindow::on_pushButton_2_pressed()
{
    rightMove->start();
}

void MainWindow::on_pushButton_2_released()
{
    rightMove->terminate();
    robot->standStill();
}

void MainWindow::on_pushButton_3_clicked()
{
    robot->takeDamage();
}
