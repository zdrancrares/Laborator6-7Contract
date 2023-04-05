#include "Teste.h"
#include "Consola.h"

int main() {
	Teste t;
	t.teste_domain();
	t.teste_validator();
	t.teste_repo();
	t.teste_service();

	RepoDisciplina repo;
	ValidatorDisciplina validator;
	ServiceDisciplina srv{ repo, validator };

	Consola c{srv};
	c.run();
}