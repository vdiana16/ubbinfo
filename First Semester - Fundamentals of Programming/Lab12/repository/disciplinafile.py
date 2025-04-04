from repository.disciplinarepo import DisciplineInMemoryRepository
from domain.entities import Disciplina


class DisciplinaFileRepository(DisciplineInMemoryRepository):
    def __init__(self, fileN):
        """
        Se initializaza clasa
        :param fileN: calea catre fisierul de studenti
        """
        DisciplineInMemoryRepository.__init__(self)
        self.__fileName = fileN
        self.__loadFromFile()

    def __loadFromFile(self):
        with open(self.__fileName, "r") as f:
            linie = f.readline().strip()
            while linie != "":
                dfis = linie.split(";")
                iddis = dfis[0]
                denumire = dfis[1]
                profesor = dfis[2]
                dis = Disciplina(iddis,denumire,profesor)
                DisciplineInMemoryRepository.adaugaredis(self, dis)
                linie = f.readline().strip()

    def __storeToFile(self):
        with open(self.__fileName,"w") as f:
            ldis = DisciplineInMemoryRepository.getToateDisciplinele(self)
            for dis in ldis:
                disrf = str(dis.getIdd()) + ";" + dis.getDenumire() + ";" + dis.getProf() + ";"
                disrf = disrf + "\n"
                f.write(disrf)

    def adaugaredis(self, dis):
        DisciplineInMemoryRepository.adaugaredis(self, dis)
        self.__storeToFile()

    def modificaredis(self, iddis, denumiren, profn):
        DisciplineInMemoryRepository.modificaredis(self, iddis, denumiren, profn)
        self.__storeToFile()

    def stergeredis(self, iddis):
        dis = DisciplineInMemoryRepository.stergeredis(self, iddis)
        self.__storeToFile()
        return dis

    def stergetoatedis(self):
        DisciplineInMemoryRepository.stergetoatedis(self)
        self.__storeToFile()


def testaddis():
    fileName = "teststudent.txt"
    repo = DisciplinaFileRepository(fileName)
    repo.stergetoatedis()
    dis = Disciplina("2", "Matematica","Anda")
    repo.adaugaredis(dis)
    assert repo.lgdis() == 1
    assert repo.cautaredisid("2") == dis
    repo2 = DisciplinaFileRepository(fileName)
    assert repo2.lgdis() == 1
    assert repo2.cautaredisid("2") == dis

def testmoddis():
    fileName = "teststudent.txt"
    repo = DisciplinaFileRepository(fileName)
    repo.modificaredis("2","Istorie","Irina")
    dis = repo.cautaredisid("2")
    assert dis.getDenumire() == "Istorie"
    repo2 = DisciplinaFileRepository(fileName)
    assert repo2.lgdis() == 1
    assert repo2.cautaredisid("2") == dis

def teststergdis():
    fileName = "teststudent.txt"
    repo = DisciplinaFileRepository(fileName)
    repo.stergeredis("2")
    assert repo.lgdis() == 0
    try:
        repo.cautaredisid("2")
        assert False
    except ValueError:
        assert True
    repo2 = DisciplinaFileRepository(fileName)
    assert repo2.lgdis() == 0


testaddis()
testmoddis()
teststergdis()