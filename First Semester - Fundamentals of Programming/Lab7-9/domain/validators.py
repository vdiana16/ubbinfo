from domain.entities import Student, Disciplina, Nota

class ValidatorException(Exception):
    def __init__(self, eror):
        self.erori = eror

    def getErori(self):
        return self.erori

class StudentValidator:
    def validare(self, st):
        """
        Valideaza campurile pe care le contina clasa Student
        :param st:
        :return:
        """
        erori = []
        if st.getId() == "":
            erori.append("Id nu poate sa fie vid")
        if st.getNume() == "":
            erori.append("Nume nu poate sa fie vid")
        if len(erori) > 0:
            raise ValidatorException(erori)

class DisciplinaValidator:
    def validare(self, dis):
        """
        Valideaza campurile pe care le contina clasa Disciplina
        :param dis:
        :return:
        """
        erori = []
        if dis.getIdd() == "":
            erori.append("Id nu poate sa fie vid")
        if dis.getDenumire() == "":
            erori.append("Denumirea nu poate sa fie vida")
        if dis.getProf() == "":
            erori.append("Numele profesorului nu poate sa fie vida")
        if len(erori) > 0:
            raise ValidatorException(erori)

class NotaValidator:
    def validare(self, notaa):
        """
        Valideaza campurile clasei Nota
        :param st: 
        :return: 
        """""
        erori = []
        if notaa.getIdstudent() == "":
            erori.append("IC studentului nu poate sa fie vid")
        if notaa.getIddisciplina() == "":
            erori.append("Id-ul disciplinei nu poate sa fie vid")
        if notaa.getNota() == "":
            erori.append("Nota nu poate sa fie vida")
        if len(erori) > 0:
            raise ValidatorException(erori)

def test_StudentValidator():
    validator = StudentValidator()

    st = Student("", "")
    try:
        validator.validare(st)
        assert False
    except ValidatorException as ex:
        assert len(ex.getErori()) == 2

    st = Student("1", "")
    try:
        validator.validare(st)
        assert False
    except ValidatorException as ex:
        assert len(ex.getErori()) == 1

    st = Student("2", "Maria")
    try:
        validator.validare(st)
        assert True
    except ValidatorException as ex:
        assert False

def test_DisciplinaValidator():
    validator = DisciplinaValidator()

    dis = Disciplina("","","")
    try:
        validator.validare(dis)
        assert False
    except ValidatorException as ex:
        assert len(ex.getErori()) == 3

    dis = Disciplina("1", "", "")
    try:
        validator.validare(dis)
        assert False
    except ValidatorException as ex:
        assert len(ex.getErori()) == 2

    dis = Disciplina("1", "Matematica", "Horatiu Mircea")
    try:
        validator.validare(dis)
        assert True
    except ValidatorException as ex:
        assert False

def test_NotaValidator():
    validator = NotaValidator()

    notaa = Nota("","","")
    try:
        validator.validare(notaa)
        assert False
    except ValidatorException as ex:
        assert len(ex.getErori()) == 3

    notaa = Nota("1","","")
    try:
        validator.validare(notaa)
        assert False
    except ValidatorException as ex:
        assert len(ex.getErori()) == 2

    notaa = Nota("", "", "9")
    try:
        validator.validare(notaa)
        assert True
    except ValidatorException as ex:
        assert len(ex.getErori()) == 2

    notaa = Nota("", "1", "9")
    try:
        validator.validare(notaa)
        assert True
    except ValidatorException as ex:
        assert len(ex.getErori()) == 1

    notaa = Nota("1", "2", "10")
    try:
        validator.validare(notaa)
        assert True
    except ValidatorException as ex:
        assert False


test_StudentValidator()
test_DisciplinaValidator()
test_NotaValidator()