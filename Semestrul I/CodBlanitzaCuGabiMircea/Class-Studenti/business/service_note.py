from domeniu.sef_promotie_dto import SefPromotieDTO


class ServiceNote:

    def __init__(self, validator_nota, repo_note, repo_studenti, repo_materii):
        self.__validator_nota = validator_nota
        self.__repo_note = repo_note
        self.__repo_studenti = repo_studenti
        self.__repo_materii = repo_materii

    def sterge_student_si_notele_lui(self, id_student):
        student = self.__repo_studenti.cauta_student_dupa_id(id_student)
        note = self.__repo_note.get_all()
        note_student = [x for x in note if x.get_student() == student]
        for nota_student in note_student:
            self.__repo_note.sterge_nota_dupa_id(nota_student.get_id_nota())
        self.__repo_studenti.sterge_student_dupa_id(id_student)

    def get_sefi_promotie(self):
        info_studenti= {}
        note=self.__repo_note.get_all()
        for nota in note:
            id_student_nota = nota.get_student().get_id_student()
            valoare_nota = nota.get_nota()
            if id_student_nota not in info_studenti:
                info_studenti[id_student_nota] = []
            info_studenti[id_student_nota].append(valoare_nota)

        sefi_promotie = []
        for id_student in info_studenti:
            student = self.__repo_studenti.cauta_student_dupa_id(id_student)
            nume_student = student.get_nume()
            medie_student = sum(info_studenti[id_student])/len(info_studenti[id_student])
            sef_promotie_dto = SefPromotieDTO(nume_student, medie_student)
            sefi_promotie.append(sef_promotie_dto)
        sefi_promotie.sort(reverse=True)
        return sefi_promotie[:3]
