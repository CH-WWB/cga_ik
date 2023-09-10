#ifndef CGA_H
#define CGA_H

#include <cmath>
#include <iostream>

namespace cga {

    class Vector;
    class Bivector;
    class Trivector;
    class Quadvector;
    class Multivector;
    


//class Vector
//-----------------------------------(start)--------------------------------------

    class Vector {
    public:
        double e1;
        double e2;
        double e3;
        double e4;
        double e5;   
     
        //构造函数进行初始化列表
        Vector() :e1(0), e2(0), e3(0), e4(0), e5(0) {}
        Vector(double e1, double e2, double e3, double e4, double e5) : e1(e1), e2(e2), e3(e3), e4(e4), e5(e5) {}      
        
        Vector& operator+=(const Vector& other) {
            e1 += other.e1;
            e2 += other.e2;
            e3 += other.e3;
            e4 += other.e5;
            e5 += other.e5;
            return *this;
        }
        Vector& operator-=(const Vector& other) {
            e1 -= other.e1;
            e2 -= other.e2;
            e3 -= other.e3;
            e4 -= other.e4;
            e5 -= other.e5;
            return *this;
        }
        Vector& operator*=(double x) {
            e1 *= x;
            e2 *= x;
            e3 *= x;
            e4 *= x;
            e5 *= x;
            return *this;
        }
        Vector& operator/=(double x) {
            e1 /= x;
            e2 /= x;
            e3 /= x;
            e4 /= x;
            e5 /= x;
            return *this;
        }
        Vector operator-()const {
            return { -e1, -e2, -e3, -e4, -e5 };
        };
    };

    inline Vector operator+(const Vector& lhs, const Vector& rhs) {
        Vector result(lhs);
        result += rhs;
        return result;
    }
    inline Vector operator-(const Vector& lhs, const Vector& rhs) {
        Vector result(lhs);
        result -= rhs;
        return result;
    }
    inline Vector operator*(const Vector& lhs, double rhs) {
        Vector result(lhs);
        result *= rhs;
        return result;
    }
    inline Vector operator*(double lhs, const Vector& rhs) {
        return rhs * lhs;
    }
    inline Vector operator/(const Vector& lhs, double rhs) {
        Vector result(lhs);
        result /= rhs;
        return result;
    }

//------------------------------------(end)---------------------------------------


//class Bivector
//-----------------------------------(start)--------------------------------------

    class Bivector {
    public:
        double e12;
        double e13;
        double e14;
        double e15;
        double e23;
        double e24;
        double e25;       
        double e34;
        double e35;     
        double e45;
        Bivector() : e23(0), e13(0), e12(0), e15(0), e25(0), e35(0), e14(0), e24(0), e34(0), e45(0) {}
        Bivector(double e23, double e13, double e12, double e15, double e25, double e35, double e14, double e24, double e34, double e45) : e23(e23), e13(e13), e12(e12), e15(e15), e25(e25), e35(e35), e14(e14), e24(e24), e34(e34), e45(e45) {}           
        Bivector& operator+=(const Bivector& other) {
            e23 += other.e23;
            e13 += other.e13;
            e12 += other.e12;
            e15 += other.e15;
            e25 += other.e25;
            e35 += other.e35;
            e14 += other.e14;
            e24 += other.e24;
            e34 += other.e34;
            e45 += other.e45;
            return *this;
        }
        Bivector& operator-=(const Bivector& other) {
            e23 -= other.e23;
            e13 -= other.e13;
            e12 -= other.e12;
            e15 -= other.e15;
            e25 -= other.e25;
            e35 -= other.e35;
            e14 -= other.e14;
            e24 -= other.e24;
            e34 -= other.e34;
            e45 -= other.e45;
            return *this;
        }
        Bivector& operator*=(double x) {
            e23 *= x;
            e13 *= x;
            e12 *= x;
            e15 *= x;
            e25 *= x;
            e35 *= x;
            e14 *= x;
            e24 *= x;
            e34 *= x;
            e45 *= x;
            return *this;
        }
        Bivector& operator/=(double x) {
            e23 /= x;
            e13 /= x;
            e12 /= x;
            e15 /= x;
            e25 /= x;
            e35 /= x;
            e14 /= x;
            e24 /= x;
            e34 /= x;
            e45 /= x;
            return *this;
        }
        Bivector operator-()const {
            return { -e23, -e13, -e12, -e15, -e25, -e35, -e14, -e24, -e34, -e45 };
        };
    };

    inline Bivector operator+(const Bivector& lhs, const Bivector& rhs) {
        Bivector result(lhs);
        result += rhs;
        return result;
    }
    inline Bivector operator-(const Bivector& lhs, const Bivector& rhs) {
        Bivector result(lhs);
        result -= rhs;
        return result;
    }
    inline Bivector operator*(const Bivector& lhs, double rhs) {
        Bivector result(lhs);
        result *= rhs;
        return result;
    }
    inline Bivector operator*(double lhs, const Bivector& rhs) {
        return rhs * lhs;
    }
    inline Bivector operator/(const Bivector& lhs, double rhs) {
        Bivector result(lhs);
        result /= rhs;
        return result;
    }

//------------------------------------(end)---------------------------------------



//class Trivector
//-----------------------------------(start)--------------------------------------

    class Trivector {
    public:
        double e123;
        double e124;
        double e125;
        double e134;
        double e135;
        double e234;
        double e235;
        double e145;
        double e245;
        double e345;

        Trivector() : e123(0), e234(0), e134(0), e124(0), e235(0), e135(0), e125(0), e145(0), e245(0), e345(0) {}
        Trivector(double e123, double e234, double e134, double e124, double e235, double e135, double e125, double e145, double e245, double e345) : e123(e123), e234(e234), e134(e134), e124(e124), e235(e235), e135(e135), e125(e125), e145(e145), e245(e245), e345(e345) {}
        
        Trivector& operator+=(const Trivector& other) {
            e123 += other.e123;
            e234 += other.e234;
            e134 += other.e134;
            e124 += other.e124;
            e235 += other.e235;
            e135 += other.e135;
            e125 += other.e125;
            e145 += other.e145;
            e245 += other.e245;
            e345 += other.e345;
            return *this;
        }
        Trivector& operator-=(const Trivector& other) {
            e123 -= other.e123;
            e234 -= other.e234;
            e134 -= other.e134;
            e124 -= other.e124;
            e235 -= other.e235;
            e135 -= other.e135;
            e125 -= other.e125;
            e145 -= other.e145;
            e245 -= other.e245;
            e345 -= other.e345;
            return *this;
        }
        Trivector& operator*=(double x) {
            e123 *= x;
            e234 *= x;
            e134 *= x;
            e124 *= x;
            e235 *= x;
            e135 *= x;
            e125 *= x;
            e145 *= x;
            e245 *= x;
            e345 *= x;
            return *this;
        }
        Trivector& operator/=(double x) {
            e123 /= x;
            e234 /= x;
            e134 /= x;
            e124 /= x;
            e235 /= x;
            e135 /= x;
            e125 /= x;
            e145 /= x;
            e245 /= x;
            e345 /= x;
            return *this;
        }
        Trivector operator-()const {
            return { -e123, -e234, -e134, -e124, -e235, -e135, -e125, -e145, -e245, -e345 };
        };
    };

    inline Trivector operator+(const Trivector& lhs, const Trivector& rhs) {
        Trivector result(lhs);
        result += rhs;
        return result;
    }
    inline Trivector operator-(const Trivector& lhs, const Trivector& rhs) {
        Trivector result(lhs);
        result -= rhs;
        return result;
    }
    inline Trivector operator*(const Trivector& lhs, double rhs) {
        Trivector result(lhs);
        result *= rhs;
        return result;
    }
    inline Trivector operator*(double lhs, const Trivector& rhs) {
        return rhs * lhs;
    }
    inline Trivector operator/(const Trivector& lhs, double rhs) {
        Trivector result(lhs);
        result /= rhs;
        return result;
    }

//------------------------------------(end)---------------------------------------



//class Quadvector 
//-----------------------------------(start)--------------------------------------


    class Quadvector {
    public:
        double e1234;
        double e1235;        
        double e1245;
        double e1345;
        double e2345;
        Quadvector() : e1234(0), e1235(0), e2345(0), e1345(0), e1245(0) {}
        Quadvector(double e1234, double e1235, double e2345, double e1345, double e1245) : e1234(e1234), e1235(e1235), e2345(e2345), e1345(e1345), e1245(e1245) {}
        Quadvector& operator+=(const Quadvector& other) {
            e1234 += other.e1234;
            e1235 += other.e1235;
            e2345 += other.e2345;
            e1345 += other.e1345;
            e1245 += other.e1245;
            return *this;
        }
        Quadvector& operator-=(const Quadvector& other) {
            e1234 -= other.e1234;
            e1235 -= other.e1235;
            e2345 -= other.e2345;
            e1345 -= other.e1345;
            e1245 -= other.e1245;
            return *this;
        }
        Quadvector& operator*=(double x) {
            e1234 *= x;
            e1235 *= x;
            e2345 *= x;
            e1345 *= x;
            e1245 *= x;
            return *this;
        }
        Quadvector& operator/=(double x) {
            e1234 /= x;
            e1235 /= x;
            e2345 /= x;
            e1345 /= x;
            e1245 /= x;
            return *this;
        }
        Quadvector operator-()const {
            return { -e1234, -e1235, -e2345, -e1345, -e1245 };
        };
    };
    inline Quadvector operator+(const Quadvector& lhs, const Quadvector& rhs) {
        Quadvector result(lhs);
        result += rhs;
        return result;
    }
    inline Quadvector operator-(const Quadvector& lhs, const Quadvector& rhs) {
        Quadvector result(lhs);
        result -= rhs;
        return result;
    }
    inline Quadvector operator*(const Quadvector& lhs, double rhs) {
        Quadvector result(lhs);
        result *= rhs;
        return result;
    }
    inline Quadvector operator*(double lhs, const Quadvector& rhs) {
        return rhs * lhs;
    }
    inline Quadvector operator/(const Quadvector& lhs, double rhs) {
        Quadvector result(lhs);
        result /= rhs;
        return result;
    }

//------------------------------------(end)---------------------------------------



// class Multivector
//-----------------------------------(start)--------------------------------------

    class Multivector {
    public:
        double s;
        Vector v;
        Bivector b;
        Trivector t;
        Quadvector q;
        double e12345;

        Multivector() : s(), v(), b(), t(), q(), e12345() {}//定义默认构造函数
        
        //非默认构造函数
        Multivector(double s, const Vector& v, const Bivector& b, const Trivector& t, const Quadvector& q, double e12345): s(s), v(v), b(b), t(t), q(q), e12345(e12345) {}
        Multivector(const Vector& v) : s(0), v(v), b(), t(), q(), e12345(0) {}//继承，该类中只有Vector参数
        Multivector(const Bivector& b) : s(0), v(), b(b), t(), q(), e12345(0) {}
        Multivector(const Trivector& t) : s(0), v(), b(), t(t), q(), e12345(0) {}
        Multivector(const Quadvector& q) : s(0), v(), b(), t(), q(q), e12345(0) {}

        Multivector& operator+=(const double& other) {
            s = this->s + other;
            v = this->v;
            b = this->b;
            t = this->t;
            q = this->q;
            e12345 = this->e12345;
            return *this;
        }
        
        Multivector& operator+=(const Multivector& other) {
            s += other.s;
            v += other.v;
            b += other.b;
            t += other.t;
            q += other.q;
            e12345 += other.e12345;
            return *this;
        }
        Multivector& operator-=(const double& other) {
            s = this->s - other;
            v = this->v;
            b = this->b;
            t = this->t;
            q = this->q;
            e12345 = this->e12345;
            return *this;
        }
        Multivector& operator-=(const Multivector& other) {
            s -= other.s;
            v -= other.v;
            b -= other.b;
            t -= other.t;
            q -= other.q;
            e12345 -= other.e12345;
            return *this;
        }
        Multivector& operator*=(double x) {
            s *= x;
            v *= x;
            b *= x;
            t *= x;
            q *= x;
            e12345 *= x;
            return *this;
        }
        Multivector& operator/=(double x) {
            s /= x;
            v /= x;
            b /= x;
            t /= x;
            q /= x;
            e12345 /= x;
            return *this;
        }
        Multivector operator-()const {
            return { -s, -v, -b, -t, -q, -e12345 };
        };
    };
    inline Multivector operator+(const Multivector& lhs, const Multivector& rhs) {
        Multivector result(lhs);
        result += rhs;
        return result;
    }
    inline Multivector operator+(const Multivector& lhs, const double& rhs) {
        Multivector result(lhs);
        result += rhs;
        return result;
    }
    inline Multivector operator+(const double& rhs, const Multivector& lhs) {
        Multivector result(lhs);
        result += rhs;
        return result;
    }
    inline Multivector operator-(const Multivector& lhs, const double& rhs) {
        Multivector result(lhs);
        result -= rhs;
        return result;
    }
    inline Multivector operator-(const double& rhs, const Multivector& lhs) {
        Multivector result(lhs);
        result -= rhs;
        return result;
    }
    inline Multivector operator-(const Multivector& lhs, const Multivector& rhs) {
        Multivector result(lhs);
        result -= rhs;
        return result;
    }
    inline Multivector operator*(const Multivector& lhs, double rhs) {
        Multivector result(lhs);
        result *= rhs;
        return result;
    }
    inline Multivector operator*(double lhs, const Multivector& rhs) {
        return rhs * lhs;
    }
    inline Multivector operator/(const Multivector& lhs, double rhs) {
        Multivector result(lhs);
        result /= rhs;
        return result;
    }

//------------------------------------(end)---------------------------------------
    
    
    
    Bivector  geom(const Vector& lhs, const Vector& rhs);//几何积
    Multivector geom(const Multivector& lhs, const Multivector& rhs);
    Multivector inner(const Multivector& lhs, const Multivector& rhs);//内积
    Multivector outer(const Multivector& lhs, const Multivector& rhs);//外积
    Multivector reverse(const Multivector& x);

    std::ostream& operator<<(std::ostream& outs, const Vector& x);
    std::ostream& operator<<(std::ostream& outs, const Bivector& x);
    std::ostream& operator<<(std::ostream& outs, const Trivector& x);
    std::ostream& operator<<(std::ostream& outs, const Quadvector& x);
    std::ostream& operator<<(std::ostream& outs, const Multivector& x);

    //execute.h
    Multivector make_rotation(double theta, Bivector axis);
    Multivector make_translation(double x, double y, double z);
    double coeff_n(Multivector& xl,int n);
    double scalarpart(Multivector val);
    Multivector vectorpart(Multivector a, int c);
    Multivector anti(Multivector A);
    Multivector conformal(double x, double y, double z);
} // namespace cga

#endif
