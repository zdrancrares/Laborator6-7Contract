#pragma once
#include "Disciplina.h"
#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;


class RepoExceptions {
private:
	string msg;

public:
	RepoExceptions(string m) :msg{ m } {}

	friend ostream& operator<<(ostream& out, const RepoExceptions& ex);
};

ostream& operator<<(ostream& out, const RepoExceptions& ex);

class RepoDisciplina
{
private:
	vector<Disciplina> discipline;

	bool exists(const Disciplina& d);
	
public:
	RepoDisciplina() = default;

	RepoDisciplina(const RepoDisciplina& ot) = delete;

	void store(const Disciplina& d);

	void deleteDisciplina(const Disciplina& d);

	void update(const Disciplina& d);

	const Disciplina& find(string id) const;

	const vector<Disciplina>& getAll();
};

