import unittest
from domain.entities import Nota
from domain.validators import ValidatorException, NotaValidator
from services.noteservice import NotaService
from repository.noterepo import NoteInMemoryRepository

class testserviceN(unittest.TestCase):

    def test_adaugareNota(self):
        rep = NoteInMemoryRepository()
        val = NotaValidator()
        srv = NotaService(rep, val)
        notaa = srv.adaugare_nota(1,1,3, 10)
        listanote = rep.getToateNotele()
        assert listanote[0].getIdnota() == notaa.getIdnota()
        assert listanote[0].getIdstudent() == notaa.getIdstudent()
        assert listanote[0].getIddisciplina() == notaa.getIddisciplina()
        assert listanote[0].getNota() == notaa.getNota()

        try:
            srv.adaugare_nota("","", "","")
            assert False
        except ValidatorException as e:
            assert True

    def test_stergeNota(self):
        rep = NoteInMemoryRepository()
        val = NotaValidator()
        srv = NotaService(rep, val)
        notaa = srv.adaugare_nota(1,1,3, 10)
        srv.stergere_nota(1,3)
        listanote = rep.getToateNotele()
        assert listanote == []
        try:
            srv.stergere_nota("","")
            assert False
        except ValueError:
            assert True

    def test_modificareNota(self):
        rep = NoteInMemoryRepository()
        val = NotaValidator()
        srv = NotaService(rep, val)
        notaa = srv.adaugare_nota(2,1, 3, 10)
        notan = srv.modificare_nota(2,1,3,9)
        assert notan.getNota() == 9

        try:
            srv.modificare_nota("","","","")
            assert False
        except ValidatorException:
            assert True

    def test_ordonare_studenti_nume(self):
        lista = [[2,1,"George",2,4],[3,0,"Alin",8,10],[1,6,"Daniel",1,4]]
        rep = NoteInMemoryRepository()
        val = NotaValidator()
        srv = NotaService(rep, val)
        srv.ordonare_studenti_nume(lista)
        assert lista[0] == [3,0,"Alin",8,10]
        assert lista[1] == [1,6,"Daniel",1,4]
        assert lista[2] == [2,1,"George",2,4]

    def test_ordonare_studenti_note(self):
        lista = [[4,1,"George",2,4],[0,0,"Alin",8,10],[1,6,"Daniel",1,4]]
        rep = NoteInMemoryRepository()
        val = NotaValidator()
        srv = NotaService(rep, val)
        srv.ordonare_studenti_note(lista)
        assert lista[0] == [4,1,"George",2,4]
        assert lista[1] == [1,6, "Daniel", 1, 4]
        assert lista[2] == [0,0, "Alin", 8, 10]

    def test_medie_note_student(self):
        rep = NoteInMemoryRepository()
        val = NotaValidator()
        srv = NotaService(rep, val)
        notaa = srv.adaugare_nota(1,1, 3, 10)
        notaa = srv.adaugare_nota(2,1, 9, 9)
        notaa = srv.adaugare_nota(3,1, 10, 8)
        medie = srv.medie_note_student(1)
        assert medie == 9

    def test_ordonare_medie(self):
        rep = NoteInMemoryRepository()
        val = NotaValidator()
        srv = NotaService(rep, val)
        lista_medie = [["Adam", 7], ["Mihai", 9], ["Grigore", 8.88], ["Miha", 6], ["Maria", 10]]
        srv.ordonare_medie(lista_medie)
        assert lista_medie == [["Maria", 10], ["Mihai", 9], ["Grigore", 8.88], ["Adam", 7], ["Miha", 6]]

    def test_primi_20_la_suta(self):
        rep = NoteInMemoryRepository()
        val = NotaValidator()
        srv = NotaService(rep, val)
        lista_medie = [["Maria",10],["Mihai",9],["Grigore",8.88],["Miha",7],["Adam",5]]
        lista = srv.primi_20_la_suta(lista_medie)
        assert lista[0] ==["Maria",10]

    def test_get_toti_studdis(self):
        rep = NoteInMemoryRepository()
        val = NotaValidator()
        srv = NotaService(rep, val)
        notaa = srv.adaugare_nota(0,1, 3, 10)
        notaa = srv.adaugare_nota(1,2, 3, 10)
        listan = srv.get_toti_studdis(3)
        assert listan[0][0] == 1
        assert listan[1][0] == 2
        try:
            srv.get_toti_studdis("")
            assert False
        except ValueError:
            assert True

    def test_get_toti_s5(self):
        rep = NoteInMemoryRepository()
        val = NotaValidator()
        srv = NotaService(rep, val)
        notaa = srv.adaugare_nota(2,1, 3, 2)
        notaa = srv.adaugare_nota(3,2, 3, 10)
        notaa = srv.adaugare_nota(0,3, 3, 3)
        listan = srv.get_toti_studdis(3)
        lista5 = srv.get_toti_s5(listan)
        assert lista5[0][1] == 2
        assert lista5[1][1] == 3

    def test_ordonare_nota_s5(self):
        rep = NoteInMemoryRepository()
        val = NotaValidator()
        srv = NotaService(rep, val)
        listas = [[1, "Adam", 7], [2, "Mihai", 9], [3, "Grigore", 8.88], [0, "Miha", 6], [5, "Maria", 10]]
        srv.ordonare_nota_s5(listas)
        assert listas == [[5, "Maria", 10], [2, "Mihai", 9], [3, "Grigore", 8.88],[1, "Adam", 7], [0, "Miha", 6]]

    def test_ordonare_nume_s5(self):
        rep = NoteInMemoryRepository()
        val = NotaValidator()
        srv = NotaService(rep, val)
        listas = [[1, "Adam", 7], [2, "Mihai", 9], [3, "Grigore", 8.88], [0, "Miha", 10], [5, "Maria", 10]]
        srv.ordonare_nota_s5(listas)
        srv.ordonare_nume_s5(listas)
        assert listas == [[5, "Maria", 10], [0, "Miha", 10], [2, "Mihai", 9], [3, "Grigore", 8.88], [1, "Adam", 7]]

if __name__ == '__main__':
    unittest.main()