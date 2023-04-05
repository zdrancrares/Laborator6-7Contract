#include "ServiceDisciplina.h"

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using std::vector;
using std::string;
using std::ostream;


void ServiceDisciplina::addDisciplina(const string& id, const string& denumire, int ore, const string& tip, const string& cadruDidactic) {
	Disciplina d{ id, denumire, ore, tip, cadruDidactic };
	validator.validate(d);
	repo.store(d);
}

void ServiceDisciplina::deleteDisciplinaSrv(const string& id) {
	vector<Disciplina> discipline = repo.getAll();
	bool gasit = 0;
	for (const auto& d : discipline)
		if (d.getId() == id) {
			repo.deleteDisciplina(d);
			gasit = 1;
			break;
		}
	if (!gasit) {
		throw ServiceExceptions("Nu exista disciplina cu acest id.");
	}
}

void ServiceDisciplina::updateDisciplina(const string& id, const string& denumireNou, int oreNou, const string& tipNou, const string& cadruDidacticNou) {
	Disciplina dNou{id, denumireNou, oreNou, tipNou, cadruDidacticNou};
	validator.validate(dNou);
	repo.update(dNou);
}

vector<Disciplina> ServiceDisciplina::filtrare(function<bool(const Disciplina&)> fct) {
	vector<Disciplina> rez;
	for (const auto& d : repo.getAll()) {
		if (fct(d)) {
			rez.push_back(d);
		}
	}
	return rez;
}

vector<Disciplina> ServiceDisciplina::filtrareOre(int nrOreInceput, int nrOreSfarsit) {
	return filtrare([nrOreInceput, nrOreSfarsit](const Disciplina& d){
		return d.getOre() >= nrOreInceput && d.getOre() <= nrOreSfarsit;
	});
}

vector<Disciplina> ServiceDisciplina::filtrareCadruDidactic(const string& cadruDidactic) {
	return filtrare([cadruDidactic](const Disciplina& d) {
		return d.getCadruDidactic() == cadruDidactic;
	});
}

ostream& operator<<(ostream& out, const ServiceExceptions& ex) {
	out << ex.msg;
	return out;
}

/*
vector<Disciplina> ServiceDisciplina::generalSort(bool(*maiMicF)(const Disciplina&, const Disciplina&)) {
	vector<Disciplina> v{ repo.getAll() };
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (!maiMicF(v[i], v[j])) {
				Disciplina aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}

vector<Disciplina> ServiceDisciplina::sortByType() {
	auto copyAll = repo.getAll();
	//std::sort(copyAll.begin(), copyAll.end(), cmpType);
	return copyAll;
	//return generalSort(cmpType);
}
*/
