from ui.meniucomun import reset_nrc
from domain.adauganumarinlista import add_complexe
from domain.modificaelementedinlista import sterge_de_pe_poz
from domain.filtrare import filtrare_reala_prim
from domain.undo import undo_list
def get_element(nrcomplex):
    a=nrcomplex[0]
    b=nrcomplex[2]
    elemcomplex={'a':a,'b':b}
    return elemcomplex

def get_pozitie(poz):
    p = int(poz)
    return p
def valideaza_preluare(preluare):
    n = len(preluare)
    for i in range(0,n):
        m=len(preluare[i])
        sir = preluare[i]
        cont = 0
        for j in range(0,m):
            if sir[j] == ',':
                cont=cont+1
        if cont >=2:
            raise ValueError("Separatorul este ;")
def meniu_batch_mode():
    print("Introduceti comanda")
    comanda=input().strip()
    preluare=comanda.split(";")
    valideaza_preluare(preluare)
    lgcom = len(preluare)
    numerecomplexe=reset_nrc()
    for i in range(0,lgcom):
        comcrt=preluare[i].split( )
        print(comcrt)
        if comcrt[0] == 'add':
            nrcomplex = comcrt[1]
            nradd = get_element(nrcomplex)
            add_complexe(numerecomplexe,nradd)
            print(numerecomplexe[0])
        elif comcrt[0] == 'del':
            poz = comcrt[1]
            pozitie = get_pozitie(poz)
            sterge_de_pe_poz(numerecomplexe,pozitie)
            print(numerecomplexe[0])
        elif comcrt[0] == 'filter':
            lista4 = []
            filtrare_reala_prim(numerecomplexe,lista4)
            print(lista4)
        elif comcrt[0] == 'undo':
            undo_list(numerecomplexe)
            print(numerecomplexe[0])
    print("Rezultat final:")
    print(numerecomplexe[0])