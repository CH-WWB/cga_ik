#ifndef EXECUTE_H
#define EXECUTE_H

#include <iostream>
#include "cga.h"

namespace cga {


//Multivector 类型数据：旋转变换//Multivector make_rotation(double theta, Bivector axis)
//-----------------------------------(start)--------------------------------------

    Multivector make_rotation(double theta, Bivector axis)
    {
        Multivector result;
        result.s = cos(theta / 2);
        result.b = -sin(theta / 2) * axis;

        return result;

    }

//------------------------------------(end)---------------------------------------
   

//Multivector 类型数据：平移变换//Multivector make_translation(double x, double y, double z)
//-----------------------------------(start)--------------------------------------

    Multivector make_translation(double x, double y, double z)
    {
        Multivector result;
        result.s = 1;
        result.b.e14 = -0.5 * x;
        result.b.e15 = -0.5 * x;
        result.b.e24 = -0.5 * y;
        result.b.e25 = -0.5 * y;
        result.b.e34 = -0.5 * z;
        result.b.e35 = -0.5 * z;
        return result;
    }

//------------------------------------(end)---------------------------------------


//Multivector 类型数据：提取一维向量en//double coeff_en(Multivector& xl)
//-----------------------------------(start)--------------------------------------

    double coeff_n(Multivector& xl,int n)//提取向量en
    {
        double val;
        if (n == 1)
        {
            val = xl.v.e1;
            return val;
        }
        else if (n == 2)
        {
            val = xl.v.e2;
            return val;
        }
        else if (n == 3)
        {
            val = xl.v.e3;
            return val;
        }
        else
            std::cout << "暂时未实现该功能！" << std::endl;

    }
 

//------------------------------------(end)---------------------------------------


//Multivector 类型数据：提取标量//scalarpart(Multivector val)
//-----------------------------------(start)--------------------------------------

    double scalarpart(Multivector val)
    {
        double t;
        t = val.s;
        return t;

    }

//------------------------------------(end)---------------------------------------


//Multivector 类型数据：取出a中向量维度为c的部分//Multivector vectorpart(Multivector a, int c)
//-----------------------------------(start)--------------------------------------

    Multivector vectorpart(Multivector a, int c)
    {
        Multivector P;
        if (c == 1)
        {
            P.v.e1 = a.v.e1;
            P.v.e2 = a.v.e2;
            P.v.e3 = a.v.e3;
            P.v.e4 = a.v.e4;
            P.v.e5 = a.v.e5;
            P.b.e12 = 0;
            P.b.e13 = 0;
            P.b.e14 = 0;
            P.b.e15 = 0;
            P.b.e23 = 0;
            P.b.e24 = 0;
            P.b.e25 = 0;
            P.b.e34 = 0;
            P.b.e35 = 0;
            P.b.e45 = 0;
            P.t.e123 = 0;
            P.t.e124 = 0;
            P.t.e125 = 0;
            P.t.e134 = 0;
            P.t.e135 = 0;
            P.t.e145 = 0;
            P.t.e234 = 0;
            P.t.e235 = 0;
            P.t.e245 = 0;
            P.t.e345 = 0;
            P.q.e1234 = 0;
            P.q.e1235 = 0;
            P.q.e1345 = 0;
            P.q.e2345 = 0;
            P.e12345 = 0;
        }


        return P;
    }

//------------------------------------(end)---------------------------------------


//Multivector 类型数据：求A的对偶函数//Multivector anti(Multivector A)
//-----------------------------------(start)--------------------------------------


    Multivector anti(Multivector A)
    {
        Multivector I;
        I.e12345 = 1;

        A = -(geom(A, I));
        return A;
    }


//------------------------------------(end)---------------------------------------



//Multivector 类型数据：conformal
//-----------------------------------(start)--------------------------------------

    Multivector conformal(double x, double y, double z)
    {

        //ei=0.5*(e1*e1+e2*e2+e3*e3)
        //e0=1
        //e4=0.5*ei-e0
        //e5=e0+0.5*ei
        Multivector result;
        result.s =0;
        result.v.e1 = x;
        result.v.e2 = y;
        result.v.e3 = z;
        result.v.e4 = ((x * x + y * y + z * z) / 2)-0.5;
        result.v.e5 = ((x * x + y * y + z * z) / 2)+0.5;
        return result;
    }

//------------------------------------(end)---------------------------------------



} // namespace cga

#endif
