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
    '''
    validator_student = ValidatorStudent()
    validator_laborator = ValidatorLaborator
    validator_nota = ValidatorNota
    repo_studenti = RepoStudenti
    repo_laboratoare = RepoLaboratoare
    repo_note = RepoNote
    service_studenti = ServiceStudenti(validator_student, repo_studenti)
    service_laboratoare = ServiceLaboratoare(validator_laborator, repo_laboratoare)
    service_note = ServiceNote(validator_nota, repo_note, repo_studenti, repo_laboratoare)
    consola = UI(service_studenti, service_laboratoare, service_note)
    consola.run()
    '''