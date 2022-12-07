'''
Created on October, 11
@author: @cosmin-andrei
'''
from domain import student
from teste.teste import Teste
from validatoare.validator_student import ValidatorStudent
from validatoare.validator_nota import ValidatorNota
from validatoare.validator_laborator import ValidatorLaborator
from infrastructura.repo_studenti import RepoStudenti
from infrastructura.repo_laboratoare import RepoLaboratoare
from infrastructura.repo_note import RepoNote
from business.service_note import ServiceNote
from business.service_studenti import ServiceStudenti
from business.service_laboratoare import ServiceLaboratoare
from prezentare.consola import UI


if __name__ == '__main__':
    teste = Teste()
    teste.ruleaza_teste()

    #validatoare
    validator_studenti = ValidatorStudent()
    validator_note = ValidatorNota()

    #repo
    repo_studenti = RepoStudenti()
    repo_note = RepoNote()

    #service
    service_studenti = ServiceStudenti(validator_studenti, repo_studenti)
    service_note = ServiceNote(validator_note, repo_note, repo_studenti)

    ruleaza = UI(service_studenti, service_note)
    ruleaza.run()