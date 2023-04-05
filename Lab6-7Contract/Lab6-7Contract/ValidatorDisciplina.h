#pragma once
#include "Disciplina.h"
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::ostream;

class ValidateExceptions {
private:
	vector<string>msgs;
public:
	ValidateExceptions(const vector<string>& errors) : msgs{ errors } {}
	friend ostream& operator<<(ostream& out, const ValidateExceptions& ex);
};

ostream& operator<<(ostream& out, const ValidateExceptions& ex);


class ValidatorDisciplina
{
public:
	void validate(const Disciplina& d);
};

