 #include "robotglwidget.h"
#include <QDebug>
#include <QtConcurrent>
#include <QFuture>
#include <QVector4D>

static int k=1;//放大系数
int num_steps = 9;//插值的步数



//定义对象e1、e2、e3、e4、e5、e0、ei,x,y,z轴

Vector e1(1, 0, 0, 0, 0);
Vector e2(0, 1, 0, 0, 0);
Vector e3(0, 0, 1, 0, 0);
Vector e4(0, 0, 0, 1, 0);
Vector e5(0, 0, 0, 0, 1);
Vector e0(0, 0, 0, -0.5, 0.5);
Vector ei(0, 0, 0, 1, 1);

Vector P1 = e0;

Bivector lz = geom(e1, e2);
Bivector ly = geom(e1, e3);
Bivector lx = geom(e2, e3);


RobotGLWidget::RobotGLWidget(QWidget *parent)
    :BaseGLWidget(parent)
{
    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,[=](){updateGL();});
    m_timer->start(5);//定时器每隔5ms扫描

    QString root = "./sl/";
    //加载STL文件

    model.base  = new STLFileLoader(root + "cgalj01.stl", k);
    model.link2 = new STLFileLoader(root + "cgalj02.stl", k);
    model.link3 = new STLFileLoader(root + "cgalj03.stl", k);
    model.link4 = new STLFileLoader(root + "cgalj04.stl", k);
    model.link5 = new STLFileLoader(root + "cgalj05.stl", k);
    model.link6 = new STLFileLoader(root + "cgalj06.stl", k);

    QThreadPool::globalInstance()->setMaxThreadCount(20);

    QtConcurrent::run([&]()
    {
        model.base->load();
    });
    QtConcurrent::run([&]()
    {
      model.link2->load();
    });
    QtConcurrent::run([&]()
    {
      model.link3->load();
    });
    QtConcurrent::run([&]()
    {
      model.link4->load();
    });
    QtConcurrent::run([&]()
    {
      model.link5->load();
    });
    QtConcurrent::run([&]()
    {
      model.link6->load();
    });

    connect(model.base, &STLFileLoader::finished, this, &RobotGLWidget::updateGL);
    connect(model.link2, &STLFileLoader::finished, this, &RobotGLWidget::updateGL);
    connect(model.link3, &STLFileLoader::finished, this, &RobotGLWidget::updateGL);
    connect(model.link4, &STLFileLoader::finished, this, &RobotGLWidget::updateGL);
    connect(model.link5, &STLFileLoader::finished, this, &RobotGLWidget::updateGL);
    connect(model.link6, &STLFileLoader::finished, this, &RobotGLWidget::updateGL);

    th1=0;
    th2=0;
    th3=0;
    th4=0;
    th5=0;
    th6=0;
}

RobotGLWidget::~RobotGLWidget()
{
    m_timer->stop();
    delete  m_timer;
    m_timer = nullptr;
}

void RobotGLWidget::drawGL()
{
    /* 网格线 */
    drawMeshline(100,30);
    /* 坐标轴 */
    drawCoordAxis();

    drawRobot();//画机械臂

    glDisable(GL_LIGHTING); // 禁用光照和材质属性

    drawpoint();//画点
    drawtrack();//画轨迹

    glEnable(GL_LIGHTING);// 启用光照和材质属性
}

void RobotGLWidget::drawRobot()
{  

    glPushMatrix();

    /* lj1 */
    glRotatef(th1, 0.0, 0.0, 1.0);//lj1相对于世界坐标的变换

    glTranslatef(-10,0,-20);//纠正lj1模型导入时相对于世界坐标的位置

    setGLMaterialColor(187,255,255);//蓝
    model.base->draw();

    /* lj2 */

    glTranslatef(10,0,20);//lj2移除lj1相对于世界坐标的纠正

    glTranslatef(0,129.09,0);//纠正lj2模型导入时相对于世界坐标的位置
    glRotatef(th2, 0.0, 1.0, 0.0);//lj2相对于世界坐标的变换

    setGLMaterialColor(255 ,0, 0);//红
    model.link2->draw();

    /* lj3 */

    glTranslatef(0,-129.09,0);//lj3移除lj2相对于世界坐标的纠正

    glTranslatef(431.8,119.09,0);//纠正lj3模型导入时相对于世界坐标的位置
    glRotatef(th3, 0.0, 1.0, 0.0);//lj3相对于世界坐标的变换
    glTranslatef(-20.32,0,0);//纠正lj3模型旋转轴的位置

    setGLMaterialColor(255,255 ,0);//黄
    model.link3->draw();

    /* lj4 */

    glTranslatef(-431.8+20.32,-119.09,0);//lj4移除lj3相对于世界坐标的纠正

    glTranslatef(431.8-20.32,149.09,-20);//纠正lj4模型导入时相对于世界坐标的位置
    glRotatef(th4, 0.0, 0.0, 1.0);//lj4相对于世界坐标的变换
    glTranslatef(-10,0,0);//纠正lj4模型旋转轴的位置

    setGLMaterialColor(255,0,255);//紫
    model.link4->draw();

    /* lj5 */

    glTranslatef(-431.8+20.32+10,-149.09,+20);//lj5移除lj4相对于世界坐标的纠正

    glTranslatef(431.8-20.32,149.09-20,433.07);//纠正lj5模型导入时相对于世界坐标的位置
    glRotatef(th5, 0.0, 1.0, 0.0);//lj5相对于世界坐标的变换
    glTranslatef(-10,0,0);//纠正lj5模型旋转轴的位置

    setGLMaterialColor(124,252,0);//绿
    model.link5->draw();

    /* lj6 */

    glTranslatef(-431.8+20.32+10,-149.09+20,-433.07);//lj6移除lj5相对于世界坐标的纠正

    glTranslatef(431.8-20.32,149.09,433.07+15);//纠正lj6模型导入时相对于世界坐标的位置
    glRotatef(th6, 0.0, 0.0, 1.0);//lj6相对于世界坐标的变换
    glTranslatef(-33,0,0);//纠正lj6模型旋转轴的位置

    setGLMaterialColor(238,230,133);//土黄
    model.link6->draw();

    glPopMatrix();
}

void RobotGLWidget::drawtrack()//画插值产生的点和线
{
    if(clear_traj==true)
    {
        chazhi_zb_2d.clear();

        chazhi_pt_yuanhu.clear();

        point_stack_n.clear();
        point_stack_n_hz.clear();
        point_stack_Pit.clear();
        point_stack_Pt.clear();

        point_vector_n.clear();
        point_vector_Pit.clear();
        point_vector_Pt.clear();

        chazhi_n_zhixian.clear();
        chazhi_pit_zhixian.clear();
        chazhi_pt_zhixian.clear();
        clear_traj=false;
    }

    //画直线插值点并连线
    glPointSize(4);
    glColor3f(0.5,1.0,1.0);//亮绿色
    glBegin(GL_POINTS);//将容器中的点画出
        for (auto it = chazhi_pt_zhixian.begin(); it != chazhi_pt_zhixian.end(); ++it)
        {
            const MultiPoint& point = *it;
            glVertex3f(point.x, point.y, point.z);
        }
    glEnd();

    glBegin(GL_LINE_STRIP);//将容器中的点连线

        for (auto it = chazhi_pt_zhixian.begin(); it != chazhi_pt_zhixian.end(); ++it)
        {
            const MultiPoint& point = *it;
            glVertex3f(point.x, point.y, point.z);
        }
    glEnd();


    //画圆弧插值点并连线
    glPointSize(4);
    glColor3f(1.0,1.0,0.0);//黄色

    glBegin(GL_POINTS);//将容器中的点画出
        for (auto it =  chazhi_pt_yuanhu.begin(); it !=  chazhi_pt_yuanhu.end(); ++it)
        {
            const MultiPoint& point = *it;
            glVertex3f(point.x, point.y, point.z);
        }
    glEnd();

    glBegin(GL_LINE_STRIP);//将容器中的点连线
        for (auto it =  chazhi_pt_yuanhu.begin(); it !=  chazhi_pt_yuanhu.end(); ++it)
        {
            const MultiPoint& point = *it;
            glVertex3f(point.x, point.y, point.z);
        }
    glEnd();
}

void RobotGLWidget::drawpoint()//画 主动标记的坐标点pt和n
{
    //画pt
    glBegin(GL_POINTS);
    glPointSize(5);
    glColor3f(1.0,0.0,0.0);
    QStack<MultiPoint>::iterator i;
    for(i = point_stack_Pt.begin(); i < point_stack_Pt.end(); ++i)
        glVertex3f(i->x, i->y, i->z);
    glEnd();

    //画n
    glBegin(GL_POINTS);
    glPointSize(50);
    glColor3f(0.0,1.0,0.0);
    QStack<PathPoint>::iterator j;
    for(j = point_stack_n_hz.begin(); j < point_stack_n_hz.end(); ++j)
        glVertex3f(j->x, j->y, j->z);
    glEnd();

    // 画连接线
    glBegin(GL_LINES);
    glLineWidth(4.0); // 设置线段宽度
    glColor3f(1.0,1.0,0.0);
    for (i = point_stack_Pt.begin(), j = point_stack_n_hz.begin();
         i != point_stack_Pt.end() && j != point_stack_n_hz.end();
         ++i, ++j)
    {
        glVertex3f(i->x, i->y, i->z);
        glVertex3f(j->x, j->y, j->z);
    }
    glEnd();
}

//正运动学函数
void RobotGLWidget::forward(const double *q)
{
    //需要输入6个角度值 不知道为什么，如果输入的角度是0就会出错，但可以输入0.1
    double arr_theta_xz[6];

    for (int i = 0; i < 6; i++)
    {
        if (q[i]== 0)
            arr_theta_xz[i] = 0.1;

        else
            arr_theta_xz[i] =q[i];

    }

    double theta_one = arr_theta_xz[0]* M_PI/180;
    double theta_two = arr_theta_xz[1] * M_PI / 180;
    double theta_three = arr_theta_xz[2] * M_PI / 180;
    double theta_four= arr_theta_xz[3] * M_PI / 180;
    double theta_five = arr_theta_xz[4] * M_PI / 180;
    double theta_six = arr_theta_xz[5] * M_PI / 180;

    //计算M_12
    Multivector R_1z = make_rotation(theta_one, lz);
    Multivector T_1y = make_translation(0, d2, 0);
    Multivector M_12 = geom(R_1z,T_1y);

    //计算M_23
    Multivector R_2y = make_rotation(theta_two, -ly);
    Multivector T_2x = make_translation(a2, 0, 0);
    Multivector M_23 = geom(R_2y, T_2x);

    //计算M_34
    Multivector R_3y = make_rotation(theta_three, -ly);
    Multivector T_3x = make_translation(a3, 0, 0);
    Multivector M_34 = geom(R_3y, T_3x);

    //计算M_45
    Multivector R_4z = make_rotation(theta_four, lz);
    Multivector T_3z = make_translation(0, 0, d4);
    Multivector M_45 = geom(R_4z, T_3z);

    //计算M_56
    Multivector R_5y = make_rotation(theta_five, -ly);
    Multivector M_56 = R_5y;

    //计算M_67
    Multivector R_6z = make_rotation(theta_six, lz);
    Multivector T_6z = make_translation(0, 0, d6);
    Multivector M_67 = geom(R_6z, T_6z);

    //计算P点
    Multivector M_07= geom(geom(geom(geom(geom(M_12, M_23), M_34),M_45),M_56),M_67);

    fk_Pt = geom(geom(M_07, e0), cga::reverse(M_07));
    fk_n = geom(geom(M_07, e3), cga::reverse(M_07));
    fk_Pit = geom(geom(M_07, e2), cga::reverse(M_07));

}

//逆运动学函数
QVector<PathTheta> RobotGLWidget::inverse(PathPoint fk_n, MultiPoint fk_Pt, MultiPoint fk_Pit)
{

    Multivector n;
    n.v.e1 = fk_n.x;
    n.v.e2 = fk_n.y;
    n.v.e3 = fk_n.z;


    Multivector Pt;
    Pt.v.e1 = fk_Pt.x;
    Pt.v.e2 = fk_Pt.y;
    Pt.v.e3 = fk_Pt.z;
    Pt.v.e4 = fk_Pt.m;
    Pt.v.e5 = fk_Pt.n;

    Multivector Pit;
    Pit.v.e1 = fk_Pit.x;
    Pit.v.e2 = fk_Pit.y;
    Pit.v.e3 = fk_Pit.z;
    Pit.v.e4 = fk_Pit.m;
    Pit.v.e5 = fk_Pit.n;

    //求p6（p5）
    //-----------------------------------(start)--------------------------------------
        Multivector T6 = 1+0.5 * d6 * geom(n, ei) ;
        Multivector P6 = geom(geom(T6, Pt), cga::reverse(T6));
        P6 = vectorpart(P6, 1);
    //------------------------------------(end)---------------------------------------

    //计算theta1
    //-----------------------------------(start)--------------------------------------
        double p6x = P6.v.e1;
        double p6y = P6.v.e2;

        double a_1 = (-p6x + sqrt(p6x * p6x + p6y * p6y - d2 * d2)) / (d2 + p6y);
        double a_2= (-p6x - sqrt(p6x * p6x + p6y * p6y - d2 * d2)) / (d2 + p6y);

        double th1_1 = 2 * atan(a_1);
        double th1_2 = 2 * atan(a_2);

    //------------------------------------(end)---------------------------------------

    //求P2
    //-----------------------------------(start)--------------------------------------
        Multivector P2_1, P2_2, Pi1_1, Pi1_2;
        P2_1 = conformal(-d2 * sin(th1_1), d2 * cos(th1_1), 0);
        P2_2 = conformal(-d2 * sin(th1_2), d2 * cos(th1_2), 0);

        Pi1_1.v.e1 = -sin(th1_1);
        Pi1_1.v.e2 = cos(th1_1);
        Pi1_1.v.e4 = d2;
        Pi1_1.v.e5 = d2;

        Pi1_2.v.e1 = -sin(th1_2);
        Pi1_2.v.e2 = cos(th1_2);
        Pi1_2.v.e4 = d2;
        Pi1_2.v.e5 = d2;
    //------------------------------------(end)---------------------------------------

    //求p3_1-3_4
    //-----------------------------------(start)--------------------------------------
        Multivector S13 = P1 - 0.5 * (d2*d2+a2*a2) * ei;
        Multivector S63 = P6 - 0.5 * (d4 * d4 + a3 * a3) * ei;
        Multivector Pp3_1 = anti(outer(outer(S13, S63), Pi1_1));
        Multivector Pp3_2 = anti(outer(outer(S13, S63), Pi1_2));
        Multivector P3_1 = formula(Pp3_1, 1);
        Multivector P3_2 = formula(Pp3_1, -1);
        Multivector P3_3 = formula(Pp3_2, 1);
        Multivector P3_4 = formula(Pp3_2, -1);
    //------------------------------------(end)---------------------------------------

    //求p4_1-4_4
    //-----------------------------------(start)--------------------------------------
        Multivector S34_1 = P3_1 - 0.5 * pow(a3, 2) * ei;
        Multivector S64 = P6 - 0.5 * pow(d4, 2) * ei;
        Multivector Pp4_1 = anti(outer(outer(S34_1, S64), Pi1_1));
        Multivector P4_1 = formula(Pp4_1, -1);

        Multivector S34_2 = P3_2 - 0.5 * pow(a3, 2) * ei;
        Multivector Pp4_2 = anti(outer(outer(S34_2, S64), Pi1_1));
        Multivector P4_2 = formula(Pp4_2, -1);

        Multivector S34_3 = P3_3 - 0.5 * pow(a3, 2) * ei;
        Multivector Pp4_3 = anti(outer(outer(S34_3, S64), Pi1_2));
        Multivector P4_3 = formula(Pp4_3, -1);

        Multivector S34_4 = P3_4 - 0.5 * pow(a3, 2) * ei;
        Multivector Pp4_4 = anti(outer(outer(S34_4, S64), Pi1_2));
        Multivector P4_4 = formula(Pp4_4, -1);
    //------------------------------------(end)---------------------------------------

    //求theta_two
    //-----------------------------------(start)--------------------------------------
        Multivector Pi123_1 = anti(outer(outer(outer(P1, P2_1), P3_1), ei));
        Multivector Pi123_2 = anti(outer(outer(outer(P1, P2_1), P3_2), ei));
        Multivector Pi123_3 = anti(outer(outer(outer(P1, P2_2), P3_3), ei));
        Multivector Pi123_4 = anti(outer(outer(outer(P1, P2_2), P3_4), ei));

        double cos_th2_1 = scalarpart(inner(Pi123_1, e3)) / sqrt(scalarpart(inner(Pi123_1, Pi123_1)));
        double cos_th2_2 = scalarpart(inner(Pi123_2, e3)) / sqrt(scalarpart(inner(Pi123_2, Pi123_2)));
        double cos_th2_3 = scalarpart(inner(Pi123_3, e3)) / sqrt(scalarpart(inner(Pi123_3, Pi123_3)));
        double cos_th2_4 = scalarpart(inner(Pi123_4, e3)) / sqrt(scalarpart(inner(Pi123_4, Pi123_4)));

        //验证th2_1：
        //-----------------------------------(start)--------------------------------------
           double th2_1;
           double th2_1_z = acos(cos_th2_1);
           double th2_1_f = -acos(cos_th2_1);
           Multivector yz_R_1z = make_rotation(th1_1, lz);
           Multivector yz_T_1y = make_translation(0, d2, 0);
           Multivector yz_M_12 = geom(yz_R_1z, yz_T_1y);

           Multivector yz_R_2y = make_rotation(th2_1_z, -ly);
           Multivector yz_T_2x = make_translation(a2, 0, 0);
           Multivector yz_M_23 = geom(yz_R_2y, yz_T_2x);

           Multivector yz_p3= geom(geom(geom(yz_M_12, yz_M_23), P1), cga::reverse(geom(yz_M_12, yz_M_23)));

           double val_1 = abs((yz_p3.v.e1 + yz_p3.v.e2 + yz_p3.v.e3) - (P3_1.v.e1 + P3_1.v.e2 + P3_1.v.e3));
           if (val_1 <1)
           {
               th2_1 = th2_1_z ;
           }
           else
           {
               th2_1 = th2_1_f;
           }
       //------------------------------------(end)---------------------------------------

       //验证th2_2：
       //-----------------------------------(start)--------------------------------------
            double th2_2;
            double th2_2_z = acos(cos_th2_2);
            double th2_2_f = -acos(cos_th2_2);
            yz_R_1z = make_rotation(th1_1, lz);
            yz_T_1y = make_translation(0, d2, 0);
            yz_M_12 = geom(yz_R_1z, yz_T_1y);

            yz_R_2y = make_rotation(th2_2_z, -ly);
            yz_T_2x = make_translation(a2, 0, 0);
            yz_M_23 = geom(yz_R_2y, yz_T_2x);

            yz_p3 = geom(geom(geom(yz_M_12, yz_M_23), P1), cga::reverse(geom(yz_M_12, yz_M_23)));

            val_1 = abs((yz_p3.v.e1 + yz_p3.v.e2 + yz_p3.v.e3) - (P3_2.v.e1 + P3_2.v.e2 + P3_2.v.e3));

            if (val_1<1)
            {
                th2_2 = th2_2_z;
            }
            else
            {
                th2_2 = th2_2_f;
            }

       //------------------------------------(end)---------------------------------------

       //验证th2_3：
       //-----------------------------------(start)--------------------------------------

           double th2_3;
           double th2_3_z = acos(cos_th2_3);
           double th2_3_f = -acos(cos_th2_3);
           yz_R_1z = make_rotation(th1_2, lz);
           yz_T_1y = make_translation(0, d2, 0);
           yz_M_12 = geom(yz_R_1z, yz_T_1y);

           yz_R_2y = make_rotation(th2_3_z, -ly);
           yz_T_2x = make_translation(a2, 0, 0);
           yz_M_23 = geom(yz_R_2y, yz_T_2x);

           yz_p3 = geom(geom(geom(yz_M_12, yz_M_23), P1), reverse(geom(yz_M_12, yz_M_23)));

           val_1 = abs((yz_p3.v.e1 + yz_p3.v.e2 + yz_p3.v.e3) - (P3_3.v.e1 + P3_3.v.e2 + P3_3.v.e3));
           if (val_1<1)
           {
           th2_3 = th2_3_z;
           }
           else
           {
           th2_3 = th2_3_f;
           }

       //------------------------------------(end)---------------------------------------

       //验证th2_4：
       //-----------------------------------(start)--------------------------------------

           double th2_4;
           double th2_4_z = acos(cos_th2_4);
           double th2_4_f = -acos(cos_th2_4);
           yz_R_1z = make_rotation(th1_2, lz);
           yz_T_1y = make_translation(0, d2, 0);
           yz_M_12 = geom(yz_R_1z, yz_T_1y);

           yz_R_2y = make_rotation(th2_4_z, -ly);
           yz_T_2x = make_translation(a2, 0, 0);
           yz_M_23 = geom(yz_R_2y, yz_T_2x);
           yz_p3 = geom(geom(geom(yz_M_12, yz_M_23), P1), reverse(geom(yz_M_12, yz_M_23)));

           val_1 = abs((yz_p3.v.e1 + yz_p3.v.e2 + yz_p3.v.e3) - (P3_4.v.e1 + P3_4.v.e2 + P3_4.v.e3));
           if (val_1 < 1)
           {
               th2_4 = th2_4_z;
           }
           else
           {
               th2_4= th2_4_f;
           }

       //------------------------------------(end)---------------------------------------

    //------------------------------------(end)---------------------------------------

    //求theta_three
    //-----------------------------------(start)--------------------------------------
        Multivector L23_1 = anti(outer(outer(P2_1, P3_1), ei));
        Multivector L34_1 = anti(outer(outer(P3_1, P4_1), ei));
        double cos_th3_1 = scalarpart(-inner(L23_1, L34_1)) / (a2 * a3);

        Multivector L23_2 = anti(outer(outer(P2_1, P3_2), ei));
        Multivector L34_2 = anti(outer(outer(P3_2, P4_2), ei));
        double cos_th3_2 = scalarpart(-inner(L23_2, L34_2)) / (a2 * a3);

        Multivector L23_3 = anti(outer(outer(P2_2, P3_3), ei));
        Multivector L34_3 = anti(outer(outer(P3_3, P4_3), ei));
        double cos_th3_3 = scalarpart(-inner(L23_3, L34_3)) / (a2 * a3);

        Multivector L23_4 = anti(outer(outer(P2_2, P3_4), ei));
        Multivector L34_4 = anti(outer(outer(P3_4, P4_4), ei));
        double cos_th3_4 = scalarpart(-inner(L23_4, L34_4)) / (a2 * a3);


        //验证th3_1：
        //-----------------------------------(start)--------------------------------------

            double th3_1;
            double th3_1_z = acos(cos_th3_1);
            double th3_1_f = -acos(cos_th3_1);

            yz_R_1z = make_rotation(th1_1, lz);
            yz_T_1y = make_translation(0, d2, 0);
            yz_M_12 = geom(yz_R_1z, yz_T_1y);

            yz_R_2y = make_rotation(th2_1, -ly);
            yz_T_2x = make_translation(a2, 0, 0);
            yz_M_23 = geom(yz_R_2y, yz_T_2x);

            Multivector yz_R_3y = make_rotation(th3_1_z, -ly);
            Multivector yz_T_3x = make_translation(a3, 0, 0);
            Multivector yz_M_34 = geom(yz_R_3y, yz_T_3x);

            Multivector yz_p4 = geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), P1), reverse(geom(geom(yz_M_12, yz_M_23), yz_M_34)));

            double val_2 = abs((yz_p4.v.e1 + yz_p4.v.e2 + yz_p4.v.e3) - (P4_1.v.e1 + P4_1.v.e2 + P4_1.v.e3));
            if (val_2 < 1)
            {
                th3_1 = th3_1_z;
            }
            else
            {
                th3_1 = th3_1_f;
            }

        //-----------------------------------(end)--------------------------------------

        //验证th3_2：
        //-----------------------------------(start)--------------------------------------

          double th3_2;
          double th3_2_z = acos(cos_th3_2);
          double th3_2_f = -acos(cos_th3_2);

          yz_R_1z = make_rotation(th1_1, lz);
          yz_T_1y = make_translation(0, d2, 0);
          yz_M_12 = geom(yz_R_1z, yz_T_1y);

          yz_R_2y = make_rotation(th2_2, -ly);
          yz_T_2x = make_translation(a2, 0, 0);
          yz_M_23 = geom(yz_R_2y, yz_T_2x);

          yz_R_3y = make_rotation(th3_2_z, -ly);
          yz_T_3x = make_translation(a3, 0, 0);
          yz_M_34 = geom(yz_R_3y, yz_T_3x);

          yz_p4 = geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), P1), reverse(geom(geom(yz_M_12, yz_M_23), yz_M_34)));

          val_2 = abs((yz_p4.v.e1 + yz_p4.v.e2 + yz_p4.v.e3) - (P4_2.v.e1 + P4_2.v.e2 + P4_2.v.e3));
          if (val_2 < 1)
          {
              th3_2 = th3_2_z;
          }
          else
          {
              th3_2 = th3_2_f;
          }

        //-----------------------------------(end)--------------------------------------

        //验证th3_3：
        //-----------------------------------(start)--------------------------------------

             double th3_3;
             double th3_3_z = acos(cos_th3_3);
             double th3_3_f = -acos(cos_th3_3);

             yz_R_1z = make_rotation(th1_2, lz);
             yz_T_1y = make_translation(0, d2, 0);
             yz_M_12 = geom(yz_R_1z, yz_T_1y);

             yz_R_2y = make_rotation(th2_3, -ly);
             yz_T_2x = make_translation(a2, 0, 0);
             yz_M_23 = geom(yz_R_2y, yz_T_2x);

             yz_R_3y = make_rotation(th3_3_z, -ly);
             yz_T_3x = make_translation(a3, 0, 0);
             yz_M_34 = geom(yz_R_3y, yz_T_3x);

             yz_p4 = geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), P1), reverse(geom(geom(yz_M_12, yz_M_23), yz_M_34)));

             val_2 = abs((yz_p4.v.e1 + yz_p4.v.e2 + yz_p4.v.e3) - (P4_3.v.e1 + P4_3.v.e2 + P4_3.v.e3));
             if (val_2 < 1)
             {
                 th3_3 = th3_3_z;
             }
             else
             {
                 th3_3 = th3_3_f;
             }

        //-----------------------------------(end)--------------------------------------

        //验证th3_4：
        //-----------------------------------(start)--------------------------------------

             double th3_4;
             double th3_4_z = acos(cos_th3_4);
             double th3_4_f = -acos(cos_th3_4);

             yz_R_1z = make_rotation(th1_2, lz);
             yz_T_1y = make_translation(0, d2, 0);
             yz_M_12 = geom(yz_R_1z, yz_T_1y);

             yz_R_2y = make_rotation(th2_4, -ly);
             yz_T_2x = make_translation(a2, 0, 0);
             yz_M_23 = geom(yz_R_2y, yz_T_2x);

             yz_R_3y = make_rotation(th3_4_z, -ly);
             yz_T_3x = make_translation(a3, 0, 0);
             yz_M_34 = geom(yz_R_3y, yz_T_3x);

             yz_p4 = geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), P1), reverse(geom(geom(yz_M_12, yz_M_23), yz_M_34)));

             val_2 = abs((yz_p4.v.e1 + yz_p4.v.e2 + yz_p4.v.e3) - (P4_4.v.e1 + P4_4.v.e2 + P4_4.v.e3));
             if (val_2 < 1)
             {
                 th3_4 = th3_4_z;
             }
             else
             {
                 th3_4 = th3_4_f;
             }

        //-----------------------------------(end)--------------------------------------

    //------------------------------------(end)---------------------------------------

    //求theta_four
    //-----------------------------------(start)--------------------------------------
        Multivector Pi46t_1 = anti(outer(outer(outer(P4_1, P6), Pt), ei));
        Multivector Pi46t_2 = anti(outer(outer(outer(P4_2, P6), Pt), ei));
        Multivector Pi46t_3 = anti(outer(outer(outer(P4_3, P6), Pt), ei));
        Multivector Pi46t_4 = anti(outer(outer(outer(P4_4, P6), Pt), ei));

        double cos_th4_1 = scalarpart(inner(Pi46t_1, Pi1_1)) / (sqrt(scalarpart(inner(Pi46t_1, Pi46t_1))) * sqrt(scalarpart(inner(Pi1_1, Pi1_1))));
        double cos_th4_2 = scalarpart(inner(Pi46t_2, Pi1_1)) / (sqrt(scalarpart(inner(Pi46t_2, Pi46t_2))) * sqrt(scalarpart(inner(Pi1_1, Pi1_1))));
        double cos_th4_3 = scalarpart(inner(Pi46t_3, Pi1_2)) / (sqrt(scalarpart(inner(Pi46t_3, Pi46t_3))) * sqrt(scalarpart(inner(Pi1_2, Pi1_2))));
        double cos_th4_4 = scalarpart(inner(Pi46t_4, Pi1_2)) / (sqrt(scalarpart(inner(Pi46t_4, Pi46t_4))) * sqrt(scalarpart(inner(Pi1_2, Pi1_2))));

        double th4_1 = judge_th(cos_th4_1, region_th4_s, region_th4_e);
        double th4_2 = judge_th(cos_th4_2, region_th4_s, region_th4_e);
        double th4_3 = judge_th(cos_th4_3, region_th4_s, region_th4_e);
        double th4_4 = judge_th(cos_th4_4, region_th4_s, region_th4_e);

    //------------------------------------(end)---------------------------------------

    //求theta_five
    //-----------------------------------(start)--------------------------------------
        Multivector L45 = anti(outer(outer(P6, P4_1), ei));
        Multivector L5t = anti(outer(outer(P6, Pt), ei));
        double cos_th5_1 = scalarpart(inner(L45, L5t)) / (d4 * d6);

        L45 = anti(outer(outer(P6, P4_2), ei));
        L5t = anti(outer(outer(P6, Pt), ei));
        double cos_th5_2 = scalarpart(inner(L45, L5t)) / (d4 * d6);

        L45 = anti(outer(outer(P6, P4_3), ei));
        L5t = anti(outer(outer(P6, Pt), ei));
        double cos_th5_3 = scalarpart(inner(L45, L5t)) / (d4 * d6);

        L45 = anti(outer(outer(P4_4, P6), ei));
        L5t = anti(outer(outer(P6, Pt), ei));
        double cos_th5_4 = scalarpart(inner(L45,L5t)) / (d4 * d6);


//        //超新验证th5_1：
//     //-----------------------------------(start)--------------------------------------


//     double th5_1;
//     double zf5_1 = acos(cos_th5_1);
//     double th5_1z;
//     double th5_1f;
//     double th5_1_z;
//     double th5_1_f;
//     if (zf5_1 >= 0)
//     {
//         th5_1z = acos(cos_th5_1);
//         th5_1f = -acos(cos_th5_1);
//         th5_1_z = acos(cos_th5_1) * 180 / M_PI - 180;
//         th5_1_f = -acos(cos_th5_1) * 180 / M_PI + 180;
//     }
//     else
//     {
//         th5_1z = -acos(cos_th5_1);
//         th5_1f = acos(cos_th5_1);
//         th5_1_z = -acos(cos_th5_1) * 180 / M_PI - 180;
//         th5_1_f = acos(cos_th5_1) * 180 / M_PI + 180;
//     }

//     th5_1_z = th5_1_z * M_PI / 180;
//     th5_1_f = th5_1_f * M_PI / 180;

//     yz_R_1z = make_rotation(th1_1, lz);
//     yz_T_1y = make_translation(0, d2, 0);
//     yz_M_12 = geom(yz_R_1z, yz_T_1y);

//     yz_R_2y = make_rotation(th2_1, -ly);
//     yz_T_2x = make_translation(a2, 0, 0);
//     yz_M_23 = geom(yz_R_2y, yz_T_2x);

//     yz_R_3y = make_rotation(th3_1, -ly);
//     yz_T_3x = make_translation(a3, 0, 0);
//     yz_M_34 = geom(yz_R_3y, yz_T_3x);

//     Multivector yz_R_4z = make_rotation(th4_1, lz);
//     Multivector yz_T_3z = make_translation(0, 0, d4);
//     Multivector yz_M_45 = geom(yz_R_4z,yz_T_3z);

//     Multivector yz_R_5y = make_rotation(th5_1z, -ly);
//     Multivector yz_M_56 = yz_R_5y;

//     Multivector yz_R_6z = make_rotation(0, lz);
//     Multivector yz_T_6z = make_translation(0, 0, d6);
//     Multivector yz_M_67 = geom(yz_R_6z, yz_T_6z);

//     Multivector yz_pt = geom(geom(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67), P1), reverse(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67)));

//     double val_51 = abs((yz_pt.v.e1 + yz_pt.v.e2 + yz_pt.v.e3) - (Pt.v.e1 + Pt.v.e2 + Pt.v.e3));

//     if (val_51 < 0.1)
//     {
//         th5_1 = th5_1z * 180 / M_PI;
//     }
//     else
//     {
//         yz_R_5y = make_rotation(th5_1f, -ly);
//         yz_M_56 = yz_R_5y;
//         yz_pt = geom(geom(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67), P1), reverse(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67)));
//         double val_52 = abs((yz_pt.v.e1 + yz_pt.v.e2 + yz_pt.v.e3) - (Pt.v.e1 + Pt.v.e2 + Pt.v.e3));

//         if (val_52 < 0.1)
//         {
//             th5_1 = th5_1f * 180 / M_PI;
//         }
//         else
//         {
//             yz_R_5y = make_rotation(th5_1_z, -ly);
//             yz_M_56 = yz_R_5y;
//             yz_pt = geom(geom(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67), P1), reverse(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67)));
//             double val_53 = abs((yz_pt.v.e1 + yz_pt.v.e2 + yz_pt.v.e3) - (Pt.v.e1 + Pt.v.e2 + Pt.v.e3));

//             if (val_53 < 0.1)
//             {
//                 th5_1 = th5_1_z * 180 / M_PI;
//             }
//             else
//             {
//                 th5_1 = th5_1_f * 180 / M_PI;
//             }
//         }
//     }

//     //-----------------------------------(end)--------------------------------------

//     //超新验证th5_2：
//     //-----------------------------------(start)--------------------------------------

//     double th5_2;
//     double zf5_2 = acos(cos_th5_2);
//     double th5_2z;
//     double th5_2f;
//     double th5_2_z;
//     double th5_2_f;
//     if (zf5_2 >= 0)
//     {
//         th5_2z = acos(cos_th5_2);
//         th5_2f = -acos(cos_th5_2);
//         th5_2_z = acos(cos_th5_2) * 180 / M_PI - 180;
//         th5_2_f = -acos(cos_th5_2) * 180 / M_PI + 180;
//     }
//     else
//     {
//         th5_2z = -acos(cos_th5_2);
//         th5_2f = acos(cos_th5_2);
//         th5_2_z = -acos(cos_th5_2) * 180 / M_PI - 180;
//         th5_2_f = acos(cos_th5_2) * 180 / M_PI + 180;
//     }


//     th5_2_z = th5_2_z * M_PI / 180;
//     th5_2_f = th5_2_f * M_PI / 180;

//     yz_R_1z = make_rotation(th1_1, lz);
//     yz_T_1y = make_translation(0, d2, 0);
//     yz_M_12 = geom(yz_R_1z, yz_T_1y);

//     yz_R_2y = make_rotation(th2_2, -ly);
//     yz_T_2x = make_translation(a2, 0, 0);
//     yz_M_23 = geom(yz_R_2y, yz_T_2x);

//     yz_R_3y = make_rotation(th3_2, -ly);
//     yz_T_3x = make_translation(a3, 0, 0);
//     yz_M_34 = geom(yz_R_3y, yz_T_3x);


//     yz_R_4z = make_rotation(th4_2, lz);
//     yz_T_3z = make_translation(0, 0, d4);
//     yz_M_45 = geom(yz_R_4z, yz_T_3z);

//     yz_R_5y = make_rotation(th5_2z, -ly);
//     yz_M_56 = yz_R_5y;

//     yz_R_6z = make_rotation(0, lz);
//     yz_T_6z = make_translation(0, 0, d6);
//     yz_M_67 = geom(yz_R_6z, yz_T_6z);

//     yz_pt = geom(geom(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67), P1), reverse(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67)));

//     val_51 = abs((yz_pt.v.e1 + yz_pt.v.e2 + yz_pt.v.e3) - (Pt.v.e1 + Pt.v.e2 + Pt.v.e3));

//     if (val_51 < 0.1)
//     {
//         th5_2 = th5_2z * 180 / M_PI;
//     }
//     else
//     {
//         yz_R_5y = make_rotation(th5_2f, -ly);
//         yz_M_56 = yz_R_5y;
//         yz_pt = geom(geom(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67), P1), reverse(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67)));
//         double val_52 = abs((yz_pt.v.e1 + yz_pt.v.e2 + yz_pt.v.e3) - (Pt.v.e1 + Pt.v.e2 + Pt.v.e3));

//         if (val_52 < 0.1)
//         {
//             th5_2 = th5_2f * 180 / M_PI;
//         }
//         else
//         {
//             yz_R_5y = make_rotation(th5_2_z, -ly);
//             yz_M_56 = yz_R_5y;
//             yz_pt = geom(geom(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67), P1), reverse(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67)));
//             double val_53 = abs((yz_pt.v.e1 + yz_pt.v.e2 + yz_pt.v.e3) - (Pt.v.e1 + Pt.v.e2 + Pt.v.e3));

//             if (val_53 < 0.1)
//             {
//                 th5_2 = th5_2_z * 180 / M_PI;
//             }
//             else
//             {
//                 th5_2 = th5_2_f * 180 / M_PI;
//             }
//         }
//     }

//     //-----------------------------------(end)--------------------------------------

//     //超新验证th5_3：
//     //-----------------------------------(start)--------------------------------------

//     double th5_3;
//     double zf5_3 = acos(cos_th5_3);
//     double th5_3z;
//     double th5_3f;
//     double th5_3_z;
//     double th5_3_f;
//     if (zf5_3 >= 0)
//     {
//         th5_3z = acos(cos_th5_3);
//         th5_3f = -acos(cos_th5_3);
//         th5_3_z = acos(cos_th5_3) * 180 / M_PI - 180;
//         th5_3_f = -acos(cos_th5_3) * 180 / M_PI + 180;
//     }
//     else
//     {
//         th5_3z = -acos(cos_th5_3);
//         th5_3f = acos(cos_th5_3);
//         th5_3_z = -acos(cos_th5_3) * 180 / M_PI - 180;
//         th5_3_f = acos(cos_th5_3) * 180 / M_PI + 180;
//     }


//     th5_3_z = th5_3_z * M_PI / 180;
//     th5_3_f = th5_3_f * M_PI / 180;

//     yz_R_1z = make_rotation(th1_2, lz);
//     yz_T_1y = make_translation(0, d2, 0);
//     yz_M_12 = geom(yz_R_1z, yz_T_1y);

//     yz_R_2y = make_rotation(th2_3, -ly);
//     yz_T_2x = make_translation(a2, 0, 0);
//     yz_M_23 = geom(yz_R_2y, yz_T_2x);

//     yz_R_3y = make_rotation(th3_3, -ly);
//     yz_T_3x = make_translation(a3, 0, 0);
//     yz_M_34 = geom(yz_R_3y, yz_T_3x);

//     yz_R_4z = make_rotation(th4_3, lz);
//     yz_T_3z = make_translation(0, 0, d4);
//     yz_M_45 = geom(yz_R_4z, yz_T_3z);

//     yz_R_5y = make_rotation(th5_3z, -ly);
//     yz_M_56 = yz_R_5y;

//     yz_R_6z = make_rotation(0, lz);
//     yz_T_6z = make_translation(0, 0, d6);
//     yz_M_67 = geom(yz_R_6z, yz_T_6z);

//     yz_pt = geom(geom(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67), P1), reverse(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67)));

//     val_51 = abs((yz_pt.v.e1 + yz_pt.v.e2 + yz_pt.v.e3) - (Pt.v.e1 + Pt.v.e2 + Pt.v.e3));

//     if (val_51 < 0.1)
//     {
//         th5_3 = th5_3z * 180 / M_PI;
//     }
//     else
//     {
//         yz_R_5y = make_rotation(th5_3f, -ly);
//         yz_M_56 = yz_R_5y;
//         yz_pt = geom(geom(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67), P1), reverse(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67)));
//         double val_52 = abs((yz_pt.v.e1 + yz_pt.v.e2 + yz_pt.v.e3) - (Pt.v.e1 + Pt.v.e2 + Pt.v.e3));

//         if (val_52 < 0.1)
//         {
//             th5_3 = th5_3f * 180 / M_PI;
//         }
//         else
//         {
//             yz_R_5y = make_rotation(th5_3_z, -ly);
//             yz_M_56 = yz_R_5y;
//             yz_pt = geom(geom(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67), P1), reverse(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67)));
//             double val_53 = abs((yz_pt.v.e1 + yz_pt.v.e2 + yz_pt.v.e3) - (Pt.v.e1 + Pt.v.e2 + Pt.v.e3));

//             if (val_53 < 0.1)
//             {
//                 th5_3 = th5_3_z * 180 / M_PI;
//             }
//             else
//             {
//                 th5_3 = th5_3_f * 180 / M_PI;
//             }
//         }
//     }

//     //-----------------------------------(end)--------------------------------------

//     //超新验证th5_4：
//     //-----------------------------------(start)--------------------------------------


//     double th5_4;
//     double zf5_4 = acos(cos_th5_4);
//     double th5_4z;
//     double th5_4f;
//     double th5_4_z;
//     double th5_4_f;
//     if (zf5_4 >= 0)
//     {
//         th5_4z = acos(cos_th5_4);
//         th5_4f = -acos(cos_th5_4);
//         th5_4_z = acos(cos_th5_4) * 180 / M_PI - 180;
//         th5_4_f = -acos(cos_th5_4) * 180 / M_PI + 180;
//     }
//     else
//     {
//         th5_4z = -acos(cos_th5_4);
//         th5_4f = acos(cos_th5_4);
//         th5_4_z = -acos(cos_th5_4) * 180 / M_PI - 180;
//         th5_4_f = acos(cos_th5_4) * 180 / M_PI + 180;
//     }



//     th5_4_z = th5_4_z * M_PI / 180;
//     th5_4_f = th5_4_f * M_PI / 180;

//     yz_R_1z = make_rotation(th1_2, lz);
//     yz_T_1y = make_translation(0, d2, 0);
//     yz_M_12 = geom(yz_R_1z, yz_T_1y);

//     yz_R_2y = make_rotation(th2_4, -ly);
//     yz_T_2x = make_translation(a2, 0, 0);
//     yz_M_23 = geom(yz_R_2y, yz_T_2x);

//     yz_R_3y = make_rotation(th3_4, -ly);
//     yz_T_3x = make_translation(a3, 0, 0);
//     yz_M_34 = geom(yz_R_3y, yz_T_3x);


//     yz_R_4z = make_rotation(th4_4, lz);
//     yz_T_3z = make_translation(0, 0, d4);
//     yz_M_45 = geom(yz_R_4z, yz_T_3z);
//     yz_R_5y = make_rotation(th5_4z, -ly);
//     yz_M_56 = yz_R_5y;
//     yz_R_6z = make_rotation(0, lz);
//     yz_T_6z = make_translation(0, 0, d6);
//     yz_M_67 = geom(yz_R_6z, yz_T_6z);
//     yz_pt = geom(geom(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67), P1), reverse(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67)));

//     val_51 = abs((yz_pt.v.e1 + yz_pt.v.e2 + yz_pt.v.e3) - (Pt.v.e1 + Pt.v.e2 + Pt.v.e3));
//     if (val_51 < 0.1)
//     {
//         th5_4 = th5_4z * 180 / M_PI;
//     }
//     else
//     {
//         yz_R_5y = make_rotation(th5_4f, -ly);
//         yz_M_56 = yz_R_5y;
//         yz_pt = geom(geom(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67), P1), reverse(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67)));

//         double val_52 = abs((yz_pt.v.e1 + yz_pt.v.e2 + yz_pt.v.e3) - (Pt.v.e1 + Pt.v.e2 + Pt.v.e3));

//         if (val_52 < 0.1)
//         {
//             th5_4 = th5_4f * 180 / M_PI;
//         }
//         else
//         {
//             yz_R_5y = make_rotation(th5_4_z, -ly);
//             yz_M_56 = yz_R_5y;

//             yz_pt = geom(geom(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67), P1), reverse(geom(geom(geom(geom(geom(yz_M_12, yz_M_23), yz_M_34), yz_M_45), yz_M_56), yz_M_67)));
//             double val_53 = abs((yz_pt.v.e1 + yz_pt.v.e2 + yz_pt.v.e3) - (Pt.v.e1 + Pt.v.e2 + Pt.v.e3));

//             if (val_53 < 0.1)
//             {
//                 th5_4 = th5_4_z * 180 / M_PI;
//             }
//             else
//             {
//                 th5_4 = th5_4_f * 180 / M_PI;
//             }
//         }
//     }

//     //-----------------------------------(end)--------------------------------------

        double th5_1 = judge_th(cos_th5_1, region_th5_s, region_th5_e);
        double th5_2 = judge_th(cos_th5_2, region_th5_s, region_th5_e);
        double th5_3 = judge_th(cos_th5_3, region_th5_s, region_th5_e);
        double th5_4 = judge_th(cos_th5_4, region_th5_s, region_th5_e);

    //------------------------------------(end)---------------------------------------

    //求theta_six
    //-----------------------------------(start)--------------------------------------
        double cos_th6_1 = scalarpart(inner(Pi46t_1, Pit)) / (sqrt(scalarpart(inner(Pi46t_1, Pi46t_1))) * sqrt(scalarpart(inner(Pit, Pit))));
        double cos_th6_2 = scalarpart(inner(Pi46t_2, Pit)) / (sqrt(scalarpart(inner(Pi46t_2, Pi46t_2))) * sqrt(scalarpart(inner(Pit, Pit))));
        double cos_th6_3 = scalarpart(inner(Pi46t_3, Pit)) / (sqrt(scalarpart(inner(Pi46t_3, Pi46t_3))) * sqrt(scalarpart(inner(Pit, Pit))));
        double cos_th6_4 = scalarpart(inner(Pi46t_4, Pit)) / (sqrt(scalarpart(inner(Pi46t_4, Pi46t_4))) * sqrt(scalarpart(inner(Pit, Pit))));

        double th6_1 = judge_th(cos_th6_1, region_th6_s, region_th6_e);
        double th6_2 = judge_th(cos_th6_2, region_th6_s, region_th6_e);
        double th6_3 = judge_th(cos_th6_3, region_th6_s, region_th6_e);
        double th6_4 = judge_th(cos_th6_4, region_th6_s, region_th6_e);
    //------------------------------------(end)---------------------------------------

      //寻找最优逆解：
      //将计算出的4组，按列存入4X6数组，列号为逆解编号

      double tangel[NUM_SOLUTIONS][NUM_JOINTS];
      //第1组解
      tangel[0][0] = th1_1 * 180 / M_PI; tangel[0][1] = th2_1* 180 / M_PI;; tangel[0][2] = th3_1* 180 / M_PI;;tangel[0][3] = th4_1; tangel[0][4] = th5_1; tangel[0][5] = th6_1;
      //第2组解
      tangel[1][0] = th1_1 * 180 / M_PI; tangel[1][1] = th2_2* 180 / M_PI;; tangel[1][2] = th3_2* 180 / M_PI;;tangel[1][3] = th4_2; tangel[1][4] = th5_2; tangel[1][5] = th6_2;
      //第3组解
      tangel[2][0] = th1_2 * 180 / M_PI; tangel[2][1] = th2_3* 180 / M_PI;; tangel[2][2] = th3_3* 180 / M_PI;;tangel[2][3] = th4_3; tangel[2][4] = th5_3; tangel[2][5] = th6_3;
      //第4组解
      tangel[3][0] = th1_2 * 180 / M_PI; tangel[3][1] = th2_4* 180 / M_PI;; tangel[3][2] = th3_4* 180 / M_PI;;tangel[3][3] = th4_4; tangel[3][4] = th5_4; tangel[3][5] = th6_4;


      QVector<PathTheta> linshi_theta_vector;
      for (int i = 0; i <4; i++)
      {
          PathTheta PT;
          PT.th1=tangel[i][0];
          PT.th2=tangel[i][1];
          PT.th3=tangel[i][2];
          PT.th4=tangel[i][3];
          PT.th5=tangel[i][4];
          PT.th6=tangel[i][5];
          linshi_theta_vector.append(PT);//将产生的4组解装入linshi_theta_vector容器中
      }

     return linshi_theta_vector;

}

void RobotGLWidget::setTh1(double _th1)
{
    if ( _th1< JOINT_MIN[0])
        th1= JOINT_MIN[0];
    else if(_th1 > JOINT_MAX[0])
        th1 = JOINT_MAX[0];
    else
        th1 = _th1;
}

void RobotGLWidget::setTh2(double _th2)
{

    if (_th2<JOINT_MIN[1])
        th2= -JOINT_MIN[1];
    else if(_th2 > JOINT_MAX[1])
        th2 = -JOINT_MAX[1];
    else
        th2 =-_th2;
}

void RobotGLWidget::setTh3(double _th3)
{
    if ( _th3< JOINT_MIN[2])
        th3= -JOINT_MIN[2];
    else if(_th3 >JOINT_MAX[2] )
        th3 =-JOINT_MAX[2];
    else
        th3 =-_th3;
}

void RobotGLWidget::setTh4(double _th4)
{
    if ( _th4< JOINT_MIN[3])
        th4=  JOINT_MIN[3];
    else if(_th4 >JOINT_MAX[3] )
        th4 =JOINT_MAX[3];
    else
        th4 = _th4;
}

void RobotGLWidget::setTh5(double _th5)
{
    if ( _th5<JOINT_MIN[4])
        th5= -JOINT_MIN[4];
    else if(_th5 >JOINT_MAX[4] )
        th5 =-JOINT_MAX[4];
    else
        th5 =-_th5;
}

void RobotGLWidget::setTh6(double _th6)
{
    if ( _th6<JOINT_MIN[5])
        th6= JOINT_MIN[5];
    else if(_th6 >JOINT_MAX[5] )
        th6 =JOINT_MAX[5];
    else
        th6 = _th6;
}

void RobotGLWidget::setPoint()//设置标记点的函数
{ 
    //理论上应该直接使用选中的点，将选中的点的三维坐标放入point_stack中，
    //本例中，使用正运动学计算出选中的点的三维坐标，并将它们放入point_stack中。

    //使用正运动学计算出挪动模型时指定的点的三维坐标，将三维坐标储存在point_stack
    double b[6] = { th1, th2, th3, th4, th5,th6};

    forward(b);//使用正运动学计算fk_Pt、fk_n和fk_Pit的值;

    MultiPoint m_1;//fk_Pt
    m_1.x=fk_Pt.v.e1;
    m_1.y=fk_Pt.v.e2;
    m_1.z=fk_Pt.v.e3;
    m_1.m=fk_Pt.v.e4;
    m_1.n=fk_Pt.v.e5;
    point_stack_Pt.push(m_1);

    MultiPoint m_2;//fk_Pit
    m_2.x=fk_Pit.v.e1;
    m_2.y=fk_Pit.v.e2;
    m_2.z=fk_Pit.v.e3;
    m_2.m=fk_Pit.v.e4;
    m_2.n=fk_Pit.v.e5;
    point_stack_Pit.push(m_2);

    PathPoint p_1;//fk_n
    p_1.x=fk_n.v.e1;
    p_1.y=fk_n.v.e2;
    p_1.z=fk_n.v.e3;
    point_stack_n.push(p_1);

    PathPoint p_2;//fk_n_hz
    p_2.x=fk_n.v.e1*30+m_1.x;
    p_2.y=fk_n.v.e2*30+m_1.y;
    p_2.z=fk_n.v.e3*30+m_1.z;
    point_stack_n_hz.push(p_2);

    //主动标记的点的数量num_marked
    num_marked++;

    qDebug()<<"=======================================";
    qDebug()<<"第"<<num_marked<<"个标记点";
    qDebug()<<"n:"<<" p_1.x="<<p_1.x<<" p_1.y="<<p_1.y<<" p_1.z="<<p_1.z;
//    qDebug()<<"n_hz:"<<" p_2.x="<<p_2.x<<" p_2.y="<<p_2.y<<" p_2.z="<<p_2.z;
    qDebug()<<"Pt:"<<" m_1.x="<<m_1.x<<" m_1.y="<<m_1.y<<" m_1.z="<<m_1.z<<" m_1.m="<<m_1.m<<" m_1.n="<<m_1.n;
    qDebug()<<"Pit:"<<" m_2.x="<<m_2.x<<" m_2.y="<<m_2.y<<" m_2.z="<<m_2.z<<" m_2.m="<<m_2.m<<" m_2.n="<<m_2.n;
    qDebug()<<"th1="<<th1<<" th2="<<-th2<<" th3="<<-th3<<" th4="<<th4<<" th5="<<-th5<<" th6="<<th6;

    if(num_marked==1)//将起始点对应的theta值传递给start_theta数组，用以筛选最优逆运动学解
    {
        start_theta[0]=th1;
        start_theta[1]=-th2;
        start_theta[2]=-th3;
        start_theta[3]=th4;
        start_theta[4]=-th5;
        start_theta[5]=th6;
    }
}

void RobotGLWidget::delePoint()//删除标记点的函数
{
   point_stack_Pt.pop();
}

//计算二维圆弧
void RobotGLWidget::SetArcRadius(double dStart[2], double dMid[2], double dEnd[2])
{
    double two_CenterPos[2];
    two_CenterPos[0] =
        (
            -dMid[0] * dMid[0] * dStart[1] + dEnd[0] * dEnd[0] * dStart[1] + dStart[0] * dStart[0] * dMid[1] - dEnd[0] * dEnd[0] * dMid[1] +
            dStart[1] * dStart[1] * dMid[1] - dStart[1] * dMid[1] * dMid[1] - dStart[0] * dStart[0] * dEnd[1] + dMid[0] * dMid[0] * dEnd[1] -
            dStart[1] * dStart[1] * dEnd[1] + dMid[1] * dMid[1] * dEnd[1] + dStart[1] * dEnd[1] * dEnd[1] - dMid[1] * dEnd[1] * dEnd[1])
        / (2 * (-dMid[0] * dStart[1] + dEnd[0] * dStart[1] + dStart[0] * dMid[1] - dEnd[0] * dMid[1] - dStart[0] * dEnd[1] + dMid[0] * dEnd[1])
            );

    two_CenterPos[1] =
        -(-dStart[0] * dStart[0] * dMid[0] + dStart[0] * dMid[0] * dMid[0] + dStart[0] * dStart[0] * dEnd[0] - dMid[0] * dMid[0] * dEnd[0] -
            dStart[0] * dEnd[0] * dEnd[0] + dMid[0] * dEnd[0] * dEnd[0] - dMid[0] * dStart[1] * dStart[1] + dEnd[0] * dStart[1] * dStart[1] +
            dStart[0] * dMid[1] * dMid[1] - dEnd[0] * dMid[1] * dMid[1] - dStart[0] * dEnd[1] * dEnd[1] + dMid[0] * dEnd[1] * dEnd[1])
        / (2 * (dMid[0] * dStart[1] - dEnd[0] * dStart[1] - dStart[0] * dMid[1] + dEnd[0] * dMid[1] + dStart[0] * dEnd[1] - dMid[0] * dEnd[1]));

    //圆的半径
    double two_dRadius = sqrt((dStart[0] - two_CenterPos[0]) * (dStart[0] - two_CenterPos[0]) + (dStart[1] - two_CenterPos[1]) * (dStart[1] - two_CenterPos[1]));

    //起始角度
    double two_dStartPhi = atan2((dStart[1] - two_CenterPos[1]), (dStart[0] - two_CenterPos[0]));

    two_dStartPhi=two_dStartPhi*180/PI;//弧度转换角度

    //终止角度
    double two_dEndPhi = atan2(dEnd[1] - two_CenterPos[1], dEnd[0] - two_CenterPos[0]);
    two_dEndPhi=two_dEndPhi*180/PI;

    //起始点终止点相对于圆心的夹角
    double jia_theta = abs(two_dEndPhi - two_dStartPhi);

    //给定插值步数//num_steps =9，求每步的角位移
    double d_jia_theta = jia_theta / (num_steps+1);

//    qDebug()<<"原点two_CenterPos坐标"<<"x:two_CenterPos[0]="<<two_CenterPos[0]<<" "<<"y:two_CenterPos[1]="<<two_CenterPos[1]<<endl;
//    qDebug()<<"起始角度="<<two_dStartPhi;
//    qDebug()<<"终止角度="<<two_dEndPhi;
//    qDebug()<<"半径长度="<<two_dRadius;
//    qDebug()<<"夹角jia_theta ="<<jia_theta;
//    qDebug()<<"角度：d_jia_theta="<<d_jia_theta;

    //将角度转弧度
    d_jia_theta=d_jia_theta*PI/180;
    two_dStartPhi=two_dStartPhi*PI/180;
    two_dEndPhi=two_dEndPhi*PI/180;

    for(int i=0;i<=num_steps+1;i++)
    {
        CZ_Point CZ_P;
        if(two_CenterPos[0]*two_CenterPos[1]<0)//原点x,y异号
        {
            CZ_P.x=two_CenterPos[0]+two_dRadius*(cos(PI-two_dStartPhi+i*d_jia_theta));
            CZ_P.y=two_CenterPos[1]+two_dRadius*(sin(PI-two_dStartPhi+i*d_jia_theta));
        }
        else//原点x,y同号
        {
            CZ_P.x=two_CenterPos[0]+two_dRadius*(cos(two_dStartPhi+i*d_jia_theta));
            CZ_P.y=two_CenterPos[1]+two_dRadius*(sin(two_dStartPhi+i*d_jia_theta));
        }

        chazhi_zb_2d.append(CZ_P);
//        qDebug()<<"储存到chazhi_zb_2d中的坐标";
//        qDebug()<<"i="<<i<<" "
//               <<"d_jia_theta="<<i*d_jia_theta*180/PI
//               <<"cos(i*d_jia_theta)="<<cos(i*d_jia_theta)
//               <<" "<<"CZ_P.x="<<CZ_P.x<<"CZ_P.y="<<CZ_P.y;
    }

}

//!=============================================================================================================
//设置变换矩阵,将二维变换成三维
void RobotGLWidget::SetChangeMatrix_n(double dStart[3], double dMid[3], double dEnd[3])
{
    //xx[3]表示新坐标轴x轴的向量
    //yy[3]表示新坐标轴y轴的向量
    //zz[3]表示新坐标轴z轴的向量

    double xx[3], yy[3], zz[3], xl_ab[3], normx, normy, normz;

    xx[0] = dEnd[0] - dStart[0];
    xx[1] = dEnd[1] - dStart[1];
    xx[2] = dEnd[2] - dStart[2];

    xl_ab[0] = dMid[0] - dStart[0];
    xl_ab[1] = dMid[1] - dStart[1];
    xl_ab[2] = dMid[2] - dStart[2];

    //xx和xl_ab做叉乘
    zz[0]=xx[1]*xl_ab[2]-xx[2]*xl_ab[1];
    zz[1]=xx[2]*xl_ab[0]-xx[0]*xl_ab[2];
    zz[2]=xx[0]*xl_ab[1]-xx[1]*xl_ab[0];

    //zz和xx做叉乘
    yy[0]=zz[1]*xx[2]-zz[2]*xx[1];
    yy[1]=zz[2]*xx[0]-zz[0]*xx[2];
    yy[2]=zz[0]*xx[1]-zz[1]*xx[0];

    normx = sqrt(xx[0] * xx[0] + xx[1] * xx[1] + xx[2] * xx[2]);
    normy = sqrt(yy[0] * yy[0] + yy[1] * yy[1] + yy[2] * yy[2]);
    normz = sqrt(zz[0] * zz[0] + zz[1] * zz[1] + zz[2] * zz[2]);

    //向矩阵第0行第0列写入数值xx[0]/normx
    double s00 = xx[0] / normx; double s01 = yy[0] / normy; double s02 = zz[0] / normz; double s03 = dStart[0];
    double s10 = xx[1] / normx; double s11 = yy[1] / normy; double s12 = zz[1] / normz; double s13 = dStart[1];
    double s20 = xx[2] / normx; double s21 = yy[2] / normy; double s22 = zz[2] / normz; double s23 = dStart[2];

    QMatrix4x4 M10,M10_inver;
    // 设置矩阵的元素
    M10.setRow(0, QVector4D(s00, s01, s02, s03));
    M10.setRow(1, QVector4D(s10, s11, s12, s13));
    M10.setRow(2, QVector4D(s20, s21, s22, s23));
    M10.setRow(3, QVector4D(0.0, 0.0, 0.0, 1.0));

    M10_inver = M10.inverted();//逆矩阵

    // 将dStart[3], dMid[3], dEnd[3]的double数组转换为QVector<double>
    QVector4D dstartVector(dStart[0], dStart[1], dStart[2], 1.0);
    QVector4D dMidVector(dMid[0], dMid[1], dMid[2], 1.0);
    QVector4D dEndVector(dEnd[0], dEnd[1], dEnd[2], 1.0);

    //将dStart[3], dMid[3], dEnd[3]三个点的坐标从世界坐标系通过乘以逆矩阵转换为新坐标系
    QVector4D MNew_Start = M10_inver * dstartVector;
    QVector4D MNew_Mid = M10_inver * dMidVector;
    QVector4D MNew_End = M10_inver * dEndVector;

    //定义在新坐标系下与dStart[3], double dMid[3], double dEnd[3]相对应的点
    double newPoint_start[2], newPoint_mid[2], newPoint_end[2];
    newPoint_start[0] = MNew_Start.x();
    newPoint_start[1] = MNew_Start.y();

    newPoint_mid[0] = MNew_Mid.x();
    newPoint_mid[1] = MNew_Mid.y();

    newPoint_end[0] = MNew_End.x();
    newPoint_end[1] = MNew_End.y();

    qDebug()<<endl<<"进入SetArcRadius函数"<<endl;
    chazhi_zb_2d.clear();
    qDebug()<<"以下是在二维坐标系下的值：";
    qDebug()<<"进入SetArcRadius函数前的chazhi_zb_2d.size()="<<chazhi_zb_2d.size()<<endl;

    //按照正常的平面插补算法进行计算
    SetArcRadius(newPoint_start, newPoint_mid, newPoint_end);

    qDebug()<<"退出SetArcRadius函数后的chazhi_zb_2d.size()="<<chazhi_zb_2d.size()<<endl;

    //将计算出的平面插补的数据乘以M10以形成在标准坐标系下的三维点

    for (int i= chazhi_zb_2d.size()-1;i>=0; i--)
    {
        CZ_Point point_2d = chazhi_zb_2d[i];//倒着取出chazhi_zb_2d中的二维点!!!!
        QVector4D midmatr_one(point_2d.x, point_2d.y, 0, 1.0);
        QVector4D midmatr_two=M10*midmatr_one;//平面插补的数据乘以M10

        //形成在标准坐标系下的三维点
        PathPoint point_3d;
        point_3d.x=midmatr_two.x();
        point_3d.y=midmatr_two.y();
        point_3d.z=midmatr_two.z();
        chazhi_n_yuanhu.append(point_3d);
    }

    qDebug()<<"======================================";
    qDebug()<<"chazhi_n_yuanhu.size()="<<chazhi_n_yuanhu.size();
    qDebug()<<"打印chazhi_n_yuanhu中的数据";
    for (auto it = chazhi_n_yuanhu.begin(); it != chazhi_n_yuanhu.end(); ++it)
    {
        PathPoint point = *it;
        qDebug() << "x:" << point.x << " y:" << point.y << " z:" << point.z;
    }
}

void RobotGLWidget::SetChangeMatrix_pit(double dStart[3], double dMid[3], double dEnd[3])
{
    //xx[3]表示新坐标轴x轴的向量
    //yy[3]表示新坐标轴y轴的向量
    //zz[3]表示新坐标轴z轴的向量

    double xx[3], yy[3], zz[3], xl_ab[3], normx, normy, normz;

    xx[0] = dEnd[0] - dStart[0];
    xx[1] = dEnd[1] - dStart[1];
    xx[2] = dEnd[2] - dStart[2];

    xl_ab[0] = dMid[0] - dStart[0];
    xl_ab[1] = dMid[1] - dStart[1];
    xl_ab[2] = dMid[2] - dStart[2];

    //xx和xl_ab做叉乘
    zz[0]=xx[1]*xl_ab[2]-xx[2]*xl_ab[1];
    zz[1]=xx[2]*xl_ab[0]-xx[0]*xl_ab[2];
    zz[2]=xx[0]*xl_ab[1]-xx[1]*xl_ab[0];

    //zz和xx做叉乘
    yy[0]=zz[1]*xx[2]-zz[2]*xx[1];
    yy[1]=zz[2]*xx[0]-zz[0]*xx[2];
    yy[2]=zz[0]*xx[1]-zz[1]*xx[0];

    normx = sqrt(xx[0] * xx[0] + xx[1] * xx[1] + xx[2] * xx[2]);
    normy = sqrt(yy[0] * yy[0] + yy[1] * yy[1] + yy[2] * yy[2]);
    normz = sqrt(zz[0] * zz[0] + zz[1] * zz[1] + zz[2] * zz[2]);

    //向矩阵第0行第0列写入数值xx[0]/normx
    double s00 = xx[0] / normx; double s01 = yy[0] / normy; double s02 = zz[0] / normz; double s03 = dStart[0];
    double s10 = xx[1] / normx; double s11 = yy[1] / normy; double s12 = zz[1] / normz; double s13 = dStart[1];
    double s20 = xx[2] / normx; double s21 = yy[2] / normy; double s22 = zz[2] / normz; double s23 = dStart[2];

    QMatrix4x4 M10,M10_inver;
    // 设置矩阵的元素
    M10.setRow(0, QVector4D(s00, s01, s02, s03));
    M10.setRow(1, QVector4D(s10, s11, s12, s13));
    M10.setRow(2, QVector4D(s20, s21, s22, s23));
    M10.setRow(3, QVector4D(0.0, 0.0, 0.0, 1.0));

    M10_inver = M10.inverted();//逆矩阵

    // 将dStart[3], dMid[3], dEnd[3]的double数组转换为QVector<double>
    QVector4D dstartVector(dStart[0], dStart[1], dStart[2], 1.0);
    QVector4D dMidVector(dMid[0], dMid[1], dMid[2], 1.0);
    QVector4D dEndVector(dEnd[0], dEnd[1], dEnd[2], 1.0);

    //将dStart[3], dMid[3], dEnd[3]三个点的坐标从世界坐标系通过乘以逆矩阵转换为新坐标系
    QVector4D MNew_Start = M10_inver * dstartVector;
    QVector4D MNew_Mid = M10_inver * dMidVector;
    QVector4D MNew_End = M10_inver * dEndVector;

    //定义在新坐标系下与dStart[3], double dMid[3], double dEnd[3]相对应的点
    double newPoint_start[2], newPoint_mid[2], newPoint_end[2];
    newPoint_start[0] = MNew_Start.x();
    newPoint_start[1] = MNew_Start.y();

    newPoint_mid[0] = MNew_Mid.x();
    newPoint_mid[1] = MNew_Mid.y();

    newPoint_end[0] = MNew_End.x();
    newPoint_end[1] = MNew_End.y();

    qDebug()<<endl<<"进入SetArcRadius函数"<<endl;
    chazhi_zb_2d.clear();
    qDebug()<<"以下是在二维坐标系下的值：";
    qDebug()<<"进入SetArcRadius函数前的chazhi_zb_2d.size()="<<chazhi_zb_2d.size()<<endl;

    //按照正常的平面插补算法进行计算
    SetArcRadius(newPoint_start, newPoint_mid, newPoint_end);

    qDebug()<<"退出SetArcRadius函数后的chazhi_zb_2d.size()="<<chazhi_zb_2d.size()<<endl;

    //将计算出的平面插补的数据乘以M10以形成在标准坐标系下的三维点

    for (int i= chazhi_zb_2d.size()-1;i>=0; i--)
    {
        CZ_Point point_2d = chazhi_zb_2d[i];//倒着取出chazhi_zb_2d中的二维点!!!!
        QVector4D midmatr_one(point_2d.x, point_2d.y, 0, 1.0);
        QVector4D midmatr_two=M10*midmatr_one;//平面插补的数据乘以M10

        Multivector midmatr_three=conformal(midmatr_two.x(), midmatr_two.y(), midmatr_two.z());

        //形成在标准坐标系下的三维点
        MultiPoint point_5d;
        point_5d.x=midmatr_three.v.e1;
        point_5d.y=midmatr_three.v.e2;
        point_5d.z=midmatr_three.v.e3;
        point_5d.m=midmatr_three.v.e4;
        point_5d.n=midmatr_three.v.e5;
        chazhi_pit_yuanhu.append(point_5d);
    }

    qDebug()<<"======================================";
    qDebug()<<"chazhi_pit_yuanhu.size()="<<chazhi_pit_yuanhu.size();
    qDebug()<<"打印chazhi_pit_yuanhu中的数据";
    for (auto it = chazhi_pit_yuanhu.begin(); it != chazhi_pit_yuanhu.end(); ++it)
    {
        MultiPoint point = *it;
        qDebug() << "x:" << point.x << " y:" << point.y << " z:" << point.z<< " m:" << point.m<< " n:" << point.n;
    }
}

void RobotGLWidget::SetChangeMatrix_pt(double dStart[3], double dMid[3], double dEnd[3])
{
    //xx[3]表示新坐标轴x轴的向量
    //yy[3]表示新坐标轴y轴的向量
    //zz[3]表示新坐标轴z轴的向量

    double xx[3], yy[3], zz[3], xl_ab[3], normx, normy, normz;

    xx[0] = dEnd[0] - dStart[0];
    xx[1] = dEnd[1] - dStart[1];
    xx[2] = dEnd[2] - dStart[2];

    xl_ab[0] = dMid[0] - dStart[0];
    xl_ab[1] = dMid[1] - dStart[1];
    xl_ab[2] = dMid[2] - dStart[2];

    //xx和xl_ab做叉乘
    zz[0]=xx[1]*xl_ab[2]-xx[2]*xl_ab[1];
    zz[1]=xx[2]*xl_ab[0]-xx[0]*xl_ab[2];
    zz[2]=xx[0]*xl_ab[1]-xx[1]*xl_ab[0];

    //zz和xx做叉乘
    yy[0]=zz[1]*xx[2]-zz[2]*xx[1];
    yy[1]=zz[2]*xx[0]-zz[0]*xx[2];
    yy[2]=zz[0]*xx[1]-zz[1]*xx[0];

    normx = sqrt(xx[0] * xx[0] + xx[1] * xx[1] + xx[2] * xx[2]);
    normy = sqrt(yy[0] * yy[0] + yy[1] * yy[1] + yy[2] * yy[2]);
    normz = sqrt(zz[0] * zz[0] + zz[1] * zz[1] + zz[2] * zz[2]);

    //向矩阵第0行第0列写入数值xx[0]/normx
    double s00 = xx[0] / normx; double s01 = yy[0] / normy; double s02 = zz[0] / normz; double s03 = dStart[0];
    double s10 = xx[1] / normx; double s11 = yy[1] / normy; double s12 = zz[1] / normz; double s13 = dStart[1];
    double s20 = xx[2] / normx; double s21 = yy[2] / normy; double s22 = zz[2] / normz; double s23 = dStart[2];

    QMatrix4x4 M10,M10_inver;
    // 设置矩阵的元素
    M10.setRow(0, QVector4D(s00, s01, s02, s03));
    M10.setRow(1, QVector4D(s10, s11, s12, s13));
    M10.setRow(2, QVector4D(s20, s21, s22, s23));
    M10.setRow(3, QVector4D(0.0, 0.0, 0.0, 1.0));

    M10_inver = M10.inverted();//逆矩阵

    // 将dStart[3], dMid[3], dEnd[3]的double数组转换为QVector<double>
    QVector4D dstartVector(dStart[0], dStart[1], dStart[2], 1.0);
    QVector4D dMidVector(dMid[0], dMid[1], dMid[2], 1.0);
    QVector4D dEndVector(dEnd[0], dEnd[1], dEnd[2], 1.0);

    //将dStart[3], dMid[3], dEnd[3]三个点的坐标从世界坐标系通过乘以逆矩阵转换为新坐标系
    QVector4D MNew_Start = M10_inver * dstartVector;
    QVector4D MNew_Mid = M10_inver * dMidVector;
    QVector4D MNew_End = M10_inver * dEndVector;

    //定义在新坐标系下与dStart[3], double dMid[3], double dEnd[3]相对应的点
    double newPoint_start[2], newPoint_mid[2], newPoint_end[2];
    newPoint_start[0] = MNew_Start.x();
    newPoint_start[1] = MNew_Start.y();

    newPoint_mid[0] = MNew_Mid.x();
    newPoint_mid[1] = MNew_Mid.y();

    newPoint_end[0] = MNew_End.x();
    newPoint_end[1] = MNew_End.y();

    qDebug()<<endl<<"进入SetArcRadius函数"<<endl;
    chazhi_zb_2d.clear();
    qDebug()<<"以下是在二维坐标系下的值：";
    qDebug()<<"进入SetArcRadius函数前的chazhi_zb_2d.size()="<<chazhi_zb_2d.size()<<endl;

    //按照正常的平面插补算法进行计算
    SetArcRadius(newPoint_start, newPoint_mid, newPoint_end);

    qDebug()<<"退出SetArcRadius函数后的chazhi_zb_2d.size()="<<chazhi_zb_2d.size()<<endl;

    //将计算出的平面插补的数据乘以M10以形成在标准坐标系下的三维点

    for (int i= chazhi_zb_2d.size()-1;i>=0; i--)
    {
        CZ_Point point_2d = chazhi_zb_2d[i];//倒着取出chazhi_zb_2d中的二维点!!!!
        QVector4D midmatr_one(point_2d.x, point_2d.y, 0, 1.0);
        QVector4D midmatr_two=M10*midmatr_one;//平面插补的数据乘以M10

        Multivector midmatr_three=conformal(midmatr_two.x(), midmatr_two.y(), midmatr_two.z());

        //形成在标准坐标系下的三维点
        MultiPoint point_5d;
        point_5d.x=midmatr_three.v.e1;
        point_5d.y=midmatr_three.v.e2;
        point_5d.z=midmatr_three.v.e3;
        point_5d.m=midmatr_three.v.e4;
        point_5d.n=midmatr_three.v.e5;
        chazhi_pt_yuanhu.append(point_5d);
    }

    qDebug()<<"======================================";
    qDebug()<<"chazhi_pt_yuanhu.size()="<<chazhi_pt_yuanhu.size();
    qDebug()<<"打印chazhi_pt_yuanhu中的数据";
    for (auto it = chazhi_pt_yuanhu.begin(); it != chazhi_pt_yuanhu.end(); ++it)
    {
        MultiPoint point = *it;
        qDebug() << "x:" << point.x << " y:" << point.y << " z:" << point.z<< " m:" << point.m<< " n:" << point.n;
    }
}
//!=============================================================================================================


//!=============================================================================================================
//直线轨迹规划:

void RobotGLWidget::traj_zhixian_n()
{
    //将point_stack_n中的数据复制到point_vector_n中
    point_vector_n= QVector<PathPoint>::fromStdVector(point_stack_n.toStdVector());

    qDebug()<<"======================================";
    qDebug()<<"直线轨迹规划:打印point_vector_n中的 向量 数据";
    qDebug()<<"point_vector_n.size()="<<point_vector_n.size();
    for (auto it = point_vector_n.begin(); it != point_vector_n.end(); ++it)
    {
        PathPoint point_n = *it;
        qDebug() << "x:" << point_n.x << " y:" << point_n.y << " z:" << point_n.z;
    }

    //声明chazhi_n_zhixian的大小
    int rongqi_size=(point_vector_n.size()-1)*num_steps+point_vector_n.size();
    chazhi_n_zhixian.resize(rongqi_size);
    //如果不声明chazhi_zb_zhixian的大小，使用索引访问chazhi_zb_zhixian时，可能会超出其有效范围，这会导致未定义的行为

    for(int j=0;j<(point_vector_n.size()-1);++j)
    {
        for (int i = 0; i <= num_steps; ++i)
        {
           chazhi_n_zhixian[(num_steps+1)*j+i].x=
                   point_vector_n[j].x+ i * ((point_vector_n[j+1].x - point_vector_n[j].x) / (num_steps+1));

           chazhi_n_zhixian[(num_steps+1)*j+i].y=
                   point_vector_n[j].y+ i * ((point_vector_n[j+1].y - point_vector_n[j].y) / (num_steps+1));

           chazhi_n_zhixian[(num_steps+1)*j+i].z=
                   point_vector_n[j].z+ i * ((point_vector_n[j+1].z - point_vector_n[j].z) / (num_steps+1));
        }
    }
    //最后一个值
    chazhi_n_zhixian[(num_steps+1)*(point_vector_n.size()-2)+num_steps+1].x=
            point_vector_n[point_vector_n.size()-1].x;
    chazhi_n_zhixian[(num_steps+1)*(point_vector_n.size()-2)+num_steps+1].y=
            point_vector_n[point_vector_n.size()-1].y;
    chazhi_n_zhixian[(num_steps+1)*(point_vector_n.size()-2)+num_steps+1].z=
            point_vector_n[point_vector_n.size()-1].z;


    qDebug()<<"======================================";
    qDebug()<<"chazhi_n_zhixian.size()="<<chazhi_n_zhixian.size();
    qDebug()<<"打印chazhi_n_zhixian中的数据";
    for (auto it = chazhi_n_zhixian.begin(); it != chazhi_n_zhixian.end(); ++it)
    {
        PathPoint point = *it;
        qDebug() << "x:" << point.x << " y:" << point.y << " z:" << point.z;
    }

}

void RobotGLWidget::traj_zhixian_pit()
{
    //将point_stack_Pit中的数据复制到point_vector_Pit中
    point_vector_Pit= QVector<MultiPoint>::fromStdVector(point_stack_Pit.toStdVector());

    qDebug()<<"======================================";
    qDebug()<<"直线轨迹规划:打印point_vector_Pit中的 Pit数据";
    qDebug()<<"point_vector_Pit.size()="<<point_vector_Pit.size();
    for (auto it = point_vector_Pit.begin(); it != point_vector_Pit.end(); ++it)
    {
        MultiPoint point_n = *it;
        qDebug() << "x:" << point_n.x << " y:" << point_n.y << " z:" << point_n.z;
    }

    //声明chazhi_pit_zhixian的大小
    int rongqi_size=(point_vector_Pit.size()-1)*num_steps+point_vector_Pit.size();
    chazhi_pit_zhixian.resize(rongqi_size);


    for(int j=0;j<(point_vector_Pit.size()-1);++j)
    {
        for (int i = 0; i <= num_steps; ++i)
        {
           chazhi_pit_zhixian[(num_steps+1)*j+i].x=
                   point_vector_Pit[j].x+ i * ((point_vector_Pit[j+1].x - point_vector_Pit[j].x) / (num_steps+1));

           chazhi_pit_zhixian[(num_steps+1)*j+i].y=
                   point_vector_Pit[j].y+ i * ((point_vector_Pit[j+1].y - point_vector_Pit[j].y) / (num_steps+1));

           chazhi_pit_zhixian[(num_steps+1)*j+i].z=
                   point_vector_Pit[j].z+ i * ((point_vector_Pit[j+1].z - point_vector_Pit[j].z) / (num_steps+1));

           chazhi_pit_zhixian[(num_steps+1)*j+i].m=
                   point_vector_Pit[j].m+ i * ((point_vector_Pit[j+1].m - point_vector_Pit[j].m) / (num_steps+1));

           chazhi_pit_zhixian[(num_steps+1)*j+i].n=
                   point_vector_Pit[j].n+ i * ((point_vector_Pit[j+1].n - point_vector_Pit[j].n) / (num_steps+1));
        }
    }
    //最后一个值
    chazhi_pit_zhixian[(num_steps+1)*(point_vector_Pit.size()-2)+num_steps+1].x=
            point_vector_Pit[point_vector_Pit.size()-1].x;
    chazhi_pit_zhixian[(num_steps+1)*(point_vector_Pit.size()-2)+num_steps+1].y=
            point_vector_Pit[point_vector_Pit.size()-1].y;
    chazhi_pit_zhixian[(num_steps+1)*(point_vector_Pit.size()-2)+num_steps+1].z=
            point_vector_Pit[point_vector_Pit.size()-1].z;

    chazhi_pit_zhixian[(num_steps+1)*(point_vector_Pit.size()-2)+num_steps+1].m=
            point_vector_Pit[point_vector_Pit.size()-1].m;

    chazhi_pit_zhixian[(num_steps+1)*(point_vector_Pit.size()-2)+num_steps+1].n=
            point_vector_Pit[point_vector_Pit.size()-1].n;

    qDebug()<<"======================================";
    qDebug()<<"chazhi_pit_zhixian.size()="<<chazhi_pit_zhixian.size();
    qDebug()<<"打印chazhi_pit_zhixian中的数据";
    for (auto it = chazhi_pit_zhixian.begin(); it != chazhi_pit_zhixian.end(); ++it)
    {
        MultiPoint point = *it;
        qDebug() << "x:" << point.x << " y:" << point.y << " z:" << point.z<< " m:" << point.m<< " n:" << point.n;
    }
}

void RobotGLWidget::traj_zhixian_pt()
{
    //将point_stack_Pt中的数据复制到point_vector_Pt中
    point_vector_Pt= QVector<MultiPoint>::fromStdVector(point_stack_Pt.toStdVector());

    qDebug()<<"======================================";
    qDebug()<<"直线轨迹规划:打印point_vector_Pt中的 坐标数据";
    qDebug()<<"point_vector_Pt.size()="<<point_vector_Pt.size();
    for (auto it = point_vector_Pt.begin(); it != point_vector_Pt.end(); ++it)
    {
        MultiPoint point_n = *it;
        qDebug() << "x:" << point_n.x << " y:" << point_n.y << " z:" << point_n.z;
    }

    //声明chazhi_pt_zhixian的大小
    int rongqi_size=(point_vector_Pt.size()-1)*num_steps+point_vector_Pt.size();
    chazhi_pt_zhixian.resize(rongqi_size);

    for(int j=0;j<(point_vector_Pt.size()-1);++j)
    {
        for (int i = 0; i <= num_steps; ++i)
        {
           chazhi_pt_zhixian[(num_steps+1)*j+i].x=
                   point_vector_Pt[j].x+ i * ((point_vector_Pt[j+1].x - point_vector_Pt[j].x) / (num_steps+1));

           chazhi_pt_zhixian[(num_steps+1)*j+i].y=
                   point_vector_Pt[j].y+ i * ((point_vector_Pt[j+1].y - point_vector_Pt[j].y) / (num_steps+1));

           chazhi_pt_zhixian[(num_steps+1)*j+i].z=
                   point_vector_Pt[j].z+ i * ((point_vector_Pt[j+1].z - point_vector_Pt[j].z) / (num_steps+1));

           chazhi_pt_zhixian[(num_steps+1)*j+i].m=
                   point_vector_Pt[j].m+ i * ((point_vector_Pt[j+1].m - point_vector_Pt[j].m) / (num_steps+1));

           chazhi_pt_zhixian[(num_steps+1)*j+i].n=
                   point_vector_Pt[j].n+ i * ((point_vector_Pt[j+1].n - point_vector_Pt[j].n) / (num_steps+1));
        }
    }
    //最后一个值
    chazhi_pt_zhixian[(num_steps+1)*(point_vector_Pt.size()-2)+num_steps+1].x=
            point_vector_Pt[point_vector_Pt.size()-1].x;
    chazhi_pt_zhixian[(num_steps+1)*(point_vector_Pt.size()-2)+num_steps+1].y=
            point_vector_Pt[point_vector_Pt.size()-1].y;
    chazhi_pt_zhixian[(num_steps+1)*(point_vector_Pt.size()-2)+num_steps+1].z=
            point_vector_Pt[point_vector_Pt.size()-1].z;

    chazhi_pt_zhixian[(num_steps+1)*(point_vector_Pt.size()-2)+num_steps+1].m=
            point_vector_Pt[point_vector_Pt.size()-1].m;

    chazhi_pt_zhixian[(num_steps+1)*(point_vector_Pt.size()-2)+num_steps+1].n=
            point_vector_Pt[point_vector_Pt.size()-1].n;

    qDebug()<<"======================================";
    qDebug()<<"chazhi_pt_zhixian.size()="<<chazhi_pt_zhixian.size();
    qDebug()<<"打印chazhi_pt_zhixian中的数据";
    for (auto it = chazhi_pt_zhixian.begin(); it != chazhi_pt_zhixian.end(); ++it)
    {
        MultiPoint point = *it;
        qDebug() << "x:" << point.x << " y:" << point.y << " z:" << point.z<< " m:" << point.m<< " n:" << point.n;
    }

}

//!=============================================================================================================

//!=============================================================================================================
//圆弧轨迹规划

void RobotGLWidget::traj_yuanhu_n()
{
    chazhi_zb_2d.clear();

    chazhi_n_yuanhu.clear();
    point_vector_n.clear();

    //将point_stack_n中的数据复制到point_vector_n中
    point_vector_n = QVector<PathPoint>::fromStdVector(point_stack_n.toStdVector());
    qDebug()<<"======================================";
    qDebug()<<"圆弧轨迹规划*****打印point_vector_n中的数据";
    qDebug()<<"point_vector_n.size()="<<point_vector_n.size();
    for (auto it = point_vector_n.begin(); it != point_vector_n.end(); ++it)
    {
        PathPoint point = *it;
        qDebug() << "x:" << point.x << " y:" << point.y << " z:" << point.z;
    }

    int num2=point_vector_n.size();
    int chushu=num2/3;//两个数相除后的解的整数
    int yushu=num2%3;//两个数相除后的余数
    int cout=chushu;//用以记录有几个包含3个点的集合
    while(chushu+yushu>=3)
    {
        num2=chushu+yushu;
        chushu=num2/3;
        yushu=num2%3;
        cout=cout+chushu;
    }

    qDebug()<<"========================";
    qDebug()<<"三次插值的组数cout="<<cout;//cout的数值就代表着进行三次插值的组数，即调用SetChangeMatrix_n函数的次数
    qDebug()<<"========================";

    for(int j=0;j<cout;j++)
    {
        double trans_point[9];//存放3个点的x,y,z值
        for (int i = 0; i < 3; ++i)
        {
            const PathPoint& point = point_vector_n.at(i+2*j);
            trans_point[3*i+0]=point.x;
            trans_point[3*i+1]=point.y;
            trans_point[3*i+2]=point.z;
        }

        double Start_point[3]={trans_point[0],trans_point[1],trans_point[2]};
        double Mid_point[3]={trans_point[3],trans_point[4],trans_point[5]};
        double End_point[3]={trans_point[6],trans_point[7],trans_point[8]};

        qDebug()<<"当j="<<j<<"时进入SetChangeMatrix_n的三个点：";
        qDebug()<<"Start_point[0]="<<Start_point[0]<<" "<<"Start_point[1]="<<Start_point[1]<<" "<<"Start_point[2]="<<Start_point[2];
        qDebug()<<"Mid_point[0]="<<Mid_point[0]<<" "<<"Mid_point[1]="<<Mid_point[1]<<" "<<"Mid_point[2]="<<Mid_point[2];
        qDebug()<<"End_point[0]="<<End_point[0]<<" "<<"End_point[1]="<<End_point[1]<<" "<<"End_point[2]="<<End_point[2];

        SetChangeMatrix_n(Start_point, Mid_point, End_point);

        qDebug()<<"========================";
        qDebug()<<"第"<<j<<"次SetChangeMatrix_n执行完毕！";
        qDebug()<<"========================";

    }

    //使用逆运动学将对应的三维坐标转换成角度值
}

void RobotGLWidget::traj_yuanhu_pit()
{
    chazhi_zb_2d.clear();

    chazhi_pt_yuanhu.clear();
    point_vector_Pit.clear();

    //将point_stack_Pit中的数据复制到point_vector_Pit中
    point_vector_Pit = QVector<MultiPoint>::fromStdVector(point_stack_Pit.toStdVector());
    qDebug()<<"======================================";
    qDebug()<<"圆弧轨迹规划*****打印point_vector_Pit中的数据";
    qDebug()<<"point_vector_Pit.size()="<<point_vector_Pit.size();
    for (auto it = point_vector_Pit.begin(); it != point_vector_Pit.end(); ++it)
    {
        MultiPoint point = *it;
        qDebug() << "x:" << point.x << " y:" << point.y << " z:" << point.z;
    }

    int num2=point_vector_Pit.size();
    int chushu=num2/3;//两个数相除后的解的整数
    int yushu=num2%3;//两个数相除后的余数
    int cout=chushu;//用以记录有几个包含3个点的集合
    while(chushu+yushu>=3)
    {
        num2=chushu+yushu;
        chushu=num2/3;
        yushu=num2%3;
        cout=cout+chushu;
    }

    qDebug()<<"========================";
    qDebug()<<"三次插值的组数cout="<<cout;//cout的数值就代表着进行三次插值的组数，即调用SetChangeMatrix_pit函数的次数
    qDebug()<<"========================";

    for(int j=0;j<cout;j++)
    {
        double trans_point[9];//存放3个点的x,y,z值
        for (int i = 0; i < 3; ++i)
        {
            const MultiPoint& point = point_vector_Pit.at(i+2*j);
            trans_point[3*i+0]=point.x;
            trans_point[3*i+1]=point.y;
            trans_point[3*i+2]=point.z;
        }

        double Start_point[3]={trans_point[0],trans_point[1],trans_point[2]};
        double Mid_point[3]={trans_point[3],trans_point[4],trans_point[5]};
        double End_point[3]={trans_point[6],trans_point[7],trans_point[8]};

        qDebug()<<"当j="<<j<<"时进入SetChangeMatrix_pit的3个点：";
        qDebug()<<"Start_point[0]="<<Start_point[0]<<" "<<"Start_point[1]="<<Start_point[1]<<" "<<"Start_point[2]="<<Start_point[2];
        qDebug()<<"Mid_point[0]="<<Mid_point[0]<<" "<<"Mid_point[1]="<<Mid_point[1]<<" "<<"Mid_point[2]="<<Mid_point[2];
        qDebug()<<"End_point[0]="<<End_point[0]<<" "<<"End_point[1]="<<End_point[1]<<" "<<"End_point[2]="<<End_point[2];

        SetChangeMatrix_pit(Start_point, Mid_point, End_point);

        qDebug()<<"========================";
        qDebug()<<"第"<<j<<"次SetChangeMatrix_pit执行完毕！";
        qDebug()<<"========================";

    }

    //使用逆运动学将对应的三维坐标转换成角度值
}

void RobotGLWidget::traj_yuanhu_pt()
{
    chazhi_zb_2d.clear();

    chazhi_pt_yuanhu.clear();
    point_vector_Pt.clear();

    //将point_stack_Pt中的数据复制到point_vector_Pt中
    point_vector_Pt = QVector<MultiPoint>::fromStdVector(point_stack_Pt.toStdVector());
    qDebug()<<"======================================";
    qDebug()<<"圆弧轨迹规划*****打印point_vector_Pt中的数据";
    qDebug()<<"point_vector_Pt.size()="<<point_vector_Pt.size();
    for (auto it = point_vector_Pt.begin(); it != point_vector_Pt.end(); ++it)
    {
        MultiPoint point = *it;
        qDebug() << "x:" << point.x << " y:" << point.y << " z:" << point.z;
    }

    int num2=point_vector_Pt.size();
    int chushu=num2/3;//两个数相除后的解的整数
    int yushu=num2%3;//两个数相除后的余数
    int cout=chushu;//用以记录有几个包含3个点的集合
    while(chushu+yushu>=3)
    {
        num2=chushu+yushu;
        chushu=num2/3;
        yushu=num2%3;
        cout=cout+chushu;
    }

    qDebug()<<"========================";
    qDebug()<<"三次插值的组数cout="<<cout;//cout的数值就代表着进行三次插值的组数，即调用SetChangeMatrix_pt函数的次数
    qDebug()<<"========================";

    for(int j=0;j<cout;j++)
    {
        double trans_point[9];//存放3个点的x,y,z值
        for (int i = 0; i < 3; ++i)
        {
            const MultiPoint& point = point_vector_Pt.at(i+2*j);
            trans_point[3*i+0]=point.x;
            trans_point[3*i+1]=point.y;
            trans_point[3*i+2]=point.z;
        }

        double Start_point[3]={trans_point[0],trans_point[1],trans_point[2]};
        double Mid_point[3]={trans_point[3],trans_point[4],trans_point[5]};
        double End_point[3]={trans_point[6],trans_point[7],trans_point[8]};

        qDebug()<<"当j="<<j<<"时进入SetChangeMatrix_pt的3个点：";
        qDebug()<<"Start_point[0]="<<Start_point[0]<<" "<<"Start_point[1]="<<Start_point[1]<<" "<<"Start_point[2]="<<Start_point[2];
        qDebug()<<"Mid_point[0]="<<Mid_point[0]<<" "<<"Mid_point[1]="<<Mid_point[1]<<" "<<"Mid_point[2]="<<Mid_point[2];
        qDebug()<<"End_point[0]="<<End_point[0]<<" "<<"End_point[1]="<<End_point[1]<<" "<<"End_point[2]="<<End_point[2];

        SetChangeMatrix_pt(Start_point, Mid_point, End_point);

        qDebug()<<"========================";
        qDebug()<<"第"<<j<<"次SetChangeMatrix_pt执行完毕！";
        qDebug()<<"========================";

    }

    //使用逆运动学将对应的三维坐标转换成角度值
}

//!=============================================================================================================

void RobotGLWidget::clear()//清除插值点和轨迹
{
    clear_traj=true;
}

void RobotGLWidget::Run_zhixian()
{
    //inverse(fk_n, fk_Pt, fk_Pit);
    //将初始点对应的theta值放入zhixian_ik_theta中
    PathTheta st_one;
    st_one.th1=start_theta[0];
    st_one.th2=start_theta[1];
    st_one.th3=start_theta[2];
    st_one.th4=start_theta[3];
    st_one.th5=start_theta[4];
    st_one.th6=start_theta[5];
    zhixian_ik_theta.append(st_one);
    int num_vector=0;

    //将初始点后的一个点用逆运动学算出其对应的theta值
    QVector<PathPoint>::iterator it_n;
    QVector<MultiPoint>::iterator it_pt;
    QVector<MultiPoint>::iterator it_pit;

    for(it_n = chazhi_n_zhixian.begin()+1,it_pt = chazhi_pt_zhixian.begin()+1,it_pit = chazhi_pit_zhixian.begin()+1;
    it_n!= chazhi_n_zhixian.end()&& it_pt!= chazhi_pt_zhixian.end()&& it_pit!= chazhi_pit_zhixian.end(); ++it_n,++it_pt,++it_pit)
    {

        num_vector++;

        QVector<PathTheta> linshi_theta_vector;//定义一个临时容器用以接收inverse一次传出的8组解

        linshi_theta_vector=inverse(*it_n, *it_pt, *it_pit);

        qDebug()<<"==============================================";
        qDebug()<<"输出第"<<num_vector<<"个点通过逆运动学传入linshi_theta_vector的各组解"<<endl;

        qDebug()<<"第一组解";
        qDebug()<<"l_t_v:"<<"th1="<<linshi_theta_vector[0].th1<<" th2="<<linshi_theta_vector[0].th2<<" th3="<<linshi_theta_vector[0].th3
        <<"th4="<<linshi_theta_vector[0].th4<<" th5="<<linshi_theta_vector[0].th5<<" th6="<<linshi_theta_vector[0].th6;

        qDebug()<<"第二组解";
        qDebug()<<"l_t_v:"<<"th1="<<linshi_theta_vector[1].th1<<" th2="<<linshi_theta_vector[1].th2<<" th3="<<linshi_theta_vector[1].th3
        <<"th4="<<linshi_theta_vector[1].th4<<" th5="<<linshi_theta_vector[1].th5<<" th6="<<linshi_theta_vector[1].th6;

        qDebug()<<"第三组解";
        qDebug()<<"l_t_v:"<<"th1="<<linshi_theta_vector[2].th1<<" th2="<<linshi_theta_vector[2].th2<<" th3="<<linshi_theta_vector[2].th3
        <<"th4="<<linshi_theta_vector[2].th4<<" th5="<<linshi_theta_vector[2].th5<<" th6="<<linshi_theta_vector[2].th6;

        qDebug()<<"第四组解";
        qDebug()<<"l_t_v:"<<"th1="<<linshi_theta_vector[3].th1<<" th2="<<linshi_theta_vector[3].th2<<" th3="<<linshi_theta_vector[3].th3
        <<"th4="<<linshi_theta_vector[3].th4<<" th5="<<linshi_theta_vector[3].th5<<" th6="<<linshi_theta_vector[3].th6;


        qDebug()<<"num_vector="<<num_vector;

        //选择转动幅度最小的逆解
        double minRotationAmplitude = std::numeric_limits<double>::max();
        //max()是std::numeric_limits类的一个静态成员函数，用于返回给定类型(double)的最大可能值，
        //当关节位置与目标位置之间的差值小于此值时，替换该值
        int bestSolutionIndex = -1;//记录产生最小差值的解的序号
        double rotationAmplitude = 0.0;

        for (int i = 0; i <4; ++i)
        {
             rotationAmplitude=
                      abs(linshi_theta_vector[i].th1-zhixian_ik_theta[(num_vector-1)].th1)
                     +abs(linshi_theta_vector[i].th2-zhixian_ik_theta[(num_vector-1)].th2)
                     +abs(linshi_theta_vector[i].th3-zhixian_ik_theta[(num_vector-1)].th3)
                     +abs(linshi_theta_vector[i].th4-zhixian_ik_theta[(num_vector-1)].th4)
                     +abs(linshi_theta_vector[i].th5-zhixian_ik_theta[(num_vector-1)].th5)
                     +abs(linshi_theta_vector[i].th6-zhixian_ik_theta[(num_vector-1)].th6);

             qDebug() << "==========================" ;
             qDebug() << "i=" <<i;
             qDebug() << "zhixian_ik_theta:th1=" <<zhixian_ik_theta[(num_vector-1)].th1<<" th2="<<zhixian_ik_theta[(num_vector-1)].th2
                       <<" th3="<<zhixian_ik_theta[(num_vector-1)].th3<<" th4="<<zhixian_ik_theta[(num_vector-1)].th4
                         <<" th5="<<zhixian_ik_theta[(num_vector-1)].th5<<" th6="<<zhixian_ik_theta[(num_vector-1)].th6;

              qDebug()<<"linshi_theta_vector:th1="<<linshi_theta_vector[i].th1<<" th2="<<linshi_theta_vector[i].th2
                        <<" th3="<<linshi_theta_vector[i].th3<<" th4="<<linshi_theta_vector[i].th4
                          <<" th5="<<linshi_theta_vector[i].th5<<" th6="<<linshi_theta_vector[i].th6;

             if (rotationAmplitude <= minRotationAmplitude)
             {
                  minRotationAmplitude = rotationAmplitude;
                  bestSolutionIndex = i;
             }

             qDebug() << "rotationAmplitude=" <<rotationAmplitude;
             qDebug()<<"此时的minRotationAmplitude"<<minRotationAmplitude;
        }

        qDebug() << "最好的解为第" << bestSolutionIndex+1<< "组解" ;

        //将最好的解装入zhixian_ik_theta
        PathTheta st_two;
        st_two.th1=linshi_theta_vector[bestSolutionIndex].th1;
        st_two.th2=linshi_theta_vector[bestSolutionIndex].th2;
        st_two.th3=linshi_theta_vector[bestSolutionIndex].th3;
        st_two.th4=linshi_theta_vector[bestSolutionIndex].th4;
        st_two.th5=linshi_theta_vector[bestSolutionIndex].th5;
        st_two.th6=linshi_theta_vector[bestSolutionIndex].th6;
        zhixian_ik_theta.append(st_two);

    }

    //输出zhixian_ik_theta中的值
    qDebug()<<"==============================================";
    qDebug()<<"输出zhixian_ik_theta中的theta数据：";
    for(auto it = zhixian_ik_theta.begin(); it != zhixian_ik_theta.end(); ++it)
    {
        const PathTheta& pt = *it;
        qDebug()<<"th1="<<pt.th1<<" th2="<<pt.th2<<"th3="<<pt.th3<<"th4="<<pt.th4<<" th5="<<pt.th5<<"th6="<<pt.th6;
    }

    connect(&dingshi_zx, &QTimer::timeout, [&]()
    { // 将定时器的timeout信号连接到一个槽函数
        ss++;
        // 检查指定位置是否有效
        if (ss >= 0 && ss< zhixian_ik_theta.size())
        {
            const PathTheta& dh =zhixian_ik_theta[ss];

            th1=dh.th1;
            th2=dh.th2;
            th3=dh.th3;
            th4=dh.th4;
            th5=-dh.th5;
            th6=dh.th6;

            qDebug()<<"动画：th1="<<th1<<" th2="<<-th2<<" th3="<<-th3<<" th4="<<th4<<" th5="<<-th5<<" th6="<<th6;
        }
        else
        {
//            th1=0;
//            th2=0;
//            th3=0;
//            th4=0;
//            th5=0;
//            th6=0;
            ss=0;
            zhixian_ik_theta.clear();
            qDebug() << "动画计数ss超范围";
            dingshi_zx.stop();
        }
    });
    dingshi_zx.start(500); // 设置定时器的时间间隔为500毫秒(即0.5秒)

}

void RobotGLWidget::Run_yuanhu()
{
    //将初始点对应的theta值放入yuanhu_ik_theta中
    PathTheta st_one;
    st_one.th1=start_theta[0];
    st_one.th2=start_theta[1];
    st_one.th3=start_theta[2];
    st_one.th4=start_theta[3];
    st_one.th5=start_theta[4];
    st_one.th6=start_theta[5];
    yuanhu_ik_theta.append(st_one);
    int num_vector=0;

    //将初始点后的一个点用逆运动学算出其对应的theta值
    QVector<PathPoint>::iterator it_n;
    QVector<MultiPoint>::iterator it_pt;
    QVector<MultiPoint>::iterator it_pit;

    for(it_n = chazhi_n_yuanhu.begin()+1,it_pt = chazhi_pt_yuanhu.begin()+1,it_pit = chazhi_pit_yuanhu.begin()+1;
    it_n!= chazhi_n_yuanhu.end()&& it_pt!= chazhi_pt_yuanhu.end()&& it_pit!= chazhi_pit_yuanhu.end(); ++it_n,++it_pt,++it_pit)
    {

        num_vector++;

        QVector<PathTheta> linshi_theta_vector;//定义一个临时容器用以接收inverse一次传出的8组解

        linshi_theta_vector=inverse(*it_n, *it_pt, *it_pit);

        qDebug()<<"==============================================";
        qDebug()<<"输出第"<<num_vector<<"个点通过逆运动学传入linshi_theta_vector的各组解"<<endl;

        qDebug()<<"第一组解";
        qDebug()<<"l_t_v:"<<"th1="<<linshi_theta_vector[0].th1<<" th2="<<linshi_theta_vector[0].th2<<" th3="<<linshi_theta_vector[0].th3
        <<"th4="<<linshi_theta_vector[0].th4<<" th5="<<linshi_theta_vector[0].th5<<" th6="<<linshi_theta_vector[0].th6;

        qDebug()<<"第二组解";
        qDebug()<<"l_t_v:"<<"th1="<<linshi_theta_vector[1].th1<<" th2="<<linshi_theta_vector[1].th2<<" th3="<<linshi_theta_vector[1].th3
        <<"th4="<<linshi_theta_vector[1].th4<<" th5="<<linshi_theta_vector[1].th5<<" th6="<<linshi_theta_vector[1].th6;

        qDebug()<<"第三组解";
        qDebug()<<"l_t_v:"<<"th1="<<linshi_theta_vector[2].th1<<" th2="<<linshi_theta_vector[2].th2<<" th3="<<linshi_theta_vector[2].th3
        <<"th4="<<linshi_theta_vector[2].th4<<" th5="<<linshi_theta_vector[2].th5<<" th6="<<linshi_theta_vector[2].th6;

        qDebug()<<"第四组解";
        qDebug()<<"l_t_v:"<<"th1="<<linshi_theta_vector[3].th1<<" th2="<<linshi_theta_vector[3].th2<<" th3="<<linshi_theta_vector[3].th3
        <<"th4="<<linshi_theta_vector[3].th4<<" th5="<<linshi_theta_vector[3].th5<<" th6="<<linshi_theta_vector[3].th6;


        qDebug()<<"num_vector="<<num_vector;

        //选择转动幅度最小的逆解
        double minRotationAmplitude = std::numeric_limits<double>::max();
        //max()是std::numeric_limits类的一个静态成员函数，用于返回给定类型(double)的最大可能值，
        //当关节位置与目标位置之间的差值小于此值时，替换该值
        int bestSolutionIndex = -1;//记录产生最小差值的解的序号
        double rotationAmplitude = 0.0;

        for (int i = 0; i <4; ++i)
        {
             rotationAmplitude=
                      abs(linshi_theta_vector[i].th1-yuanhu_ik_theta[(num_vector-1)].th1)
                     +abs(linshi_theta_vector[i].th2-yuanhu_ik_theta[(num_vector-1)].th2)
                     +abs(linshi_theta_vector[i].th3-yuanhu_ik_theta[(num_vector-1)].th3)
                     +abs(linshi_theta_vector[i].th4-yuanhu_ik_theta[(num_vector-1)].th4)
                     +abs(linshi_theta_vector[i].th5-yuanhu_ik_theta[(num_vector-1)].th5)
                     +abs(linshi_theta_vector[i].th6-yuanhu_ik_theta[(num_vector-1)].th6);

             qDebug() << "==========================" ;
             qDebug() << "i=" <<i;
             qDebug() << "yuanhu_ik_theta:th1=" <<yuanhu_ik_theta[(num_vector-1)].th1<<" th2="<<yuanhu_ik_theta[(num_vector-1)].th2
                       <<" th3="<<yuanhu_ik_theta[(num_vector-1)].th3<<" th4="<<yuanhu_ik_theta[(num_vector-1)].th4
                         <<" th5="<<yuanhu_ik_theta[(num_vector-1)].th5<<" th6="<<yuanhu_ik_theta[(num_vector-1)].th6;

              qDebug()<<"linshi_theta_vector:th1="<<linshi_theta_vector[i].th1<<" th2="<<linshi_theta_vector[i].th2
                        <<" th3="<<linshi_theta_vector[i].th3<<" th4="<<linshi_theta_vector[i].th4
                          <<" th5="<<linshi_theta_vector[i].th5<<" th6="<<linshi_theta_vector[i].th6;

             if (rotationAmplitude <= minRotationAmplitude)
             {
                  minRotationAmplitude = rotationAmplitude;
                  bestSolutionIndex = i;
             }

             qDebug() << "rotationAmplitude=" <<rotationAmplitude;
             qDebug()<<"此时的minRotationAmplitude"<<minRotationAmplitude;
        }

        qDebug() << "最好的解为第" << bestSolutionIndex+1<< "组解" ;

        //将最好的解装入yuanhu_ik_theta
        PathTheta st_two;
        st_two.th1=linshi_theta_vector[bestSolutionIndex].th1;
        st_two.th2=linshi_theta_vector[bestSolutionIndex].th2;
        st_two.th3=linshi_theta_vector[bestSolutionIndex].th3;
        st_two.th4=linshi_theta_vector[bestSolutionIndex].th4;
        st_two.th5=linshi_theta_vector[bestSolutionIndex].th5;
        st_two.th6=linshi_theta_vector[bestSolutionIndex].th6;
        yuanhu_ik_theta.append(st_two);

    }

    //输出yuanhu_ik_theta中的值
    qDebug()<<"==============================================";
    qDebug()<<"输出yuanhu_ik_theta中的theta数据：";
    for(auto it = yuanhu_ik_theta.begin(); it != yuanhu_ik_theta.end(); ++it)
    {
        const PathTheta& pt = *it;
        qDebug()<<"th1="<<pt.th1<<" th2="<<pt.th2<<"th3="<<pt.th3;
    }

    connect(&dingshi_yh, &QTimer::timeout, [&]()
    { // 将定时器的timeout信号连接到一个槽函数
        ss++;
        // 检查指定位置是否有效
        if (ss >= 0 && ss<yuanhu_ik_theta.size())
        {
            const PathTheta& dh =yuanhu_ik_theta[ss];
            th1=dh.th1;
            th2=dh.th2;
            th3=dh.th3;
            th4=dh.th4;
            th5=-dh.th5;
            th6=dh.th6;

            qDebug()<<"动画：th1="<<th1<<" th2="<<-th2<<" th3="<<-th3<<" th4="<<th4<<" th5="<<-th5<<" th6="<<th6;
        }
        else
        {
            ss=0;
            yuanhu_ik_theta.clear();
            qDebug() << "动画计数ss超范围";
            dingshi_yh.stop();
        }
    });
    dingshi_yh.start(1000); // 设置定时器的时间间隔为1000毫秒(即1秒)

}

//已知 点对 求点公式1
Multivector RobotGLWidget::formula(Multivector Ppn,int t)
{
    Multivector einfPpn = inner(ei, Ppn);
    double normeinfPpn = scalarpart(geom(einfPpn, reverse(einfPpn)));
    Multivector inveinfPpn = einfPpn / normeinfPpn;
    inveinfPpn = vectorpart(inveinfPpn, 1);

    Multivector pn = -geom(Ppn+((t*sqrt(abs(scalarpart(inner(Ppn, Ppn)))))), inveinfPpn);
    pn = vectorpart(pn, 1);
    return pn;
}

//判断theta取值函数
double RobotGLWidget::judge_th(double _cos_th,double _region_s,double _region_e)
{
    double th_a = 1000;
    double th_a_z = acos(_cos_th) * 180 / PI;
    double th_a_f = -acos(_cos_th) * 180 / PI;

    double arr_th_a[4];

    if (th_a_z > 0)
    {
        arr_th_a[0] = th_a_z;
        arr_th_a[1] = th_a_f;
        arr_th_a[2] = th_a_z - 180;
        arr_th_a[3] = th_a_f + 180;
    }
    else if (th_a_z < 0)
    {
        arr_th_a[0] = th_a_z;
        arr_th_a[1] = th_a_f;
        arr_th_a[2] = th_a_z + 180;
        arr_th_a[3] = th_a_f - 180;
    }
    else
    {
        th_a = 0;
    }

    if (th_a != 0)
    {
        for (int i = 0; i < 4; i++)
        {
            if ((arr_th_a[i] >= _region_s) && (arr_th_a[i] <= _region_e))
                th_a = arr_th_a[i];
        }

    }

    return th_a;
}
