from utils.erori import valideaza_poziti,valideaza_modific
from domain.adauganumarinlista import get_lista_crt,get_lista_undo
def suma_secv(numerecomplexe,pozstart,pozstop,suma):
    complexe = get_lista_crt(numerecomplexe)
    n = len(complexe)
    valideaza_poziti(pozstart,pozstop,complexe)
    sreal=0
    simag=0
    for i in range(pozstart,pozstop+1):
        dict = complexe[i]
        a = dict['a']
        b = dict['b']
        sreal=sreal+a
        simag=simag+b
    suma.append(sreal)
    suma.append(simag)

def produs_secv(numerecomplexe,pozin,pozsf,produs):
    complexe = get_lista_crt(numerecomplexe)
    valideaza_poziti(pozin,pozsf,complexe)
    preal=1
    pimag=1
    for i in range(pozin,pozsf+1):
        dict=complexe[i]
        a=dict['a']
        b=dict['b']
        preal=preal*a
        pimag=pimag*b
    produs.append(preal)
    produs.append(pimag)

def get_parte_imag(complexe,i):
    laux1 = complexe[i]
    img = laux1['b']
    return img
def sortare_imag(numerecomplexe):
    complexe = get_lista_crt(numerecomplexe)
    copie = []
    n = len(complexe)
    modific = False
    for i in range(0,n-1):
        for j in range(i+1,n):
            a=get_parte_imag(complexe,i)
            b=get_parte_imag(complexe,j)
            if a < b:
                modific = True
                aux = []
                aux = complexe[i]
                complexe[i] = complexe[j]
                complexe[j] = aux
    for i in range(0, n):
        copie.append(complexe[i])
    listaundo = numerecomplexe[1]
    listaundo.append(copie)
    valideaza_modific(modific)

