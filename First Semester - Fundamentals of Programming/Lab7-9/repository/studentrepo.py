from domain.entities import Student

class StudentiInMemoryRepository:
    def __init__(self):
        self.__studenti = []

    def adaugarestud(self, st):
        """
        Adauga un student nou in catalog
        :param st:
        :return:
        """
        self.__studenti.append(st)

    def stergerestud(self, idst):
        """
        Sterge studentul cu id idst din catalog
        :param idst:
        :return:
        """
        listastudaux = []
        for st in self.__studenti:
            if st.getId() != idst:
                listastudaux.append(st)
        self.__studenti = listastudaux

    def modificarestud(self, idst, numenou):
        """
        Modifica numele studentului cu id-ul idst
        :param idst:
        :param numenou:
        :return:
        """
        listastudaux = []
        for st in self.__studenti:
            if st.getId() == idst:
                st.setNume(numenou)
            listastudaux.append(st)
        self.__studenti = listastudaux

    def cautarestudid(self, idst):
        """
        Cauta un student dupa id
        :param idst:
        :return:
        """
        for st in self.__studenti:
            if st.getId() == idst:
                return st
        raise ValueError("Clientul nu a fost gasit")

    def cautarestudnume(self, nume):
        """
        Cauta un student dupa nume
        :param nume:
        :return:
        """
        for st in self.__studenti:
            if st.getNume() == nume:
                return st
        raise ValueError("Clientul nu a fost gasit")

    def lgstud(self):
        """
        Returneaza numarul de studenti din depozit
        :return:
        """
        return len(self.__studenti)

    def getTotiStudentii(self):
        """
        Returneaza toti studentii salvati in lista
        :return:
        """
        return self.__studenti


def test_adaugare_student():
    st1 = Student(1, "Maria")
    rep = StudentiInMemoryRepository()
    assert rep.lgstud() == 0
    rep.adaugarestud(st1)
    lista = rep.getTotiStudentii()
    assert rep.lgstud() == 1
    assert lista[0].getId() == 1
    assert lista[0].getNume() == "Maria"
    st2 = Student(2, "Mara")
    rep.adaugarestud(st2)
    lista = rep.getTotiStudentii()
    assert rep.lgstud() == 2
    assert lista[1].getId() == 2
    assert lista[1].getNume() == "Mara"

def test_stergere_student():
    rep = StudentiInMemoryRepository()
    assert rep.lgstud() == 0
    st1 = Student(1, "Maria")
    rep.adaugarestud(st1)
    st2 = Student(2, "Mara")
    rep.adaugarestud(st2)
    rep.stergerestud(2)
    lista = rep.getTotiStudentii()
    assert rep.lgstud() == 1
    assert lista[0].getId() == 1
    assert lista[0].getNume() == "Maria"

def test_modificare_student():
    rep = StudentiInMemoryRepository()
    assert rep.lgstud() == 0
    st1 = Student(1, "Maria")
    rep.adaugarestud(st1)
    st2 = Student(2, "Mara")
    rep.adaugarestud(st2)
    st3 = Student(4, "Mihnea")
    rep.adaugarestud(st3)
    rep.modificarestud(4, "Adriana")
    lista = rep.getTotiStudentii()
    assert lista[2].getId() == 4
    assert lista[2].getNume() == "Adriana"

def test_cautareid_student():
    rep = StudentiInMemoryRepository()
    assert rep.lgstud() == 0
    st1 = Student(1, "Maria")
    rep.adaugarestud(st1)
    st2 = Student(2, "Mara")
    rep.adaugarestud(st2)
    st3 = Student(5, "Mihnea")
    rep.adaugarestud(st3)
    st = rep.cautarestudid(5)
    assert st.getNume() == "Mihnea"

def test_cautarenume_student():
    rep = StudentiInMemoryRepository()
    assert rep.lgstud() == 0
    st1 = Student(1, "Maria")
    rep.adaugarestud(st1)
    st2 = Student(2, "Mara")
    rep.adaugarestud(st2)
    st3 = Student(5, "Mihnea")
    rep.adaugarestud(st3)
    st = rep.cautarestudnume("Maria")
    assert st.getId() == 1

test_adaugare_student()
test_stergere_student()
test_modificare_student()
test_cautareid_student()
test_cautarenume_student()