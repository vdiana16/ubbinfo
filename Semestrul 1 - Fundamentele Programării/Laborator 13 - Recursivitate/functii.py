def cresc(lista):
    if not lista:
        return False
    copie = sorted(lista)
    if copie == lista:
        return True
    return False


def descresc(lista):
    if not lista:
        return False
    copie = sorted(lista, reverse=True)
    if copie == lista:
        return True
    return False

def conditie(lista, minim):
    indexminim = lista.index(minim)
    if indexminim == 0 or indexminim == len(lista) - 1:
        return False
    if descresc(lista[:indexminim]) == False or cresc(lista[indexminim + 1:]) == False:
        return False
    return True

def printlista(lista):
    if lista:
        for el in lista:
            for i in range(0, len(el)):
                if i == len(el) - 1:
                    print(el[i])
                else:
                    print(el[i], end=" ")
    else:
        raise ValueError("Nu exista permutari!")