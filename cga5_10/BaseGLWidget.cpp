#include "BaseGLWidget.h"
#include <GL/glu.h>
#include <QDebug>
#include <QMouseEvent>
#include <QMatrix4x4>
#include <QVector4D>

BaseGLWidget::BaseGLWidget(QWidget *parent)
    : QGLWidget(parent)
{
    m_xRotate = -2276;
    m_yRotate = 1736;
    m_zoom    = -3000;
    m_xTrans  = 0;
    m_yTrans  = 0;
}

BaseGLWidget::~BaseGLWidget() {}


void BaseGLWidget::initializeGL()
{
    //用来初始化这个OpenGL窗口部件的，可以在里面设定一些有关选项
    GLfloat ambientLight[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat diffuseLight[] = {0.8f, 0.9f, 0.9f, 1.0f};
    GLfloat specularLight[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat positionLight[] = {20.0f, 20.0f, 20.0f, 0.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);
    glLightfv(GL_LIGHT0, GL_POSITION, positionLight);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

}

/**
 * @brief BaseGLWidget::paintGL GL绘制
 */
void BaseGLWidget::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//设置背景颜色为黑色
    glClearDepth(1.0);//设置深度缓存的初始值为1
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    glTranslated(0, 0, m_zoom);//沿着 z 轴平移，移动的距离由变量 m_zoom 决定
    glTranslated(m_xTrans, m_yTrans, 0);//在 x 和 y 轴上平移，移动的距离由变量 m_xTrans 和 m_yTrans 决定
    glRotated(m_xRotate / 16.0, 1.0, 0.0, 0.0); /* 绕x轴旋转 */
    glRotated(m_yRotate / 16.0, 0.0, 1.0, 0.0); /* 绕y轴旋转 */
    glRotated(+90.0, 1.0, 0.0, 0.0);

    drawGL();

    glPopMatrix();
}

/**
 * @brief BaseGLWidget::resizeGL
 * @param w
 * @param h
 */
void BaseGLWidget::resizeGL(int w, int h)
{
    if (w < 0 || h < 0)
    {
        return;
    }
    glViewport(0, 0, w, h);//观察矩阵(View Matrix)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(35.0, w / float(h), 1.0, 20000.0);//投影矩阵(Projection Matrix)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 * @brief BaseGLWidget::mousePressEvent 鼠标按下事件
 * @param event
 */
void BaseGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

/**
 * @brief BaseGLWidget::mouseMoveEvent 鼠标移动事件
 * @param event
 */
void BaseGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    if (event->buttons() & Qt::LeftButton)
    {
        setXRotation(m_xRotate + 4 * dy);
        setYRotation(m_yRotate - 4 * dx);
    }
    else if (event->buttons() & Qt::MidButton)
    {
        setXYTranslate(4 * dx, 4* dy);
    }
    lastPos = event->pos();
}

/**
 * @brief BaseGLWidget::wheelEvent 鼠标滚动事件
 * @param event
 */
void BaseGLWidget::wheelEvent(QWheelEvent *event)
{
    auto scroll_offest = event->angleDelta().y() / 2;
    setZoom(m_zoom + (float)scroll_offest);
}

void BaseGLWidget::setGLMaterialColor(int r, int g, int b)
{

    GLfloat colorfv[] = {r / 255.0f, g / 255.0f, b / 255.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, colorfv);
}

/**
 * @brief BaseGLWidget::setXRotation  X旋转
 * @param angle
 */
void BaseGLWidget::setXRotation(int angle)
{
    int tangle = angle;
    if (tangle != m_xRotate)
    {
        m_xRotate = tangle;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        updateGL();
    }
}

/**
 * @brief BaseGLWidget::setYRotation Y旋转
 * @param angle
 */
void BaseGLWidget::setYRotation(int angle)
{
    int tangle = angle;
    if (tangle != m_yRotate)
    {
        m_yRotate = tangle;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

/**
 * @brief BaseGLWidget::setXYTranslate XY平移
 * @param dx
 * @param dy
 */
void BaseGLWidget::setXYTranslate(int dx, int dy)
{
    m_xTrans += dx;
    m_yTrans -= dy;
    updateGL();
}

/**
 * @brief BaseGLWidget::setZoom  放大、缩小
 * @param zoom
 */
void BaseGLWidget::setZoom(int zoom)
{
    //qDebug() << zoom;
    m_zoom = zoom;
    if(m_zoom < -9600)
    {
        m_zoom = -9600;
    }
    if(m_zoom > 35)
    {
        m_zoom = 35;
    }
    updateGL();
}

/**
 * @brief BaseGLWidget::drawMeshline 网格线
 * @param size
 * @param count
 */
void BaseGLWidget::drawMeshline(float size, int count)
{
    glPushMatrix();
    GLfloat color[] = {8.0f / 255, 108.0f / 255, 162.0f / 255};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    float start = count * (size / 2);
    float posX = start, posZ = start;
    for (int i = 0; i <= count; ++i)
    {
        glBegin(GL_LINES);
        glVertex3f(posX, start, 0);
        glVertex3f(posX, -start, 0);
        glVertex3f(start, posZ, 0);
        glVertex3f(-start, posZ, 0);
        glEnd();

        posX = posX - size;
        posZ = posZ - size;
    }
    glPopMatrix();
}

/**
 * @brief BaseGLWidget::drawCoordAxis 坐标轴
 * @param length
 */
void BaseGLWidget::drawCoordAxis(float length)
{
    glPushMatrix();

    glLineWidth(4.0f);

    glBegin(GL_LINES);
    setGLMaterialColor(255, 0, 0);  // X axis is red.
    glVertex3f(-length, 0, 0);
    glVertex3f(length, 0, 0);

    setGLMaterialColor(0, 255, 0);  // Y axis is green.
    glVertex3f(0, -length, 0);
    glVertex3f(0, length, 0);

    setGLMaterialColor(0, 0, 255);   // Z axis is blue.
    glVertex3f(0, 0, -length);
    glVertex3f(0, 0, length);
    glEnd();

    // Draw labels
    glColor3f(0.0, 1.0, 1.0);
    renderText(0, 0, length, "+Z", QFont("helvetica", 12, QFont::Bold, true));

    glColor3f(1.0, 0.0, 0.0);
    renderText(length, 0, 0, "+X", QFont("helvetica", 12, QFont::Bold, true));

    glColor3f(0.0, 1.0, 0.0);
    renderText(0, length, 0, "+Y", QFont("helvetica", 12, QFont::Bold, true));

    glLineWidth(1.0f);
    glPopMatrix();
}
