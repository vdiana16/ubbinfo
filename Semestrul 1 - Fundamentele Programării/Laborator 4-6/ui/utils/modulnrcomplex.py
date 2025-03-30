def modul(nrcompl):
    """
    returneaza modulul unui numar complex
    """
    modulnr = int(nrcompl['a'] * nrcompl['a'] + nrcompl['b'] * nrcompl['b'])
    return modulnr

def test_modul():
    """
    testeaza functia modul
    :return:
    """
    assert modul({'a':0,'b':3}) == 9
    assert modul({'a':5,'b':0}) == 25
    assert modul({'a':3,'b':5}) == 34

test_modul()