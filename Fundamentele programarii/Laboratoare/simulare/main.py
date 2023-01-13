from business.service_produse import ServiceProduse
from business.service_vanzari import ServiceVanzare
from infrastructura.repo_produse import RepoProduse
from infrastructura.repo_vanzari import RepoVanzari
from testare.teste import Teste
from user.ui import UI


def main():
    teste = Teste()
    teste.run_teste()
    repo_produse = RepoProduse("date.txt")
    repo_vanzari = RepoVanzari("vanzari.txt")
    service_produse = ServiceProduse(repo_produse)
    service_vanzari = ServiceVanzare(repo_vanzari)
    ui = UI(service_produse, service_vanzari)
    ui.run()

main()