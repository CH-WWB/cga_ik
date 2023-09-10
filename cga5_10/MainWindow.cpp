#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <robotglwidget.h>
#include <QSettings>
#include <QDebug>
#include <QtConcurrent>

const QString CONFIG_PATH = "config.ini";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QStringLiteral("cga的机械臂运动仿真软件"));
    initUi();
    this->setGeometry(50, 50, 2000, 1400);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUi()
{
    //机械臂
    m_robotGLWidget = new RobotGLWidget();

    ui->vly3d->addWidget(m_robotGLWidget);

}


void MainWindow::on_pushButton_clicked()//执行直线轨迹运动
{
    m_robotGLWidget->Run_zhixian();
}
void MainWindow::on_pushButton_7_clicked()//执行圆弧轨迹运动
{
    m_robotGLWidget->Run_yuanhu();
}

void MainWindow::on_pushButton_2_clicked()//标记此点
{
    m_robotGLWidget->setPoint();
}

void MainWindow::on_pushButton_3_clicked()//清除上一个标记点
{
    m_robotGLWidget->delePoint();
}

void MainWindow::on_pushButton_4_clicked()//圆弧轨迹规划
{
    m_robotGLWidget->traj_yuanhu_n();
    m_robotGLWidget->traj_yuanhu_pit();
    m_robotGLWidget->traj_yuanhu_pt();
}

void MainWindow::on_pushButton_6_clicked()//直线轨迹规划
{
    m_robotGLWidget->traj_zhixian_n();
     m_robotGLWidget->traj_zhixian_pit();
      m_robotGLWidget->traj_zhixian_pt();
}


void MainWindow::on_pushButton_5_clicked()//清除轨迹
{
     m_robotGLWidget->clear();
}


void MainWindow::on_hSlider1_valueChanged(int value)
{
    m_robotGLWidget->setTh1(value);
}

void MainWindow::on_hSlider2_valueChanged(int value)
{
    m_robotGLWidget->setTh2(value);
}

void MainWindow::on_hSlider3_valueChanged(int value)
{
    m_robotGLWidget->setTh3(value);
}

void MainWindow::on_hSlider4_valueChanged(int value)
{
    m_robotGLWidget->setTh4(value);
}

void MainWindow::on_hSlider5_valueChanged(int value)
{
    m_robotGLWidget->setTh5(value);
}

void MainWindow::on_hSlider6_valueChanged(int value)
{
    m_robotGLWidget->setTh6(value);
}





