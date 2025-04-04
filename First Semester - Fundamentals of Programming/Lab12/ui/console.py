import math
from domain.validators import ValidatorException


class Consola:
    def __init__(self, srvs, srvd, srvn):
        self.__srvs = srvs
        self.__srvd = srvd
        self.__srvn = srvn

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
            ids = self.__srvs.cautaid()
            st = self.__srvs.adaugareStudent(str(ids), nume)
            print("Student ", st.getNume(), " salvat...")
        except ValidatorException as ex:
            print(ex.getErori())

    def __adaugrandomStudent(self):
        x = int(input("Dati numarul de stuudenti pe care doriti sa ii adaugati:"))
        try:
            contor = self.__srvs.cautaid()
            self.__srvs.adaugarerandomStudent(x, contor)
            print("Au fost salvati", x, "studenti")
        except ValidatorException as ex:
            print(ex.getErori())

    def __stergStudent(self):
        """
        Sterg studentul cu id idst din catalog
        :return:
        """
        idst = input("Dati id-ul studentului: ")
        try:
            self.__srvs.stergereStudent(idst)
            print("Student ", idst, " sters...")
        except ValueError as e:
            print(e)
        except ValidatorException as ex:
            print(ex.getErori())

    def __stergtStudent(self):
        """
        Strerge toti studentii
        :return:
        """
        self.__srvs.stergeretotiStudent()

    def __modificaStudent(self):
        idst = input("Dati id-ul studentului: ")
        try:
            numenou = input("Dati numele nou al studentului: ")
            self.__srvs.modificareStudent(idst, numenou)
            print("Student ", numenou, " modificat...")
        except ValueError as e:
            print(e)
        except ValidatorException as ex:
            print(ex.getErori())

    def __cautaStudentid(self):
        idst = input("Dati id-ul studentului dorit: ")
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
            idd = self.__srvd.cautaidd()
            dis = self.__srvd.adaugareDisciplina(str(idd), denumire, profesor)
            print("Disciplina ", dis.getDenumire(), " salvata...")
        except ValidatorException as ex:
            print(ex.getErori())

    def __stergDisciplina(self):
        """
        Sterg discipline cu id iddis
        :return:
        """
        iddis = input("Dati id-ul disciplinei: ")
        try:
            self.__srvd.stergereDisciplina(iddis)
            print("Disciplina ", iddis, " stearsa...")
        except ValidatorException as ex:
            print(ex.getErori())

    def __stergtDisciplina(self):
        """
        Strerge toate disciplinele
        :return:
        """
        self.__srvd.stergeretotDisciplina()


    def __modificaDisciplina(self):
        iddis = input("Dati id-ul disciplinei: ")
        denumirenoua = input("Dati denumirea noua a disciplinei: ")
        profnou = input("Dati numele profesorului disciplinei: ")
        try:
            self.__srvd.modificareDisciplina(iddis, denumirenoua, profnou)
            print("Disciplina ", denumirenoua, " modificata...")
        except ValidatorException as ex:
            print(ex.getErori())

    def __cautaDisciplinaid(self):
        iddis = input("Dati id-ul disciplinei dorite: ")
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
            cont = self.__srvd.cautaidd()
            self.__srvd.adaugarerandomDisciplina(y, cont)
            print("Au fost salvate", y, "discipline")
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
                print("Id nota:",notaa.getIdnota(), "Id student:",notaa.getIdstudent(),"Id disciplina:", notaa.getIddisciplina(), "Nota:", notaa.getNota())
    def __adaugNota(self):
        """
        Adauga nota
        :return:
        """
        try:
            idst = input("Dati id-ul studentului: ")
            student = self.__srvs.cautareStudentid(idst)
            if student:
                print("\n")
                print("Acestea sunt disciplinele disponibile:")
                lista = self.__srvd.getToateDis()
                for dis in lista:
                    print(dis.getDenumire(),"cu id-ul", dis.getIdd())
                print("\n")
                iddis = input("Dati id-ul disciplinei: ")
                discip = self.__srvd.cautareDisciplinaid(iddis)
                if discip:
                    notaa = float(input("Dati nota studentului: "))
                    idn = self.__srvn.cautaidn()
                    self.__srvn.adaugare_nota(idn,idst, iddis, notaa)
        except ValueError as ex:
            print(ex)
        except ValidatorException as e:
            print(e.getErori())

    def __stergNota(self):
        """
        Sterg nota
        :return:
        """
        try:
            idst = input("Dati id-ul studentului: ")
            student = self.__srvs.cautareStudentid(idst)
            if student:
                print("\n")
                print("Acestea sunt disciplinele disponibile:")
                lista = self.__srvd.getToateDis()
                for dis in lista:
                    print(dis.getDenumire())
                print("\n")
                iddis = input("Dati id-ul disciplinei: ")
                discip = self.__srvd.cautareDisciplinaid(iddis)
                if discip:
                    self.__srvn.stergere_nota(idst, iddis)
        except ValueError as e:
            print(e)
        except ValidatorException as ex:
            print(ex.getErori())

    def __stergtNote(self):
        """
        Strerge toate disciplinele
        :return:
        """
        self.__srvn.stergere_tot_nota()


    def __modificaNota(self):
        """
        Modifica nota
        :return:
        """
        try:
            idn = input("Dati id-ul notei: ")
            idst = input("Dati id-ul studentului: ")
            student = self.__srvs.cautareStudentid(idst)
            if student:
                print("\n")
                print("Acestea sunt disciplinele disponibile:")
                lista = self.__srvd.getToateDis()
                for dis in lista:
                    print(dis.getDenumire(), "cu id-ul", dis.getIdd())
                print("\n")
                iddis = input("Dati id-ul disciplinei: ")
                discip = self.__srvd.cautareDisciplinaid(iddis)
                if discip:
                    notanoua = float(input("Dati nota modificata a studentului: "))
                    self.__srvn.modificare_nota(idn, idst, iddis, notanoua)
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
        try:
            lista_note = self.__srvn.getNote()
            lista = []
            for nota in lista_note:
                st = self.__srvs.cautareStudentid(nota.getIdstudent())
                lista.append([nota.getIdnota(), nota.getIdstudent(), st.getNume(), nota.getIddisciplina(), nota.getNota()])
            self.__srvn.ordonare_studenti_nume(lista)
            print("Statistica privind notele studentilor, ordonati alfabetic dupa nume")
            for elem in lista:
                print("id student:", elem[1])
                print("nume student:", elem[2])
                print("id disciplina", elem[3])
                print("nota diciplina", elem[4])
        except ValueError as e:
            print(e)

    def __statistica_crescator_note(self):
        """
        Generare statistica
        :return:
        """
        try:
            lista_note = self.__srvn.getNote()
            lista = []
            for nota in lista_note:
                st = self.__srvs.cautareStudentid(nota.getIdstudent())
                lista.append([nota.getIdnota(), nota.getIdstudent(), st.getNume(), nota.getIddisciplina(), nota.getNota()])
            self.__srvn.ordonare_studenti_note(lista)
            print("Statistica privind notele studentilor, ordonati crescator dupa nota")
            for elem in lista:
                print("id student:", elem[1])
                print("nume student:", elem[2])
                print("id disciplina", elem[3])
                print("nota diciplina", elem[4])
        except ValueError as e:
            print(e)

    def __statistica_20(self):
        try:
            lista_studenti = self.__srvs.getTotiStud()
            lista_medie = []
            for st in lista_studenti:
                id_stud = st.getId()
                nume = st.getNume()
                medie = self.__srvn.medie_note_student(id_stud)
                lista_medie.append([nume, medie])
            self.__srvn.ordonare_medie(lista_medie)
            lista_m = self.__srvn.primi_20_la_suta(lista_medie)
            print("Statistica privind 20% dintre studenti")
            for i in range (len(lista_m)):
                print("Nume student: ",lista_m[i][0],"Medie student: ",lista_m[i][1])
        except ValueError as e:
            print(e)
    def __statistica_speciala(self):
        print("Acestea sunt disciplinele disponibile:")
        lista = self.__srvd.getToateDis()
        for dis in lista:
            print(dis.getDenumire(),"cu id:",dis.getIdd())
        id_disciplina = int(input("Dati id-ul disciplinei: "))
        try:
            lista = self.__srvn.get_toti_studdis(id_disciplina)
            listafilt = self.__srvn.get_toti_s5(lista)
            listaspec = self.__srvs.ad_nume_lista_spec(listafilt)
            self.__srvn.ordonare_nota_s5(listaspec)
            for i in range(len(listaspec)):
                print("Numele studentului: ",listaspec[i][1], "Nota studentului: ",listaspec[i][2])
        except ValueError as e:
            print(e)

    def printmeniugen(self):
        print("         Introduceti comanda generala dorita:")
        print("     Studenti pentru studenti")
        print("     Discipline pentru discipline")
        print("     Note pentru note")
        print("     Statistici pentru statistici")

    def printmeniustud(self):
        print("         Introduceti comanda dorita:")
        print("     Adauga - pentru a adauga un student")
        print("     Adauga random - pentru a adauga x studenti")
        print("     Sterge - pentru a  sterge studentul x")
        print("     Sterge tot- pentru a  sterge toti studentii")
        print("     Modifica - pentru a modifica studentul x")
        print("     Cauta dupa id - pentru a cauta studentul x dupa id")
        print("     Cauta dupa nume - pentru a cauta studentul x dupa nume")

    def printmeniunota(self):
        print("         Introduceti comanda dorita:")
        print("     Adauga - pentru a adauga o nota unui student la o disciplina")
        print("     Sterge - pentru a  sterge nota unui student la o disciplina")
        print("     Sterge tot- pentru a  sterge toate notele")
        print("     Modifica - pentru a modifica nota unui student la o disciplina")
        print("     Afiseaza - pentru a afisa lista de note")

    def printmeniudis(self):
        print("         Introduceti comanda dorita:")
        print("     Adauga - pentru a adauga o discipline")
        print("     Adauga random - pentru a adauga x discipline")
        print("     Sterge - pentru a  sterge disciplina x")
        print("     Sterge tot- pentru a  sterge toate disciplinele")
        print("     Modifica - pentru a modifica disciplina x")
        print("     Cauta dupa id - pentru a cauta disciplina x dupa id")
        print("     Cauta dupa nume - pentru a cauta disciplina x dupa denumire")
        print("     Cauta dupa nume - pentru a cauta disciplina x dupa profesor")

    def printmeniustatistici(self):
        print("         Introduceti comanda dorita:")
        print("     A - pentru statistica privind notele studentilor, ordonati crescator dupa nume")
        print("     B - pentru statistica privind notele studentilor, ordonati crescator dupa nota")
        print("     C - pentru statistica privind primi 20% din studenți ordonat dupa media notelor la toate disciplinele")
        print("     D - pentru statistica privind primi 20% din studenți ordonat dupa media notelor la toate disciplinele -nume și notă")
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
                    elif comanda == "Sterge tot":
                        self.__stergtStudent()
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
                    elif comanda == "Sterge tot":
                        self.__stergtDisciplina()
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
                    elif comanda == "Sterge tot":
                        self.__stergtNote()
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
                        self.__statistica_crescator_note()
                    elif comanda == "C":
                        self.__statistica_20()
                    elif comanda == "D":
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
