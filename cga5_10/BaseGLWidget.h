
#ifndef RRGLWIDGET_H
#define RRGLWIDGET_H

#include <QGLWidget>
#include <QWidget>

class  BaseGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    BaseGLWidget(QWidget *parent = 0);
    ~BaseGLWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    void setGLMaterialColor(int r, int g, int b);
    //void setGLMaterialColor(const QColor &color);

    void setXRotation(int angle);
    void setYRotation(int angle);
    void setXYTranslate(int dx, int dy);
    void setZoom(int zoom);

    virtual void drawGL() = 0;
    virtual void drawMeshline(float size = 50, int count = 15);
    virtual void drawCoordAxis(float length = 100);

protected:
    double m_intervalAngle = 10;
    GLdouble m_xRotate;   /**< x旋转角度 */
    GLdouble m_yRotate;   /**< y旋转角度 */
    GLdouble m_zoom;      /**< 缩放 */
    GLdouble m_xTrans;    /**< 界面显示X位置 */
    GLdouble m_yTrans;    /**< 界面显示Y位置 */
    QPoint   lastPos;
};
#endif
