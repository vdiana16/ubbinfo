from utils.modulnrcomplex import modul
from utils.erori import valideaza_poziti, valideaza_lista
from domain.adauganumarinlista import get_lista_crt
def get_parte_imag(complexe,i):
    nr = complexe[i]
    b = nr['b']
    return b
def imag_interval(numerecomplexe, pozinc, pozsf, lista1):
    complexe = get_lista_crt(numerecomplexe)
    valideaza_poziti(pozinc, pozsf, complexe)
    for i in range(pozinc, pozsf+1):
        partimag = get_parte_imag(complexe,i)
        lista1.append(partimag)

def modul_mai_mic_decat_10(numerecomplexe, lista2):
    complexe = get_lista_crt(numerecomplexe)
    n = len(complexe)
    for i in range(0,n):
        if modul(complexe[i])<10:
            lista2.append(complexe[i])
    valideaza_lista(lista2)

def modul_egal_cu_10(numerecomplexe, lista3):
    complexe = get_lista_crt(numerecomplexe)
    n = len(complexe)
    for i in range(0,n):
        if modul(complexe[i])==10:
            lista3.append(complexe[i])
    valideaza_lista(lista3)

