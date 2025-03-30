from utils.testnrprim import t_nr_prim
from utils.modulnrcomplex import modul
from utils.erori import valideaza_modific
from domain.adauganumarinlista import get_lista_crt
def get_parte_reala(complexe,i):
    dictionar = complexe[i]
    a = dictionar['a']
    return a
def filtrare_reala_prim(numerecomplexe,lista4):
    complexe = get_lista_crt(numerecomplexe)
    modific = False
    n = len(complexe)
    i = 0
    for i in range(0,n):
        partreal = get_parte_reala(complexe,i)
        if t_nr_prim(partreal) == 0:
            modific = True
            lista4.append(complexe[i])
    valideaza_modific(modific)

def filtrare_modul_nr(numerecomplexe,nrdat,s,lista5):
    complexe = get_lista_crt(numerecomplexe)
    modific = False
    n = len(complexe)
    if s == '1':
        for i in range(0,n):
            print(modul(complexe[i]))
            if modul(complexe[i]) >= nrdat:
                modific = True
                lista5.append(complexe[i])
    if s == '2':
        for i in range(0,n):
            if modul(complexe[i]) != nrdat:
                modific = True
                lista5.append(complexe[i])
    if s == '3':
        for i in range(0,n):
            if modul(complexe[i]) <= nrdat:
                modific = True
                lista5.append(complexe[i])
    valideaza_modific(modific)
