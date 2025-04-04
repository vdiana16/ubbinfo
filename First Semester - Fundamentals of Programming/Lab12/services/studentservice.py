from domain.entities import Student
from domain.validators import StudentValidator, ValidatorException
from repository.studentrepo import StudentiInMemoryRepository
from utils.functions import string_generator

class StudentService:
    def __init__(self, rep, val):
        """
        Initializare service
        :param rep: obiectul in care depozitam studentii
        :param val: pboectul in care se valideaza studentii
        """
        self.__rep = rep
        self.__val = val

    def adaugareStudent(self, idst, nume):
        """
        Adauga studentul in catalog
        :param idst:
        :param nume:
        :return: Student
        """
        st = Student(idst, nume)
        self.__val.validare(st)
        self.__rep.adaugarestud(st)
        return st

    def stergereStudent(self, idst):
        """
        Sterge studentul din catalog
        :param idst:
        :return:
        """
        if idst == "":
            raise ValueError("Id vid!")
        self.__rep.stergerestud(idst)

    def stergeretotiStudent(self):
        """
        Sterge toti studentii
        :return:
        """
        self.__rep.stergeretotistud()

    def modificareStudent(self, idst, numenou):
        """
        Modifica studentul
        :param idst:
        :param numenou:
        :return:
        """
        st = Student(idst, numenou)
        self.__val.validare(st)
        self.__rep.modificarestud(idst, numenou)
        return st

    def cautaid(self):
        """
        Cauta id-ul care urmeaza sa fie initializat
        :return:
        """
        return self.__rep.cautareid()

    def cautareStudentid(self, idst):
        """
        Cauta un student dupa id
        :param idst:
        :return:
        """
        if idst == "":
            raise ValueError("Id vid!")
        st = self.__rep.cautarestudid(idst)
        return st

    def cautareStudentnume(self, nume):
        """
        Cauta un student dupa nume
        :param nume:
        :return:
        """
        if nume == "":
            raise ValueError("Nume vid!")
        st = self.__rep.cautarestudnume(nume)
        return st

    def adaugarerandomStudent(self, x, contor):

        for i in range(x):
            st = Student(contor, string_generator(6))
            contor += 1
            self.__val.validare(st)
            self.__rep.adaugarestud(st)

    """
    def ad_nume_lista(self,lista_note):
        if lista_note == []:
            raise ValueError("Lista vida!")
        lista = []
        for nota in lista_note:
            id = nota.getId()
            st = self.cautareStudentid(id)
            lista.append([lista_note[i][0], lista_note[i][1], st.getNume(), lista_note[i][2], lista_note[i][3]])
        return lista
    """
    def ad_nume_lista_spec(self,listas):
        if listas == []:
            raise ValueError("Lista vida!")
        lista = []
        for i in range(len(listas)):
            st = self.cautareStudentid(listas[i][1])
            lista.append([listas[i][0], listas[i][1], st.getNume(), listas[i][3]])
        return lista

    def getTotiStud(self):
        """
        Returneaza lista de studenti
        :return:
        """
        return self.__rep.getTotiStudentii()


def test_adaugareStudent():
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


def test_stergereStudent():
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


def test_modificareStudent():
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


def test_cautareidStudent():
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


def test_cautarenumeStudent():
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

def test_adaugarerandomStudent():
    rep = StudentiInMemoryRepository()
    val = StudentValidator()
    srv = StudentService(rep, val)
    srv.adaugarerandomStudent(20,0)
    assert rep.lgstud() == 20
"""
def test_ad_nume_lista():
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

def test_ad_nume_lista_spec():
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
"""
test_adaugareStudent()
test_stergereStudent()
test_modificareStudent()
test_cautareidStudent()
test_cautarenumeStudent()
test_adaugarerandomStudent()
