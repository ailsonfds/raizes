#ifndef __TERM_HPP__
#define __TERM_HPP__

#include <string>
#include <iostream>
#include <sstream>
#include <locale>
#include <cmath>
#include <list>

//1. No método da bisseção, vamos dividindo o intervalo por 2 até encontrarmos um valor de aproximação aceitável.

class Term{
private:
	int deg;
	double coef;
	char inc;
	int precision;
public:
	Term(){
		coef = 1;
		deg = 0;
		inc = 'x';
		precision = 2;
	}
	Term(std::string term, int precision=15);
	Term(double coef, int deg, char inc='x', int precision=15);
	int get_deg() { return this->deg; }
	double get_coef() { return this->coef; }
	double solve(double var);
	Term& derivative();
	double derivative(double var);
	std::istream& read(std::istream& in);
	std::string toString();
	friend bool operator<(Term& t1, Term& t2){
		if(t1.get_deg() < t2.get_deg()) return true;
		else if(t1.get_deg() == t2.get_deg()) return t1.get_coef() < t2.get_coef();
		else return false;
	}
	friend bool operator>(Term& t1, Term& t2){ return t2 < t1; }
	friend bool operator<=(Term& t1, Term& t2){ return !(t1 > t2); }
	friend bool operator>=(Term& t1, Term& t2){ return !(t1 < t2); }
	friend bool operator==(Term& t1, Term& t2){
		return t1.get_deg() == t2.get_deg() && t1.get_coef() == t2.get_coef();
	}
	friend bool operator!=(Term& t1,Term& t2){ return !(t1 == t2); }
	friend std::ostream& operator<<(std::ostream& out, Term& t){
		out << t.get_coef() << "*" << t.inc << "^" << t.get_deg();
		return out;
	}
	friend std::istream& operator>>(std::istream& in, Term& t){
		return t.read(in);
	}
};

#endif /** __TERM_HPP__ **/