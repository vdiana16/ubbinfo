def t_nr_prim(numar):
    """
    Returneaza 1 daca numarul este prim, altfel returneaza 0
    """
    nr = int(numar)
    if nr < 2:
        return 0
    else:
        for d in range(2, nr):
            if nr % d == 0:
                return 0
    return 1

def test_t_nr_prim():
    """
    Testeaza functia de numar prim
    """
    assert t_nr_prim(2) == 1
    assert t_nr_prim(1) == 0
    assert t_nr_prim(9) == 0
    assert t_nr_prim(17) == 1
    assert t_nr_prim(97) == 1

test_t_nr_prim()