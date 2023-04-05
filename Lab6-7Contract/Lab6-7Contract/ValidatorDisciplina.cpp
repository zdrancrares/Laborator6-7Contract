#include "ValidatorDisciplina.h"

#include <sstream>
using std::ostream;

void ValidatorDisciplina::validate(const Disciplina& d) {
	vector<string> msgs;
	if (d.getDenumire().size() == 0) msgs.push_back("Denumirea nu poate sa fie vida.");
	if (d.getOre() <= 0) msgs.push_back("Numarul de ore nu poate sa fie <= 0.");
	if (d.getTip().size() == 0) msgs.push_back("Tipul nu poate sa fie vid.");
	if (d.getCadruDidactic().size() < 4) msgs.push_back("Lungimea numelui trebuie sa fie >= 4.");
	if (msgs.size() > 0) {
		throw ValidateExceptions(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateExceptions& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}
