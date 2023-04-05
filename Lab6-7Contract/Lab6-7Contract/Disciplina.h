#pragma once
#include <string>

using std::string;

class Disciplina
{
private:
	string id;
	string denumire;
	int ore;
	string tip;
	string cadruDidactic;

public:
	Disciplina(string id, string denumire, int ore, string tip, string cadruDidactic) :id{ id }, denumire{ denumire }, ore{ ore }, tip{ tip }, cadruDidactic{ cadruDidactic } {
	}

	Disciplina(const Disciplina& ot) : id{ ot.id }, denumire{ ot.denumire }, ore{ ot.ore }, tip{ ot.tip }, cadruDidactic{ ot.cadruDidactic } {
	}

	///getters and setters
	string getId() const{
		return id;
	}
	string getDenumire() const{
		return denumire;
	}
	int getOre() const{
		return ore;
	}
	string getTip() const{
		return tip;
	}
	string getCadruDidactic() const{
		return cadruDidactic;
	}
	void setId(string valoare) {
		id = valoare;
	}
	void setDenumire(string valoare) {
		denumire = valoare;
	}
	void setOre(int valoare) {
		ore = valoare;
	}
	void setTip(string valoare) {
		tip = valoare;
	}
	void setCadruDidactic(string valoare) {
		cadruDidactic = valoare;
	}

	//suprascrie operatorul == pentru obiecte de tip Disciplina
	bool operator==(const Disciplina& ot) {
		if (ot.id == id)
			return true;
		return false;
	}

	Disciplina& operator=(const Disciplina& ot) = default;

	//bool cmpType(const Disciplina& d1, const Disciplina& d2);
};

