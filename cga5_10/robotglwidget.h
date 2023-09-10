#ifndef ROBOTGL_H
#define ROBOTGL_H
#include <QStack>
#include <QReadWriteLock>
#include <QMatrix4x4>
#include <QTimer>
#include "BaseGLWidget.h"
#include "stlfileloader.h"

#include "cga.h"


#define PI 3.1415926

struct PathTheta {double th1,th2,th3,th4,th5,th6;};//theta类型的数据

struct PathPoint { double x, y,z ;};//x,y,z坐标类型的数据

struct CZ_Point { double x, y;};//2d插值坐标类型的数据

struct MultiPoint { double x, y,z,m,n ;};//fk_n和fk_Pit的坐标类型的数据


const int NUM_SOLUTIONS = 4;
const int NUM_JOINTS = 6;

const double JOINT_MIN[NUM_JOINTS] = { -180, -180, -180, -180, -180, -180};
const double JOINT_MAX[NUM_JOINTS] = { 180,  180,  180,180,  180,  180};

using namespace std;
using namespace cga;

class RobotGLWidget: public BaseGLWidget
{
    Q_OBJECT
public:
    RobotGLWidget(QWidget *parent = 0);
    ~RobotGLWidget();

    void drawGL() override;
    void drawRobot();
    void drawtrack();//画插值产生的点和轨迹
    void drawpoint();//画主动标记的点

    //运动学函数
    void forward(const double* q);//正运动学

    QVector<PathTheta> inverse(PathPoint fk_n, MultiPoint fk_Pt,MultiPoint fk_Pit);//逆运动学

    //计算二维圆弧的半径//需要3个点//起始点//中间点//终点
    void SetArcRadius(double dStart[2], double dMid[2], double dEnd[2]);

    //设置变换矩阵,将二维变换成三维
    void SetChangeMatrix_n(double dStart[3], double dMid[3], double dEnd[3]);
    void SetChangeMatrix_pit(double dStart[3], double dMid[3], double dEnd[3]);
    void SetChangeMatrix_pt(double dStart[3], double dMid[3], double dEnd[3]);

    void Run_zhixian();//执行直线轨迹运动仿真
    void Run_yuanhu();//执行圆弧轨迹运动仿真

    Multivector formula(Multivector Ppn,int t);
    double judge_th(double _cos_th,double _region_s,double _region_e);

public slots:

    void setTh1(double th1);//槽函数，用以更新成员变量th
    void setTh2(double th2);
    void setTh3(double th3);
    void setTh4(double th4);
    void setTh5(double th5);
    void setTh6(double th6);

    //直线轨迹规划
    void traj_zhixian_pt();
    void traj_zhixian_pit();
    void traj_zhixian_n();

    //圆弧轨迹规划
    void traj_yuanhu_pt();
    void traj_yuanhu_pit();
    void traj_yuanhu_n();

    void clear();//清除轨迹
    void setPoint();//设置标记点的函数
    void delePoint();//删除标记点的函数

public:

     struct STLModel
     {
         STLFileLoader *base;      /**< 底座 */
         STLFileLoader *link2;     /**< 关节2 */
         STLFileLoader *link3;     /**< 关节3 */
         STLFileLoader *link4;     /**< 关节4 */
         STLFileLoader *link5;     /**< 关节5 */
         STLFileLoader *link6;     /**< 关节6 */
     };

     //机械臂尺寸
     double d2 = 149.09;
     double d4 = 433.07;
     double d6 = 56.25;
     double a2 = 431.8;
     double a3 = -20.32;

     STLModel model;

     QTimer *m_timer =nullptr;

     double th1,th2,th3,th4,th5,th6;

     QStack<PathPoint> point_stack_n_hz;//存放 用以画箭头的n

     QStack<PathPoint> point_stack_n;//存放 标记产生的点的n
     QStack<MultiPoint> point_stack_Pt;//存放 标记产生的点的Pt
     QStack<MultiPoint> point_stack_Pit;//存放 标记产生的点的Pit

     QVector<PathPoint> point_vector_n;//存放 point_stack_n中的点
     QVector<MultiPoint> point_vector_Pt;//存放 point_stack_Pt中的点
     QVector<MultiPoint> point_vector_Pit;//存放 point_stack_Pit中的点


     QVector<double> chazhi_theta_2d;
     QVector<CZ_Point> chazhi_zb_2d;

     QVector<PathPoint> chazhi_n_zhixian;//存放 经过直线轨迹规划产生的 向量插值点
     QVector<MultiPoint> chazhi_pt_zhixian;//存放 经过直线轨迹规划产生的 坐标pt插值点
     QVector<MultiPoint> chazhi_pit_zhixian;//存放 经过直线轨迹规划产生的 pit插值点

     QVector<PathPoint> chazhi_n_yuanhu;//存放 经过圆弧轨迹规划产生的 向量插值点
     QVector<MultiPoint> chazhi_pit_yuanhu;//存放 经过圆弧轨迹规划产生的 pit插值点
     QVector<MultiPoint> chazhi_pt_yuanhu;//存放 经过圆弧轨迹规划产生的 坐标pt插值点

     //动画
     //需要获得直线和圆弧轨迹规划插值点对应的角度值
     QVector<PathTheta> zhixian_ik_theta;//存放 将chazhi_X_zhixian 通过逆运动学 转换成对应的关节角度
     QVector<PathTheta> yuanhu_ik_theta;//存放 将chazhi_zb_3d 通过逆运动学 转换成对应的关节角度

     int num_marked=0;//主动标记的点的数量
     double start_theta[6];//存放起始点的各关节theta值，用以进行最优逆运动学解的筛选

     //用于动画的变量dingshi和ss一定要是全局的成员变量，而不能写到change_theta()函数中变成局部变量，否则会出错
     QTimer dingshi_zx; // 创建定时器对象
     QTimer dingshi_yh;
     int ss=0;

     bool clear_traj;

     Multivector fk_Pt ;
     Multivector fk_n ;
     Multivector fk_Pit ;

//     //th2的取值区间
//     double region_th2_s=0;
//     double region_th2_e=90;

//     //th3的取值区间
//     double region_th3_s=0;
//     double region_th3_e=90;

     //th4的取值区间
     double region_th4_s=0;
     double region_th4_e=90;

     //th5的取值区间
     double region_th5_s=0;
     double region_th5_e=90;

     //th6的取值区间
     double region_th6_s=0;
     double region_th6_e=90;

};

#endif
