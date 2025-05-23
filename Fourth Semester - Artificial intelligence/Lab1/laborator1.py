1. Să se determine ultimul (din punct de vedere alfabetic) cuvânt care poate apărea
într-un text care conține mai multe cuvinte separate prin ” ” (spațiu). De ex.
ultimul (dpdv alfabetic) cuvânt din ”Ana are mere rosii si galbene” este cuvântul
"si".
"""
def ultimulCuvant(text):
    """
    Determina ultimul cuvant din punct de vedere lexicografic dintr-un text
    :param text: str
    :return: str
    Complexitate timp: Theta(n), unde n e numarul de litere din text
    Complexitate spatiu: Theta(m), unde m e numarul de cuvinte din text
    """
    if len(text) == 0:
        raise ValueError("Textul nu poate fi gol")
    x = text.split()
    max = x[0]
    x = x[1:]
    for word in x:
        if word > max:
            max = word
    return max

def testep1():
  assert(ultimulCuvant("Ana are mere rosii si galbene") == "si")
  assert(ultimulCuvant("Ana are zece mere si zeci de portocale") == "zeci")
  assert(ultimulCuvant("A B C Z A A") == "Z")
  assert(ultimulCuvant("Ana are 2 mere") == "mere")
  try:
    ultimulCuvant("")
    assert False
  except ValueError:
    assert True

def ultimulCuvantAI(text):
    """
    Determina ultimul cuvant din punct de vedere lexicografic dintr-un text
    Complexitate timp: Theta(n)
    Complexitate spatiu: Theta(n)
    """
    cuvinte = text.split()  # Separă textul în cuvinte
    return max(cuvinte)  # Returnează cuvântul cel mai mare alfabetic

def main1():
    testep1()
    text = input("Introduceti textul ")
    print(ultimulCuvant(text))
    print(ultimulCuvantAI(text))

main1()

"""
2.Să se determine distanța Euclideană între două locații identificate prin
 perechi de numere. De ex. distanța între (1,5) și (4,1) este 5.0
"""
def distantaEuclidiana(a, b):
  """
  Determina distanta euclidiana dintre doua puncte
  :param a: tuplu
  :param b: tuplu
  :return: float
  Complexitate timp: Theta(1)
  Complexitate spatiu: Theta(1)
  """
  dist = ((b[0]-a[0])**2 + (b[1]-a[1])**2) ** 0.5
  return dist

def testep2():
  assert(distantaEuclidiana((1, 5), (4, 1)) == 5)
  assert(distantaEuclidiana((3, 0), (0, 4)) == 5)
  assert(distantaEuclidiana((0, 3), (4, 0)) == 5)

import math
def distantaEuclidianaAI(punct1, punct2):
  """
  Determina distanta euclidiana dintre doua puncte
  Complexitate timp: Theta(1)
  Complexitate spatiu: Theta(1)
  """
  x1, y1 = punct1
  x2, y2 = punct2
  return math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

def main2():
  testep2()
  punct1 = (int(input("Introduceti x1: ")), int(input("Introduceti y1: ")))
  punct2 = (int(input("Introduceti x2: ")), int(input("Introduceti y2: ")))
  print(distantaEuclidiana(punct1, punct2))
  print(distantaEuclidianaAI(punct1, punct2))

main2()

"""
3.Să se determine produsul scalar a doi vectori rari care conțin numere reale.
 Un vector este rar atunci când conține multe elemente nule.
 Vectorii pot avea oricâte dimensiuni. De ex. produsul scalar a 2 vectori
 unidimensionali [1,0,2,0,3] și [1,2,0,3,1] este 4.
"""

def produsScalar(vector1, vector2):
  """
  Determina produsul scalar a doi vectori
  :param vector1: list
  :param vector2: list
  :return: float
  Complexitate timp: Theta(n), unde n e numarul de elemente continute de
                               vectorii rari
  Complexitate spatiu: Theta(1)
  """
  if len(vector1) != len(vector2):
    raise ValueError("Vectorii trebuie să aibă aceeași dimensiune!")
  produs = 0
  n = len(vector1)
  for i in range(n):
    produs += vector1[i] * vector2[i]
  return produs

def testep3():
  assert(produsScalar([1,0,2,0,3], [1,2,0,3,1]) == 4)
  assert(produsScalar([1,2,3,4], [5,4,3,2]) == 30)
  assert(produsScalar([0,0,0,0,0], [1,2,3,4,5]) == 0)
  assert(produsScalar([1,2,3,4], [0,0,0,0]) == 0)
  try:
    produsScalar([1,2,3,4], [0,0,0,0,0])
    assert False
  except ValueError:
    assert True

def produsScalarAI(vector1, vector2):
  """
  Determina produsul scalar a doi vectori
  Complexitate timp: Theta(n), unde n e numarul de elemente continute de
                               vectorii rari
  Complexitate spatiu: Theta(1)
  """
    # Verificăm că vectorii au aceeași dimensiune
    #assert len(vector1) == len(vector2), "Vectorii trebuie să aibă aceeași dimensiune!"

    # Calculăm doar pentru pozițiile unde cel puțin un element este nenul
  return sum(v1 * v2 for v1, v2 in zip(vector1, vector2) if v1 != 0 and v2 != 0)

def main3():
  testep3()
  lista1 = list(map(int, input("Introduceți primul vector rar: ").split()))
  lista2 = list(map(int, input("Introduceți al doilea vector rar: ").split()))
  print(produsScalar(lista1, lista2))
  print(produsScalarAI(lista1, lista2))

main3()

"""
4.Să se determine cuvintele unui text care apar exact o singură dată în acel
text. De ex. cuvintele care apar o singură dată în ”ana are ana are mere rosii
ana" sunt: 'mere' și 'rosii'.
"""

def cuvinteUnice(text):
  """
  Determina cuvintele unice dintr-un text
  :param text: str
  :return: list
  Complexitate timp: Theta(n), unde n e numarul de litere din text
  Complexitate spatiu: Theta(m), unde m e numarul de cuvinte din text
  """
  if len(text) == 0:
    raise ValueError("Textul nu poate fi gol")
  cuvinte = text.split()
  frecvcuv = {}
  for cuv in cuvinte:
    frecvcuv[cuv] = frecvcuv.get(cuv, 0) + 1
  rezultat = ""
  for cuv in frecvcuv:
    if frecvcuv[cuv] == 1:
      rezultat += cuv + " "
  return rezultat

def testep4():
  assert(cuvinteUnice("ana are ana are mere rosii ana") == "mere rosii ")
  assert(cuvinteUnice("ana are mere") == "ana are mere ")
  assert(cuvinteUnice("ana are mere mere mere rosii") == "ana are rosii ")
  try:
    cuvinteUnice("")
    assert False
  except ValueError:
    assert True

from collections import Counter

def cuvinte_unice(text):
  """
  Determina cuvintele unice dintr-un text
  Complexitate timp: Theta(n), unde n e numarul de litere din text
  Complexitate spatiu: Theta(m), unde m e numarul de cuvinte din text
  """
  # Împărțim textul în cuvinte
  cuvinte = text.split()

  # Numărăm frecvența fiecărui cuvânt
  frecventa_cuvintelor = Counter(cuvinte)

  # Selectăm cuvintele care apar o singură dată
  cuvinte_o_data = [cuvant for cuvant, frecventa in frecventa_cuvintelor.items()
                    if frecventa == 1]

  return cuvinte_o_data

def main4():
  testep4()
  text = input("Introduceti textul ")
  print(cuvinteUnice(text))
  print(cuvinte_unice(text))

main4()

"""
5.Pentru un șir cu n elemente care conține valori din mulțimea{1, 2, ..., n - 1}
astfel încât o singură valoare se repetă de două ori, să se identifice acea
valoare care se repetă. De ex. în șirul [1,2,3,4,2] valoarea 2 apare de două ori
"""
def valoareDuplicata(lista):
  """
  Determina valoarea care se repetă de exact două ori într-o listă
  :param lista: list
  :return: int
  Complexitate timp: Theta(1)
  Complexitate spatiu: Theta(1)
  """
  suma = sum(lista)
  n = len(lista)
  sumaGauss = n * (n - 1) // 2
  return suma - sumaGauss

def testp5():
  assert(valoareDuplicata([1,2,3,4,2]) == 2)
  assert(valoareDuplicata([2,5,1,3,4,3]) == 3)
  assert(valoareDuplicata([1,2,3,4,5,1,6,7,8,9]) == 1)

def valoareDuplicataAI(nums):
  """
  Determina valoarea care se repetă de exact două ori într-o listă
  Complexitate timp: Theta(n)
  Complexitate spatiu: Theta(1)
  """
  n = len(nums)
  suma_asteptata = (n - 1) * n // 2  # Suma primelor n-1 numere naturale
  suma_actuala = sum(nums)  # Suma elementelor din șir
  return suma_actuala - suma_asteptata  # Valoarea care se repetă

def main5():
  testp5()
  lista = list(map(int, input("Introduceți lista: ").split()))
  print(valoareDuplicata(lista))
  print(valoareDuplicataAI(lista))

main5()

"""
6.Pentru un șir cu n numere întregi care conține și duplicate, să se determine
elementul majoritar (care apare de mai mult de n / 2 ori). De ex. 2 este
elementul majoritar în șirul [2,8,7,2,2,5,2,3,1,2,2].
"""
def elementMajoritar(lista):
  """
  Determina elementul majoritar dintr-o listă
  :param lista: list
  :return: int
  Complexitate timp: Theta(n)
  Complexitate spatiu: Theta(n)
  """
  frecvnr = {}
  for i in lista:
    frecvnr[i] = frecvnr.get(i, 0) + 1
    if frecvnr[i] > len(lista) // 2:
      return i
  return None

def testp6():
  assert(elementMajoritar([2,8,7,2,2,5,2,3,1,2,2]) == 2)
  assert(elementMajoritar([1,2,3,4,5,6,7,8,9]) == None)
  assert(elementMajoritar([1,1,1,1,1,1,1,1,1,1,1,1]) == 1)

def elementMajoritarAI(sir):
  """
  Determina elementul majoritar dintr-o listă
  Complexitate timp: Theta(n)
  Complexitate spatiu: Theta(1)
  """
  # Etapa 1: Găsim un candidat
  candidat = None
  count = 0

  for numar in sir:
    if count == 0:
      candidat = numar
      count = 1
    elif numar == candidat:
      count += 1
    else:
      count -= 1

  # Etapa 2: Verificăm dacă candidatul este majoritar
  count = 0
  for numar in sir:
    if numar == candidat:
      count += 1

  if count > len(sir) // 2:
    return candidat
  else:
    return None  # Dacă nu există niciun element majoritar

def main6():
  testp6()
  lista = list(map(int, input("Introduceți lista: ").split()))
  print(elementMajoritar(lista))
  print(elementMajoritarAI(lista))

main6()

"""
7.Să se determine al k-lea cel mai mare element al unui șir de numere cu n
 elemente (k < n). De ex. al 2-lea cel mai mare element din șirul [7,4,6,3,9,1]
 este 7.
"""
def partition(lista, st, dr):
  pivot = lista[dr]
  i = st - 1
  for j in range(st, dr):
    if lista[j] <= pivot:
      i = i + 1
      (lista[i], lista[j]) = (lista[j], lista[i])
  (lista[i + 1], lista[dr]) = (lista[dr], lista[i + 1])
  return i + 1
def quickSort(lista, st, dr):
  """
  Sortează o listă folosind quicksort
  :param lista: list
  :param st: int
  :param dr: int
  :return: None
  Complexitate timp: Theta(n log n)
  Complexitate spatiu: Theta(1)
  """
  if st < dr:
    pivot = partition(lista, st, dr)
    quickSort(lista, st, pivot - 1)
    quickSort(lista, pivot + 1, dr)

def kCelMaiMareElement(lista, k):
  """
  Determina al k-lea cel mai mare element dintr-o listă
  :param lista: list
  :param k: int
  :return: int
  Complexitate timp: Theta(n log n)
  Complexitate spatiu: Theta(1)
  """
  quickSort(lista, 0, len(lista) - 1)
  return lista[len(lista) - k]


def testp7():
  assert(kCelMaiMareElement([7,4,6,3,9,1], 2) == 7)
  assert(kCelMaiMareElement([17,16,31,90,10], 3) == 17)
  assert(kCelMaiMareElement([27,8,19,2,11,1,8], 1) == 27)

def kCelMaiMareElementAI(sir, k):
  """
  Determina al k-lea cel mai mare element dintr-o listă
  Complexitate timp: Theta(n log n)
  Complexitate spatiu: Theta(1)
  """
  sir_sortat = sorted(sir, reverse=True)  # Sortăm descrescător
  return sir_sortat[k - 1]  # Al k-lea element (indexat de la 0)

def main7():
  testp7()
  lista = list(map(int, input("Introduceți lista: ").split()))
  k = int(input("Introduceți k: "))
  print(kCelMaiMareElement(lista, k))
  print(kCelMaiMareElementAI(lista, k))

main7()

"""
8.Să se genereze toate numerele (în reprezentare binară) cuprinse între 1 și n.
 De ex. dacă n = 4, numerele sunt: 1, 10, 11, 100.
"""
def transformare(n):
  """
  Transforma un număr întreg în reprezentarea binară
  :param x: int
  :return: str
  Complexitate timp: Theta(log n)
  Complexitate spatiu: Theta(1)
  """
  rezultat = ""
  while n > 0:
    rezultat = str(n % 2) + rezultat
    n = n // 2
  return rezultat

def numereBinare(n):
  """
  Generează toate numerele binare cuprinse între 1 și n
  :param n: int
  :return: list
  Complexitate timp: Theta(nlogn)
  Complexitate spatiu: Theta(n)
  """
  rez = []
  for i in range(1, n + 1):
    rez.append(transformare(i))
  return rez

def testp8():
  assert(numereBinare(4) == ["1", "10", "11", "100"])
  assert(numereBinare(5) == ["1", "10", "11", "100", "101"])
  assert(numereBinare(6) == ["1", "10", "11", "100", "101", "110"])

def numereBinareAI(n):
  """
  Generează toate numerele binare cuprinse între 1 și n
  Complexitate timp: Theta(nlogn)
  Complexitate spatiu: Theta(1)
  """
  return [bin(i)[2:] for i in range(1, n + 1)]

def main8():
  testp8()
  n = int(input("Introduceți n: "))
  print(numereBinare(n))
  print(numereBinareAI(n))

main8()

"""
9.Considerându-se o matrice cu n x m elemente întregi și o listă cu perechi
formate din coordonatele a 2 căsuțe din matrice ((p,q) și (r,s)), să se
calculeze suma elementelor din sub-matricile identificate de fieare pereche.

De ex, pt matricea
[[0, 2, 5, 4, 1],
[4, 8, 2, 3, 7],
[6, 3, 4, 6, 2],
[7, 3, 1, 8, 3],
[1, 5, 7, 9, 4]]
și lista de perechi ((1, 1) și (3, 3)), ((2, 2) și (4, 4)), suma elementelor
 din prima sub-matrice este 38, iar suma elementelor din a 2-a sub-matrice
 este 44.
"""
def sumaSubmatrice(lista, p, q, r, s):
  """
  Calculează suma elementelor dintr-o sub-matrice
  :param lista: list[list[int]]
  :param p: int
  :param q: int
  :return: int
  Complexitate timp: Theta((r-p+1)*(s-q+1))
  Complexitate spatiu: Theta(1)
  """
  suma = 0
  for i in range(p, r + 1):
    suma += sum(lista[i][j] for j in range(q, s + 1))
  return suma

def sumaSubmatricePerechi(lista, listaperechi):
  """
  Determina suma elementelor din submatricele determinate de perechile date
  :param lista: list[list[int]]
  :param listaperechi: list[tuple[int]]
  :return: list
  Complexitate timp: Theta(np*k*l), unde k si l sunt numarul medii de lini,
                                    respectiv coloane
  Complexitate spatiu: Theta(np), unde np e numarul de perechi din lista
  """
  rezultat = []
  for i in listaperechi:
    p, q = i[0]
    r, s = i[1]
    rezultat.append(sumaSubmatrice(lista, p, q, r, s))
  return rezultat

def testp9():
  l = [[0, 2, 5, 4, 1],
   [4, 8, 2, 3, 7],
   [6, 3, 4, 6, 2],
   [7, 3, 1, 8, 3],
   [1, 5, 7, 9, 4]]
  p1 = [((1, 1), (3, 3)), ((2, 2), (4, 4))]
  p2 = [((0, 0), (1, 1)), ((1, 3), (4, 4))]

  assert(sumaSubmatricePerechi(l, p1) == [38, 44])
  assert(sumaSubmatricePerechi(l, p2) == [14, 42])

  lp = [[0, 2, 5, 4, 1, 0],
   [4, 8, 2, 3, 7, 11],
   [6, 3, 4, 6, 2, 8],
   [7, 3, 1, 8, 3, 10],
   [1, 5, 7, 9, 4, 12]]
  p3 = [((1, 2), (3, 5)), ((3, 1), (4, 5))]
  assert(sumaSubmatricePerechi(lp, p3) == [65, 62])

def compute_prefix_sum(matrix):
  n, m = len(matrix), len(matrix[0])
  S = [[0] * (m + 1) for _ in range(n + 1)]

  for i in range(1, n + 1):
    for j in range(1, m + 1):
      S[i][j] = matrix[i-1][j-1] + S[i-1][j] + S[i][j-1] - S[i-1][j-1]

  return S

def sum_submatrix(prefix_sum, p, q, r, s):
  return (prefix_sum[r][s] - prefix_sum[p-1][s] - prefix_sum[r][q-1] +
          prefix_sum[p-1][q-1])

def sumaSubmatricePerechiAI(matrix, queries):
  """
  Determina suma elementelor din submatricele determinate de perechile date
  Complexitate timp: Theta(np*n),
  Complexitate spatiu: Theta(np), unde np e numarul de perechi din lista
  """
  prefix_sum = compute_prefix_sum(matrix)
  for (p, q), (r, s) in queries:
    print(f"Suma pentru sub-matricea ({p}, {q}) - ({r}, {s}):",
          sum_submatrix(prefix_sum, p, q, r, s))

def main9():
  testp9()
main9()

"""
10.Considerându-se o matrice cu n x m elemente binare (0 sau 1) sortate
 crescător pe linii, să se identifice indexul liniei care conține cele mai
  multe elemente de 1.

De ex. în matricea
[[0,0,0,1,1],
[0,1,1,1,1],
[0,0,1,1,1]]
a doua linie conține cele mai multe elemente 1.
"""

def linieMax(lista, n, m):
  """
  Identifica indexul liniei care conține cele mai multe elemente de 1
  :param lista: list[list[int]]
  :return: int
  Complexitate timp: Theta(n*m)
  Complexitate spatiu: Theta(1)
  """
  smax = 0
  for i in range(n):
    suma = sum(lista[i][j] for j in range(m))
    if suma > smax:
      smax = suma
      imax = i + 1
  return imax

def testp10():
  l = [[0,0,0,1,1],
   [0,1,1,1,1],
   [0,0,1,1,1]]
  assert(linieMax(l, 3, 5) == 2)
  l1 = [[0,0,0,1,1,1],
   [0,1,1,1,1,1],
   [0,0,1,1,1,1],
   [0,0,1,1,1,1]]
  assert(linieMax(l1, 4, 6) == 2)
  l2 = [[0,0,0,0,1,1,1],
   [0,0,0,0,0,0,1],
   [0,0,0,0,1,1,1],
   [0,0,0,1,1,1,1],
   [0,0,0,1,1,1,1]]
  assert(linieMax(l2, 5, 7) == 4)

def linieMaxAI(matrice, n, m):
  """
  Identifica indexul liniei care conține cele mai multe elemente de 1
  Complexitate timp: Theta(n*logm)
  Complexitate spatiu: Theta(1)
  """
  max_1 = -1
  index_linie = -1

  for i in range(n):
    # Folosim căutarea binară pentru a găsi poziția primului 1
    stanga, dreapta = 0, m - 1
    pozitie_primul_1 = m  # Inițializăm cu m, în caz că nu există 1 pe linie

    while stanga <= dreapta:
      mijloc = (stanga + dreapta) // 2
      if matrice[i][mijloc] == 1:
        pozitie_primul_1 = mijloc
        dreapta = mijloc - 1
      else:
        stanga = mijloc + 1

      # Calculăm numărul de 1-uri pe linie
      numar_1 = m - pozitie_primul_1

      # Actualizăm maximul și indexul liniei
      if numar_1 > max_1:
        max_1 = numar_1
        index_linie = i

  return index_linie

def main10():
  testp10()

main10()


    
