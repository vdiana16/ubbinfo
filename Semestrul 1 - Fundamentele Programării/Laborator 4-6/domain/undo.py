def undo_list(numerecomplexe):
    listaundo = numerecomplexe[1]
    if listaundo == [[]]:
        raise ValueError("Nu exista nicio operatie de refacuta")
    else:
        complexe = listaundo[-2]
        listaundo = listaundo [:-2]
        numerecomplexe[0] = complexe
        numerecomplexe[1] = listaundo

