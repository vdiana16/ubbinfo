import unittest
from domain.entities import Student, Disciplina, Nota
class testStudenti(unittest.TestCase):
    def test_creare_student(self):
        """
        Testez crearea unui student
        :return:
        """
        st = Student("1", "Maia")
        assert st.getId() == "1"
        assert st.getNume() == "Maia"

    def test_egals(self):
        """
        Testez validarea egalitatii
        :return:
        """
        st1 = Student("9", "George")
        st2 = Student("9", "George")
        assert st1 == st2

class testDiscipline(unittest.TestCase):
    def test_creare_disciplina(self):
        """
        Testez crearea unei discipline
        :return:
        """
        dis = Disciplina("1", "Matematica", "Cristian")
        assert dis.getIdd() == "1"
        assert dis.getDenumire() == "Matematica"
        assert dis.getProf() == "Cristian"

    def test_egald(self):
        """
        Testez validarea egalitatii
        :return:
        """
        st1 = Disciplina(9, "Analiza", "Mihnea")
        st2 = Disciplina(9, "Algebra", "Sebastian")
        assert st1 == st2

class testNote(unittest.TestCase):
    def test_creare_nota(self):
        """
        Testez crearea unei disciplineunei note
        :return:
        """
        notat = Nota(2, 1, 2, 10)
        assert notat.getIdnota() == 2
        assert notat.getIdstudent() == 1
        assert notat.getIddisciplina() == 2
        assert notat.getNota() == 10

    def test_egaln(self):
        """
        Testez validarea egalitatii
        :return:
        """
        nota1 = Nota(1, 2, 2, 10)
        nota2 = Nota(1, 1, 2, 10)
        assert nota1 == nota2

if __name__ == '__main__':
    unittest.main()
