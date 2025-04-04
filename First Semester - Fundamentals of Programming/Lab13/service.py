from functii import cresc,descresc
def conditie(lista, maxim):
    minim = lista.index(maxim)
    if minim == 0 or minim == len(lista) - 1:
        return False
    if descresc(lista[:minim]) == False or cresc(lista[minim + 1:]) == False:
        return False
    return True


def backIter(n, lista):
    rez = []
    mini = min(lista)
    x = [(list(lista), 0)]
    while x:
        permcrt, index = x.pop()
        if index == n - 1:
            continue
        for i in range(index, n):
            permcrt[index], permcrt[i] = permcrt[i], permcrt[index]
            if not permcrt in rez:
                if conditie(permcrt, mini):
                    rez.append(list(permcrt))
            x.append((list(permcrt), index + 1))
            permcrt[index], permcrt[i] = permcrt[i], permcrt[index]
    return rez
