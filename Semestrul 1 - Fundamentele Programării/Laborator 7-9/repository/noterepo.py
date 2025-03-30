from repository.studentrepo import StudentiInMemoryRepository
from repository.disciplinarepo import DisciplineInMemoryRepository
from domain.entities import Student, Disciplina
from domain.validators import StudentValidator, DisciplinaValidator
class NoteInMemoryRepository:
    def __init__(self):
        """
        Initializam clasa in care vom adauga notele
        """
        self.__note = []

    def adaugarenota(self, ids, idd, notaa):
        """
        Functia adauga in lista de note o noua disciplina
        :param ids: id-ul studentului
        :param idd: id-ul disciplinei
        :return:
        """
        self.__note.append([ids, idd, notaa])

    def stergerenota(self,  ids, idd):
        """
        Functia sterge o nota
        :param ids:
        :param idd:
        :return:
        """
        ok = False
        i = 0
        for i in range(len(self.__note)):
            if self.__note[i][0] == ids and self.__note[i][1] == idd:
                self.__note.pop(i)
                ok = True
                break
        if ok == False:
            raise ValueError("Nota nu a fost gasita")

    def modificarenota(self, ids, idd, notanoua):
        """
        Modificam nota unui student
        :param ids:
        :param idd:
        :param notanoua:
        :return:
        """
        ok = False
        i = 0
        for i in range(len(self.__note)):
            if self.__note[i][0] == ids and self.__note[i][1] == idd:
                self.__note[i][2] = notanoua
                ok = True
                break
        if ok == False:
            raise ValueError("Nota nu a fost gasita")

    def get_statistica(self,ids):
        frecv = [0] * 100
        for i in (len(self.__note)):


        return frecv

    def get_stat(self):
        frecvn = [0] * 100
        for id1, id2 in self.__rents:
            freq[id1] += 1
        return freq

    def getToateNotele(self):
        """
        Afiseaza toat notele
        :return:
        """
        return self.__note

def test_adaugarenota():
    reps = StudentiInMemoryRepository()
    repd = DisciplineInMemoryRepository()
    repn = NoteInMemoryRepository()
    st = Student(1,"Maria")
    dis = Disciplina(2,"Matematica", "Mircea")
    reps.adaugarestud(st)
    repd.adaugaredis(dis)
    notaa = 10
    repn.adaugarenota(st.getId(),dis.getIdd(),10)
    assert repn.getToateNotele() == [[1,2,10]]

def test_stergerenota():
    reps = StudentiInMemoryRepository()
    repd = DisciplineInMemoryRepository()
    repn = NoteInMemoryRepository()
    st = Student(1, "Maria")
    dis = Disciplina(2, "Matematica", "Mircea")
    reps.adaugarestud(st)
    repd.adaugaredis(dis)
    notaa = 10
    repn.adaugarenota(st.getId(), dis.getIdd(), 10)
    assert repn.getToateNotele() == [[1, 2, 10]]
    repn.stergerenota(st.getId(), dis.getIdd())
    assert repn.getToateNotele() == []

def test_modificarenota():
    reps = StudentiInMemoryRepository()
    repd = DisciplineInMemoryRepository()
    repn = NoteInMemoryRepository()
    st = Student(1, "Maria")
    dis = Disciplina(2, "Matematica", "Mircea")
    reps.adaugarestud(st)
    repd.adaugaredis(dis)
    notaa = 10
    repn.adaugarenota(st.getId(), dis.getIdd(), 10)
    assert repn.getToateNotele() == [[1, 2, 10]]
    notanoua = 9
    repn.modificarenota(st.getId(), dis.getIdd(), notanoua)
    assert repn.getToateNotele() == [[1, 2, 9]]

test_adaugarenota()
test_stergerenota()
test_modificarenota()