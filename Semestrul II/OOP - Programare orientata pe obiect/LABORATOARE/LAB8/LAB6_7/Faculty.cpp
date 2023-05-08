#include "Faculty.h"
using std::shuffle;

void Faculty::addDisciplinaToFaculty(const Disciplina& d) {
	this->disciplineFaculty.push_back(d);
}
void Faculty::emptyFaculty() {
	this->disciplineFaculty.clear();
}

void Faculty::addRandomDiscipline(vector<Disciplina> originalDiscipline, int howMany) {
	shuffle(originalDiscipline.begin(), originalDiscipline.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
	while (disciplineFaculty.size() < howMany && originalDiscipline.size() > 0) {
		disciplineFaculty.push_back(originalDiscipline.back());
		originalDiscipline.pop_back();
	}
}
const vector<Disciplina>& Faculty::getAllDisciplineFaculty() {
	return this->disciplineFaculty;
}