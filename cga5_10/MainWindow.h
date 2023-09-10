#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class RobotGLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initUi();

private slots:


    void on_hSlider1_valueChanged(int value);
    void on_hSlider2_valueChanged(int value);
    void on_hSlider3_valueChanged(int value);
    void on_hSlider4_valueChanged(int value);
    void on_hSlider5_valueChanged(int value);
    void on_hSlider6_valueChanged(int value);


    void on_pushButton_clicked();//执行直线轨迹
    void on_pushButton_7_clicked();//执行圆弧轨迹
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    RobotGLWidget  *m_robotGLWidget;     /* 机械臂对象 */
};

#endif
