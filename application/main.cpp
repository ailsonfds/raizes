#include <iomanip>
#include "polynomial.hpp"

/**
 * Bisection method
 *
 * Method used to provide equations aproximations of their roots.
 * Consists into find a mean point.
 */
double bissecao(Polynomial eq, double a, double b, double precision = 1e-14){
	if(eq.solve(a) < precision && eq.solve(a) > -precision){
		std::cout << "a=" << a << std::endl;
		return a;
	}
	else if(eq.solve(b) < precision && eq.solve(b) > -precision){
		std::cout << "b=" << b << std::endl;
		return b;
	}
	if(fabs(a - b) != 0) {
		double m = (a+b)/2.0;
		if(eq.solve(m) < precision && eq.solve(m) > -precision){
			std::cout << "m=" << m << std::endl;
			return m;
		}else if(eq.solve(a)*eq.solve(m) < 0.0){
			std::cout << "a=" << a << "/m=" << m << std::endl;
			bissecao(eq, a, m);
		}else if(eq.solve(m)*eq.solve(b) < 0.0){
			std::cout << "m=" << m << "/b=" << b << std::endl;
			bissecao(eq, m, b);
		}
	} else {
		return NAN;
	}
}

double newton_raphson(Polynomial eq, double x0, double precision=1e-10){
	std::cout << "x0=" << x0 << std::endl;
	std::cout << "f(" << x0 << ")=" << eq.solve(x0) << std::endl;
	if (eq.solve(x0) < precision && eq.solve(x0) > -precision) return x0;
	else newton_raphson(eq, x0 - (eq.solve(x0)/eq.derivative(x0)));
}

double s(double t){
	return (300-(300*32.17*t/0.1)+((pow(300,2)*32.17/pow(0.1,2))*(1-(pow(M_E,(-0.1*t)/300)))));
}

double ds(double t){
	return (-96510 + 96510*pow(M_E,(-0.1*t)));
}

double newton_raphson(double (*f)(double), double (*df)(double), double x0, double precision=1e-4){
	// std::cout << "x0=" << x0 << std::endl;
	// std::cout << "f(" << x0 << ")=" << (*f)(x0) << std::endl;
	if ((*f)(x0) < precision && (*f)(x0) > -precision) return x0;
	else newton_raphson(f, df, x0 - ((*f)(x0)/(*df)(x0)));
}

int main(){
	Polynomial pol("x^3+4.6*x^2+1.6*x-7.2");
	using namespace std;
	cout << "P(1)=" << setprecision(16) << pol.solve(1.0) << endl;
	cout << "Bisseção(1,-1): " << bissecao(pol, 1.0, -1.0) << endl;
	cout << "Bisseção(0,-2): " << bissecao(pol, 0.0, -2.0) << endl;
	cout << "Bisseção(-2,-3): " << bissecao(pol, -2.0, -3.0) << endl;
	cout << "Bisseção(-3,-4): " << bissecao(pol, -3.0, -4.0) << endl;
	cout << "Bisseção(20,-30): " << bissecao(pol, 20.0, -30.0) << endl;
	pol.~Polynomial();
	Polynomial *pol2 = new Polynomial("x^3-1.7*x^2-12.78*x-10.08");
	cout << "O polinomio eh: " << *pol2 << endl;
	cout << "Sua derivada eh: " << pol2->derivative() << endl;
	cout << "Usando o metodo de Newton-Raphson:" << endl << "Entre com o valor de x0:" << endl;
	double x0 = 0;
	cin >> x0;
	cout << "x=" << newton_raphson(*pol2, x0) << endl;
	pol2->~Polynomial();
	delete pol2;
	cout << newton_raphson(&s, &ds, x0) << endl;
	return 0;
}
	
