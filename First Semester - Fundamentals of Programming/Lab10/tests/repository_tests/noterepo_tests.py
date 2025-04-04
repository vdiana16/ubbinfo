import unittest
from domain.entities import Student, Disciplina, Nota
from repository.studentrepo import StudentiInMemoryRepository
from repository.disciplinarepo import DisciplineInMemoryRepository
from repository.noterepo import NoteInMemoryRepository


class testrepoN(unittest.TestCase):
    def test_adaugarenota(self):
        reps = StudentiInMemoryRepository()
        repd = DisciplineInMemoryRepository()
        repn = NoteInMemoryRepository()
        st = Student(1, "Maria")
        dis = Disciplina(2, "Matematica", "Mircea")
        reps.adaugarestud(st)
        repd.adaugaredis(dis)
        notaa = Nota("1", st.getId(), dis.getIdd(), "10")
        repn.adaugarenota(notaa)
        lista = repn.getToateNotele()
        assert repn.lgnote() == 1
        assert lista[0].getIdnota() == "1"
        assert lista[0].getIdstudent() == st.getId()
        assert lista[0].getIddisciplina() == dis.getIdd()
        assert lista[0].getNota() == "10"

    def test_stergerenota(self):
        reps = StudentiInMemoryRepository()
        repd = DisciplineInMemoryRepository()
        repn = NoteInMemoryRepository()
        st = Student(1, "Maria")
        dis = Disciplina(2, "Matematica", "Mircea")
        reps.adaugarestud(st)
        repd.adaugaredis(dis)
        dis = Disciplina(3, "Matematica", "Mircea")
        repd.adaugaredis(dis)
        notaa = Nota("5", 1, 2, "10")
        repn.adaugarenota(notaa)
        notaa = Nota("6", 1, 3, "9")
        repn.adaugarenota(notaa)
        repn.stergerenota(1, 3)
        lista = repn.getToateNotele()
        assert repn.lgnote() == 1
        assert lista[0].getIdnota() == "5"
        assert lista[0].getIdstudent() == 1
        assert lista[0].getIddisciplina() == 2
        assert lista[0].getNota() == "10"

    def test_modificarenota(self):
        reps = StudentiInMemoryRepository()
        repd = DisciplineInMemoryRepository()
        repn = NoteInMemoryRepository()
        st = Student(1, "Maria")
        dis = Disciplina(2, "Matematica", "Mircea")
        reps.adaugarestud(st)
        repd.adaugaredis(dis)
        notaa = Nota("3", 1, 2, 9)
        repn.adaugarenota(notaa)
        repn.modificarenota(1, 2, 10)
        lista = repn.getToateNotele()
        assert repn.lgnote() == 1
        assert lista[0].getIdnota() == "3"
        assert lista[0].getIdstudent() == 1
        assert lista[0].getIddisciplina() == 2
        assert lista[0].getNota() == 10

if __name__ == '__main__':
    unittest.main()
