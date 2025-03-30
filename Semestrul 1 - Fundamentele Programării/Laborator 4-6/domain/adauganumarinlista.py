from utils.erori import valideaza_p_ins, valideaza_numere
def get_lista_crt(numerecomplexe):
    return numerecomplexe[0]
def get_lista_undo(numerecomplexe):
    return numerecomplexe[1]
def add_complexe(numerecomplexe,c1):
    """
    Adauga un numar complex la sfarsitul listei
    """
    valideaza_numere(c1)
    complexe = get_lista_crt(numerecomplexe)
    complexe.append(c1)
    copie = []
    n = len(complexe)
    for i in range(0, n):
        copie.append(complexe[i])
    listaundo = get_lista_undo(numerecomplexe)
    listaundo.append(copie)

def ins_complexe_pe_poz(numerecomplexe,p,c):
    complexe = get_lista_crt(numerecomplexe)
    valideaza_p_ins(p, complexe)
    copie = []
    n = len(complexe)
    for i in range(0, n):
        copie.append(complexe[i])
    listaundo = get_lista_undo(numerecomplexe)
    listaundo.append(copie)
    aux = []
    for i in range(p, n):
        aux.append(complexe[i])
    del complexe[p:n]
    complexe.append(c)
    j = 0
    n = n + 1
    for i in range(p + 1, n ):
        complexe.append(aux[j])
        j = j + 1

