from domain.entities import Nota
from repository.noterepo import NoteInMemoryRepository

class NoteFileRepository(NoteInMemoryRepository):
    def __init__(self, fileN):
        """
        Se initializaza clasa
        :param fileN: calea catre fisierul de studenti
        """
        NoteInMemoryRepository.__init__(self)
        self.__fileName = fileN
        self.__loadFromFile()

    def __loadFromFile(self):
        with open(self.__fileName, "r") as f:
            linie = f.readline().strip()
            while linie != "":
                nfis = linie.split(";")
                idn = nfis[0]
                id_st = nfis[1]
                id_dis = nfis[2]
                notaa = nfis[3]
                n = Nota(idn, id_st, id_dis, notaa)
                NoteInMemoryRepository.adaugarenota(self, n)
                linie = f.readline().strip()

    def __storeToFile(self):
        with open(self.__fileName,"w") as f:
            lnot = NoteInMemoryRepository.getToateNotele(self)
            for nota in lnot:
                notrf = str(nota.getIdnota()) + ";" + str(nota.getIdstudent()) + ";" + str(nota.getIddisciplina()) + ";" + str(nota.getNota()) + ";"
                notrf = notrf + "\n"
                f.write(notrf)

    def adaugarenota(self, nota):
        NoteInMemoryRepository.adaugarenota(self, nota)
        self.__storeToFile()

    def modificarenota(self, idstud, iddis):
        NoteInMemoryRepository.modificarenota(self, idstud, iddis)
        self.__storeToFile()

    def stergerenota(self, idstud, iddis):
        nota = NoteInMemoryRepository.stergerenota(self, idstud, iddis)
        self.__storeToFile()
        return nota

    def stergeretoatenot(self):
        NoteInMemoryRepository.stergeretoatenot(self)
        self.__storeToFile()


def testStorenot():
    fileName = "notetest.txt"
    repo = NoteFileRepository(fileName)
    repo.stergeretoatenot()
    n = Nota("3","1","2","10")
    repo.adaugarenota(n)
    assert repo.lgnote() == 1
    assert repo.cautareidnota("3") == n
    repo2 = NoteFileRepository(fileName)
    assert repo2.lgnote() == 1
    assert repo2.cautareidnota("3") == n

testStorenot()