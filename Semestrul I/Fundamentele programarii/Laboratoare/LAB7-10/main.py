'''
Created on October, 11
@author: @cosmin-andrei
'''
from business.service_laborator import ServiceLaborator
from business.service_note import ServiceNote
from business.service_student import ServiceStudent
from infrastructura.TextRepoLabs import FileRepoLabs
from infrastructura.TextRepoNote import FileRepoNote
from infrastructura.TextRepoStud import FileRepoStud
from prezentare.UI import UI
from teste.testPyUnit import Testare
from validatoare.validator_laborator import ValidatorLaborator
from validatoare.validator_nota import ValidatorNota
from validatoare.validator_student import ValidatorStudent

if __name__ == '__main__':
    teste = Testare()
    teste.ruleaza_teste()

    # validatoare
    validator_studenti = ValidatorStudent()
    validator_note = ValidatorNota()
    validator_laborator = ValidatorLaborator()

    # repo
    repo_studenti = FileRepoStud("studenti")
    repo_note = FileRepoNote("note")
    repo_laboratoare = FileRepoLabs("laboratoare")

    # service
    service_studenti = ServiceStudent(validator_studenti, repo_studenti)
    service_laboratoare = ServiceLaborator(validator_laborator, repo_laboratoare)
    service_note = ServiceNote(validator_note, repo_studenti, repo_laboratoare, repo_note)

    ruleaza = UI(service_studenti, service_laboratoare, service_note)
    ruleaza.run()
