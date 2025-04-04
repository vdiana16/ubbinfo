def valideaza_p_ins(p, complexe):
    n = len(complexe)
    if p > n or p < 0:
        raise ValueError("Pozitie incorecta!")

def valideaza_poziti(p1, p2, complexe):
    n = len(complexe)
    if p1 > p2:
        raise ValueError("Pozitii incorecte!")
    else:
        if p1 < 0 or p1 >= n:
            raise ValueError("Pozitia de inceput a secventei este incorecta!")
        else:
            if p2 < 0 or p2 >= n:
                raise ValueError("Pozitia de sfarsit a secventei este incorecta!")

def valideaza_lista(lista):
    lg = len(lista)
    if lg == 0:
        raise ValueError("Nu exista numere complexe cu modulul mai mic decat 10!")

def valideaza_p_sterg(p, complexe):
    n = len(complexe)
    if p > n + 1 or p < 0:
        raise ValueError("Pozitie incorecta!")

def valideaza_modific(modific):
    if modific == False:
        raise ValueError("Nu s-a efectuat nicio modificare!")

def valideaza_numere(c1):
    if c1['a'] == 0 and c1['b'] == 0:
        raise ValueError("Numere nule!")