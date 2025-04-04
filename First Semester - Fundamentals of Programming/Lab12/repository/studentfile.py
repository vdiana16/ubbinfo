from repository.studentrepo import StudentiInMemoryRepository
from domain.entities import Student


class StudentFileRepository(StudentiInMemoryRepository):
    def __init__(self, fileN):
        """
        Se initializaza clasa
        :param fileN: calea catre fisierul de studenti
        """
        StudentiInMemoryRepository.__init__(self)
        self.__fileName = fileN
        self.__loadFromFile()

    def __loadFromFile(self):
        with open(self.__fileName, "r") as f:
            linie = f.readline().strip()
            while linie != "":
                sfis = linie.split(",")
                ids = sfis[0]
                nume = sfis[1]
                st = Student(ids, nume)
                StudentiInMemoryRepository.adaugarestud(self, st)
                linie = f.readline().strip()

    def __storeToFile(self):
        with open(self.__fileName,"w") as f:
            sts = StudentiInMemoryRepository.getTotiStudentii(self)
            for st in sts:
                strf = str(st.getId()) + "," + st.getNume() + ","
                strf = strf + "\n"
                f.write(strf)

    def adaugarestud(self, st):
        StudentiInMemoryRepository.adaugarestud(self, st)
        self.__storeToFile()

    def modificarestud(self, idst, numenou):
        StudentiInMemoryRepository.modificarestud(self, idst, numenou)
        self.__storeToFile()

    def stergerestud(self, id):
        st = StudentiInMemoryRepository.stergerestud(self, id)
        self.__storeToFile()
        return st

    def stergeretotistud(self):
        StudentiInMemoryRepository.stergeretotistud(self)
        self.__storeToFile()


def testadstud():
    fileName = "teststudent.txt"
    repo = StudentFileRepository(fileName)
    repo.stergeretotistud()
    st = Student("1", "Ilinca")
    repo.adaugarestud(st)
    assert repo.lgstud() == 1
    assert repo.cautarestudid("1") == st
    repo2 = StudentFileRepository(fileName)
    assert repo2.lgstud() == 1
    assert repo2.cautarestudid("1") == st

def testmodstud():
    fileName = "teststudent.txt"
    repo = StudentFileRepository(fileName)
    repo.modificarestud("1","Ana")
    st2 = repo.cautarestudid("1")
    assert st2.getNume() == "Ana"
    repo2 = StudentFileRepository(fileName)
    assert repo2.lgstud() == 1
    assert repo2.cautarestudid("1") == st2

def testdelstud():
    fileName = "teststudent.txt"
    repo = StudentFileRepository(fileName)
    repo.stergerestud("1")
    assert repo.lgstud() == 0
    try:
        repo.cautarestudid("1")
        assert False
    except ValueError:
        assert True
    repo2 = StudentFileRepository(fileName)
    assert repo2.lgstud() == 0


testadstud()
testmodstud()
testdelstud()
