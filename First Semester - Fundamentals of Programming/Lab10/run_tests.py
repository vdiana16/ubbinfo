import unittest
from tests.domain_tests.entities_tests import testStudenti, testDiscipline, testNote
from tests.domain_tests.validators_tests import testValidatorS, testValidatorD, testValidatorN
from tests.repository_tests.disciplinarepo_tests import testrepoD
from tests.repository_tests.studentrepo_tests import testrepoS
from tests.repository_tests.noterepo_tests import testrepoN
from tests.service_tests.studentservice_tests import testserviceS
from tests.service_tests.disciplinaservice_tests import testserviceD
from tests.service_tests.noteservice_tests import testserviceN
def suite():
    test_suite = unittest.TestSuite()
    test_suite.addTest(unittest.TestLoader().loadTestsFromTestCase(testCaseClass=testStudenti))
    test_suite.addTest(unittest.TestLoader().loadTestsFromTestCase(testCaseClass=testDiscipline))
    test_suite.addTest(unittest.TestLoader().loadTestsFromTestCase(testCaseClass=testNote))
    test_suite.addTest(unittest.TestLoader().loadTestsFromTestCase(testCaseClass=testValidatorS))
    test_suite.addTest(unittest.TestLoader().loadTestsFromTestCase(testCaseClass=testValidatorD))
    test_suite.addTest(unittest.TestLoader().loadTestsFromTestCase(testCaseClass=testValidatorN))
    test_suite.addTest(unittest.TestLoader().loadTestsFromTestCase(testCaseClass=testrepoD))
    test_suite.addTest(unittest.TestLoader().loadTestsFromTestCase(testCaseClass=testrepoS))
    test_suite.addTest(unittest.TestLoader().loadTestsFromTestCase(testCaseClass=testrepoN))
    test_suite.addTest(unittest.TestLoader().loadTestsFromTestCase(testCaseClass=testserviceS))
    test_suite.addTest(unittest.TestLoader().loadTestsFromTestCase(testCaseClass=testserviceD))
    test_suite.addTest(unittest.TestLoader().loadTestsFromTestCase(testCaseClass=testserviceN))



    return test_suite

if __name__ == '__main__':
    runner = unittest.TextTestRunner()
    runner.run(suite())
