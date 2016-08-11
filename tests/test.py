import unittest
import program_tests
import util_tests

if __name__ == '__main__':
    programTestSuite = unittest.TestLoader().loadTestsFromTestCase(program_tests.TestProgram)
    utilTestSuite = unittest.TestLoader().loadTestsFromTestCase(util_tests.TestUtils)
    unittest.TextTestRunner(verbosity=2).run(programTestSuite)
    unittest.TextTestRunner(verbosity=2).run(utilTestSuite)
