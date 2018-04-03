#include "polynomial.hpp"
#include <iostream>
Polynomial::Polynomial(std::string polynomial){
	using namespace std;
	while(polynomial.find_last_of("+-") != string::npos){
		int signal_pos = polynomial.find_last_of("+-");
		string term = polynomial.substr(signal_pos, polynomial.length());
		polynomial = polynomial.substr(0, signal_pos);
		if(term.empty()){
			continue;
		}
		terms.push_front(*(new Term(term)));
	}
	terms.push_front(*(new Term(polynomial)));
}

Polynomial::~Polynomial(){
	for (int i=terms.size(); i > 0 ; --i){
    	terms.pop_front();
    	// std::cout << *it << '=' << it->solve(var) << '|' << ret << std::endl;
    }
}

double Polynomial::solve(double var){
	double ret = 0.0;
	for (std::list<Term>::iterator it=terms.begin(); it!=terms.end() ; ++it){
    	ret = ret + (it->solve(var));
    	// std::cout << *it << '=' << it->solve(var) << '|' << ret << std::endl;
    }
    return ret;
}


Polynomial& Polynomial::derivative(){
	std::list<Term> *terms = new std::list<Term>();
	if (!this->terms.empty()){
		for (Term& t : this->terms){
			terms->push_back(t.derivative());
		}
	}
	Polynomial * result = new Polynomial();
	result->set_terms(*terms);
	delete terms;
	return *result;
}

double Polynomial::derivative(double var){
	double result = 0;
	for (Term& t : this->terms){
		result += t.derivative(var);
	}
	return result;
}


void Polynomial::set_terms(std::list<Term>& terms){
	this->terms.clear();
	for (Term& t : terms){
		this->terms.push_back(t);
	}
}

std::string Polynomial::toString(){
	std::string ret;
	std::list<Term>::iterator it=terms.begin();
	while (it!=terms.end()){
    	ret += it->toString();
    	if((++it)!=terms.end()){
    		if (!(it->get_coef() < 0))
    			ret += "+";
    	}
    }
    return ret;
}
