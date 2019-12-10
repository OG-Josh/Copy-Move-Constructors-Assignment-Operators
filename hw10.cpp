// hw10.cpp
// to illustrate copy & move constructors, assignment operators

/*************************************************************************
 * AUTHOR     : Joshua Yang	
 * Lab #6     : copy & move constructors, assignment operators
 * CLASS      : CS 1C
 * SECTION    : March 26, 2019
 *************************************************************************/

#include <iostream>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::istream;
using std::ostream;

// file hw10.h

namespace hw10
{

//--Q#1,2,3,4-------------------------------------------------------------------

// a basic implementation of our stl like vector class
// basic vector is a fixed size array of doubles

class vector
{
    int vsize;
    double* elem;
    void copy(const vector& source);              // copy elements from source into *elem
public:
    vector(int s) :
            vsize
            { s }, elem
            { new double[s] }
    {
    } // constructor
    vector(const vector&);                        // copy constructor: defines the copy operation
    vector(vector&&);                             // move constructor: defines the move operation
    ~vector()
    {
        delete[] elem;
    }                  // destructor

    int size() const
    {
        return vsize;
    }            // the current size

    double get(int n)
    {
        return elem[n];
    }         // access: read
    void set(int n, double v)
    {
        elem[n] = v;
    }      // access: write

    vector& operator=(const vector&);             // copy assignment
    vector& operator=(vector&&);                  // move assignment
};

//------------------------------------------------------------------------------

}// hw10

//------------------------------------------------------------------------------

// class member function, function definitions go into hw10.cpp:

// hw10.cpp

namespace hw10
{

// member function definitions:

//------------------------------------------------------------------------------

void vector::copy(const vector& source)
// copy elements 0 to original.vsize-1
{
    for (int i = 0; i < source.vsize; ++i)
        elem[i] = source.elem[i];
}

//--Q#1-------------------------------------------------------------------------

vector::vector(const vector& source) // copy constructor
// allocate elements, then initialize them via copy operation
// : ...
{
    vsize = source.vsize; // assign size
    elem = new double[vsize]; // Allocate the elem array
    copy(source); // use class defined copy operation
}

//--Q#3-------------------------------------------------------------------------

vector::vector(vector&& source) // move constructor
// copy source elem and vsize only, no need for copy operation
// : ...
{
    vsize = source.vsize; // assign size
    elem = source.elem; // assign to source pointer

    source.vsize = 0; // assign the source size to zero
    source.elem = nullptr; // now that source vector contents have been moved, empty the vector
}

//--Q#2-------------------------------------------------------------------------

vector& vector::operator=(const vector& rhs) // copy assignment
// make this vector a copy of the rhs (i.e. source)
{

    double* pD = new double[rhs.vsize];               // allocate new space for double[]
    std::copy(rhs.elem, rhs.elem + rhs.vsize, pD); // use std::copy algorithm to copy rhs elements into pD double[]
    delete[] elem;                              // deallocate old space
    elem = pD;                              // now that we've copied new, deallocated old elems, reset elem pointer
    vsize = rhs.vsize;                              // reset vector size
    return *this;                       // return a self-reference
}

//--Q#4-------------------------------------------------------------------------

vector& vector::operator=(vector&& rhs) // move assignment
// move rhs (i.e. source) to this vector
{
    delete[] elem;                // deallocate old space
    vsize = rhs.vsize;                // copy rh's elements and size, move implies copying element pointer only
    elem = rhs.elem;
    rhs.elem = nullptr;                // empty the rhs vector
    return *this;         // return a self-reference
}

//------------------------------------------------------------------------------

// function definitions:

//--Q#5-------------------------------------------------------------------------

vector fill_doubles(istream& is, int size)
{
    vector temp
    { size };          // instantiate temp vector
    for (int i = 0; i < size; i++)
    {
        double x;
        is >> x;                // store double from input stream in vector
        temp.set(i, x);
    }
    return temp;                // return temp by value, move constructor invoked
}

//------------------------------------------------------------------------------

ostream& print(ostream& os, vector& v)
// print vector element values to the output stream
{
    for (int i = 0; i < v.size(); ++i)
        os << v.get(i) << " ";
    return os;
}

//------------------------------------------------------------------------------

}// hw10

//------------------------------------------------------------------------------

using namespace hw10;

int main()
{
    // console header
    cout << endl;
    cout << "************************************** " << endl;
    cout << "*           Running HW10             * " << endl;
    cout << "*      Programmed by First Last      * " << endl;
    cout << "*      CS1C Date & Time              * " << endl;
    cout << "************************************** " << endl;
    cout << endl;

    // Q#1,2 - vector copy constructor and assignment operatior

    vector v
    { 3 };        // define a vector
    v.set(1, 100.5);     // set v[1] to 100.5 <- v(0 100.5 0)

    vector v2 = v;  // [1.1] copy v to v2: what happens here? <- v2 is copied, v not change. v2(0 100.5 0). v(0 100.5 0)
    v2.set(0, 25);       // set v2[0] to 25 <- v2(25 100.5 0)

    cout << "v  double values: ";
    print(cout, v);
    cout << endl;
    cout << "v2 double values (after copy, set): ";
    print(cout, v2);
    cout << endl << endl;

    vector v3
    { 3 };
    vector v4
    { 4 };
    v3.set(2, 3.3);
    v4.set(2, 4.4);

    cout << "v3 double values: ";
    print(cout, v3);
    cout << endl;
    cout << "v4 double values: ";
    print(cout, v4);
    cout << endl;

    v3 = v4;            // [2.1] assign v4 to v3: what happens here? <- v3 is assign to v4. Old v3 is deallocated

    cout << "v3 double values (after assignment): ";
    print(cout, v3);
    cout << endl << endl;

    vector v5
    { 10 };
    v5 = v5;            // [2.2] self assignment: what happens here, any problems? <- Self assign is fine. No problem

    // Q#5 - move assignment

    cout << "fill up v6 with five doubles" << endl;
    vector v6 = fill_doubles(cin, 5); // temp vector in function scope moved to v6
    cout << "v6 double values: ";
    print(cout, v6);
    cout << endl;

    return 0;
}

//------------------------------------------------------------------------------

// WRITTEN ANSWERS are here!

// Question 5:
// What is the difference between a copy and move operation?
//
// In the copy operation. We need to allocate the dest elem array, then copy one by one from source.
// In the move operation. Don't need to allocate the dest, just assign elem array to source elem. Then deallocate the source.

// What happens when the temp vector (in function scope) is
// returned (by value) from the fill_doubles function and
// assigned to v6 in main?
// Is the copy or move constructor
// invoked? How does this result in improved performance?
//
// The temp vector is assigned to v6, the move constructor is called.
// The performance is improved because we don't need to allocated new array and copy one by one to elem array.
