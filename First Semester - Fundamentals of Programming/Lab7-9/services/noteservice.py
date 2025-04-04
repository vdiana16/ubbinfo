from repository.noterepo import NoteInMemoryRepository
from domain.validators import NotaValidator, ValidatorException
from domain.entities import Nota
class NotaService:
    def __init__(self, rep, val):
        self.__rep = rep
        self.__val = val

    def adaugare_nota(self, idst, iddis, notaa):
        """
        Adauga o nota unui student
        :param idst:
        :param iddis:
        :param notaa:
        :return:
        """
        notad = Nota(idst, iddis, notaa)
        self.__val.validare(notad)
        self.__rep.adaugarenota(idst, iddis, notaa)
        return notad

    def stergere_nota(self, idst, iddis):
        """
        Sterge nota cu idst si iddis
        :param idst:
        :param iddis:
        :return:
        """
        if idst == "" or iddis == "":
            raise ValueError("Id-ul nu poate sa fie vid")
        self.__rep.stergerenota(idst, iddis)

    def modificare_nota(self, idst, iddis, notanoua):
        """
        Modifica nota cu idst si iddis
        :param idst:
        :param iddis:
        :param notanoua:
        :return:
        """
        notad = Nota(idst, iddis, notanoua)
        self.__val.validare(notad)
        self.__rep.modificarenota(idst, iddis, notanoua)
        return notad

    def getNote(self):
        """
        Returneaza toate notele
        :return:
        """
        return self.__rep.getToateNotele()

def test_adaugareNota():
    rep = NoteInMemoryRepository()
    val = NotaValidator()
    srv = NotaService(rep, val)
    notaa = srv.adaugare_nota(1,3, 10)
    listanote = rep.getToateNotele()
    assert listanote[0][0] == notaa.getIdstudent()
    assert listanote[0][1] == notaa.getIddisciplina()
    assert listanote[0][2] == notaa.getNota()

    try:
        srv.adaugare_nota("", "","")
        assert False
    except ValidatorException as e:
        assert True

def test_stergeNota():
    rep = NoteInMemoryRepository()
    val = NotaValidator()
    srv = NotaService(rep, val)
    notaa = srv.adaugare_nota(1,3, 10)
    srv.stergere_nota(1,3)
    listanote = rep.getToateNotele()
    assert listanote == []
    try:
        srv.stergere_nota("","")
        assert False
    except ValueError:
        assert True

def test_modificareNota():
    rep = NoteInMemoryRepository()
    val = NotaValidator()
    srv = NotaService(rep, val)
    notaa = srv.adaugare_nota(1, 3, 10)
    notan = srv.modificare_nota(1,3,9)
    assert notan.getNota() == 9

    try:
        srv.modificare_nota("","","")
        assert False
    except ValidatorException:
        assert True



test_adaugareNota()
test_stergeNota()
test_modificareNota()