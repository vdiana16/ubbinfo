from domain.adauganumarinlista import add_complexe, ins_complexe_pe_poz, get_lista_undo, get_lista_crt
from domain.modificaelementedinlista import sterge_de_pe_poz, sterge_din_interval, inlocuieste_aparitii
from domain.cautarenumere import imag_interval, modul_mai_mic_decat_10, modul_egal_cu_10
from domain.operatiicunumereledinlista import suma_secv, produs_secv, sortare_imag
from domain.filtrare import filtrare_reala_prim, filtrare_modul_nr
from domain.undo import undo_list
from ui.meniubatch import reset_nrc
def afis(nrc):
    print(nrc)

def afis_lista(listal):
    n = len(listal)
    if n== 0:
        print("Lista vida")
    else:
        print(listal[0],"+",listal[1],"i")
def afis_imag(nrc):
    n = len(nrc)
    for i in range(0, n):
        print(nrc[i],"i")

def afis_lista_de_liste(nrc):
    n = len(nrc)
    if n == 0:
        print("Lista vida!")
    else:
        for i in range(0, n):
            dictionar = nrc[i]
            a = int(dictionar['a'])
            b = int(dictionar['b'])
            print(a,"+",b,"i")

def get_elem():
    a = int(input("Introduceti partea reala a numarului complexe: "))
    b = int(input("Introduceti partea imaginara a numarului complexe: "))
    c = {'a': a, 'b': b}
    return c


def adaugare_la_complex(numerecomplexe):
    """
    Citeste un numar complex si il adauga la sfarsitul listei
    """
    c1=get_elem()
    try:
        add_complexe(numerecomplexe,c1)
        complexe = get_lista_crt(numerecomplexe)
        afis_lista_de_liste(complexe)
    except ValueError:
        print("Numere nule!")

def inserare_pe_poz(numerecomplexe):
    """
    Citeste pozitia si numarul complex care urmeaza sa fie adaugat si il adauga in lista
    """
    p=int(input("Introduceti pozitia pe care doriti sa inserati numarul complex: "))
    c=get_elem()
    try:
        ins_complexe_pe_poz(numerecomplexe,p,c)
        complexe = get_lista_crt(numerecomplexe)
        afis_lista_de_liste(complexe)
    except ValueError:
        print("Pozitie incorecta! Introduceti o pozitia valida!")

def partea_imaginara_din_interval(numerecomplexe):
    """
     Citeste capetele unui interval si afiseaza partea imaginara a numerelor complexe din intervalul respectiv
    """
    pozinc = int(input("Introduceti pozitia de inceput a secventei: "))
    pozsf = int(input("Introduceti pozitia de sfarsit a secventei: "))
    lista1 = []
    try:
        imag_interval(numerecomplexe, pozinc, pozsf, lista1)
        afis_imag(lista1)
    except ValueError:
        print("Cel putin una dintre pozitiile introduse nu e corecta! Introduceti pozitii valide!")

def tipareste_modul_maimic_decat10(numerecomplexe):
    """
    Afiseaza nr complexe care au modulul mai mic decat 10
    """
    lista2 = []
    try:
        modul_mai_mic_decat_10(numerecomplexe, lista2)
        afis_lista_de_liste(lista2)
    except ValueError:
        print("Nu exista numere complexe cu modulul mai mic decat 10!")

def tipareste_modul_egal_cu10(numerecomplexe):
    """
    Afiseaza nr complexe care au modulul egal cu 10
    """
    lista3 = []
    try:
        modul_egal_cu_10(numerecomplexe, lista3)
        afis_lista_de_liste(lista3)
    except ValueError:
        print("Nu exista numere complexe cu modulul egal cu 10!")

def sterge_nr_poz(numerecomplexe):
    """
    Sterge nr complex de pe pozitia introdusa
    """
    m = int(input("Introduceti pozitia de pe care doriti sa stergeti elementul: "))
    try:
        sterge_de_pe_poz(numerecomplexe,m)
        complexe = get_lista_crt(numerecomplexe)
        afis_lista_de_liste(complexe)
    except ValueError:
        print("Pozitie incorecta! Introduceti o pozitia valida!")

def sterge_interval(numerecomplexe):
    """
    Sterge nr complexe din intervalul introdus
    """
    pozst = int(input("Introduceti pozitia de pe care doriti sa inceapa stergerea elementelor: "))
    pozdr = int(input("Introduceti pozitia pana pe care doriti sa se stearga elementele: "))
    try:
        sterge_din_interval(numerecomplexe,pozst,pozdr)
        complexe = get_lista_crt(numerecomplexe)
        afis_lista_de_liste(complexe)
    except ValueError:
        print("Pozitii incorecte! Introduceti pozitii valide")

def inloc_aparitii(numerecomplexe):
    print("Introduceti numarul de inlocuit: ")
    cdeinloc = get_elem()
    print("Introduceti numarul inlocuitor: ")
    cinloc = get_elem()
    try:
        inlocuieste_aparitii(numerecomplexe,cdeinloc,cinloc)
        complexe = get_lista_crt(numerecomplexe)
        afis_lista_de_liste(complexe)
    except ValueError:
        print("Nu s-a efectuat nicio modificare!")

def sum_secv(numerecomplexe):
    suma = []
    pozstart = int(input("Introduceti pozitia de inceput a secventei: "))
    pozstop = int(input("Introduceti pozitia de sfarsit a secventei: "))
    try:
        suma_secv(numerecomplexe,pozstart,pozstop,suma)
        afis_lista(suma)
    except ValueError:
        print("Cel putin una dintre pozitiile introduse nu e corecta! Introduceti pozitii valide!")

def prod_secv(numerecomplexe):
    pozin = int(input("Introduceti pozitia de inceput a secventei: "))
    pozsf = int(input("Introduceti pozitia de sfarsit a secventei: "))
    produs = []
    try:
        produs_secv(numerecomplexe,pozin,pozsf,produs)
        afis_lista(produs)
    except ValueError:
        print("Cel putin una dintre pozitiile introduse nu e corecta! Introduceti pozitii valide!")

def sort_imag(numerecomplexe):
    """
    Sorteaza descrescator in functie de partea imaginara nr complexe din lista
    """
    try:
        sortare_imag(numerecomplexe)
        complexe = get_lista_crt(numerecomplexe)
        afis_lista_de_liste(complexe)
    except ValueError:
        print("Nu s-a efectuat nicio modificare listei!")

def filt_reala_prim(numerecomplexe):
    """
    Filtreaza numerele prime din lista de nr complexe
    :param complexe:
    :return:
    """
    try:
        lista = []
        filtrare_reala_prim(numerecomplexe,lista)
        afis_lista_de_liste(lista)
    except ValueError:
        print("Nu s-a efectuat nicio modificare listei!")

def filt_modul_nr(numerecomplexe,s):
    nrdat = int(input("Introduceti numarul dupa care se va filtra lista in functie de modul: "))
    try:
        lista = []
        filtrare_modul_nr(numerecomplexe, nrdat, s, lista)
        afis_lista_de_liste(lista)
    except ValueError:
        print("Nu s-a efectuat nicio modificare listei!")

def undo(numerecomplexe):
    try:
        undo_list(numerecomplexe)
        complexe = get_lista_crt(numerecomplexe)
        afis_lista_de_liste(complexe)
    except ValueError:
        print("Nicio operatie care sa modifice lista nu a fost efectuata")
def tipareste_meniu():
    """
    Afiseaza meniul problemei, operatiile pe care le poate realiz
    """
    print("Operatii cu numere complexe: ")
    print("1 pentru adaugare număr complex la sfârșitul listei")
    print("2 pentru inserare număr complex pe o poziție dată")
    print("3 pentru stergerea unui element de pe o poziție dată")
    print("4 pentru stergerea elementelor de pe un interval de poziții")
    print("5 pentru inlocuirea tuturor aparițiilor unui număr complex cu un alt număr complex.")
    print("6 pentru tipărire partea imaginara pentru numerele din listă. Se dă intervalul de poziții")
    print("7 pentru tipărire toate numerele complexe care au modulul mai mic decât 10")
    print("8 pentru tipărește toate numerele complexe care au modulul egal cu 10 ")
    print("9 pentru suma numerelor dintr-o subsecventă dată.Se da poziția de început și sfârșit")
    print("10 pentru produsul numerelor dintr-o subsecventă dată (se da poziția de început și sfârșit).")
    print("11 pentru tiparirea listei sortate descrescător după partea imaginara")
    print("12 pentru filtrare parte reala prim – elimină din listă numerele complexe la care partea reala este prim")
    print("13 pentru filtrare modul – elimina din lista numerele complexe la care modulul este: ")
    print("14 pentru refacerea ultimei operații (lista de numere revine la numerele ce existau înainte de ultima operație care a modificat lista)")
    print("Introduceti tasta dorita: ")

def tipareste_mini_meniu():
    print("1 in functie de modulul numerelor mai mici decat un numar dat")
    print("2 in functie de modulul numerelor egale cu un numar dat")
    print("3 in functie de modulul numerelor mare decat un numar dat")
    print("Introduceti tasta dorita: ")


def run():
    """
    Implementeaza interfata utilizator
    """
    numerecomplexe = reset_nrc()
    ok = False
    while not ok:
        print("Lista curenta: ")
        afis_lista_de_liste(numerecomplexe[0])
        tipareste_meniu()
        m = input().strip()
        if m == '1':
            adaugare_la_complex(numerecomplexe)
        elif m == '2':
            inserare_pe_poz(numerecomplexe)
        elif m == '3':
            sterge_nr_poz(numerecomplexe)
        elif m == '4':
            sterge_interval(numerecomplexe)
        elif m == '5':
            inloc_aparitii(numerecomplexe)
        elif m == '6':
            partea_imaginara_din_interval(numerecomplexe)
        elif m == '7':
            tipareste_modul_maimic_decat10(numerecomplexe)
        elif m == '8':
            tipareste_modul_egal_cu10(numerecomplexe)
        elif m == '9':
            sum_secv(numerecomplexe)
        elif m == '10':
            prod_secv(numerecomplexe)
        elif m == '11':
            sort_imag(numerecomplexe)
        elif m == '12':
            filt_reala_prim(numerecomplexe)
        elif m == '13':
            tipareste_mini_meniu()
            s = input().strip()
            filt_modul_nr(numerecomplexe,s)
        elif m == '14':
            undo(numerecomplexe)
        elif m == '15':
            ok = True
        else:
            print("Tasta incorecta! Mai incearca...")
    print("Pa, pa!")