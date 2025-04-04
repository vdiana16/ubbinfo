from domain.entities import Disciplina
from domain.validators import DisciplinaValidator, ValidatorException
from repository.disciplinarepo import DisciplineInMemoryRepository
from utils.functions import string_generator

class DisciplinaService:
    def __init__(self, rep, val):
        """
        Initializare service
        :param rep: obiectul in care depozitam disciplinele
        :param val: obiectul in care se valideaza disciplinele
        """
        self.__rep = rep
        self.__val = val

    def adaugareDisciplina(self, iddis, denumire, prof):
        """
        Adaug disciplina
        :param iddis: 
        :param denumire: 
        :param prof: 
        :return: 
        """""
        dis = Disciplina(iddis, denumire, prof)
        self.__val.validare(dis)
        self.__rep.adaugaredis(dis)
        return dis

    def adaugarerandomDisciplina(self, x, cont):
        """
        Adauga x discipline random
        :param x:
        :param cont:
        :return:
        """
        for i in range(x):
            dis = Disciplina(cont, string_generator(6), string_generator(6))
            cont += 1
            self.__val.validare(dis)
            self.__rep.adaugaredis(dis)


    def stergereDisciplina(self, iddis):
        """
        Sterge disciplina
        :param iddis:
        :return:
        """
        if iddis == "":
            raise ValueError("Id vid!")
        self.__rep.stergeredis(iddis)

    def stergeretotDisciplina(self):
        """
        Sterge toate disciplinele
        :return:
        """
        self.__rep.stergetoatedis()

    def modificareDisciplina(self, iddis, denumirenoua, prof):
        """
        Modifica disciplina
        :param iddis:
        :param denumirenoua:
        :return:
        """
        dis = Disciplina(iddis, denumirenoua, prof)
        self.__val.validare(dis)
        self.__rep.modificaredis(iddis, denumirenoua, prof)
        return dis

    def cautareDisciplinaid(self, iddis):
        """
        Cauta o disciplina dupa id
        :param iddis:
        :return: dis
        """
        if iddis == "":
            raise ValueError("Id vid!")
        dis = self.__rep.cautaredisid(iddis)
        return dis

    def cautareDisciplinaden(self, denumire):
        """
        Cauta o disciplina dupa denumire
        :param denumire: 
        :return: 
        """""
        if denumire == "":
            raise ValueError("Denumire vida!")
        dis = self.__rep.cautaredendis(denumire)
        return dis

    def cautareDisciplinaprof(self, prof):
        """
        Cauta o disciplina dupa profesor
        :param prof: 
        :return: 
        """""
        if prof == "":
            raise ValueError("Numele profesorului vid!")
        dis = self.__rep.cautareprofdis(prof)
        return dis


    def getToateDis(self):
        """
        Returneaza lista de discipline
        :return:
        """
        return self.__rep.getToateDisciplinele()

def test_adaugareDisciplina():
    rep = DisciplineInMemoryRepository()
    val = DisciplinaValidator()
    srv = DisciplinaService(rep,val)
    dis = srv.adaugareDisciplina(1,"Franceza", "Anca")
    assert rep.lgdis() == 1
    listadis = rep.getToateDisciplinele()
    assert listadis[0] == dis

    try:
        srv.adaugareDisciplina("", "","")
        assert False
    except ValidatorException as e:
        assert True

def test_stergereDisciplina():
    rep = DisciplineInMemoryRepository()
    val = DisciplinaValidator()
    srv = DisciplinaService(rep,val)
    srv.adaugareDisciplina(1,"Franceza", "Anca")
    srv.adaugareDisciplina(3, "Geografie", "Ana")
    srv.stergereDisciplina(3)
    listadis = rep.getToateDisciplinele()
    assert listadis[0].getIdd() == 1
    assert listadis[0].getDenumire() == "Franceza"
    assert listadis[0].getProf() == "Anca"

    try:
        srv.stergereDisciplina("")
        assert False
    except ValueError:
        assert True

def test_modificareDisciplina():
    rep = DisciplineInMemoryRepository()
    val = DisciplinaValidator()
    srv = DisciplinaService(rep,val)
    srv.adaugareDisciplina(1,"Franceza", "Anca")
    srv.adaugareDisciplina(3, "Geografie", "Ana")
    srv.adaugareDisciplina(11, "Fizica", "Oproiu")
    srv.modificareDisciplina(3,"Muzica", "Gina")
    listadis = rep.getToateDisciplinele()
    assert listadis[1].getIdd() == 3
    assert listadis[1].getDenumire() == "Muzica"
    assert listadis[1].getProf() == "Gina"

    try:
        srv.modificareDisciplina("","","")
        assert False
    except ValidatorException:
        assert True

def test_cautareidDisciplina():
    rep = DisciplineInMemoryRepository()
    val = DisciplinaValidator()
    srv = DisciplinaService(rep,val)
    srv.adaugareDisciplina(1,"Franceza", "Anca")
    srv.adaugareDisciplina(3, "Geografie", "Ana")
    srv.adaugareDisciplina(11, "Fizica", "Oproiu")
    dis = srv.cautareDisciplinaid(11)
    listadis = rep.getToateDisciplinele()
    assert listadis[2] == dis

    try:
        srv.cautareDisciplinaid("")
        assert False
    except ValueError:
        assert True

def test_cautaredenumireDisciplina():
    rep = DisciplineInMemoryRepository()
    val = DisciplinaValidator()
    srv = DisciplinaService(rep,val)
    srv.adaugareDisciplina(1,"Franceza", "Anca")
    srv.adaugareDisciplina(3, "Geografie", "Ana")
    srv.adaugareDisciplina(11, "Fizica", "Oproiu")
    dis = srv.cautareDisciplinaden("Geografie")
    listadis = rep.getToateDisciplinele()
    assert listadis[1] == dis

    try:
        srv.cautareDisciplinaden("")
        assert False
    except ValueError:
        assert True

def test_cautareprofDisciplina():
    rep = DisciplineInMemoryRepository()
    val = DisciplinaValidator()
    srv = DisciplinaService(rep,val)
    srv.adaugareDisciplina(1,"Franceza", "Anca")
    srv.adaugareDisciplina(3, "Geografie", "Ana")
    srv.adaugareDisciplina(11, "Fizica", "Oproiu")
    dis = srv.cautareDisciplinaprof("Anca")
    listadis = rep.getToateDisciplinele()
    assert listadis[0] == dis

    try:
        srv.cautareDisciplinaprof("")
        assert False
    except ValueError:
        assert True

def test_adaugarerandomDisciplina():
    rep = DisciplineInMemoryRepository()
    val = DisciplinaValidator()
    srv = DisciplinaService(rep, val)
    srv.adaugarerandomDisciplina(16,0)
    assert rep.lgdis() == 16


test_adaugareDisciplina()
test_stergereDisciplina()
test_modificareDisciplina()
test_cautareidDisciplina()
test_cautaredenumireDisciplina()
test_cautareprofDisciplina()
test_adaugarerandomDisciplina()