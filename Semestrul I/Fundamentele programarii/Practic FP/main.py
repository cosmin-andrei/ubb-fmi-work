from business.service_examene import ServiceExamene
from infrastructure.FileRepoExamene import FileRepoExamene
from prezentare.user import UI
from testare.teste import Teste
from validatoare.validator_examen import ValidareExamen

if __name__ == '__main__':
    teste = Teste()
    teste.run()
    repo = FileRepoExamene("examene.txt")
    validator = ValidareExamen()
    service = ServiceExamene(repo, validator)
    ui = UI(service)
    ui.run()