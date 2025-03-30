from domain.adauganumarinlista import add_complexe, ins_complexe_pe_poz
from domain.cautarenumere import imag_interval, modul_mai_mic_decat_10, modul_egal_cu_10
from domain.filtrare import filtrare_reala_prim, filtrare_modul_nr
from domain.modificaelementedinlista import sterge_de_pe_poz, sterge_din_interval, inlocuieste_aparitii
from domain.operatiicunumereledinlista import suma_secv, produs_secv, sortare_imag
from domain.undo import undo_list
def get_rez(listat):
    return listat[0]
def get_rezl(lista):
    return lista
def test_add_complexe():
    numerecomplexe = [[],[[]]]
    c1 = {'a' : 1,'b' : 10}
    add_complexe(numerecomplexe,c1)
    assert get_rez(numerecomplexe) == [{'a' : 1, 'b' : 10}]
    c1 = {'a' : 2, 'b' : 3}
    add_complexe(numerecomplexe, c1)
    assert get_rez(numerecomplexe) == [{'a': 1, 'b': 10}, {'a': 2, 'b': 3}]
    c1 = {'a' : 4, 'b' : 8}
    add_complexe(numerecomplexe, c1)
    assert get_rez(numerecomplexe) == [{'a': 1, 'b': 10}, {'a': 2, 'b': 3}, {'a': 4, 'b': 8}]
    c1={'a' : 0, 'b' : 0}
    try:
        add_complexe(numerecomplexe, c1)
        assert False
    except ValueError:
        assert True
def test_ins_complexe_pe_poz():
    numerecomplexe = [[{'a': 1, 'b': 10}, {'a': 2, 'b': 3}, {'a': 4, 'b': 8}],[[],[{'a': 1, 'b': 10}, {'a': 2, 'b': 3}, {'a': 4, 'b': 8}]]]
    p = 0
    c = {'a' : 5, 'b' : 9}
    ins_complexe_pe_poz(numerecomplexe, p, c)
    assert get_rez(numerecomplexe) == [{'a' : 5, 'b' : 9}, {'a': 1, 'b': 10}, {'a': 2, 'b': 3}, {'a': 4, 'b': 8}]
    p = 4
    c = {'a': 11, 'b': 7}
    ins_complexe_pe_poz(numerecomplexe, p, c)
    assert get_rez(numerecomplexe) == [{'a': 5, 'b': 9}, {'a': 1, 'b': 10}, {'a': 2, 'b': 3}, {'a': 4, 'b': 8}, {'a': 11, 'b': 7}]
    p = 3
    c = {'a': 21, 'b': 3}
    ins_complexe_pe_poz(numerecomplexe, p, c)
    assert get_rez(numerecomplexe) == [{'a': 5, 'b': 9}, {'a': 1, 'b': 10}, {'a': 2, 'b': 3}, {'a': 21, 'b': 3}, {'a': 4, 'b': 8}, {'a': 11, 'b': 7}]
    p = -1
    c = {'a': 11, 'b': 8}
    try:
        ins_complexe_pe_poz(numerecomplexe, p, c)
        assert False
    except ValueError:
        assert True
    p = 7
    c = {'a': 11, 'b': 8}
    try:
        ins_complexe_pe_poz(numerecomplexe, p, c)
        assert False
    except ValueError:
        assert True

def test_imag_interval():
    numerecomplexe = [[{'a': 5, 'b': 9}, {'a': 1, 'b': 10}, {'a': 2, 'b': 3}, {'a': 21, 'b': 3}, {'a': 4, 'b': 8}, {'a': 11, 'b': 7}, {'a': 11, 'b': 79}] , [[],[{'a': 5, 'b': 9}, {'a': 1, 'b': 10}, {'a': 2, 'b': 3}, {'a': 21, 'b': 3}, {'a': 4, 'b': 8}, {'a': 11, 'b': 7}, {'a': 11, 'b': 79}]]]
    lista1= []
    imag_interval(numerecomplexe,1,2,lista1)
    assert get_rezl(lista1) == [10, 3]
    lista1 = []
    imag_interval(numerecomplexe, 0, 3, lista1)
    assert get_rezl(lista1) == [9, 10, 3, 3]
    lista1 = []
    imag_interval(numerecomplexe, 4,6, lista1)
    assert get_rezl(lista1) == [8, 7, 79]
    lista1 = []
    try:
        imag_interval(numerecomplexe, -1, 10, lista1)
        assert False
    except ValueError:
        assert True

def test_modul_mai_mic_decat_10():
    numerecomplexe = [[{'a': 1, 'b': 0}, {'a': 9, 'b': 10}, {'a': 2, 'b': 1}, {'a': 21, 'b': 3}, {'a': 4, 'b': 8}, {'a': 0, 'b': 3}, {'a': 1, 'b': 3}] , [[],[{'a': 1, 'b': 0}, {'a': 9, 'b': 10}, {'a': 2, 'b': 1}, {'a': 21, 'b': 3}, {'a': 4, 'b': 8}, {'a': 0, 'b': 3}, {'a': 1, 'b': 3}]]]
    lista2 = []
    modul_mai_mic_decat_10(numerecomplexe,lista2)
    assert get_rezl(lista2) == [{'a': 1, 'b': 0}, {'a': 2, 'b': 1}, {'a': 0, 'b': 3}]
    numerecomplexe = [[{'a': 9, 'b': 10}, {'a': 21, 'b': 3}, {'a': 4, 'b': 8}, {'a': 1, 'b': 3}] , []]
    lista2 = []
    try:
        modul_mai_mic_decat_10(numerecomplexe,lista2)
        assert False
    except ValueError:
        assert True

def test_modul_egal_cu_10():
    numerecomplexe = [[{'a': 3, 'b': 1}, {'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 21, 'b': 3}, {'a': 4, 'b': 8}, {'a': 0, 'b': 3}, {'a': 1, 'b': 3}] , [[],[{'a': 3, 'b': 1}, {'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 21, 'b': 3}, {'a': 4, 'b': 8}, {'a': 0, 'b': 3}, {'a': 1, 'b': 3}]]]
    lista3 = []
    modul_egal_cu_10(numerecomplexe,lista3)
    assert get_rezl(lista3) == [{'a': 3, 'b': 1}, {'a': 1, 'b': 3}, {'a': 1, 'b': 3}]
    numerecomplexe = [[{'a': 9, 'b': 10}, {'a': 21, 'b': 3}, {'a': 4, 'b': 8}, {'a': 1, 'b': 9}, {'a': 8, 'b': 9}] , []]
    lista3 = []
    try:
        modul_egal_cu_10(numerecomplexe,lista3)
        assert False
    except ValueError:
        assert True

def test_filtrare_reala_prim():
    numerecomplexe = [[{'a': 3, 'b': 1}, {'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 23, 'b': 3}, {'a': 4, 'b': 8}, {'a': 0, 'b': 3}, {'a': 19, 'b': 3}] , []]
    lista4 = []
    filtrare_reala_prim(numerecomplexe, lista4)
    assert get_rezl(lista4) == [{'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 4, 'b': 8}, {'a': 0, 'b': 3}]
    numerecomplexe = [[{'a': 3, 'b': 10}, {'a': 2, 'b': 3}, {'a': 11, 'b': 8}, {'a': 37, 'b': 3}],[[]]]
    lista4 = []
    try:
        filtrare_reala_prim(numerecomplexe, lista4)
        assert False
    except ValueError:
        assert True

def test_filtrare_modul_nr():
    numerecomplexe = [
        [{'a': 3, 'b': 1}, {'a': 6, 'b': 8}, {'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 23, 'b': 3}, {'a': 4, 'b': 8},
         {'a': 0, 'b': 10}, {'a': 19, 'b': 3}], [[],[{'a': 3, 'b': 1}, {'a': 6, 'b': 8}, {'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 23, 'b': 3}, {'a': 4, 'b': 8},
         {'a': 0, 'b': 10}, {'a': 19, 'b': 3}]]]
    lista5 = []
    filtrare_modul_nr(numerecomplexe, 12, 1, lista5)
    assert get_rezl(lista5) == [{'a': 6, 'b': 8}, {'a': 9, 'b': 10}, {'a': 23, 'b': 3}, {'a': 4, 'b': 8},
                                {'a': 0, 'b': 10}, {'a': 19, 'b': 3}]
    lista5 = []
    filtrare_modul_nr(numerecomplexe, 100, 2, lista5)
    assert get_rezl(lista5) == [{'a': 3, 'b': 1}, {'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 23, 'b': 3},
                                {'a': 4, 'b': 8}, {'a': 19, 'b': 3}]
    lista5 = []
    filtrare_modul_nr(numerecomplexe, 90, 3, lista5)
    assert get_rezl(lista5) == [{'a': 3, 'b': 1}, {'a': 1, 'b': 3}, {'a': 4, 'b': 8}]
    numerecomplexe = [[{'a': 3, 'b': 1}, {'a': 6, 'b': 8}, {'a': 9, 'b': 10}],[]]
    lista5 = []
    try:
        filtrare_modul_nr(numerecomplexe, 200, 1, lista5)
        assert False
    except ValueError:
        assert True
    numerecomplexe = [[{'a': 10, 'b': 0}, {'a': 6, 'b': 8}, {'a': 8, 'b': 6}], []]
    lista5 = []
    try:
        filtrare_modul_nr(numerecomplexe, 100, 2, lista5)
        assert False
    except ValueError:
        assert True
    numerecomplexe = [[{'a': 30, 'b': 1}, {'a': 6, 'b': 8}, {'a': 9, 'b': 10}], []]
    lista5 = []
    try:
        filtrare_modul_nr(numerecomplexe, 50, 3, lista5)
        assert False
    except ValueError:
        assert True

def test_sterge_de_pe_poz():
    numerecomplexe = [[{'a': 3, 'b': 1}, {'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 23, 'b': 3}, {'a': 4, 'b': 8}, {'a': 19, 'b': 3}], [[],[{'a': 3, 'b': 1}, {'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 23, 'b': 3}, {'a': 4, 'b': 8}, {'a': 19, 'b': 3}]]]
    sterge_de_pe_poz(numerecomplexe,0)
    assert get_rez(numerecomplexe) == [{'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 23, 'b': 3}, {'a': 4, 'b': 8}, {'a': 19, 'b': 3}]
    sterge_de_pe_poz(numerecomplexe, 2)
    assert get_rez(numerecomplexe) == [{'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 4, 'b': 8}, {'a': 19, 'b': 3}]
    sterge_de_pe_poz(numerecomplexe, 3)
    assert get_rez(numerecomplexe) == [{'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 4, 'b': 8}]
    try:
        sterge_de_pe_poz(numerecomplexe, 11)
        assert False
    except ValueError:
        assert True
    try:
        sterge_de_pe_poz(numerecomplexe, -1)
        assert False
    except ValueError:
        assert True

def test_sterge_din_interval():
    numerecomplexe = [[{'a': 3, 'b': 1}, {'a': 6, 'b': 8}, {'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 23, 'b': 3},
                       {'a': 4, 'b': 8}, {'a': 0, 'b': 10}, {'a': 19, 'b': 3}], [[],[{'a': 3, 'b': 1}, {'a': 6, 'b': 8}, {'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 23, 'b': 3},
                       {'a': 4, 'b': 8}, {'a': 0, 'b': 10}, {'a': 19, 'b': 3}]]]
    sterge_din_interval(numerecomplexe,1,2)
    assert get_rez(numerecomplexe) == [{'a': 3, 'b': 1}, {'a': 1, 'b': 3}, {'a': 23, 'b': 3}, {'a': 4, 'b': 8},
                                       {'a': 0, 'b': 10}, {'a': 19, 'b': 3}]
    sterge_din_interval(numerecomplexe, 0, 0)
    assert get_rez(numerecomplexe) == [{'a': 1, 'b': 3}, {'a': 23, 'b': 3}, {'a': 4, 'b': 8}, {'a': 0, 'b': 10},
                                       {'a': 19, 'b': 3}]
    sterge_din_interval(numerecomplexe, 2, 4)
    assert get_rez(numerecomplexe) == [{'a': 1, 'b': 3}, {'a': 23, 'b': 3}]
    try:
        sterge_din_interval(numerecomplexe, -1, 8)
        assert False
    except ValueError:
        assert True
    try:
        sterge_din_interval(numerecomplexe, 1, 0)
        assert False
    except ValueError:
        assert True

def test_inlocuieste_aparitii():
    numerecomplexe = [[{'a': 1, 'b': 3}, {'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 11, 'b': 311}, {'a': 4, 'b': 8}, {'a': 1, 'b': 3}], [[],[{'a': 1, 'b': 3}, {'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 11, 'b': 311}, {'a': 4, 'b': 8}, {'a': 1, 'b': 3}]]]
    inlocuieste_aparitii(numerecomplexe,{'a': 1, 'b': 3},{'a': 8, 'b': 11})
    assert get_rez(numerecomplexe) == [{'a': 8, 'b': 11}, {'a': 9, 'b': 10}, {'a': 8, 'b': 11}, {'a': 11, 'b': 311}, {'a': 4, 'b': 8}, {'a': 8, 'b': 11}]
    try:
        inlocuieste_aparitii(numerecomplexe,{'a': 1, 'b': 3},{'a': 8, 'b': 11})
        assert False
    except ValueError:
        assert True
def test_suma_secv():
    numerecomplexe = [[{'a': 3, 'b': 1}, {'a': 6, 'b': 8}, {'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 23, 'b': 3},
                       {'a': 4, 'b': 8}, {'a': 0, 'b': 10}, {'a': 19, 'b': 3}], [[],[{'a': 3, 'b': 1}, {'a': 6, 'b': 8}, {'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 23, 'b': 3},
                       {'a': 4, 'b': 8}, {'a': 0, 'b': 10}, {'a': 19, 'b': 3}]]]
    suma = []
    suma_secv(numerecomplexe,0,1,suma)
    assert get_rezl(suma) == [9,9]
    suma = []
    suma_secv(numerecomplexe, 3, 5, suma)
    assert get_rezl(suma) == [28, 14]
    suma = []
    suma_secv(numerecomplexe, 7, 7, suma)
    assert get_rezl(suma) == [19, 3]
    suma = []
    try:
        suma_secv(numerecomplexe, -1, 3, suma)
        assert False
    except ValueError:
        assert True

def test_produs_secv():
    numerecomplexe = [[{'a': 3, 'b': 1}, {'a': 6, 'b': 8}, {'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 23, 'b': 3},
                       {'a': 4, 'b': 8}, {'a': 0, 'b': 10}, {'a': 19, 'b': 3}], [[],[{'a': 3, 'b': 1}, {'a': 6, 'b': 8}, {'a': 9, 'b': 10}, {'a': 1, 'b': 3}, {'a': 23, 'b': 3},
                       {'a': 4, 'b': 8}, {'a': 0, 'b': 10}, {'a': 19, 'b': 3}]]]
    produs = []
    produs_secv(numerecomplexe,0,2,produs)
    assert get_rezl(produs) == [162,80]
    produs = []
    produs_secv(numerecomplexe, 5, 5, produs)
    assert get_rezl(produs) == [4, 8]
    produs = []
    produs_secv(numerecomplexe,6,7,produs)
    assert get_rezl(produs) == [0, 30]
    produs = []
    try:
        produs_secv(numerecomplexe,12,2,produs)
        assert False
    except ValueError:
        assert True

def test_sortare_imag():
    numerecomplexe = [[{'a': 3, 'b': 1}, {'a': 6, 'b': 8}, {'a': 9, 'b': 10}, {'a': 11, 'b': 3}, {'a': 23, 'b': 31},
                       {'a': 4, 'b': 8}, {'a': 0, 'b': 101}, {'a': 19, 'b': 300}], [[],[{'a': 3, 'b': 1}, {'a': 6, 'b': 8}, {'a': 9, 'b': 10}, {'a': 11, 'b': 3}, {'a': 23, 'b': 31},
                       {'a': 4, 'b': 8}, {'a': 0, 'b': 101}, {'a': 19, 'b': 300}]]]
    sortare_imag(numerecomplexe)
    assert get_rez(numerecomplexe)  == [{'a': 19, 'b': 300}, {'a': 0, 'b': 101}, {'a': 23, 'b': 31}, {'a': 9, 'b': 10}, {'a': 6, 'b': 8}, {'a': 4, 'b': 8},
                                        {'a': 11, 'b': 3}, {'a': 3, 'b': 1}]
    try:
        sortare_imag(numerecomplexe)
        assert False
    except ValueError:
        assert True

def test_undo_list():
    numerecomplexe = [[{'a': 1, 'b': 3}, {'a': 5, 'b': 7}, {'a': 9, 'b': 11}],[[],[{'a': 1, 'b': 3}],[{'a': 1, 'b': 3}, {'a': 5, 'b': 7}, {'a': 9, 'b': 11}]]]
    undo_list(numerecomplexe)
    assert get_rezl(numerecomplexe) == [[{'a': 1, 'b': 3}], [[]]]
    try:
        undo_list(numerecomplexe)
        assert False
    except ValueError:
        assert True


def teste_functionalitati():
    test_add_complexe()
    test_ins_complexe_pe_poz()
    test_imag_interval()
    test_modul_mai_mic_decat_10()
    test_modul_egal_cu_10()
    test_filtrare_reala_prim()
    test_sterge_de_pe_poz()
    test_sterge_din_interval()
    test_inlocuieste_aparitii()
    test_suma_secv()
    test_produs_secv()
    test_sortare_imag()
    test_undo_list()