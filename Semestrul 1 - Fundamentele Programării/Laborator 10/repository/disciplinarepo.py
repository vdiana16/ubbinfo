from domain.entities import Disciplina

class DisciplineInMemoryRepository:
    def __init__(self):
        self.__discipline = []

    def adaugaredis(self, dis):
        """
        Adauga disciplina
        :param dis:
        :return:
        """
        self.__discipline.append(dis)

    def stergeredis(self, iddis):
        """
        Sterge disciplina cu id iddis
        :param iddis:
        :return:
        """
        listadisaux = []
        for dis in self.__discipline:
            if dis.getIdd() != iddis:
                listadisaux.append(dis)
        self.__discipline = listadisaux

    def stergetoatedis(self):
        self.__discipline = []

    def modificaredis(self, iddis, denumirenoua, profnou):
        """
        Modifica denumirea si profesorul disciplinei cu id-ul iddis
        :param iddis:
        :param denumirenoua:
        :param profnou:
        :return:
        """
        listadisaux = []
        for dis in self.__discipline:
            if dis.getIdd() == iddis:
                dis.setDenumire(denumirenoua)
                dis.setProf(profnou)
            listadisaux.append(dis)
        self.__discipline = listadisaux


    def cautaredisid(self, iddis):
        """
        Cauta o disciplina dupa id
        :param iddis:
        :return:
        """
        for dis in self.__discipline:
            if dis.getIdd() == iddis:
                return dis
        raise ValueError("Nicio disciplina gasita cu acest id!")

    def cautaredendis(self, denumire):
        """
        Caut ao disciplina dupa denumire
        :param denumire:
        :return:
        """
        for dis in self.__discipline:
            if dis.getDenumire() == denumire:
                return dis
        raise ValueError("Nicio disciplina gasita cu aceasta denumire!")

    def cautareprofdis(self, prof):
        """
        Caut ao disciplina dupa denumire
        :param denumire:
        :return:
        """
        for dis in self.__discipline:
            if dis.getProf() == prof:
                return dis
        raise ValueError("Nicio disciplina care sa aiba acest nume de profesor!")

    def lgdis(self):
        """
        Returneaza numarul de discipline
        :return:
        """
        return len(self.__discipline)

    def getToateDisciplinele(self):
        """
        Returneaza toate disciplinele salvate in lista
        :return:
        """
        return self.__discipline

def test_adaugare_disciplina():
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

def test_stergere_disciplina():
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

def test_modificare_disciplina():
    rep = DisciplineInMemoryRepository()
    assert rep.lgdis() == 0
    dis1 = Disciplina(1, "Matematica", "George")
    rep.adaugaredis(dis1)
    dis2 = Disciplina(0, "Informatica", "Adam")
    rep.adaugaredis(dis2)
    dis3 = Disciplina(4, "Engleza", "Paul")
    rep.adaugaredis(dis3)
    rep.modificaredis(0,"Economie","Brancus Ioana")
    lista = rep.getToateDisciplinele()
    assert lista[1].getIdd() == 0
    assert lista[1].getDenumire() == "Economie"
    assert lista[1].getProf() == "Brancus Ioana"

def test_cautareid_disciplina():
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

def test_cautareden_disciplina():
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

def test_cautareprof_disciplina():
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

test_adaugare_disciplina()
test_stergere_disciplina()
test_modificare_disciplina()
test_cautareid_disciplina()
test_cautareden_disciplina()
test_cautareprof_disciplina()