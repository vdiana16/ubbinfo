    from iter import bckiterativ
from rec import bckrecursiv
from teste import test_cresc,test_descresc
from functii import printlista
def tipareste_meniu():
    print("Optiuni:")
    print("1 pentru backtracking iterativ")
    print("2 pentru backtracking recursiv")
    print("3 pentru iesire")
def run_teste():
    test_cresc()
    test_descresc()

def run():
    ok = False
    while not ok:
        tipareste_meniu()
        print("Introduceti optiunea dorita:")
        m = input().strip()

        if m == "1":
            n = int(input("Introduceti numarul de elemente ale listei: "))
            lista = []
            numere = input("Introduceti lista: ")
            lista = [int(x) for x in numere.split()]
            lista = bckiterativ(n, lista)
            try:
                printlista(lista)
            except ValueError as eroare:
                print(eroare)

        elif m == "2":
            n = int(input("Introduceti numarul de elemente ale listei: "))
            lista = []
            numere = input("Introduceti lista: ")
            lista = [int(x) for x in numere.split()]
            lista = bckrecursiv(n, lista)
            try:
                printlista(lista)
            except ValueError as eroare:
                print(eroare)
        elif m == "3":
            ok = True
        else:
            print("Optiune incorecta")
    print("Pa,pa!")


    
