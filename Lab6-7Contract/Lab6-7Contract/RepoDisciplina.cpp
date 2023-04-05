#include "RepoDisciplina.h"

#include <iostream>
#include <sstream>

using std::string;


void RepoDisciplina::store(const Disciplina& d) {
	if (exists(d)) {
		throw RepoExceptions("Exista deja disciplina cu id: " + d.getId());
	}
	discipline.push_back(d);
}

void RepoDisciplina::deleteDisciplina(const Disciplina& d) {
	if (!exists(d)) {
		throw RepoExceptions("Nu exista disciplina cu id: " + d.getId());
	}
	int cnt = 0;

	if (discipline.size() == 1) {
		discipline.pop_back();
	}
	else {
		for (const auto& elem : discipline) {
			if (elem.getId() == d.getId()) {
				int poz = cnt;
				Disciplina copie = d;
				for (int j = poz; j <= discipline.size() - 2; j++) {
					discipline[j] = discipline[j + 1];
				}
				discipline[discipline.size() - 1] = d;
				discipline.pop_back();
				break;}
			cnt++;
		}
	}
}

void RepoDisciplina::update(const Disciplina& d) {
	if (!exists(d)) {
		throw RepoExceptions("Nu exista disciplina cu id: " + d.getId());
	}
	int poz = 0;
	for (const auto& elem : discipline) {
		if (elem.getId() == d.getId()) {
			break;
		}
		poz++;
	}
	discipline[poz] = d;
}

const Disciplina& RepoDisciplina::find(string id) const {
	for (const auto& d : discipline) {
		if (d.getId() == id) 
			return d;
	}
	throw RepoExceptions("Nu exista disciplina cu id: " + id);}

const vector<Disciplina>& RepoDisciplina::getAll() {
	return discipline;
}

bool RepoDisciplina::exists(const Disciplina& d) {
	try {
		find(d.getId());
		return true;
	}
	catch (RepoExceptions&) {
		return false;}
}

ostream& operator<<(ostream& out, const RepoExceptions& ex) {
	out << ex.msg;
	return out;
}