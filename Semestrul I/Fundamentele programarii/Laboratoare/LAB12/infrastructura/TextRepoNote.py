from domain.nota import Nota
from infrastructura.repo_note import RepoNote

class FileRepoNote(RepoNote):

    def __init__(self, __cale_catre_fisier):
        RepoNote.__init__(self)
        self.__cale_catre_fisier = __cale_catre_fisier

    def __read_all_from_file(self):
        with open(self.__cale_catre_fisier,"r") as f:
            lines = f.readlines()
            self._note.clear()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split()
                    id_nota = int(parts[0])
                    id_stud = int(parts[1])
                    id_lab = int(parts[2])
                    valoare_nota = int(parts[3])
                    nota = Nota(id_nota, id_stud, id_lab, valoare_nota)
                    self._note[id_nota] = nota

    def __write_all_to_file(self):
        with open(self.__cale_catre_fisier, "w") as f:
            for nota in self._note:
                f.write(str(nota) + "\n")

    def __append_to_file(self, nota):
        with open(self.__cale_catre_fisier, "a") as f:
            f.write(str(nota) + "\n")

    def adauga_nota(self, nota):
        self.__read_all_from_file()
        RepoNote.adauga_nota(self, nota)
        self.__append_to_file(nota)

    def sterge_nota_dupa_id(self, id_nota):
        self.__read_all_from_file()
        RepoNote.sterge_nota_dupa_id(self, id_nota)
        self.__write_all_to_file()

    def get_all(self):
        self.__read_all_from_file()
        return RepoNote.get_all(self)