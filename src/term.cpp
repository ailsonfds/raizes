#include "term.hpp"

Term::Term(std::string term, int precision){
	using namespace std;
	char trash;
	istringstream str(term);
	// cout << term << endl;
	if(term.find_first_of("*") != string::npos){
		str >> this->coef;
		str >> trash;
	} else if((term[0] >= 'a' && term[0] <= 'z') || (term[0] >= 'A' && term[0] <= 'Z')){
		this->coef = 1.0;
	} else {
		str >> this->coef;
		this->inc = 'x';
		this->deg = 0;
		return;
	}
	str >> this->inc;
	if(term.find_first_of("^") != string::npos){
		str >> trash;
		str >> this->deg;
	} else {
		this->deg = 1;
	}
	this->precision = precision;
}

Term::Term(double coef, int deg, char inc, int precision){
	this->coef = coef;
	this->inc = inc;
	this->deg = deg;
	this->precision = precision;
}

double Term::solve(double var){
	return this->coef*pow(var,deg);
}

Term& Term::derivative(){
	if (this->deg < pow(10,-this->precision) && this->deg > -pow(10,-this->precision)){
		Term *d = new Term(0, 0 - 1);
		return *d;
	}
	Term *d = new Term(this->coef*this->deg, this->deg - 1);
	return *d;
}

double Term::derivative(double var){
	return (this->derivative()).solve(var);
}

std::istream& Term::read(std::istream& in){
	using namespace std;
	string line;
	in >> line;
	stringstream *strsl = new stringstream(line);
	istream::sentry se(*strsl);
	if (se){
		if(strsl->good()){
			char c = strsl->get();
			// Catch coeficient if any
			if(c == '+' || c == '-' || isdigit(c,strsl->getloc())){
				string coef;
				coef += c;
				c = strsl->get();
				// Catch integer part if any
				while(strsl->good() && isdigit(c,strsl->getloc())){
					coef += c;
					c = strsl->get();
				}
				// Catch decimal part if any
				if(c == '.'){
					coef+=c;
					c = strsl->get();
					while(strsl->good() && isdigit(c,strsl->getloc())){
						coef += c;
						c = strsl->get();
					}
				}
				stringstream sstr(coef);
				sstr >> this->coef;
				sstr.~stringstream();
			}
			if(c == '*') {
				c = strsl->get();
				if(strsl->good() && isalpha(c,strsl->getloc())) {
					this->inc = c;
					c = strsl->get();
					if (c == '^') {
						c = strsl->get();
						if(c == '+' || c == '-' || isdigit(c,strsl->getloc())) {
							string deg;
							deg += c;
							c = strsl->get();
							// Catch integer part if any
							while(strsl->good() && isdigit(c,strsl->getloc())) {
								deg += c;
								c = strsl->get();
							}
							// Catch decimal part if any
							if(c == '.') {
								deg+=c;
								c = strsl->get();
								while(strsl->good() && isdigit(c,strsl->getloc())) {
									deg += c;
									c = strsl->get();
								}
							}
							stringstream sstr(deg);
							sstr >> this->deg;
							sstr.~stringstream();
						}
					} else {
						this->deg = 1;
					}
				}
			}
		}
		in.rdbuf(strsl->rdbuf());
		strsl->~stringstream();
		delete strsl;
	}
	se.~sentry();
	return in;
}

std::string Term::toString(){
	using namespace std;
	string ret = to_string(this->coef);
	ret += "*";
	ret += this->inc;
	ret += "^";
	ret += to_string(this->deg);
	return ret;
}