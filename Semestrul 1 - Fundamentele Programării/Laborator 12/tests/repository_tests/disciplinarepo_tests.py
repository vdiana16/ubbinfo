import unittest
from domain.entities import Disciplina
from repository.disciplinarepo import DisciplineInMemoryRepository
from repository.disciplinafile import DisciplinaFileRepository

class testrepoD(unittest.TestCase):

    def test_adaugare_disciplina(self):
        dis1 = Disciplina(1, "Matematica", "George")
        rep = DisciplineInMemoryRepository()
        assert rep.lgdis() == 0
        rep.adaugaredis(dis1)
        lista = rep.getToateDisciplinele()
        assert rep.lgdis() == 1
        assert lista[0].getIdd() == 1
        assert lista[0].getDenumire() == "Matematica"
        assert lista[0].getProf() == "George"
        dis2 = Disciplina(0, "Informatica", "Adam")
        rep.adaugaredis(dis2)
        lista = rep.getToateDisciplinele()
        assert rep.lgdis() == 2
        assert lista[1].getIdd() == 0
        assert lista[1].getDenumire() == "Informatica"
        assert lista[1].getProf() == "Adam"

    def test_stergere_disciplina(self):
        rep = DisciplineInMemoryRepository()
        assert rep.lgdis() == 0
        dis1 = Disciplina(1, "Matematica", "George")
        rep.adaugaredis(dis1)
        dis2 = Disciplina(0, "Informatica", "Adam")
        rep.adaugaredis(dis2)
        rep.stergeredis(1)
        lista = rep.getToateDisciplinele()
        assert rep.lgdis() == 1
        assert lista[0].getIdd() == 0
        assert lista[0].getDenumire() == "Informatica"
        assert lista[0].getProf() == "Adam"

    def test_modificare_disciplina(self):
        rep = DisciplineInMemoryRepository()
        assert rep.lgdis() == 0
        dis1 = Disciplina(1, "Matematica", "George")
        rep.adaugaredis(dis1)
        dis2 = Disciplina(0, "Informatica", "Adam")
        rep.adaugaredis(dis2)
        dis3 = Disciplina(4, "Engleza", "Paul")
        rep.adaugaredis(dis3)
        rep.modificaredis(0, "Economie", "Brancus Ioana")
        lista = rep.getToateDisciplinele()
        assert lista[1].getIdd() == 0
        assert lista[1].getDenumire() == "Economie"
        assert lista[1].getProf() == "Brancus Ioana"

    def test_cautareid_disciplina(self):
        rep = DisciplineInMemoryRepository()
        assert rep.lgdis() == 0
        dis1 = Disciplina(1, "Matematica", "George")
        rep.adaugaredis(dis1)
        dis2 = Disciplina(0, "Informatica", "Adam")
        rep.adaugaredis(dis2)
        dis3 = Disciplina(4, "Engleza", "Paul")
        rep.adaugaredis(dis3)
        dis = rep.cautaredisid(1)
        assert dis.getIdd() == 1
        assert dis.getDenumire() == "Matematica"
        assert dis.getProf() == "George"
        try:
            rep.cautaredisid(678)
            assert False
        except ValueError:
            assert True

    def test_cautareden_disciplina(self):
        rep = DisciplineInMemoryRepository()
        assert rep.lgdis() == 0
        dis1 = Disciplina(1, "Matematica", "George")
        rep.adaugaredis(dis1)
        dis2 = Disciplina(0, "Informatica", "Adam")
        rep.adaugaredis(dis2)
        dis3 = Disciplina(4, "Engleza", "Paul")
        rep.adaugaredis(dis3)
        dis = rep.cautaredendis("Matematica")
        assert dis.getIdd() == 1
        assert dis.getDenumire() == "Matematica"
        assert dis.getProf() == "George"
        try:
            rep.cautaredendis("Filosofie")
            assert False
        except ValueError:
            assert True

    def test_cautareprof_disciplina(self):
        rep = DisciplineInMemoryRepository()
        assert rep.lgdis() == 0
        dis1 = Disciplina(1, "Matematica", "George")
        rep.adaugaredis(dis1)
        dis2 = Disciplina(0, "Informatica", "Adam")
        rep.adaugaredis(dis2)
        dis3 = Disciplina(4, "Engleza", "Paul")
        rep.adaugaredis(dis3)
        dis = rep.cautareprofdis("George")
        assert dis.getIdd() == 1
        assert dis.getDenumire() == "Matematica"
        assert dis.getProf() == "George"
        try:
            rep.cautareprofdis("Arnold")
            assert False
        except ValueError:
            assert True

    def testaddis(self):
        fileName = "teststudent.txt"
        repo = DisciplinaFileRepository(fileName)
        repo.stergetoatedis()
        dis = Disciplina("2", "Matematica", "Anda")
        repo.adaugaredis(dis)
        assert repo.lgdis() == 1
        assert repo.cautaredisid("2") == dis
        repo2 = DisciplinaFileRepository(fileName)
        assert repo2.lgdis() == 1
        assert repo2.cautaredisid("2") == dis

    def testmoddis(self):
        fileName = "teststudent.txt"
        repo = DisciplinaFileRepository(fileName)
        repo.modificaredis("2", "Istorie", "Irina")
        dis = repo.cautaredisid("2")
        assert dis.getDenumire() == "Istorie"
        repo2 = DisciplinaFileRepository(fileName)
        assert repo2.lgdis() == 1
        assert repo2.cautaredisid("2") == dis

    def teststergdis(self):
        fileName = "teststudent.txt"
        repo = DisciplinaFileRepository(fileName)
        repo.stergeredis("2")
        assert repo.lgdis() == 0
        try:
            repo.cautaredisid("2")
            assert False
        except ValueError:
            assert True
        repo2 = DisciplinaFileRepository(fileName)
        assert repo2.lgdis() == 0


if __name__ == '__main__':
        unittest.main()