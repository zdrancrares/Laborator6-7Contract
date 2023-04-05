#pragma once
#include "ServiceDisciplina.h"

#include <iostream>

class Consola
{
private:
	ServiceDisciplina& srv;
public:
	Consola(ServiceDisciplina& srv) :srv{ srv } {}

	void printMenu();
	void printDisciplineUI(vector<Disciplina> discipline);
	void addDisciplinaUI();
	void deleteDisciplinaUI();
	void updateDisciplinaUI();
	void filtrareDisciplineUI();
	void run();
	
};

