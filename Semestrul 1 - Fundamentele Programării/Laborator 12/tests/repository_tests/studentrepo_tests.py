import unittest
from domain.entities import Student
from repository.studentrepo import StudentiInMemoryRepository
from repository.studentfile import StudentFileRepository

class testrepoS(unittest.TestCase):
    def setUp(self) -> None:
        self.__repo = StudentiInMemoryRepository()
        self.__repo1 = StudentiInMemoryRepository()
        self.__repo2 = StudentiInMemoryRepository()
        self.__repo3 = StudentiInMemoryRepository()
        self.__new_repo = StudentiInMemoryRepository()


    def test_adaugarestudent(self):
        st = Student(1, "Maria")
        self.__repo.adaugarestud(st)

        self.assertEqual(len(self.__repo.getTotiStudentii()),1)


    def test_stergere_student(self):
        st = Student(1, "Maria")
        self.__repo.adaugarestud(st)
        self.__repo.stergerestud(1)
        self.assertEqual(len(self.__repo.getTotiStudentii()),0)


    def test_cautareid_student(self):
        st = Student(1, "Maria")
        self.__repo.adaugarestud(st)
        st1 = Student(2, "Mara")
        self.__repo.adaugarestud(st1)
        self.assertEqual(self.__repo.cautarestudid(1), st)
        self.assertEqual(self.__repo.cautarestudid(2), st1)



if __name__ == '__main__':
    unittest.main()
