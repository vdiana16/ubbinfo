from repository.noterepo import NoteInMemoryRepository
from domain.validators import NotaValidator, ValidatorException
from domain.entities import Nota
from utils.functions import selectionSort, cocktailSort, recurSelectionSort
import math
class NotaService:
    def __init__(self, rep, val):
        self.__rep = rep
        self.__val = val

    def adaugare_nota(self, idn, idst, iddis, notaa):
        """
        Adauga o nota unui student
        :param idst:
        :param iddis:
        :param notaa:
        :return:
        """
        notad = Nota(idn, idst, iddis, notaa)
        self.__val.validare(notad)
        self.__rep.adaugarenota(notad)
        return notad

    def cautaidn(self):
        """
            Cauta id-ul care urmeaza sa fie initializat
            :return:
        """
        return self.__rep.cautareidn()

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

    def stergere_tot_nota(self):
        """
        Sterge toate notele
        :return:
        """
        self.__rep.stergeretoatenot()

    def modificare_nota(self, idn, idst, iddis, notanoua):
        """
        Modifica nota cu idst si iddis
        :param idst:
        :param iddis:
        :param notanoua:
        :return:
        """
        notad = Nota(idn, idst, iddis, notanoua)
        self.__val.validare(notad)
        self.__rep.modificarenota(idst, iddis, notanoua)
        return notad

    def getNote(self):
        """
        Returneaza toate notele
        :return:
        """
        return self.__rep.getToateNotele()

    def ordonare_studenti_nume(self, lista):
        """
        Ordonare studenti in functie de nume
        :param lista:
        :return:
        """
        lista = selectionSort(lista,key=lambda x:x[2])
        """
        for i in range(len(lista)-1):
            for j in range(i+1, len(lista)):
                if lista[i][2] > lista[j][2]:
                    aux = lista[i]
                    lista[i] = lista[j]
                    lista[j] = aux
        """

    def ordonare_studenti_note(self, lista):
        """
        Ordonare studenti in functie de nota
        :param lista:
        :return:
        """
        lista = cocktailSort(lista, key=lambda x: x[4], reverse=False)

        """
        for i in range(len(lista)-1):
            for j in range(i+1, len(lista)):
                if lista[i][4] > lista[j][4]:
                    aux = lista[i]
                    lista[i] = lista[j]
                    lista[j] = aux
        """

    def medie_note_student(self, id_student):
        suma_note = 0
        contor = 0
        lnote = self.__rep.getToateNotele()
        for elem in lnote:
            if elem.getIdstudent() == id_student:
                suma_note += float(elem.getNota())
                contor += 1
        if contor == 0:
            raise ValueError("Studentul nu are nicio nota!")
        return float(suma_note/contor)

    def ordonare_medie(self,lista_medie):
        lista_medie = selectionSort(lista_medie,key=lambda x:x[1],reverse=True)
        """
        for i in range(len(lista_medie)-1):
            for j in range(i+1,len(lista_medie)):
                if lista_medie[i][1] < lista_medie[j][1]:
                    aux = lista_medie[i]
                    lista_medie[i] = lista_medie[j]
                    lista_medie[j] = aux
        """

    def primi_20_la_suta(self,lista_medie):
        n = int(len(lista_medie))
        lista20 =[]
        doua_zeci_la_suta_din_nr_studenti = math.ceil(0.2 * n)
        for i in range(len(lista_medie)):
            if i + 1 <= doua_zeci_la_suta_din_nr_studenti:
                lista20.append(lista_medie[i])
        return lista20

    def get_toti_studdis(self, id_disciplina):
        if id_disciplina == "":
            raise ValueError("Id vid!")
        return self.__rep.get_toti_stud(id_disciplina)

    def get_toti_s5(self,lista):
        ls5 = []
        for i in range(len(lista)):
            if lista[i][1] < 5:
                ls5.append(lista[i])
        return ls5

    def ordonare_nota_s5(self,lista):
        lista = selectionSort(lista, key=lambda x: (-x[2],x[1]))
        """
        for i in range(len(lista)-1):
            for j in range(i+1, len(lista)):
                if lista[i][2] < lista[j][2]:
                    aux = lista[i]
                    lista[i] = lista[j]
                    lista[j] = aux
        """


def test_adaugareNota():
    rep = NoteInMemoryRepository()
    val = NotaValidator()
    srv = NotaService(rep, val)
    notaa = srv.adaugare_nota(1,1,3, 10)
    listanote = rep.getToateNotele()
    assert listanote[0].getIdnota() == notaa.getIdnota()
    assert listanote[0].getIdstudent() == notaa.getIdstudent()
    assert listanote[0].getIddisciplina() == notaa.getIddisciplina()
    assert listanote[0].getNota() == notaa.getNota()

    try:
        srv.adaugare_nota("","", "","")
        assert False
    except ValidatorException as e:
        assert True

def test_stergeNota():
    rep = NoteInMemoryRepository()
    val = NotaValidator()
    srv = NotaService(rep, val)
    notaa = srv.adaugare_nota(1,1,3, 10)
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
    notaa = srv.adaugare_nota(2,1, 3, 10)
    notan = srv.modificare_nota(2,1,3,9)
    assert notan.getNota() == 9

    try:
        srv.modificare_nota("","","","")
        assert False
    except ValidatorException:
        assert True

def test_ordonare_studenti_nume():
    lista = [[2,1,"George",2,4],[3,0,"Alin",8,10],[1,6,"Daniel",1,4]]
    rep = NoteInMemoryRepository()
    val = NotaValidator()
    srv = NotaService(rep, val)
    srv.ordonare_studenti_nume(lista)
    assert lista[0] == [3,0,"Alin",8,10]
    assert lista[1] == [1,6,"Daniel",1,4]
    assert lista[2] == [2,1,"George",2,4]

def test_ordonare_studenti_note():
    lista = [[4,1,"George",2,4],[0,0,"Alin",8,10],[1,6,"Daniel",1,4]]
    rep = NoteInMemoryRepository()
    val = NotaValidator()
    srv = NotaService(rep, val)
    srv.ordonare_studenti_note(lista)
    assert lista[0] == [4,1,"George",2,4]
    assert lista[1] == [1,6, "Daniel", 1, 4]
    assert lista[2] == [0,0, "Alin", 8, 10]

def test_medie_note_student():
    rep = NoteInMemoryRepository()
    val = NotaValidator()
    srv = NotaService(rep, val)
    notaa = srv.adaugare_nota(1,1, 3, 10)
    notaa = srv.adaugare_nota(2,1, 9, 9)
    notaa = srv.adaugare_nota(3,1, 10, 8)
    medie = srv.medie_note_student(1)
    assert medie == 9

def test_ordonare_medie():
    rep = NoteInMemoryRepository()
    val = NotaValidator()
    srv = NotaService(rep, val)
    lista_medie = [["Adam", 7], ["Mihai", 9], ["Grigore", 8.88], ["Miha", 6], ["Maria", 10]]
    srv.ordonare_medie(lista_medie)
    assert lista_medie == [["Maria", 10], ["Mihai", 9], ["Grigore", 8.88], ["Adam", 7], ["Miha", 6]]

def test_primi_20_la_suta():
    rep = NoteInMemoryRepository()
    val = NotaValidator()
    srv = NotaService(rep, val)
    lista_medie = [["Maria",10],["Mihai",9],["Grigore",8.88],["Miha",7],["Adam",5]]
    lista = srv.primi_20_la_suta(lista_medie)
    assert lista[0] ==["Maria",10]

def test_get_toti_studdis():
    rep = NoteInMemoryRepository()
    val = NotaValidator()
    srv = NotaService(rep, val)
    notaa = srv.adaugare_nota(0,1, 3, 10)
    notaa = srv.adaugare_nota(1,2, 3, 10)
    listan = srv.get_toti_studdis(3)
    assert listan[0][0] == 1
    assert listan[1][0] == 2
    try:
        srv.get_toti_studdis("")
        assert False
    except ValueError:
        assert True

def test_get_toti_s5():
    rep = NoteInMemoryRepository()
    val = NotaValidator()
    srv = NotaService(rep, val)
    notaa = srv.adaugare_nota(2,1, 3, 2)
    notaa = srv.adaugare_nota(3,2, 3, 10)
    notaa = srv.adaugare_nota(0,3, 3, 3)
    listan = srv.get_toti_studdis(3)
    lista5 = srv.get_toti_s5(listan)
    assert lista5[0][1] == 2
    assert lista5[1][1] == 3

def test_ordonare_nota_s5():
    rep = NoteInMemoryRepository()
    val = NotaValidator()
    srv = NotaService(rep, val)
    listas = [[1, "Adam", 7], [2, "Mihai", 9], [3, "Grigore", 8.88], [0, "Miha", 10], [5, "Maria", 10]]
    srv.ordonare_nota_s5(listas)
    assert listas == [[5, "Maria", 10], [0, "Miha", 10], [2, "Mihai", 9], [3, "Grigore", 8.88], [1, "Adam", 7]]


test_adaugareNota()
test_stergeNota()
test_modificareNota()
test_ordonare_studenti_nume()
test_ordonare_studenti_note()
test_medie_note_student()
test_ordonare_medie()
test_primi_20_la_suta()
test_get_toti_studdis()
test_get_toti_s5()
test_ordonare_nota_s5()