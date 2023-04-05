#include "Teste.h"

#include <iostream>
#include <sstream>

using std::string;
using std::stringstream;

void Teste::teste_domain() {
	Disciplina d1{ "AAA1", "OOP", 6, "Obligatorie", "Stan Maria" };

	assert(d1.getId() == "AAA1");
	assert(d1.getDenumire() == "OOP");
	assert(d1.getOre() == 6);
	assert(d1.getTip() == "Obligatorie");
	assert(d1.getCadruDidactic() == "Stan Maria");

	d1.setId("BBB2");
	d1.setDenumire("FP");
	d1.setOre(8);
	d1.setTip("Optionala");
	d1.setCadruDidactic("Stan Maria-Elena");

	assert(d1.getId() == "BBB2");
	assert(d1.getDenumire() == "FP");
	assert(d1.getOre() == 8);
	assert(d1.getTip() == "Optionala");
	assert(d1.getCadruDidactic() == "Stan Maria-Elena");

	Disciplina d2{"BBB2", "OOP2", 6, "Obligatorie", "Stan Maria-Elena"};

	assert(d1 == d2);

	Disciplina d3{ "BBB3", "OOP", 6, "Obligatorie", "Alexandrescu Marius" };

	bool testare_egalitate = (d1 == d3);

	assert(testare_egalitate == false);

	Disciplina d4 = d1;
	
	assert(d4.getId() == "BBB2");
	assert(d4.getDenumire() == "FP");
	assert(d4.getOre() == 8);
	assert(d4.getTip() == "Optionala");
	assert(d4.getCadruDidactic() == "Stan Maria-Elena");

	d2 = d3;

	assert(d2.getId() == "BBB3");
	assert(d2.getDenumire() == "OOP");
	assert(d2.getOre() == 6);
	assert(d2.getTip() == "Obligatorie");
	assert(d2.getCadruDidactic() == "Alexandrescu Marius");

}


void Teste::teste_repo() {
	RepoDisciplina repo;
	Disciplina d1{"ABCD1234", "OOP", 10, "Oblig.", "Popescu Marian"};
	repo.store(d1);
	vector<Disciplina> D = repo.getAll();
	assert(D.size() == 1);
	assert(D[0].getId() == "ABCD1234");
	assert(D[0].getDenumire() == "OOP");
	assert(D[0].getOre() == 10);
	assert(D[0].getTip() == "Oblig.");
	assert(D[0].getCadruDidactic() == "Popescu Marian");

	Disciplina d2{"ABCD1234", "OOP2", 10, "Oblig.", "Popescu Marian-Alexandru"};
	try {
		repo.store(d2);
		assert(false);
	}
	catch (RepoExceptions&) {
		assert(true);
	}

	Disciplina d3{ "ZZZZ8", "ASC", 12, "Obligatorie", "Vancea Alexandru" };
	repo.store(d3);
	D = repo.getAll();
	assert(D.size() == 2);

	Disciplina d4{ "ZZZYYY1", "Logica Computationala", 8, "Obligatorie", "Pop Malina" };

	try {
		repo.deleteDisciplina(d4);
		assert(false);
	}
	catch (RepoExceptions&) {
		assert(true);
	}
	
	repo.store(d4);
	D = repo.getAll();
	assert(D.size() == 3);

	repo.deleteDisciplina(d1);
	try {
		repo.find(d1.getId());
		assert(false);
	}
	catch (RepoExceptions& e) {
		stringstream os;
		os << e;
		assert(true);
	}
	D = repo.getAll();
	assert(D.size() == 2);
	repo.deleteDisciplina(d3);
	D = repo.getAll();
	assert(D.size() == 1);

	repo.deleteDisciplina(d4);
	D = repo.getAll();
	assert(D.size() == 0);

	try {
		repo.update(d1);
		assert(false);
	}
	catch (RepoExceptions&) {
		assert(true);
	}

	Disciplina d5{"ABK240","SDA", 8, "Oglibatorie2", "Matei Filipescu"};
	repo.store(d5);
	Disciplina d6{ "ABK240", "SDA2", 10, "ObligatorieSem2", "Matei Filipescu-Razvan" };
	repo.update(d6);
	assert(d6.getDenumire() == "SDA2");
	assert(d6.getOre() == 10);
	assert(d6.getTip() == "ObligatorieSem2");
	assert(d6.getCadruDidactic() == "Matei Filipescu-Razvan");
}

void Teste::teste_validator() {
	ValidatorDisciplina v;
	Disciplina d1{ "ABCD1234", "", 10, "Oblig.", "Popescu Marian" };
	try {
		v.validate(d1);
		assert(false);
	}
	catch (ValidateExceptions& e) {
		stringstream os;
		os << e;
		assert(true);
	}
	Disciplina d2{ "ABCD1234", "OOP", 0, "Oblig.", "Popescu Marian" };
	try {
		v.validate(d2);
		assert(false);
	}
	catch (ValidateExceptions&) {
		assert(true);
	}
	Disciplina d3{ "ABCD1234", "OOP", 10, "Obligatorie", "Ana" };
	try {
		v.validate(d3);
		assert(false);
	}
	catch (ValidateExceptions&) {
		assert(true);
	}
}

void Teste::teste_service() {
	RepoDisciplina repo;
	ValidatorDisciplina validator;
	ServiceDisciplina srv{ repo, validator };

	srv.addDisciplina("ABC", "OOP", 14, "Facultativa", "Marius Alexandrescu");
	vector<Disciplina>discipline = srv.getAll();
	assert(discipline.size() == 1);
	assert(discipline[0].getId() == "ABC");
	assert(discipline[0].getTip() == "Facultativa");
	assert(discipline[0].getCadruDidactic() == "Marius Alexandrescu");

	srv.addDisciplina("ABCDEF", "OOP2", 16, "Obligatorie", "Marius Alexandrescu");
	discipline = srv.getAll();
	assert(discipline.size() == 2);
	assert(discipline[1].getId() == "ABCDEF");

	srv.deleteDisciplinaSrv("ABC");
	discipline = srv.getAll();
	assert(discipline.size() == 1);
	assert(discipline[0].getId() == "ABCDEF");

	srv.updateDisciplina("ABCDEF", "OOP3", 8, "Oblig.", "Marius Alex.");
	discipline = srv.getAll();
	assert(discipline.size() == 1);
	assert(discipline[0].getDenumire() == "OOP3");
	assert(discipline[0].getOre() == 8);
	assert(discipline[0].getTip() == "Oblig.");
	assert(discipline[0].getCadruDidactic() == "Marius Alex.");

	try {
		srv.addDisciplina("ABCDEF", "OOP", 8, "Obligatorie", "Marius");
		assert(false);
	}
	catch (RepoExceptions&) {
		assert(true);
	}

	try {
		srv.deleteDisciplinaSrv("ABC");
		assert(false);
	}
	catch (ServiceExceptions& e) {
		stringstream os;
		os << e;
		assert(true);
	}

	try {
		srv.addDisciplina("ABCDEFGHI1", "", 10, "Facultativa", "Anamaria Alexandra");
		assert(false);
	}
	catch (ValidateExceptions&) {
		assert(true);
	}

	srv.addDisciplina("abc1234", "ASC", 12, "Facultativa", "Marius Vanta");
	srv.addDisciplina("pqro8888", "SDA", 8, "Optionala", "Ramona Mariana");
	srv.addDisciplina("lmn4321", "FP", 14, "Obligatorie", "Popescu Alexandru");

	assert(srv.filtrareOre(12, 14).size() == 2);
	assert(srv.filtrareOre(8, 8).size() == 2);
	assert(srv.filtrareCadruDidactic("Marius Vanta").size() == 1);
	assert(srv.filtrareCadruDidactic("Popescu Alexandru").size() == 1);

	srv.updateDisciplina("pqro8888", "SDA", 10, "Oblig.", "Marius Alex");
	srv.deleteDisciplinaSrv("lmn4321");
}