/*** Gives a string representation of this polynomial in standard
 * form where zero terms, coefficients 1 or -1, and exponents 1
 * are not displayed.
 * @param poly a degree-coefficients array representation of a* polynomial.
 * @return a string representation of this polynomial
 */



#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;

int main()
{
    string polyToString (const double poly[]);
    double polyEval(const double poly[],double x);
    double nIntegrate(const double poly[], double x1, double x2, double delX);
    void print_polynomial(double poly[], int n);
    double* integrate(const double poly[], double c);
    int n;
    string spoly;
    
    cout<<" Enter the degree of a Polynomial -> ";
    cin>>n;
    double poly [n+2];
    poly[0] = n;
    cout<<endl<<"Enter the coefficients -> ";
    cin.ignore();
    getline(cin, spoly);
    
    //from here
    std::string delimiter = " ";
    
    size_t pos = 0;
    //"2 2 2"
    std::string token;
    if(n+1 == 1){poly[1] = std::stoi(spoly);}
    else{
        
        for(int i = 1; i <= n+1; i++){
            pos = spoly.find(delimiter);
            token = spoly.substr(0, pos);
            poly[i] = std::stoi( token );
            spoly.erase(0, pos+1);
            
        }
    }
    cout << "f(x) = " << polyToString(poly) << endl;
    
    int x;
    cout <<endl<< "Enter x at which to evaluate f (x) -> ";
    cin >> x;
    cout << "f(" << x << ") = " << polyEval(poly, x);
    
    cout << endl << "Enter the lower and upper limits for the integrals -> ";
    //catch input for upper and lower, send to integral
    
    cin.ignore();
    getline(cin, spoly);
    pos = spoly.find(delimiter);
    token = spoly.substr(0, pos);
    double x1 = std::stoi( token );
    spoly.erase(0, pos+1);
    double x2 = std::stoi( spoly );
    
    double c = 2;
    
    cout << endl << "I[f(x), dx] = ";// << polyToString(integrate(poly,c));
    
    double delX = .0000001;
    
    cout << endl << "Exact:" <<endl << "I[" << polyToString(poly)
    << " dx, " << x1 << ", " << x2 << "] = "<< nIntegrate(poly, x1, x2, delX)<<endl;
    
    cout << endl << "Trapezoid Rule:" <<endl << "I[" << polyToString(poly)
    << ", deltax = 1E-7, " << x1 << ", " << x2 << "] = "<< nIntegrate(poly, x1, x2, delX)<<endl;
    
    //cout << endl << "Error Calculation: ";
    
}
/**
 * Gives a string representation of this polynomial in standard
 * form where zero terms, coefficients 1 or -1, and exponents 1
 * are not displayed.
 * <pre>
 * Note: Rules for Representing a Polynomial in Normalized Form:
 * 1. If the degree of the polynomial is 0, return a string
 * representing the number.
 * 2. If the degree of the polynomial is 1, return a string
 * representing the polynomial in the form ax + b, where when
 * b is zero it should not be displayed and when a is -1 or 1
 * it should not be displayed as a coefficient of x.
 * 3. If the degree of the polynomial is 2 or more, follow these
 * steps:
 * A. Generate the string representation of the highest order
 * term without using 1, -1 as its coefficient.
 * B. Generate the string representations of all other, but
 * the last two, terms beginning from the second highest
 * order term without the use of 1 and -1 as coefficients
 * and without including a zero term. Then deal with the
 * last two terms:
 * i. If its linear term is non-zero, generate and append
 * the linear term but without the use of 1 and -1 as
 * its coefficient and 1 as its exponent.
 * ii. Finally, append the constant term, the lowest order
 * term, if it is non-zero.
 * eg: [6, 3, 0, -1, 0, 1, 1, 0] -> 3x^6 - x^4 + x^2 + x
 * [5, -1, 0, 3, 0, -1, 1] -> -x^5 + 3x^3 - x + 1
 * </pre>
 * @param poly a degree-coefficients array representation of a
 * polynomial.
 * @return a string representation of this polynomial
 */
string polyToString(const double poly[])
{
    
    
    stringstream ss;
    
    double degree = poly[0];
    
    
    if(degree==0)
    {
        ss << poly[1];
    }
    
    else if(degree==1)
    {
        int a = poly[1];
        int b = poly[2];
        
        if (b > 0)
        {
            if (a == 1)
                ss << "x + " << b;
            else if ( a == -1)
                ss << "-x + " << b;
            else
                ss << a << "x + " << b;
        }
        else if (b < 0)
        {
            if (a == 1)
                ss << "x " << b;
            else if ( a == -1 )
                ss << "-x " << b;
            else
                ss << a << "x" << b;
        }
        else
            if (a == 1)
                ss << "x";
            else if (a == -1)
                ss << "-x";
            else
                ss << a << "x";
    }
    else if(degree > 1)
    {
        int i;
        if (poly[1] == 1)
            ss << "x^" << degree;
        else if (poly[1] == -1)
            ss << "-x^" << degree;
        else
            ss << poly[1] << "x^" << degree << " ";
        
        for (i = 2; i <= degree-1; i++)
        {
            if (poly[i] > 0)
            {
                if (poly[i] == 1)
                    ss << "+" << "x^" << degree - i+1 << " ";
                else if (poly[i] == -1)
                    ss << "+" << "x^" << degree - i+1 << " ";
                else
                    ss << "+" << poly[i] << "x^" << degree - i+1 << " ";
            }
            else if (poly[i] < 0)
            {
                if(poly[i] == 1)
                    ss << "-" << "x^" << degree - i+1 << " ";
                else if (poly[i] == -1)
                    ss << "-" << "x^" << degree - i+1 << " ";
                else
                    ss << " " << poly[i] << "x^" << degree - i+1 << " ";
            }
            else
                ;
        }
        int a = poly[i];
        int b = poly[i + 1];
        
        if(b > 0)
        {
            if (a > 0)
            {
                if (a == 1)
                    ss << "+ x + " << b;
                else
                    ss << "+ " << a << "x + " << b;
            }
            else if (a < 0)
            {
                if (a == -1)
                    ss << "- x + " << b;
                else
                    ss << a << "x + " << b;
            }
            else
                ss << "+ " << b;
        }
        else if (b < 0)
        {
            {
                if (a > 0)
                {
                    if (a == 1)
                        ss << "+ x +- " << b;
                    else
                        ss << "+ " << a << "x - " << b;
                }
                else
                    ss << b;
            }
        }
        else
        {
            if (a > 0)
            {
                if (a == 1)
                    ss << "+ x";
                else
                    ss << "+" << a << "x";
            }
            else if (a < 0)
            {
                if(a == -1)
                    ss << "-x";
                else
                    ss << a << "x";
            }
            else
                ;
        }
    }
    return ss.str();
}

/**
 * Computes an indefinite integral for the specified
 * polynomial
 * @param poly a degree-coefficients array representation of a
 * polynomial.
 * @param c the constant term
 * @return the array representation of the integeral of the
 * specified
 * polynomial with the specified constant term.
 */
double* integrate(const double poly[], double c)
{
    return 0;
}

/**
 * Evaluates the polynomial represented by the array at the
 * specified value.
 * @param poly a degree-coefficients array representation of a
 * polynomial.
 * @param x numeric value at which the polynomial is to be
 * evaluated.
 * @return the value of the polynomial when evaluated with x
 */

double polyEval(const double poly[],double x)
{
    int degree = poly[0];
    double result = 0;
    int n = 1;
    int i;
    
    for (i=degree; i > 0; i--){
        result += poly[i]*pow(x,n);
        n++;
    }
    
    result += poly[degree+1];
    
    return result;
}
/**
 * Computes a definite integral for the specified
 * polynomial using the trapezoidal rule.
 * @param poly a degree-coefficients array representation of a
 * polynomial.
 * @param x1 the lower limit
 * @param x2 the upper limit
 * @return the area under the curve in the interval [x1, x2]
 */
double nIntegrate(const double poly[], double x1, double x2, double delX)
{
    double integral = 0;
    while (x1  < x2)
    {
        integral = integral + delX + ((polyEval(poly, x1) + polyEval(poly, x1 + delX))/2);
        x1 = x1 + delX;
    }
    return integral;
}
