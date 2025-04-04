from functii import cresc, descresc
def test_cresc():
    assert cresc([4,5,6,7]) == True
    assert cresc([6,7,8]) == True
    assert cresc([4,3,1]) == False
    assert cresc([]) == False


def test_descresc():
    assert descresc([9,8,7,6]) == True
    assert descresc([8,8,8]) == True
    assert descresc([4,5,6]) == False
    assert descresc([]) == False


