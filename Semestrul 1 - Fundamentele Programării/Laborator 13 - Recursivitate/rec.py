from functii import conditie
def  bckrecursiv(n, lista, result=None, index=0):
    if result is None:
        result = []
    mini = min(lista)

    if index == n - 1:
        return result

    for i in range(index, n):
        lista[index], lista[i] = lista[i], lista[index]
        if lista not in result:
            if conditie(lista, mini):
                result.append(list(lista))
        bckrecursiv(n, list(lista), result, index + 1)
        lista[index], lista[i] = lista[i], lista[index]

    return result
