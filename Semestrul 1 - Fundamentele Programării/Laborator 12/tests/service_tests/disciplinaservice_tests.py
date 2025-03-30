import unittest
from domain.entities import Disciplina
from domain.validators import ValidatorException, DisciplinaValidator
from services.disciplinaservice import DisciplinaService
from repository.disciplinarepo import DisciplineInMemoryRepository

class testserviceD(unittest.TestCase):
    def test_adaugareDisciplina(self):
        rep = DisciplineInMemoryRepository()
        val = DisciplinaValidator()
        srv = DisciplinaService(rep, val)
        dis = srv.adaugareDisciplina(1, "Franceza", "Anca")
        assert rep.lgdis() == 1
        listadis = rep.getToateDisciplinele()
        assert listadis[0] == dis

        try:
            srv.adaugareDisciplina("", "", "")
            assert False
        except ValidatorException as e:
            assert True

    def test_stergereDisciplina(self):
        rep = DisciplineInMemoryRepository()
        val = DisciplinaValidator()
        srv = DisciplinaService(rep, val)
        srv.adaugareDisciplina(1, "Franceza", "Anca")
        srv.adaugareDisciplina(3, "Geografie", "Ana")
        srv.stergereDisciplina(3)
        listadis = rep.getToateDisciplinele()
        assert listadis[0].getIdd() == 1
        assert listadis[0].getDenumire() == "Franceza"
        assert listadis[0].getProf() == "Anca"

        try:
            srv.stergereDisciplina("")
            assert False
        except ValueError:
            assert True

    def test_modificareDisciplina(self):
        rep = DisciplineInMemoryRepository()
        val = DisciplinaValidator()
        srv = DisciplinaService(rep, val)
        srv.adaugareDisciplina(1, "Franceza", "Anca")
        srv.adaugareDisciplina(3, "Geografie", "Ana")
        srv.adaugareDisciplina(11, "Fizica", "Oproiu")
        srv.modificareDisciplina(3, "Muzica", "Gina")
        listadis = rep.getToateDisciplinele()
        assert listadis[1].getIdd() == 3
        assert listadis[1].getDenumire() == "Muzica"
        assert listadis[1].getProf() == "Gina"

        try:
            srv.modificareDisciplina("", "", "")
            assert False
        except ValidatorException:
            assert True

    def test_cautareidDisciplina(self):
        rep = DisciplineInMemoryRepository()
        val = DisciplinaValidator()
        srv = DisciplinaService(rep, val)
        srv.adaugareDisciplina(1, "Franceza", "Anca")
        srv.adaugareDisciplina(3, "Geografie", "Ana")
        srv.adaugareDisciplina(11, "Fizica", "Oproiu")
        dis = srv.cautareDisciplinaid(11)
        listadis = rep.getToateDisciplinele()
        assert listadis[2] == dis

        try:
            srv.cautareDisciplinaid("")
            assert False
        except ValueError:
            assert True

    def test_cautaredenumireDisciplina(self):
        rep = DisciplineInMemoryRepository()
        val = DisciplinaValidator()
        srv = DisciplinaService(rep, val)
        srv.adaugareDisciplina(1, "Franceza", "Anca")
        srv.adaugareDisciplina(3, "Geografie", "Ana")
        srv.adaugareDisciplina(11, "Fizica", "Oproiu")
        dis = srv.cautareDisciplinaden("Geografie")
        listadis = rep.getToateDisciplinele()
        assert listadis[1] == dis

        try:
            srv.cautareDisciplinaden("")
            assert False
        except ValueError:
            assert True

    def test_cautareprofDisciplina(self):
        rep = DisciplineInMemoryRepository()
        val = DisciplinaValidator()
        srv = DisciplinaService(rep, val)
        srv.adaugareDisciplina(1, "Franceza", "Anca")
        srv.adaugareDisciplina(3, "Geografie", "Ana")
        srv.adaugareDisciplina(11, "Fizica", "Oproiu")
        dis = srv.cautareDisciplinaprof("Anca")
        listadis = rep.getToateDisciplinele()
        assert listadis[0] == dis

        try:
            srv.cautareDisciplinaprof("")
            assert False
        except ValueError:
            assert True

    def test_adaugarerandomDisciplina(self):
        rep = DisciplineInMemoryRepository()
        val = DisciplinaValidator()
        srv = DisciplinaService(rep, val)
        srv.adaugarerandomDisciplina(16, 0)
        assert rep.lgdis() == 16

if __name__ == '__main__':
    unittest.main()