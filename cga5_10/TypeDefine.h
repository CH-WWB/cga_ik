#ifndef TYPEDEFINE_H
#define TYPEDEFINE_H

//#include <QVector>


//struct RobotAngle
//{
//    RobotAngle() {}
//    RobotAngle(double a1, double a2, double a3, double a4, double a5, double a6)
//        : angle1(a1), angle2(a2), angle3(a3), angle4(a4), angle5(a5), angle6(a6) {}
//    double angle1 = 0;
//    double angle2 = 0;
//    double angle3 = 0;
//    double angle4 = 0;
//    double angle5 = 0;
//    double angle6 = 0;

//    QVector<double> toVector()
//    {
//        QVector<double> vec;
//        vec.push_back(angle1);
//        vec.push_back(angle2);
//        vec.push_back(angle3);
//        vec.push_back(angle4);
//        vec.push_back(angle5);
//        vec.push_back(angle6);
//        return vec;
//    }
//};

//struct DhPara
//{
//    DhPara() {}
//    DhPara(double tlinkLength, double ttorsionAngle, double tlinkOffset, double tjointAngle)
//        : linkLength(tlinkLength), torsionAngle(ttorsionAngle),
//          linkOffset(tlinkOffset), jointAngle(tjointAngle) {}

//    double linkLength   = 0;   /**< 连杆长度 */
//    double torsionAngle = 0;   /**< 扭转角 */
//    double linkOffset   = 0;   /**< 连杆偏移量 */
//    double jointAngle   = 0;   /**< 关节角 */

//    QVector<double> toVector()
//    {
//        QVector<double> vec;
//        vec.push_back(linkLength);
//        vec.push_back(torsionAngle);
//        vec.push_back(linkOffset);
//        vec.push_back(jointAngle);
//        return vec;
//    }

//    void setValue(int i, double val)
//    {
//        if(0 == i)
//        {
//            linkLength = val;
//        }
//        else if(1 == i)
//        {
//            torsionAngle = val;
//        }
//        else if(2 == i)
//        {
//            linkOffset = val;
//        }
//        else if(3 == i)
//        {
//            jointAngle = val;
//        }
//    }
//};

//struct DhModelData
//{
//    DhPara paras[6];
//};
#endif // TYPEDEFINE_H
