from utils.erori import valideaza_p_sterg, valideaza_poziti,valideaza_modific
from domain.adauganumarinlista import get_lista_crt
def sterge_de_pe_poz(numerecomplexe,m):
    complexe = get_lista_crt(numerecomplexe)
    valideaza_p_sterg(m,complexe)
    n = len(complexe)
    aux = []
    for i in range(m+1,n):
        aux.append(complexe[i])
    del complexe[m:n]
    j=0
    for i in range(m,n-1):
        complexe.append(aux[j])
        j=j+1
    copie = []
    n = len(complexe)
    for i in range(0, n):
        copie.append(complexe[i])
    listaundo = numerecomplexe[1]
    listaundo.append(copie)

def sterge_din_interval(numerecomplexe,pozst,pozdr):
    complexe = get_lista_crt(numerecomplexe)
    copie = []
    n = len(complexe)
    valideaza_poziti(pozst,pozdr,complexe)
    aux = []
    for i in range(pozdr+1,n):
        aux.append(complexe[i])
    del complexe[pozst:n]
    poz = n - (pozdr - pozst + 1)
    j = 0
    for i in range(pozst,poz):
        complexe.append(aux[j])
        j=j+1
    n = len(complexe)
    for i in range(0, n):
        copie.append(complexe[i])
    listaundo = numerecomplexe[1]
    listaundo.append(copie)

def inlocuieste_aparitii(numerecomplexe,cdeinloc,cinloc):
    complexe = get_lista_crt(numerecomplexe)
    copie = []
    n = len(complexe)
    for i in range(0, n):
        copie.append(complexe[i])
    listaundo = numerecomplexe[1]
    listaundo.append(copie)
    modific = False
    for i in range(0, n):
        if complexe[i] == cdeinloc:
            complexe[i] = []
            complexe[i] = cinloc
            modific = True
    valideaza_modific(modific)
