from domain.validators import ValidatorException


class Consola:
    def __init__(self, srvs, srvd, srvn):
        self.__srvs = srvs
        self.__srvd = srvd
        self.__srvn = srvn
        self.__ids = 0
        self.__ids1 = 0
        self.__idd = 0

    """
    Prelucrare student 
    """
    def __afisezTotiStudentii(self):
        """
        Afisez toti studentii
        :return:
        """
        sts = self.__srvs.getTotiStud()
        if len(sts) == 0:
            print("Niciun student in catalog")
        else:
            for st in sts:
                print(st.getId(), st.getNume())

    def __adaugStudent(self):
        """
        Adauga student in catalog
        :return:
        """
        nume = input("Dati numele studentului: ")
        try:
            st = self.__srvs.adaugareStudent(self.__ids, nume)
            self.__ids += 1
            print("Student ", st.getNume(), " salvat...")
        except ValidatorException as ex:
            print(ex.getErori())

    def __adaugrandomStudent(self):
        x = int(input("Dati numarul de stuudenti pe care doriti sa ii adaugati:"))
        try:
            contor = self.__ids
            self.__srvs.adaugarerandomStudent(x, contor)
            self.__ids = self.__ids + x
            print("Au fost salvati", x, "studenti")
        except ValidatorException as ex:
            print(ex.getErori())

    def __stergStudent(self):
        """
        Sterg studentul cu id idst din catalog
        :return:
        """
        idst = int(input("Dati id-ul studentului: "))
        if idst > self.__ids:
            print("Id-ul nu este valid")
        else:
            try:
                self.__srvs.stergereStudent(idst)
                self.__ids -= 1
                print("Student ", idst, " sters...")
            except ValidatorException as ex:
                print(ex.getErori())

    def __modificaStudent(self):
        idst = int(input("Dati id-ul studentului: "))
        numenou = input("Dati numele nou al studentului: ")
        if idst > self.__ids:
            print("Id-ul nu este valid")
        try:
            self.__srvs.modificareStudent(idst, numenou)
            print("Student ", numenou, " modificat...")
        except ValidatorException as ex:
            print(ex.getErori())

    def __cautaStudentid(self):
        idst = int(input("Dati id-ul studentului dorit: "))
        try:
            st = self.__srvs.cautareStudentid(idst)
            print("Studentul cautat este:")
            print("Id: ", st.getId(), "Nume: ", st.getNume())
        except ValueError as e:
            print(e)
        except ValidatorException as ex:
            print(ex.getErori())

    def __cautaStudentnume(self):
        nume = input("Dati numele studentului dorit: ")
        try:
            st = self.__srvs.cautareStudentnume(nume)
            print("Studentul cautat este:")
            print("Id: ", st.getId(), "Nume: ", st.getNume())
        except ValueError as e:
            print(e)
        except ValidatorException as ex:
            print(ex.getErori())

    """
    Prelucrare disciplina
    """
    def __afisezToateDisciplinele(self):
        """
        Afisez toate disciplinele
        :return:
        """
        ldis = self.__srvd.getToateDis()
        if len(ldis) == 0:
            print("Nicio disciplina!")
        else:
            for dis in ldis:
                print(dis.getIdd(), dis.getDenumire(), dis.getProf())
    def __adaugDisciplina(self):
        """
        Adauga disciplina
        :return:
        """
        denumire = input("Dati denumirea disciplinei: ")
        profesor = input("Dati numele profesorului acestei discipline: ")
        try:
            dis = self.__srvd.adaugareDisciplina(self.__idd, denumire, profesor)
            self.__idd += 1
            print("Disciplina ", dis.getDenumire(), " salvata...")
        except ValidatorException as ex:
            print(ex.getErori())

    def __stergDisciplina(self):
        """
        Sterg discipline cu id iddis
        :return:
        """
        iddis = int(input("Dati id-ul disciplinei: "))
        if iddis > self.__idd:
            print("Id-ul nu este valid")
        else:
            try:
                self.__srvd.stergereDisciplina(iddis)
                self.__idd -= 1
                print("Disciplina ", iddis, " stearsa...")
            except ValidatorException as ex:
                print(ex.getErori())

    def __modificaDisciplina(self):
        iddis = int(input("Dati id-ul disciplinei: "))
        denumirenoua = input("Dati denumirea noua a disciplinei: ")
        profnou = input("Dati numele profesorului disciplinei: ")
        if iddis > self.__idd:
            print("Id-ul nu este valid")
        try:
            self.__srvd.modificareDisciplina(iddis, denumirenoua, profnou)
            print("Disciplina ", denumirenoua, " modificata...")
        except ValidatorException as ex:
            print(ex.getErori())

    def __cautaDisciplinaid(self):
        iddis = int(input("Dati id-ul disciplinei dorite: "))
        try:
            dis = self.__srvd.cautareDisciplinaid(iddis)
            print("Disciplina cautata este:")
            print("Id: ", dis.getIdd(), "Nume: ", dis.getDenumire(), "Profesor: ", dis.getProf())
        except ValueError as e:
            print(e)
        except ValidatorException as ex:
            print(ex.getErori())

    def __cautaDisciplinadenumire(self):
        denumire = input("Dati denumirea disciplinei: ")
        try:
            dis = self.__srvd.cautareDisciplinaden(denumire)
            print("Disciplina cautata este:")
            print("Id: ", dis.getIdd(), "Nume: ", dis.getDenumire(), "Profesor: ", dis.getProf())
        except ValueError as e:
            print(e)
        except ValidatorException as ex:
            print(ex.getErori())

    def __cautaDisciplinaprof(self):
        profesor = input("Dati numele profesorului acestei discipline: ")
        try:
            dis = self.__srvd.cautareDisciplinaprof(profesor)
            print("Disciplina cautata este:")
            print("Id: ", dis.getIdd(), "Nume: ", dis.getDenumire(), "Profesor: ", dis.getProf())
        except ValidatorException as ex:
            print(ex.getErori())

    def __adaugrandomDisciplina(self):
        y = int(input("Dati numarul de discipine pe care doriti sa le adaugati:"))
        try:
            cont = self.__idd
            self.__srvd.adaugarerandomDisciplina(y, cont)
            self.__idd = self.__idd + y
            print("Au fost salvate", y, "discipline")
        except ValidatorException as ex:
            print(ex.getErori())

    def __stergDisciplina(self):
        """
        Sterg discipline cu id iddis
        :return:
        """
        iddis = int(input("Dati id-ul disciplinei: "))
        if iddis > self.__idd:
            print("Id-ul nu este valid")
        else:
            try:
                self.__srvd.stergereDisciplina(iddis)
                self.__idd -= 1
                print("Disciplina ", iddis, " stearsa...")
            except ValidatorException as ex:
                print(ex.getErori())

    def __modificaDisciplina(self):
        iddis = int(input("Dati id-ul disciplinei: "))
        denumirenoua = input("Dati denumirea noua a disciplinei: ")
        profnou = input("Dati numele profesorului disciplinei: ")
        if iddis > self.__idd:
            print("Id-ul nu este valid")
        try:
            self.__srvd.modificareDisciplina(iddis, denumirenoua, profnou)
            print("Disciplina ", denumirenoua, " modificata...")
        except ValidatorException as ex:
            print(ex.getErori())


    """
    Prelucrare note
    """
    def __afisezToateNotele(self):
        """
        Afisez toate notele
        :return:
        """
        sts = self.__srvn.getNote()
        if len(sts) == 0:
            print("Nicio nota in catalog")
        else:
            for notaa in sts:
                print(notaa[0], notaa[1], notaa[2])
    def __adaugNota(self):
        """
        Adauga nota
        :return:
        """
        try:
            idst = int(input("Dati id-ul studentului: "))
            student = self.__srvs.cautareStudentid(idst)
            if student:
                print("\n")
                print("Acestea sunt disciplinele disponibile:")
                lista = self.__srvd.getToateDis()
                for dis in lista:
                    print(dis.getDenumire(),"cu id-ul", dis.getIdd())
                print("\n")
                iddis = int(input("Dati id-ul disciplinei: "))
                discip = self.__srvd.cautareDisciplinaid(iddis)
                if discip:
                    notaa = float(input("Dati nota studentului: "))
                    self.__srvn.adaugare_nota(idst, iddis, notaa)
        except ValidatorException as ex:
            print(ex.getErori())

    def __stergNota(self):
        """
        Sterg nota
        :return:
        """
        try:
            idst = int(input("Dati id-ul studentului: "))
            student = self.__srvs.cautareStudentid(idst)
            if student:
                print("\n")
                print("Acestea sunt disciplinele disponibile:")
                lista = self.__srvd.getToateDis()
                for dis in lista:
                    print(dis.getDenumire())
                print("\n")
                iddis = int(input("Dati id-ul disciplinei: "))
                discip = self.__srvd.cautareDisciplinaid(iddis)
                if discip:
                    self.__srvn.stergere_nota(idst, iddis)
        except ValueError as e:
            print(e)
        except ValidatorException as ex:
            print(ex.getErori())

    def __modificaNota(self):
        """
        Modifica nota
        :return:
        """
        try:
            idst = int(input("Dati id-ul studentului: "))
            student = self.__srvs.cautareStudentid(idst)
            if student:
                print("\n")
                print("Acestea sunt disciplinele disponibile:")
                lista = self.__srvd.getToateDis()
                for dis in lista:
                    print(dis.getDenumire(), "cu id-ul", dis.getIdd())
                print("\n")
                iddis = int(input("Dati id-ul disciplinei: "))
                discip = self.__srvd.cautareDisciplinaid(iddis)
                if discip:
                    notanoua = float(input("Dati nota modificata a studentului: "))
                    self.__srvn.modificare_nota(idst, iddis, notanoua)
        except ValueError as e:
            print(e)
        except ValidatorException as ex:
            print(ex.getErori())

    """
    Prelucrare statistici
    """
    def __statistica_alfabetic_nume(self):
        """
        Generare statistica
        :return:
        """
        lista_note = self.__srvn.getNote()
        lista = []
        for i in range(len(lista_note)):
            st = self.__srvs.cautareStudentid(lista_note[i][0])
            nume = st.getNume()
            lista.append([lista_note[i][0], st.getNume(), lista_note[i][1], lista_note[i][2]])

        lgi = len(lista_note)-1
        lgj = len(lista_note)
        for i in range(lgi):
            for j in range(i+1,lgj):
                if lista[i][1] > lista[j][1]:
                    aux = lista[i]
                    lista[i] = lista[j]
                    lista[j] = aux

        print("Statistica privind notele studentilor, ordonati crescator dupa nume")
        for elem in lista:
            print("id student:", elem[0])
            print("nume student:", elem[1])
            print("id disciplina", elem[2])
            print("nota diciplina", elem[3])

    def __statistica_alfabetic_note(self):
        """
        Generare statistica
        :return:
        """
        lista_note = self.__srvn.getNote()
        lista = []
        for i in range(len(lista_note)):
            st = self.__srvs.cautareStudentid(lista_note[i][0])
            nume = st.getNume()
            lista.append([lista_note[i][0], st.getNume(), lista_note[i][1], lista_note[i][2]])

        lgi = len(lista_note)-1
        lgj = len(lista_note)
        for i in range(lgi):
            for j in range(i+1,lgj):
                if lista[i][3] > lista[j][3]:
                    aux = lista[i]
                    lista[i] = lista[j]
                    lista[j] = aux

        print("Statistica privind notele studentilor, ordonati crescator dupa nota")
        for elem in lista:
            print("id student:", elem[0])
            print("nume student:", elem[1])
            print("id disciplina", elem[2])
            print("nota diciplina", elem[3])

    def __statistica_speciala(self):

        for
    def printmeniugen(self):
        print("         Introduceti comanda generala dorita:")
        print("     Studenti pentru studenti")
        print("     Discipline pentru discipline")
        print("     Note pentru note")
        print("     Statistica pentru statistici")

    def printmeniustud(self):
        print("         Introduceti comanda dorita:")
        print("     Adauga - pentru a adauga un student")
        print("     Adauga random - pentru a adauga x studenti")
        print("     Sterge - pentru a  sterge studentul x")
        print("     Modifica - pentru a modifica studentul x")
        print("     Cauta dupa id - pentru a cauta studentul x dupa id")
        print("     Cauta dupa nume - pentru a cauta studentul x dupa nume")

    def printmeniunota(self):
        print("         Introduceti comanda dorita:")
        print("     Adauga - pentru a adauga o nota unui student la o disciplina")
        print("     Sterge - pentru a  sterge nota unui student la o disciplina")
        print("     Modifica - pentru a modifica nota unui student la o disciplina")
        print("     Afiseaza - pentru a afisa lista de note")

    def printmeniudis(self):
        print("         Introduceti comanda dorita:")
        print("     Adauga - pentru a adauga o discipline")
        print("     Adauga random - pentru a adauga x discipline")
        print("     Sterge - pentru a  sterge disciplina x")
        print("     Modifica - pentru a modifica disciplina x")
        print("     Cauta dupa id - pentru a cauta disciplina x dupa id")
        print("     Cauta dupa nume - pentru a cauta disciplina x dupa denumire")
        print("     Cauta dupa nume - pentru a cauta disciplina x dupa profesor")

    def printmeniustatistici(self):
        print("         Introduceti comanda dorita:")
        print("     A - pentru statistica privind notele studentilor, ordonati crescator dupa nume")
        print("     B - pentru statistica privind notele studentilor, ordonati crescator dupa nota")
        print("     C - pentru statistica privind primi 20% din studenți ordonat dupa media notelor la toate disciplinele")

    def afiseazaUI(self):
        while True:
            self.printmeniugen()
            comandagen = input().strip()
            if comandagen == "Studenti":
                self.printmeniustud()
                while True:
                    comanda = input("Dati comanda: ").strip()
                    if comanda == "Adauga":
                        self.__adaugStudent()
                    elif comanda == "Adauga random":
                        self.__adaugrandomStudent()
                    elif comanda == "Sterge":
                        self.__stergStudent()
                    elif comanda == "Modifica":
                        self.__modificaStudent()
                    elif comanda == "Cauta dupa id":
                        self.__cautaStudentid()
                    elif comanda == "Cauta dupa nume":
                        self.__cautaStudentnume()
                    elif comanda == "Afiseaza":
                        self.__afisezTotiStudentii()
                    elif comanda == "Stop":
                        break
                    else:
                        print("Comanda incorecta!")
            elif comandagen =="Discipline":
                self.printmeniudis()
                while True:
                    comanda = input("Dati comanda: ").strip()
                    if comanda == "Adauga":
                        self.__adaugDisciplina()
                    elif comanda == "Adauga random":
                        self.__adaugrandomDisciplina()
                    elif comanda == "Sterge":
                        self.__stergDisciplina()
                    elif comanda == "Modifica":
                        self.__modificaDisciplina()
                    elif comanda == "Cauta dupa id":
                        self.__cautaDisciplinaid()
                    elif comanda == "Cauta dupa denumire":
                        self.__cautaDisciplinadenumire()
                    elif comanda == "Cauta dupa profesor":
                        self.__cautaDisciplinaprof()
                    elif comanda == "Afiseaza":
                        self.__afisezToateDisciplinele()
                    elif comanda == "Stop":
                        break
                    else:
                        print("Comanda incorecta!")
            elif comandagen == "Note":
                self.printmeniunota()
                while True:
                    comanda = input("Dati comanda: ").strip()
                    if comanda == "Adauga":
                        self.__adaugNota()
                    elif comanda == "Sterge":
                        self.__stergNota()
                    elif comanda == "Modifica":
                        self.__modificaNota()
                    elif comanda == "Afiseaza":
                        self.__afisezToateNotele()
                    elif comanda == "Stop":
                        break
                    else:
                        print("Comanda incorecta!")
            elif comandagen == "Statistici":
                self.printmeniustatistici()
                while True:
                    comanda = input("Dati comanda: ").strip()
                    if comanda == "A":
                        self.__statistica_alfabetic_nume()
                    elif comanda == "B":
                        self.__statistica_alfabetic_note()
                    elif comanda == "C":
                        self.__statistica_speciala()
                    elif comanda == "Stop":
                        break
                    else:
                        print("Comanda incorecta!")
            elif comandagen == "Stop":
                break
            else:
                print("Comanda incorecta!")
        print("Pa,pa!")
