from validare.validator_student import ValidatorStudent
from validare.validator_materie import ValidatorMaterie
from validare.validator_nota import ValidatorNota
from infrastructura.repo_note import RepoNote
from infrastructura.repo_materii import RepoMaterii
from infrastructura.repo_studenti import RepoStudenti
from business.service_note import ServiceNote
from business.service_materii import ServiceMaterii
from business.service_studenti import ServiceStudenti
from prezentare.consola import UI

if __name__ == '__main__':
    validator_student = ValidatorStudent()
    validator_materie = ValidatorMaterie()
    validator_nota = ValidatorNota()
    repo_studenti = RepoStudenti()
    repo_materii = RepoMaterii()
    repo_note = RepoNote()
    service_studenti = ServiceStudenti(validator_student, repo_studenti)
    service_materii = ServiceMaterii(validator_materie, repo_materii)
    service_note = ServiceNote(validator_nota, repo_note, repo_studenti, repo_materii)
    consola = UI(service_studenti, service_materii, service_note)
    consola.run()
