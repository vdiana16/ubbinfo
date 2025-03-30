from repository.studentrepo import StudentiInMemoryRepository
from repository.disciplinarepo import DisciplineInMemoryRepository
from domain.entities import Student, Disciplina, Nota
from domain.validators import StudentValidator, DisciplinaValidator
class NoteInMemoryRepository:
    def __init__(self):
        """
        Initializam clasa in care vom adauga notele
        """
        self.__note = []

    def adaugarenota(self, notaa):
        """
        Functia adauga in lista de note o noua nota
        :return:
        """
        self.__note.append(notaa)

    def stergerenota(self, ids, idd):
        """
        Functia sterge o nota
        :param ids:
        :param idd:
        :return:
        """
        ok = False
        i = 0
        for i in range(len(self.__note)):
            if self.__note[i].getIdstudent() == ids and self.__note[i].getIddisciplina() == idd:
                self.__note.pop(i)
                ok = True
                break
        if ok == False:
            raise ValueError("Nota nu a fost gasita")

    def stergeretoatenot(self):
        self.__note = []

    def cautareidnota(self, idn):
        """
        Cauta o nota dupa id
        :param idn:
        :return:
        """
        for nota in self.__note:
            if nota.getIdnota() == idn:
                return nota
        raise ValueError("Nicio nota gasita cu acest id!")

    def modificarenota(self, ids, idd, notanoua):
        """
        Modificam nota unui student
        :param ids:
        :param idd:
        :param notanoua:
        :return:
        """
        ok = False
        for nota in self.__note:
            if nota.getIdstudent() == ids and nota.getIddisciplina() == idd:
                nota.setNota(notanoua)
                ok = True
                break
        if ok == False:
            raise ValueError("Nota nu a fost gasita")

    def get_toti_stud(self, id_disciplina):
        studentidis = []
        for elem in self.__note:
            if elem.getIddisciplina() == id_disciplina:
                studentidis.append([elem.getIdstudent(), elem.getNota()])
        return studentidis

    def getToateNotele(self):
        """
        Afiseaza toat notele
        :return:
        """
        return self.__note

    def lgnote(self):
        return len(self.__note)

def test_adaugarenota():
    reps = StudentiInMemoryRepository()
    repd = DisciplineInMemoryRepository()
    repn = NoteInMemoryRepository()
    st = Student(1,"Maria")
    dis = Disciplina(2,"Matematica", "Mircea")
    reps.adaugarestud(st)
    repd.adaugaredis(dis)
    notaa = Nota("1", st.getId(), dis.getIdd(), "10")
    repn.adaugarenota(notaa)
    lista = repn.getToateNotele()
    assert repn.lgnote() == 1
    assert lista[0].getIdnota() == "1"
    assert lista[0].getIdstudent() == st.getId()
    assert lista[0].getIddisciplina() == dis.getIdd()
    assert lista[0].getNota() == "10"

def test_stergerenota():
    reps = StudentiInMemoryRepository()
    repd = DisciplineInMemoryRepository()
    repn = NoteInMemoryRepository()
    st = Student(1, "Maria")
    dis = Disciplina(2, "Matematica", "Mircea")
    reps.adaugarestud(st)
    repd.adaugaredis(dis)
    dis = Disciplina(3, "Matematica", "Mircea")
    repd.adaugaredis(dis)
    notaa = Nota("5", 1, 2, "10")
    repn.adaugarenota(notaa)
    notaa = Nota("6",1, 3, "9")
    repn.adaugarenota(notaa)
    repn.stergerenota(1,3)
    lista = repn.getToateNotele()
    assert repn.lgnote() == 1
    assert lista[0].getIdnota() == "5"
    assert lista[0].getIdstudent() == 1
    assert lista[0].getIddisciplina() == 2
    assert lista[0].getNota() == "10"

def test_modificarenota():
    reps = StudentiInMemoryRepository()
    repd = DisciplineInMemoryRepository()
    repn = NoteInMemoryRepository()
    st = Student(1, "Maria")
    dis = Disciplina(2, "Matematica", "Mircea")
    reps.adaugarestud(st)
    repd.adaugaredis(dis)
    notaa = Nota("3", 1, 2, 9)
    repn.adaugarenota(notaa)
    repn.modificarenota(1,2,10)
    lista = repn.getToateNotele()
    assert repn.lgnote() == 1
    assert lista[0].getIdnota() == "3"
    assert lista[0].getIdstudent() == 1
    assert lista[0].getIddisciplina() == 2
    assert lista[0].getNota() == 10

test_adaugarenota()
test_stergerenota()
test_modificarenota()