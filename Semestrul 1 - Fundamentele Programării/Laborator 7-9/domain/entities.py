class Student:
    def __init__(self, idst, numes):
        """
        Creez un nou student cu id, nume
        id, nume sunt Strings
        :param idst:
        :param numes:
        """
        self.__id = idst
        self.__nume = numes

    def getId(self):
        return self.__id
    def getNume(self):
        return self.__nume

    def setNume(self,numeset):
        self.__nume = numeset


    def __eq__(self, st):
        """
        Verifica daca studnetul st are aceelasi id cu un alt student deja introdus
        :param self:
        :param st:
        :return: True daca exista egalitate
        """
        return self.getId() == st.getId()

class Disciplina:
    def __init__(self, iddis, denumire, prof):
        """
        Creez un nou student cu id, nume
        id, nume sunt Strings
        :param idst:
        :param nume:
        """
        self.__idd = iddis
        self.__denumire = denumire
        self.__prof = prof

    def getIdd(self):
        return self.__idd
    def getDenumire(self):
        return self.__denumire
    def getProf(self):
        return self.__prof

    def setDenumire(self,numeset):
        self.__denumire = numeset
    def setProf(self, profset):
        self.__prof = profset


    def __eq__(self, dis):
        """
        Verifica daca studnetul st are aceelasi id cu un alt student deja introdus
        :param self:
        :param st:
        :return: True daca exista egalitate
        """
        return self.getIdd() == dis.getIdd()

class Nota:
    def __init__(self, idst, iddis, notaa):
        self.__id_stud = idst
        self.__id_dis = iddis
        self.__nota = notaa

    def getIdstudent(self):
        return self.__id_stud

    def getIddisciplina(self):
        return self.__id_dis

    def getNota(self):
        return self.__nota

    def setNota(self, notas):
        self.__nota = notas

    def __eq__(self, notaa):
        return self.getNota() == notaa.getNota()

def test_creare_student():
    """
    Testez crearea unui student
    :return:
    """
    st = Student("1", "Maia")
    assert st.getId() == "1"
    assert st.getNume() == "Maia"


def test_egals():
    """
    Testez validarea egalitatii
    :return:
    """
    st1 = Student("9", "George")
    st2 = Student("9", "George")
    assert st1 == st2

def test_creare_disciplina():
    """
    Testez crearea unei discipline
    :return:
    """
    dis = Disciplina("1", "Matematica", "Cristian")
    assert dis.getIdd() == "1"
    assert dis.getDenumire() == "Matematica"
    assert dis.getProf() == "Cristian"

def test_egald():
    """
    Testez validarea egalitatii
    :return:
    """
    st1 = Disciplina(9, "Analiza","Mihnea")
    st2 = Disciplina(9, "Algebra","Sebastian")
    assert st1 == st2

def test_creare_nota():
    """
    Testez crearea unei disciplineunei note
    :return:
    """
    notat = Nota(1,2,10)
    assert notat.getIdstudent() == 1
    assert notat.getIddisciplina() == 2
    assert notat.getNota() == 10

def test_egaln():
    """
    Testez validarea egalitatii
    :return:
    """
    nota1 = Nota(1,2,10)
    nota2 = Nota(1, 2, 10)
    assert nota1 == nota2

test_creare_student()
test_egals()
test_creare_disciplina()
test_egald()
test_creare_nota()
test_egaln()
