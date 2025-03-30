import unittest
from domain.entities import Student
from domain.validators import ValidatorException, StudentValidator
from services.studentservice import StudentService
from repository.studentrepo import StudentiInMemoryRepository

class testserviceS(unittest.TestCase):
    def test_adaugareStudent(self):
        rep = StudentiInMemoryRepository()
        val = StudentValidator()
        srv = StudentService(rep, val)
        st = srv.adaugareStudent(1, "George")
        assert st.getId() == 1
        assert st.getNume() == "George"
        assert rep.lgstud() == 1
        listastud = rep.getTotiStudentii()
        assert listastud[0] == st

        try:
            srv.adaugareStudent(1, "")
            assert False
        except ValidatorException as e:
            assert True

    def test_stergereStudent(self):
        rep = StudentiInMemoryRepository()
        val = StudentValidator()
        srv = StudentService(rep, val)
        srv.adaugareStudent(1, "George")
        srv.adaugareStudent(2, "Ioan")
        srv.stergereStudent(1)
        lista = rep.getTotiStudentii()
        assert lista[0].getId() == 2
        assert lista[0].getNume() == "Ioan"
        assert rep.lgstud() == 1

        try:
            srv.stergereStudent("")
            assert False
        except ValueError:
            assert True

    def test_modificareStudent(self):
        rep = StudentiInMemoryRepository()
        val = StudentValidator()
        srv = StudentService(rep, val)
        srv.adaugareStudent(1, "George")
        srv.adaugareStudent(2, "Ioan")
        srv.modificareStudent(1, "Cristian")
        lista = rep.getTotiStudentii()
        assert lista[0].getId() == 1
        assert lista[0].getNume() == "Cristian"

        try:
            srv.modificareStudent(1, "")
            assert False
        except ValidatorException as e:
            assert True

    def test_cautareidStudent(self):
        rep = StudentiInMemoryRepository()
        val = StudentValidator()
        srv = StudentService(rep, val)
        srv.adaugareStudent(1, "George")
        srv.adaugareStudent(2, "Mihai")
        srv.adaugareStudent(90, "Ioan")
        st = srv.cautareStudentid(90)
        assert st.getId() == 90
        assert st.getNume() == "Ioan"

        try:
            srv.cautareStudentid("")
            assert False
        except ValueError as e:
            assert True

    def test_cautarenumeStudent(self):
        rep = StudentiInMemoryRepository()
        val = StudentValidator()
        srv = StudentService(rep, val)
        srv.adaugareStudent(1, "George")
        srv.adaugareStudent(2, "Mihai")
        srv.adaugareStudent(90, "Ioan")
        st = srv.cautareStudentnume("Mihai")
        assert st.getId() == 2
        assert st.getNume() == "Mihai"

        try:
            srv.cautareStudentnume("")
            assert False
        except ValueError as e:
            assert True

    def test_adaugarerandomStudent(self):
        rep = StudentiInMemoryRepository()
        val = StudentValidator()
        srv = StudentService(rep, val)
        srv.adaugarerandomStudent(20, 0)
        assert rep.lgstud() == 20

    def test_ad_nume_lista(self):
        rep = StudentiInMemoryRepository()
        val = StudentValidator()
        srv = StudentService(rep, val)
        st = srv.adaugareStudent(1, "George")
        lista = srv.ad_nume_lista([[1, 1, 2, 3]])
        assert lista[0][2] == "George"
        try:
            lista = srv.ad_nume_lista([[3, 3, 2, 3]])
            assert False
        except ValueError:
            assert True
        srv.stergereStudent(1)
        try:
            lista = srv.ad_nume_lista([[4, 3, 2, 3]])
            assert False
        except ValueError:
            assert True

    def test_ad_nume_lista_spec(self):
        rep = StudentiInMemoryRepository()
        val = StudentValidator()
        srv = StudentService(rep, val)
        st = srv.adaugareStudent(1, "George")
        lista = srv.ad_nume_lista_spec([[1, 1, 1, 10]])
        assert lista[0][2] == "George"
        try:
            lista = srv.ad_nume_lista([[1, 3, 2, 3]])
            assert False
        except ValueError:
            assert True

if __name__ == '__main__':
    unittest.main()