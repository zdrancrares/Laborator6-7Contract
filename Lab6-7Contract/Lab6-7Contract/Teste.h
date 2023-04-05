#pragma once
#include <assert.h>
#include "Disciplina.h"
#include "RepoDisciplina.h"
#include "ValidatorDisciplina.h"
#include "ServiceDisciplina.h"

class Teste
{
public:
	Teste() {
	}

	void teste_domain();

	void teste_repo();

	void teste_service();

	void teste_validator();

};

