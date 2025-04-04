from functii import conditie

def bckiterativ(n, lista):
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

