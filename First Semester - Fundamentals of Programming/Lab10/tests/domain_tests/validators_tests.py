import unittest
from domain.entities import Student, Disciplina, Nota
from domain.validators import StudentValidator, DisciplinaValidator, NotaValidator
from domain.validators import ValidatorException

class testValidatorS(unittest.TestCase):
    def test_StudentValidator(self):
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

class testValidatorD(unittest.TestCase):
    def test_DisciplinaValidator(self):
        validator = DisciplinaValidator()

        dis = Disciplina("", "", "")
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

class testValidatorN(unittest.TestCase):
    def test_NotaValidator(self):
        validator = NotaValidator()

        notaa = Nota("", "", "", "")
        try:
            validator.validare(notaa)
            assert False
        except ValidatorException as ex:
            assert len(ex.getErori()) == 4

        notaa = Nota("", "1", "", "")
        try:
            validator.validare(notaa)
            assert False
        except ValidatorException as ex:
            assert len(ex.getErori()) == 3

        notaa = Nota("", "", "", "9")
        try:
            validator.validare(notaa)
            assert True
        except ValidatorException as ex:
            assert len(ex.getErori()) == 3

        notaa = Nota("", "", "1", "9")
        try:
            validator.validare(notaa)
            assert True
        except ValidatorException as ex:
            assert len(ex.getErori()) == 2

        notaa = Nota("2", "1", "2", "10")
        try:
            validator.validare(notaa)
            assert True
        except ValidatorException as ex:
            assert False

if __name__ == '__main__':
    unittest.main()