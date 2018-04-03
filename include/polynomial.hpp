#ifndef __POLYNOMIAL_HPP__
#define __POLYNOMIAL_HPP__

#include "term.hpp"

class Polynomial{
private:
	std::list<Term> terms;
public:
	Polynomial(){}
	Polynomial(std::string polynomial);
	~Polynomial();
	double solve(double var);
	Polynomial& derivative();
	double derivative(double var);
	void set_terms(std::list<Term>& terms);
	std::string toString();
	friend std::ostream& operator<<(std::ostream& out, Polynomial& p){
		std::list<Term>::iterator it=p.terms.begin();
		while (it!=p.terms.end()){
	    	out << *it;
	    	if((++it)!=p.terms.end()){
	    		if (!(it->get_coef() < 0))
	    			out << "+";
	    	}
	    }
		return out;
	}
	friend std::istream& operator>>(std::istream& in, Polynomial& p){
		using namespace std;
		string line;
		if(in >> line) {
			stringstream sstr(line);
			Term *t = new Term();
			while(t->read(sstr)){
				(p.terms).push_back(*t);
				t = new Term();
			}
		}
		return in;
	}
};

#endif /** __POLYNOMIAL_HPP__ **/