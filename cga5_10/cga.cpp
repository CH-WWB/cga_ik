#include "cga.h"


namespace cga
{

//Bivector geom(const Vector& lhs, const Vector& rhs) 几何积
//-----------------------------------(start)--------------------------------------

    Bivector geom(const Vector& lhs, const Vector& rhs)
    {
        Bivector result;


        result.e14 = lhs.e1 * rhs.e4 - lhs.e4 * rhs.e1;
        result.e24 = lhs.e2 * rhs.e4 - lhs.e4 * rhs.e2;
        result.e34 = lhs.e3 * rhs.e4 - lhs.e4 * rhs.e3;
        result.e15 = lhs.e1 * rhs.e5 - lhs.e5 * rhs.e1;
        result.e25 = lhs.e2 * rhs.e5 - lhs.e5 * rhs.e2;
        result.e35 = lhs.e3 * rhs.e5 - lhs.e5 * rhs.e3;
        result.e45 = lhs.e4 * rhs.e5 - lhs.e5 * rhs.e4;
        //result.e12 
        result.e12 = lhs.e1 * rhs.e2 - lhs.e2 * rhs.e1;
        //result.e13
        result.e13 = lhs.e1 * rhs.e3 - lhs.e3 * rhs.e1;
        //result.e23
        result.e23 = lhs.e2 * rhs.e3 - lhs.e3 * rhs.e2;

        return result;
    }

//------------------------------------(end)---------------------------------------



//Multivector outer(const Multivector& lhs, const Multivector& rhs) 外积
//-----------------------------------(start)--------------------------------------
    Multivector outer(const Multivector& lhs, const Multivector& rhs)
    { 
        Multivector result;
       
    //二维
    //-----------------------------------(start)--------------------------------------

        //result.b.e12
        result.b.e12 =
            lhs.s * rhs.b.e12 +
            lhs.b.e12 * rhs.s +
            lhs.v.e1 * rhs.v.e2 -
            lhs.v.e2 * rhs.v.e1;

        //result.b.e13
        result.b.e13 =
            lhs.s * rhs.b.e13 +
            lhs.b.e13 * rhs.s +
            lhs.v.e1 * rhs.v.e3 -
            lhs.v.e3 * rhs.v.e1;

        //result.b.e14         
        result.b.e14 =
            lhs.s * rhs.b.e14 +
            lhs.b.e14 * rhs.s +
            lhs.v.e1 * rhs.v.e4 -
            lhs.v.e4 * rhs.v.e1;

        //result.b.e15   
        result.b.e15 =
            lhs.s * rhs.b.e15 +
            rhs.s * lhs.b.e15 +
            lhs.v.e1 * rhs.v.e5 -
            lhs.v.e5 * rhs.v.e1;


        //result.b.e23
   

        result.b.e23 =
            lhs.s * rhs.b.e23 +
            rhs.s * lhs.b.e23 +
            lhs.v.e2 * rhs.v.e3 
            -lhs.v.e3 * rhs.v.e2;

        //result.b.e24 
        result.b.e24 =
            lhs.s * rhs.b.e24 +
            rhs.s * lhs.b.e24 +
            lhs.v.e2 * rhs.v.e4 -
            lhs.v.e4 * rhs.v.e2;

        //result.b.e25
        result.b.e25 =
            lhs.s * rhs.b.e25 +
            rhs.s * lhs.b.e25 +
            lhs.v.e2 * rhs.v.e5 -
            lhs.v.e5 * rhs.v.e2;

        //result.b.e34 
        result.b.e34 =
            lhs.s * rhs.b.e34 +
            rhs.s * lhs.b.e34 +
            lhs.v.e3 * rhs.v.e4 -
            lhs.v.e4 * rhs.v.e3;

        //result.b.e35
        result.b.e35 =
            lhs.s * rhs.b.e35 +
            rhs.s * lhs.b.e35 +
            lhs.v.e3 * rhs.v.e5 -
            lhs.v.e5 * rhs.v.e3;

        //result.b.e45 
        result.b.e45 =
            lhs.s * rhs.b.e45 +
            rhs.s * lhs.b.e45
            + lhs.v.e4 * rhs.v.e5
            - lhs.v.e5 * rhs.v.e4;

    //------------------------------------(end)---------------------------------------

    //三维
    //-----------------------------------(start)--------------------------------------

        result.t.e123 =
            lhs.b.e12 * rhs.v.e3
            + lhs.b.e23 * rhs.v.e1
            - lhs.b.e13 * rhs.v.e2
            + lhs.v.e3 * rhs.b.e12
            + lhs.v.e1 * rhs.b.e23
            - lhs.v.e2 * rhs.b.e13
            + lhs.s * rhs.t.e123
            + lhs.t.e123 * rhs.s;

        result.t.e124 =
            lhs.v.e1 * rhs.b.e24
            + lhs.b.e24 * rhs.v.e1
            - lhs.v.e2 * rhs.b.e14
            - lhs.b.e14 * rhs.v.e2
            + lhs.v.e4 * rhs.b.e12
            + lhs.b.e12 * rhs.v.e4;

        result.t.e125 =
            lhs.b.e25 * rhs.v.e1
            + lhs.v.e1 * rhs.b.e25
            - lhs.b.e15 * rhs.v.e2
            - lhs.v.e2 * rhs.b.e15
            + lhs.b.e12 * rhs.v.e5
            + lhs.v.e5 * rhs.b.e12;

        result.t.e134 =
            +lhs.b.e34 * rhs.v.e1
            + lhs.v.e1 * rhs.b.e34
            - lhs.b.e14 * rhs.v.e3
            - lhs.v.e3 * rhs.b.e14
            + lhs.b.e13 * rhs.v.e4
            + lhs.v.e4 * rhs.b.e13;

        result.t.e135 =
            lhs.v.e1 * rhs.b.e35
            + lhs.b.e35 * rhs.v.e1
            - lhs.v.e3 * rhs.b.e15
            - lhs.b.e15 * rhs.v.e3
            + lhs.v.e5 * rhs.b.e13
            + lhs.b.e13 * rhs.v.e5;

        result.t.e234 =
            lhs.b.e34 * rhs.v.e2
            + lhs.v.e2 * rhs.b.e34
            - lhs.b.e24 * rhs.v.e3
            - lhs.v.e3 * rhs.b.e24
            + lhs.b.e23 * rhs.v.e4;
            +lhs.v.e4 * rhs.b.e23;

        result.t.e235 =
            -lhs.v.e3 * rhs.b.e25
            - lhs.b.e25 * rhs.v.e3
            + lhs.v.e2 * rhs.b.e35
            + lhs.b.e35 * rhs.v.e2
            + lhs.v.e5 * rhs.b.e23
            + lhs.b.e23 * rhs.v.e5;

        result.t.e145 =
            lhs.b.e45 * rhs.v.e1
            + lhs.v.e1 * rhs.b.e45
            + lhs.b.e14 * rhs.v.e5
            + lhs.v.e5 * rhs.b.e14
            - lhs.b.e15 * rhs.v.e4
            - lhs.v.e4 * rhs.b.e15;

        result.t.e245 =
            lhs.b.e45 * rhs.v.e2
            + lhs.v.e2 * rhs.b.e45
            + lhs.b.e24 * rhs.v.e5
            + lhs.v.e5 * rhs.b.e24
            - lhs.b.e25 * rhs.v.e4
            - lhs.v.e4 * rhs.b.e25;

        result.t.e345 =
            lhs.b.e45 * rhs.v.e3
            + lhs.v.e3 * rhs.b.e45
            + lhs.b.e34 * rhs.v.e5
            + lhs.v.e5 * rhs.b.e34
            - lhs.b.e35 * rhs.v.e4
            - lhs.v.e4 * rhs.b.e35;

    //------------------------------------(end)---------------------------------------

    //四维
    //-----------------------------------(start)--------------------------------------

        result.q.e1234 =
            lhs.b.e12 * rhs.b.e34
            + lhs.b.e34 * rhs.b.e12
            - lhs.b.e13 * rhs.b.e24
            - lhs.b.e24 * rhs.b.e13
            + lhs.b.e14 * rhs.b.e23
            + lhs.b.e23 * rhs.b.e14
            + lhs.q.e1234 * rhs.s
            + lhs.s * rhs.q.e1234
            + lhs.v.e1 * rhs.t.e234
            - lhs.t.e234 * rhs.v.e1
            - lhs.v.e2 * rhs.t.e134
            + lhs.t.e134 * rhs.v.e2
            + lhs.v.e3 * rhs.t.e124
            - lhs.t.e124 * rhs.v.e3
            + lhs.t.e123 * rhs.v.e4
            - lhs.v.e4 * rhs.t.e123;

        result.q.e1235 =
            lhs.b.e12 * rhs.b.e35
            + lhs.b.e35 * rhs.b.e12
            - lhs.b.e13 * rhs.b.e25
            - lhs.b.e25 * rhs.b.e13
            + lhs.b.e15 * rhs.b.e23
            + lhs.b.e23 * rhs.b.e15
            + lhs.q.e1235 * rhs.s
            + lhs.s * rhs.q.e1235
            + lhs.v.e1 * rhs.t.e235
            - lhs.t.e235 * rhs.v.e1
            - lhs.v.e2 * rhs.t.e135
            + lhs.t.e135 * rhs.v.e2
            + lhs.v.e3 * rhs.t.e125
            - lhs.t.e125 * rhs.v.e3
            + lhs.t.e123 * rhs.v.e5
            - lhs.v.e5 * rhs.t.e123;

        result.q.e1245 =
            lhs.b.e12 * rhs.b.e45
            + lhs.b.e45 * rhs.b.e12
            - lhs.b.e14 * rhs.b.e25
            + lhs.b.e15 * rhs.b.e24
            - lhs.b.e25 * rhs.b.e14
            + lhs.b.e24 * rhs.b.e15
            + lhs.q.e1245 * rhs.s
            + lhs.s * rhs.q.e1245
            + lhs.v.e1 * rhs.t.e245
            - lhs.t.e245 * rhs.v.e1
            - lhs.v.e2 * rhs.t.e145
            + lhs.t.e145 * rhs.v.e2
            + lhs.v.e4 * rhs.t.e125
            - lhs.t.e125 * rhs.v.e4
            - lhs.v.e5 * rhs.t.e124
            + lhs.t.e124 * rhs.v.e5;

        result.q.e1345 =
            -lhs.b.e14 * rhs.b.e35
            + lhs.b.e13 * rhs.b.e45
            - lhs.b.e35 * rhs.b.e14
            + lhs.b.e45 * rhs.b.e13
            + lhs.q.e1345 * rhs.s
            + lhs.s * rhs.q.e1345
            - lhs.t.e135 * rhs.v.e4
            - lhs.t.e345 * rhs.v.e1
            - lhs.v.e3 * rhs.t.e145
            - lhs.v.e5 * rhs.t.e134
            + lhs.b.e15 * rhs.b.e34
            + lhs.b.e34 * rhs.b.e15
            + lhs.t.e145 * rhs.v.e3
            + lhs.t.e134 * rhs.v.e5
            + lhs.v.e1 * rhs.t.e345
            + lhs.v.e4 * rhs.t.e135;

        result.q.e2345 =
            lhs.b.e23 * rhs.b.e45
            + lhs.b.e25 * rhs.b.e34
            + lhs.b.e34 * rhs.b.e25
            + lhs.b.e45 * rhs.b.e23
            - lhs.b.e24 * rhs.b.e35
            - lhs.b.e35 * rhs.b.e24
            + lhs.q.e2345 * rhs.s
            + lhs.s * rhs.q.e2345
            +lhs.v.e2 * rhs.t.e345
            - lhs.v.e3 * rhs.t.e245
            + lhs.v.e4 * rhs.t.e235
            - lhs.v.e5 * rhs.t.e234
            + lhs.t.e234 * rhs.v.e5
            - lhs.t.e345 * rhs.v.e2
            - lhs.t.e235 * rhs.v.e4
            + lhs.t.e245 * rhs.v.e3;

    //------------------------------------(end)---------------------------------------

        return result;
    }


//------------------------------------(end)---------------------------------------



//Multivector inner(const Multivector& lhs, const Multivector& rhs) 内积
//-----------------------------------(start)--------------------------------------

    Multivector inner(const Multivector& lhs, const Multivector& rhs)
    {

        Multivector  result;
        result.s =
            +lhs.v.e1 * rhs.v.e1
            + lhs.v.e2 * rhs.v.e2
            + lhs.v.e3 * rhs.v.e3
            + lhs.v.e4 * rhs.v.e4
            - lhs.v.e5 * rhs.v.e5
            - lhs.b.e12 * rhs.b.e12
            - lhs.b.e13 * rhs.b.e13
            - lhs.b.e14 * rhs.b.e14
            + lhs.b.e15 * rhs.b.e15
            - lhs.b.e23 * rhs.b.e23
            - lhs.b.e24 * rhs.b.e24
            + lhs.b.e25 * rhs.b.e25
            - lhs.b.e34 * rhs.b.e34
            + lhs.b.e35 * rhs.b.e35
            + lhs.b.e45 * rhs.b.e45;

        result.v.e1 =
            -lhs.v.e3 * rhs.b.e13
            -lhs.v.e4 * rhs.b.e14
            + lhs.v.e5 * rhs.b.e15;

        result.v.e2 =
            -lhs.v.e3 * rhs.b.e23
            -lhs.v.e4 * rhs.b.e24
            + lhs.v.e5 * rhs.b.e25;
        result.v.e3 =
            -lhs.v.e4 * rhs.b.e34
            + lhs.v.e5 * rhs.b.e35;

        result.v.e4 =
            +lhs.v.e3 * rhs.b.e34
            +lhs.v.e5 * rhs.b.e45;

        result.v.e5 =
            +lhs.v.e3 * rhs.b.e35
            +lhs.v.e4 * rhs.b.e45;

        return result;
    }

//------------------------------------(end)---------------------------------------



//Multivector geom(const Multivector& lhs, const Multivector& rhs) 几何积 
//-----------------------------------(start)--------------------------------------

    Multivector geom(const Multivector& lhs, const Multivector& rhs)
    {
        Multivector result;  

    //一维
    //-----------------------------------(start)--------------------------------------

            result.s = lhs.s * rhs.s +
                lhs.v.e1 * rhs.v.e1 +
                lhs.v.e2 * rhs.v.e2 +
                lhs.v.e3 * rhs.v.e3 -
                lhs.b.e12 * rhs.b.e12 -
                lhs.b.e13 * rhs.b.e13 -
                lhs.b.e23 * rhs.b.e23 -
                lhs.b.e14 * rhs.b.e14 -
                lhs.b.e24 * rhs.b.e24 -
                lhs.b.e34 * rhs.b.e34 +
                lhs.b.e15 * rhs.b.e15 +
                lhs.b.e25 * rhs.b.e25 +
                lhs.b.e35 * rhs.b.e35;

            //result.v.e1
            result.v.e1 =
                lhs.s * rhs.v.e1
                + lhs.v.e1 * rhs.s
                + lhs.b.e12 * rhs.v.e2
                - lhs.v.e2 * rhs.b.e12
                + lhs.b.e13 * rhs.v.e3
                - lhs.v.e3 * rhs.b.e13
                - lhs.b.e15 * rhs.v.e5
                + lhs.v.e5 * rhs.b.e15
                + lhs.b.e14 * rhs.v.e4
                - lhs.v.e4 * rhs.b.e14
                - lhs.t.e123 * rhs.b.e23
                - lhs.b.e23 * rhs.t.e123
                - lhs.t.e124 * rhs.b.e24
                - lhs.b.e24 * rhs.t.e124
                + lhs.t.e125 * rhs.b.e25
                + lhs.b.e25 * rhs.t.e125
                - lhs.t.e134 * rhs.b.e34
                - lhs.b.e34 * rhs.t.e134
                + lhs.t.e135 * rhs.b.e35
                + lhs.b.e35 * rhs.t.e135
                + lhs.q.e1235 * rhs.t.e235
                - lhs.t.e235 * rhs.q.e1235
                - lhs.q.e1234 * rhs.t.e234
                + lhs.t.e234 * rhs.q.e1234
                - lhs.e12345 * rhs.q.e2345
                - lhs.q.e2345 * rhs.e12345;

            result.v.e2 =
                lhs.s * rhs.v.e2
                + lhs.v.e2 * rhs.s
                + lhs.v.e1 * rhs.b.e12
                - lhs.b.e12 * rhs.v.e1
                + lhs.b.e23 * rhs.v.e3
                - lhs.v.e3 * rhs.b.e23
                + lhs.b.e24 * rhs.v.e4
                - lhs.v.e4 * rhs.b.e24
                - lhs.b.e25 * rhs.v.e5
                + lhs.v.e5 * rhs.b.e25
                + lhs.t.e123 * rhs.b.e13
                + lhs.b.e13 * rhs.t.e123
                + lhs.t.e124 * rhs.b.e14
                + lhs.b.e14 * rhs.t.e124
                - lhs.t.e125 * rhs.b.e15
                - lhs.b.e15 * rhs.t.e125
                - lhs.t.e234 * rhs.b.e34
                - lhs.b.e34 * rhs.t.e234
                + lhs.t.e235 * rhs.b.e35
                + lhs.b.e35 * rhs.t.e235
                + lhs.q.e1234 * rhs.t.e134
                - lhs.t.e134 * rhs.q.e1234
                - lhs.q.e1235 * rhs.t.e135
                + lhs.t.e135 * rhs.q.e1234
                + lhs.e12345 * rhs.q.e1345
                + lhs.q.e1345 * rhs.e12345;


            result.v.e3 =
                lhs.s * rhs.v.e3
                + lhs.v.e3 * rhs.s
                - lhs.b.e13 * rhs.v.e1
                + lhs.v.e1 * rhs.b.e13
                - lhs.b.e23 * rhs.v.e2
                + lhs.v.e2 * rhs.b.e23
                + lhs.b.e34 * rhs.v.e4
                - lhs.v.e4 * rhs.b.e34
                + lhs.v.e5 * rhs.b.e35
                - lhs.b.e35 * rhs.v.e5
                - lhs.t.e123 * rhs.b.e12
                - lhs.b.e12 * rhs.t.e123
                - lhs.t.e135 * rhs.b.e15
                - lhs.b.e15 * rhs.t.e135
                + lhs.t.e134 * rhs.b.e14
                + lhs.b.e14 * rhs.t.e134
                - lhs.t.e235 * rhs.b.e25
                - lhs.b.e25 * rhs.t.e235
                + lhs.t.e234 * rhs.b.e24
                + lhs.b.e24 * rhs.t.e234
                - lhs.q.e1234 * rhs.t.e124
                + lhs.t.e124 * rhs.q.e1234
                + lhs.q.e1235 * rhs.t.e125
                - lhs.t.e125 * rhs.q.e1235
                - lhs.e12345 * rhs.q.e1245
                - lhs.q.e1245 * rhs.e12345;


            result.v.e4 =
                lhs.v.e4 * rhs.s
                + lhs.s * rhs.v.e4
                - lhs.b.e14 * rhs.v.e1
                + lhs.v.e1 * rhs.b.e14
                - lhs.b.e24 * rhs.v.e2
                + lhs.v.e2 * rhs.b.e24
                - lhs.b.e34 * rhs.v.e3
                + lhs.v.e3 * rhs.b.e34
                + lhs.v.e5 * rhs.b.e45
                - lhs.b.e45 * rhs.v.e5
                - lhs.t.e124 * rhs.b.e12
                - lhs.b.e12 * rhs.t.e124
                - lhs.t.e134 * rhs.b.e13
                - lhs.b.e13 * rhs.t.e134
                - lhs.t.e234 * rhs.b.e23
                - lhs.b.e23 * rhs.t.e234
                - lhs.t.e145 * rhs.b.e15
                - lhs.b.e15 * rhs.t.e145
                - lhs.t.e245 * rhs.b.e25
                - lhs.b.e25 * rhs.t.e245
                - lhs.t.e345 * rhs.b.e35
                - lhs.b.e35 * rhs.t.e345
                + lhs.q.e1234 * rhs.t.e123
                - lhs.t.e123 * rhs.q.e1234
                + lhs.e12345 * rhs.q.e1235
                + lhs.q.e1235 * rhs.e12345;

            result.v.e5 =
                lhs.v.e5 * rhs.s
                + lhs.s * rhs.v.e5
                - lhs.b.e15 * rhs.v.e1
                + lhs.v.e1 * rhs.b.e15
                - lhs.b.e25 * rhs.v.e2
                + lhs.v.e2 * rhs.b.e25
                - lhs.b.e35 * rhs.v.e3
                + lhs.v.e3 * rhs.b.e35
                + lhs.v.e4 * rhs.b.e45
                - lhs.b.e45 * rhs.v.e4
                - lhs.t.e125 * rhs.b.e12
                - lhs.b.e12 * rhs.t.e125
                - lhs.t.e135 * rhs.b.e13
                - lhs.b.e13 * rhs.t.e135
                - lhs.t.e235 * rhs.b.e23
                - lhs.b.e23 * rhs.t.e235
                - lhs.t.e145 * rhs.b.e14
                - lhs.b.e14 * rhs.t.e145
                - lhs.t.e245 * rhs.b.e24
                - lhs.b.e24 * rhs.t.e245
                - lhs.t.e345 * rhs.b.e34
                - lhs.b.e34 * rhs.t.e345
                + lhs.q.e1235 * rhs.t.e123
                - lhs.t.e123 * rhs.q.e1235
                + lhs.e12345 * rhs.q.e1234
                + lhs.q.e1234 * rhs.e12345;

    //------------------------------------(end)---------------------------------------

    //二维
    //-----------------------------------(start)--------------------------------------

              //result.b.e12
            result.b.e12 =
                lhs.s * rhs.b.e12 +
                lhs.b.e12 * rhs.s +
                lhs.v.e1 * rhs.v.e2 -
                lhs.v.e2 * rhs.v.e1 -
                lhs.b.e13 * rhs.b.e23 +
                lhs.b.e23 * rhs.b.e13
                + lhs.t.e345 * rhs.e12345;


            //result.b.e13
            result.b.e13 = lhs.s * rhs.b.e13 +
                lhs.b.e13 * rhs.s +
                lhs.v.e1 * rhs.v.e3 -
                lhs.v.e3 * rhs.v.e1 +
                lhs.b.e12 * rhs.b.e23 -
                lhs.b.e23 * rhs.b.e12
                - lhs.t.e245 * rhs.e12345;


            //result.b.e14         
            result.b.e14 =
                lhs.s * rhs.b.e14 +
                lhs.b.e14 * rhs.s +
                lhs.v.e1 * rhs.v.e4 -
                lhs.v.e4 * rhs.v.e1 +
                lhs.b.e12 * rhs.b.e24
                - lhs.b.e24 * rhs.b.e12
                + lhs.b.e13 * rhs.b.e34
                - lhs.b.e34 * rhs.b.e13
                - lhs.q.e1234 * rhs.b.e23
                - lhs.b.e23 * rhs.q.e1234
                + lhs.t.e235 * rhs.e12345;


            //result.b.e15   
            result.b.e15 =
                lhs.s * rhs.b.e15 +
                rhs.s * lhs.b.e15 +
                lhs.v.e1 * rhs.v.e5 -
                lhs.v.e5 * rhs.v.e1 +
                lhs.b.e12 * rhs.b.e25 -
                lhs.b.e25 * rhs.b.e12 +
                lhs.b.e13 * rhs.b.e35 -
                lhs.b.e35 * rhs.b.e13 -

                lhs.q.e1235 * rhs.b.e23 -
                lhs.b.e23 * rhs.q.e1235
                + lhs.t.e234 * rhs.e12345;


            //result.b.e23
            result.b.e23 =
                lhs.s * rhs.b.e23 +
                rhs.s * lhs.b.e23 +
                lhs.v.e2 * rhs.v.e3 -
                lhs.v.e3 * rhs.v.e2 -
                lhs.b.e12 * rhs.b.e13 +
                lhs.b.e13 * rhs.b.e12
                + lhs.t.e145 * rhs.e12345;


            //result.b.e24 
            result.b.e24 =
                lhs.s * rhs.b.e24 +
                rhs.s * lhs.b.e24 +
                lhs.v.e2 * rhs.v.e4 -
                lhs.v.e4 * rhs.v.e2
                - lhs.b.e12 * rhs.b.e14
                + lhs.b.e14 * rhs.b.e12
                + lhs.b.e23 * rhs.b.e34
                - lhs.b.e34 * rhs.b.e23
                + lhs.q.e1234 * rhs.b.e13
                + lhs.b.e13 * rhs.q.e1234
                - lhs.t.e135 * rhs.e12345;


            //result.b.e25
            result.b.e25 = lhs.s * rhs.b.e25 +
                rhs.s * lhs.b.e25 +
                lhs.v.e2 * rhs.v.e5 -
                lhs.v.e5 * rhs.v.e2 -
                lhs.b.e12 * rhs.b.e15 +
                lhs.b.e15 * rhs.b.e12 +
                lhs.b.e23 * rhs.b.e35 -
                lhs.b.e35 * rhs.b.e23 +
                lhs.q.e1235 * rhs.b.e13 +
                lhs.b.e13 * rhs.q.e1235
                - lhs.t.e134 * rhs.e12345;


            //result.b.e34 
            result.b.e34 =
                lhs.s * rhs.b.e34 +
                rhs.s * lhs.b.e34 +
                lhs.v.e3 * rhs.v.e4 -
                lhs.v.e4 * rhs.v.e3 -
                lhs.b.e13 * rhs.b.e14 +
                lhs.b.e14 * rhs.b.e13 -
                lhs.b.e23 * rhs.b.e24 +
                lhs.b.e24 * rhs.b.e23 -
                lhs.q.e1234 * rhs.b.e12 -
                lhs.b.e12 * rhs.q.e1234
                + lhs.t.e125 * rhs.e12345;

            //result.b.e35
            result.b.e35 =
                lhs.s * rhs.b.e35 +
                rhs.s * lhs.b.e35 +
                lhs.v.e3 * rhs.v.e5 -
                lhs.v.e5 * rhs.v.e3 -
                lhs.b.e13 * rhs.b.e15 +
                lhs.b.e15 * rhs.b.e13 -
                lhs.b.e23 * rhs.b.e25 +
                lhs.b.e25 * rhs.b.e23 -
                lhs.q.e1235 * rhs.b.e12 -
                lhs.b.e12 * rhs.q.e1235
                + lhs.t.e124 * rhs.e12345;


            //result.b.e45 
            result.b.e45 =
                lhs.s * rhs.b.e45 +
                rhs.s * lhs.b.e45
                + lhs.v.e4 * rhs.v.e5
                - lhs.v.e5 * rhs.v.e4

                - lhs.b.e14 * rhs.b.e15 +
                lhs.b.e15 * rhs.b.e14
                - lhs.b.e24 * rhs.b.e25 +
                lhs.b.e25 * rhs.b.e24
                - lhs.b.e34 * rhs.b.e35 +
                lhs.b.e35 * rhs.b.e34
                - lhs.q.e1235 * rhs.q.e1234 +
                lhs.q.e1234 * rhs.q.e1235

                - lhs.q.e2345 * rhs.b.e23
                - lhs.b.e23 * rhs.q.e2345
                - lhs.q.e1345 * rhs.b.e13
                - lhs.b.e13 * rhs.q.e1345
                - lhs.q.e1245 * rhs.b.e12
                - lhs.b.e12 * rhs.q.e1245
                - lhs.t.e123 * rhs.e12345
                - lhs.e12345 * rhs.t.e123;

    //------------------------------------(end)---------------------------------------

    //三维
    //-----------------------------------(start)--------------------------------------

            result.t.e123 = lhs.b.e12 * rhs.v.e3
                + lhs.b.e23 * rhs.v.e1
                - lhs.b.e13 * rhs.v.e2
                + lhs.v.e3 * rhs.b.e12
                + lhs.v.e1 * rhs.b.e23
                - lhs.v.e2 * rhs.b.e13
                + lhs.s * rhs.t.e123
                + lhs.t.e123 * rhs.s
                - lhs.t.e124 * rhs.b.e34
                + lhs.b.e34 * rhs.t.e124
                + lhs.t.e125 * rhs.b.e35
                - lhs.b.e35 * rhs.t.e125
                + lhs.t.e134 * rhs.b.e24
                - lhs.b.e24 * rhs.t.e134
                - lhs.t.e135 * rhs.b.e25
                + lhs.b.e25 * rhs.t.e135
                - lhs.t.e234 * rhs.b.e14
                + lhs.b.e14 * rhs.t.e234
                + lhs.t.e235 * rhs.b.e15
                - lhs.b.e15 * rhs.t.e235
                + lhs.q.e1234 * rhs.v.e4
                - lhs.q.e1235 * rhs.v.e5
                + rhs.q.e1234 * lhs.v.e4
                - rhs.q.e1235 * lhs.v.e5;

            result.t.e124 = 
                lhs.v.e1 * rhs.b.e24
                + lhs.b.e24 * rhs.v.e1
                - lhs.v.e2 * rhs.b.e14
                - lhs.b.e14 * rhs.v.e2
                + lhs.v.e4 * rhs.b.e12
                + lhs.b.e12 * rhs.v.e4
                -lhs.q.e1234 * rhs.v.e3
                + lhs.v.e3 * rhs.q.e1234;
               

            result.t.e125 = lhs.b.e25 * rhs.v.e1
                + lhs.v.e1 * rhs.b.e25
                - lhs.b.e15 * rhs.v.e2
                - lhs.v.e2 * rhs.b.e15
                - lhs.q.e1235 * rhs.v.e3
                + lhs.v.e3 * rhs.q.e1235
                + lhs.b.e12 * rhs.v.e5
                + lhs.v.e5 * rhs.b.e12;

            result.t.e134 = +lhs.b.e34 * rhs.v.e1
                + lhs.v.e1 * rhs.b.e34
                + lhs.q.e1234 * rhs.v.e2
                - lhs.v.e2 * rhs.q.e1234
                - lhs.b.e14 * rhs.v.e3
                - lhs.v.e3 * rhs.b.e14
                + lhs.b.e13 * rhs.v.e4
                + lhs.v.e4 * rhs.b.e13;

            result.t.e135 = lhs.v.e1 * rhs.b.e35
                + lhs.b.e35 * rhs.v.e1
                - lhs.v.e3 * rhs.b.e15
                - lhs.b.e15 * rhs.v.e3
                + lhs.v.e5 * rhs.b.e13
                + lhs.b.e13 * rhs.v.e5
                + lhs.q.e1235 * rhs.v.e2
                - lhs.v.e2 * rhs.q.e1235;

            result.t.e234 =
                -lhs.q.e1234 * rhs.v.e1
                + lhs.v.e1 * rhs.q.e1234
                + lhs.b.e34 * rhs.v.e2
                + lhs.v.e2 * rhs.b.e34
                - lhs.b.e24 * rhs.v.e3
                - lhs.v.e3 * rhs.b.e24
                + lhs.b.e23 * rhs.v.e4;
                +lhs.v.e4 * rhs.b.e23;

            result.t.e235 = -lhs.v.e3 * rhs.b.e25
                - lhs.b.e25 * rhs.v.e3
                + lhs.v.e2 * rhs.b.e35
                + lhs.b.e35 * rhs.v.e2
                + lhs.v.e5 * rhs.b.e23
                + lhs.b.e23 * rhs.v.e5
                - lhs.q.e1235 * rhs.v.e1
                + lhs.v.e1 * rhs.q.e1235;

            result.t.e145 =
                lhs.b.e45 * rhs.v.e1
                + lhs.v.e1 * rhs.b.e45
                + lhs.b.e14 * rhs.v.e5
                + lhs.v.e5 * rhs.b.e14
                - lhs.b.e15 * rhs.v.e4
                - lhs.v.e4 * rhs.b.e15
                - lhs.t.e124 * rhs.b.e25
                + lhs.b.e25 * rhs.t.e124
                - lhs.t.e125 * rhs.b.e24
                + lhs.b.e24 * rhs.t.e125
                + lhs.t.e134 * rhs.b.e34
                - lhs.b.e34 * rhs.t.e134
                - lhs.t.e134 * rhs.b.e35
                + lhs.b.e35 * rhs.t.e134
                + lhs.q.e1245 * rhs.v.e2
                - lhs.v.e2 * rhs.q.e1245
                + lhs.q.e1345 * rhs.v.e3
                - lhs.v.e3 * rhs.q.e1345
                - lhs.q.e1235 * rhs.t.e234
                - lhs.t.e234 * rhs.q.e1235
                + lhs.q.e1234 * rhs.t.e235
                + lhs.t.e235 * rhs.q.e1234
                - lhs.t.e123 * rhs.q.e2345
                - lhs.q.e2345 * rhs.t.e123;

            result.t.e245 =
                lhs.b.e45 * rhs.v.e2
                + lhs.v.e2 * rhs.b.e45
                + lhs.b.e24 * rhs.v.e5
                + lhs.v.e5 * rhs.b.e24
                - lhs.b.e25 * rhs.v.e4
                - lhs.v.e4 * rhs.b.e25
                + lhs.t.e124 * rhs.b.e15
                - lhs.b.e15 * rhs.t.e124
                - lhs.t.e125 * rhs.b.e14
                + lhs.b.e14 * rhs.t.e125
                - lhs.t.e234 * rhs.b.e35
                + lhs.b.e35 * rhs.t.e234
                + lhs.t.e235 * rhs.b.e34
                - lhs.b.e34 * rhs.t.e235
                - lhs.q.e1245 * rhs.v.e1
                + lhs.v.e1 * rhs.q.e1245
                + lhs.q.e2345 * rhs.v.e3
                - lhs.v.e3 * rhs.q.e2345
                + lhs.q.e1235 * rhs.t.e134
                + lhs.t.e134 * rhs.q.e1235
                - lhs.q.e1234 * rhs.t.e235
                - lhs.t.e235 * rhs.q.e1234
                + lhs.t.e123 * rhs.q.e1345
                + lhs.q.e1345 * rhs.t.e123;

            result.t.e345 =
                lhs.b.e45 * rhs.v.e3
                + lhs.v.e3 * rhs.b.e45
                + lhs.b.e34 * rhs.v.e5
                + lhs.v.e5 * rhs.b.e34
                - lhs.b.e35 * rhs.v.e4
                - lhs.v.e4 * rhs.b.e35
                + lhs.t.e134 * rhs.b.e15
                - lhs.b.e15 * rhs.t.e134
                - lhs.t.e135 * rhs.b.e14
                + lhs.b.e14 * rhs.t.e135
                + lhs.t.e234 * rhs.b.e25
                - lhs.b.e25 * rhs.t.e234
                - lhs.t.e235 * rhs.b.e24
                + lhs.b.e24 * rhs.t.e235
                - lhs.q.e1345 * rhs.v.e1
                + lhs.v.e1 * rhs.q.e1345
                - lhs.q.e2345 * rhs.v.e2
                + lhs.v.e2 * rhs.q.e2345
                - lhs.q.e1235 * rhs.t.e124
                - lhs.t.e124 * rhs.q.e1235
                + lhs.q.e1234 * rhs.t.e125
                + lhs.t.e125 * rhs.q.e1234
                - lhs.t.e123 * rhs.q.e1245
                - lhs.q.e1245 * rhs.t.e123;

    //------------------------------------(end)---------------------------------------
        
    //四维       
    //-----------------------------------(start)--------------------------------------

        result.q.e1234 =
            lhs.b.e12 * rhs.b.e34
            + lhs.b.e34 * rhs.b.e12
            - lhs.b.e13 * rhs.b.e24
            - lhs.b.e24 * rhs.b.e13
            + lhs.b.e14 * rhs.b.e23
            + lhs.b.e23 * rhs.b.e14
            + lhs.q.e1234 * rhs.s
            + lhs.s * rhs.q.e1234
            + lhs.v.e1 * rhs.t.e234
            - lhs.t.e234 * rhs.v.e1
            - lhs.v.e2 * rhs.t.e134
            + lhs.t.e134 * rhs.v.e2
            + lhs.v.e3 * rhs.t.e124
            - lhs.t.e124 * rhs.v.e3
            + lhs.t.e123 * rhs.v.e4
            - lhs.v.e4 * rhs.t.e123;

        result.q.e1235 =
            lhs.b.e12 * rhs.b.e35
            + lhs.b.e35 * rhs.b.e12
            - lhs.b.e13 * rhs.b.e25
            - lhs.b.e25 * rhs.b.e13
            + lhs.b.e15 * rhs.b.e23
            + lhs.b.e23 * rhs.b.e15
            + lhs.q.e1235 * rhs.s
            + lhs.s * rhs.q.e1235
            + lhs.v.e1 * rhs.t.e235
            - lhs.t.e235 * rhs.v.e1
            - lhs.v.e2 * rhs.t.e135
            + lhs.t.e135 * rhs.v.e2
            + lhs.v.e3 * rhs.t.e125
            - lhs.t.e125 * rhs.v.e3
            + lhs.t.e123 * rhs.v.e5
            - lhs.v.e5 * rhs.t.e123;

        result.q.e1245 =
            lhs.b.e12 * rhs.b.e45
            + lhs.b.e45 * rhs.b.e12
            - lhs.b.e14 * rhs.b.e25
            + lhs.b.e15 * rhs.b.e24
            - lhs.b.e25 * rhs.b.e14
            + lhs.b.e24 * rhs.b.e15
            + lhs.q.e1245 * rhs.s
            + lhs.s * rhs.q.e1245
            + lhs.v.e1 * rhs.t.e245
            - lhs.t.e245 * rhs.v.e1
            - lhs.v.e2 * rhs.t.e145
            + lhs.t.e145 * rhs.v.e2
            + lhs.v.e4 * rhs.t.e125
            - lhs.t.e125 * rhs.v.e4
            - lhs.v.e5 * rhs.t.e124
            + lhs.t.e124 * rhs.v.e5;

        result.q.e1345 =
            lhs.b.e14 * rhs.b.e35
            + lhs.b.e13 * rhs.b.e45
            + lhs.b.e35 * rhs.b.e14
            + lhs.b.e45 * rhs.b.e13
            + lhs.q.e1345 * rhs.s
            + lhs.s * rhs.q.e1345
            + lhs.t.e135 * rhs.v.e4
            + lhs.t.e345 * rhs.v.e1
            + lhs.v.e3 * rhs.t.e145
            + lhs.v.e5 * rhs.t.e134
            - lhs.b.e15 * rhs.b.e34
            - lhs.b.e34 * rhs.b.e15
            - lhs.t.e145 * rhs.v.e3
            - lhs.t.e134 * rhs.v.e5
            - lhs.v.e1 * rhs.t.e345
            - lhs.v.e4 * rhs.t.e135;

        result.q.e2345 =
            lhs.b.e23 * rhs.b.e45
            + lhs.b.e25 * rhs.b.e34
            + lhs.b.e34 * rhs.b.e25
            + lhs.b.e45 * rhs.b.e23
            + lhs.q.e2345 * rhs.s
            + lhs.s * rhs.q.e2345
            + lhs.t.e235 * rhs.v.e4
            + lhs.t.e245 * rhs.v.e3
            + lhs.v.e2 * rhs.t.e345
            + lhs.v.e5 * rhs.t.e234
            - lhs.b.e24 * rhs.b.e35
            - lhs.b.e35 * rhs.b.e24
            - lhs.t.e234 * rhs.v.e5
            - lhs.t.e345 * rhs.v.e2
            - lhs.v.e3 * rhs.t.e245
            - lhs.v.e4 * rhs.t.e235;

    //------------------------------------(end)---------------------------------------

    //五维
    //-----------------------------------(start)--------------------------------------

        result.e12345 =
            lhs.e12345 * rhs.s
            + lhs.s * rhs.e12345

            + lhs.b.e12 * rhs.t.e345
            + lhs.b.e15 * rhs.t.e234
            + lhs.b.e23 * rhs.t.e145

            + lhs.b.e13 * rhs.t.e245
            + lhs.b.e35 * rhs.t.e124
            + lhs.b.e45 * rhs.t.e123


            + lhs.t.e123 * rhs.b.e45
            + lhs.t.e124 * rhs.b.e35
            + lhs.t.e145 * rhs.b.e23
            + lhs.t.e234 * rhs.b.e15
            + lhs.t.e245 * rhs.b.e13
            + lhs.t.e134 * rhs.b.e24
            + lhs.t.e345 * rhs.b.e12

            - lhs.b.e14 * rhs.t.e235
            - lhs.b.e24 * rhs.t.e135

            - lhs.t.e235 * rhs.b.e14
            - lhs.t.e135 * rhs.b.e24

            + lhs.v.e1 * rhs.q.e2345
            + lhs.q.e2345 * rhs.v.e1
            - lhs.v.e2 * rhs.q.e1345
            - lhs.q.e1345 * rhs.v.e2
            + lhs.v.e3 * rhs.q.e1245
            + lhs.q.e1245 * rhs.v.e3
            - lhs.v.e4 * rhs.q.e1235
            - lhs.q.e1235 * rhs.v.e4
            + lhs.q.e1234 * rhs.v.e5
            + lhs.v.e5 * rhs.q.e1234;

    //------------------------------------(end)---------------------------------------
        return result;
    }

//------------------------------------(end)---------------------------------------

   

//Multivector reverse
//-----------------------------------(start)--------------------------------------

    Multivector reverse(const Multivector& x) {
        Multivector result;
        result.s = x.s;
        result.v.e1 = x.v.e1;
        result.v.e2 = x.v.e2;
        result.v.e3 = x.v.e3;
        result.v.e4 = x.v.e4;
        result.v.e5 = x.v.e5;
        result.b.e23 = -x.b.e23;
        result.b.e13 = -x.b.e13;
        result.b.e12 = -x.b.e12;
        result.b.e14 = -x.b.e14;
        result.b.e24 = -x.b.e24;
        result.b.e34 = -x.b.e34;
        result.b.e15 = -x.b.e15;
        result.b.e25 = -x.b.e25;
        result.b.e35 = -x.b.e35;
        result.b.e45 = -x.b.e45;
        result.t.e123 = -x.t.e123;
        result.t.e235 = -x.t.e235;
        result.t.e135 = -x.t.e135;
        result.t.e125 = -x.t.e125;
        result.t.e234 = -x.t.e234;
        result.t.e134 = -x.t.e134;
        result.t.e124 = -x.t.e124;
        result.t.e145 = -x.t.e145;
        result.t.e245 = -x.t.e245;
        result.t.e345 = -x.t.e345;
        result.q.e1235 = x.q.e1235;
        result.q.e1234 = x.q.e1234;
        result.q.e2345 = x.q.e2345;
        result.q.e1345 = x.q.e1345;
        result.q.e1245 = x.q.e1245;
        result.e12345 = x.e12345;
        return result;
    }

//------------------------------------(end)---------------------------------------

    

    std::ostream& operator<<(std::ostream& outs, const Vector& x) {
        outs << "e1: " << x.e1 << ", e2: " << x.e2 << ", e3: " << x.e3 << ", e4: " << x.e4 << ", e5: " << x.e5;
        return outs;
    }

    std::ostream& operator<<(std::ostream& outs, const Bivector& x) {
        outs  << "e12: " << x.e12  << ", e13: " << x.e13 << ", e14: " << x.e14 << ", e15: " << x.e15 << "， e23: " << x.e23 << ", e24: " << x.e24 << ", e25: " << x.e25 << ", e34: " << x.e34 << ", e35: " << x.e35 << ", e45: " << x.e45;
        return outs;
    }

    std::ostream& operator<<(std::ostream& outs, const Trivector& x) {
        outs << "e123: " << x.e123 << ", e124: " << x.e124 << ", e125: " << x.e125 << ", e134: " << x.e134 << ", e135: " << x.e135 << ", e234: " << x.e234 << ", e235: " << x.e235    << ", e145: " << x.e145 << ", e245: " << x.e245 << ", e345: " << x.e345;
        return outs;
    }

    std::ostream& operator<<(std::ostream& outs, const Quadvector& x) {
        outs << "e1234: " << x.e1234 << ", e1235: " << x.e1235   << ", e1245: " << x.e1245 << ", e1345: " << x.e1345 << ", e2345: " << x.e2345;
        return outs;
    }

    std::ostream& operator<<(std::ostream& outs, const Multivector& x) {
        outs << "s: " << x.s << std::endl << "v: " << x.v << std::endl << "b: " << x.b << std::endl << "t: " << x.t << std::endl << "q: " << x.q << ", e12345: " << x.e12345;
        return outs;
    }

    Multivector make_rotation(double theta, Bivector axis){
           Multivector result;
           result.s = cos(theta / 2);
           result.b = -sin(theta / 2) * axis;

           return result;

       }

    Multivector make_translation(double x, double y, double z){
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

    double coeff_n(Multivector& xl,int n){
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
               std::cout << "No function" << std::endl;

       }

    double scalarpart(Multivector val){
           double t;
           t = val.s;
           return t;

       }

    Multivector vectorpart(Multivector a, int c){
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

    Multivector anti(Multivector A){
          Multivector I;
          I.e12345 = 1;

          A = -(geom(A, I));
          return A;
      }

    Multivector conformal(double x, double y, double z){

           Multivector result;
           result.s =0;
           result.v.e1 = x;
           result.v.e2 = y;
           result.v.e3 = z;
           result.v.e4 = ((x * x + y * y + z * z) / 2)-0.5;
           result.v.e5 = ((x * x + y * y + z * z) / 2)+0.5;
           return result;
       }

}
