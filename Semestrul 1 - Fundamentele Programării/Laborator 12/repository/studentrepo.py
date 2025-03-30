from domain.entities import Student

def cautarestudrec(lista,n,ids):
    if n == 0:
        raise ValueError("Studentul nu a fost gasit")
    if lista[n-1].getId() == ids:
        return lista[n-1]
    else:
        return cautarestudrec(lista,n-1,ids)

def modificarestudrec(lista,n,ids,numenou):
    if n == 0:
        raise ValueError("Studentul nu a fost gasit")
    if lista[n-1].getId() == ids:
        lista[n-1].setNume(numenou)
        return True
    else:
        return modificarestudrec(lista,n-1,ids,numenou)


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

    def stergeretotistud(self):
        """
        Sterge toti studentii
        """
        self.__studenti = []

    def modificarestud(self, idst, numenou):
        """
        Modifica numele studentului cu id-ul idst
        :param idst:
        :param numenou:
        :return:
        """
        modificarestudrec(self.__studenti,len(self.__studenti),idst,numenou)
        """
        listastudaux = []
        for st in self.__studenti:
            if st.getId() == idst:
                st.setNume(numenou)
            listastudaux.append(st)
        self.__studenti = listastudaux
        """
    def cautarestudid(self, idst):
        """
        Cauta un student dupa id
        :param idst:
        :return:
        """
        return cautarestudrec(self.__studenti,len(self.__studenti),idst)
        #for st in self.__studenti:
        #    if st.getId() == idst:
        #        return st
        #raise ValueError("Studentul nu a fost gasit")

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

    def cautareid(self):
        """
        Cauta id-ul care urmeaza sa fie inserat
        :return:
        """
        lstud = self.__studenti
        if lstud != []:
            idst = int(lstud[-1].getId()) + 1
        else:
            idst = 0
        return idst


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

def test_cautareid():
    rep = StudentiInMemoryRepository()
    assert rep.lgstud() == 0
    st1 = Student(1, "Maria")
    rep.adaugarestud(st1)
    st2 = Student(2, "Mara")
    rep.adaugarestud(st2)
    st3 = Student(3, "Mihnea")
    rep.adaugarestud(st3)
    id = rep.cautareid()
    assert id == 4

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
test_cautareid()