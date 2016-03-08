#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QThread>
#include <QDebug>

class GameTimer;
class Robot : public QGraphicsItem {
public:
    QPixmap pm;
    QList<QPixmap> animation;
    int i = 1;
    int hp = 100;
    QRectF boundingRect() const
    {
        return QRectF(0,0,pm.width(),pm.height());
    }
    Robot(QString imageFile)
    {
        setFlag(ItemIsMovable);
        pm=QPixmap(":/sprites/"+imageFile);
    }

    void moveLeft()
    {
        pm = QPixmap(":/sprites/robot"+QString::number(i)+".png").transformed(QTransform().scale(-1, 1));
    }

    void moveRight()
    {
        pm = QPixmap(":/sprites/robot"+QString::number(i)+".png");
    }

    void standStill()
    {
        pm=QPixmap(":/sprites/robot.png");
    }

    void takeDamage()
    {
        hp = hp -10;
    }

    void move(int dir)
    {
        if(dir == 1)
        {
            moveLeft();

            this->setX(this->x()-1);
        } else {
            moveRight();

            this->setX(this->x()+1);
        }
        i++;
        if(i == 6)
        {
            i = 1;
        }
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem
               *option,
               QWidget *widget)
    {
        painter->drawPixmap(QPoint(0,0),pm);
    }

    void checkHp()
    {
        if(hp == 0)
        {
            setFlag(ItemIsMovable, false);
            pm = QPixmap(":/sprites/robot-pain.png");
        }
    }
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QGraphicsScene *scene;
    Robot *robot;
    GameTimer *leftMove;
    GameTimer *rightMove;
    GameTimer *gameLoop;

private slots:
    void onLeft();
    void onRight();
    void onGameLoop();

    void on_pushButton_pressed();

    void on_pushButton_released();

    void on_pushButton_2_pressed();

    void on_pushButton_2_released();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};

class GameTimer : public QThread
{
    Q_OBJECT
private:
    void run()
    {
        while(1)
        {
            emit signalFromThread();
            msleep(100);
        }
    }
signals:
    void signalFromThread();

};


#endif // MAINWINDOW_H
