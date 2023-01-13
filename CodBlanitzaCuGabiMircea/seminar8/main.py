from domain.baller import Baller
from infrastructure.file_repo_ballaz import FileRepoBallaz
from teste.teste_file_repo import Teste


def main():
    teste = Teste()
    teste.run_all_tests()
    repo = FileRepoBallaz("ballaz.txt")
    for balla in repo.get_all_ballaz():
        print(balla)

main()