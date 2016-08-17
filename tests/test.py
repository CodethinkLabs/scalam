import unittest
import program_tests
import system_tests
import util_tests
import random_tests
import genome_tests

def run_tests():
    programTestSuite = unittest.TestLoader().loadTestsFromTestCase(program_tests.TestProgram)
    utilTestSuite = unittest.TestLoader().loadTestsFromTestCase(util_tests.TestUtils)
    systemTestSuite = unittest.TestLoader().loadTestsFromTestCase(system_tests.TestSystem)
    randomTestSuite = unittest.TestLoader().loadTestsFromTestCase(random_tests.TestRandom)
    genomeTestSuite = unittest.TestLoader().loadTestsFromTestCase(genome_tests.TestGenome)

    unittest.TextTestRunner(verbosity=2).run(programTestSuite)
    unittest.TextTestRunner(verbosity=2).run(utilTestSuite)
    unittest.TextTestRunner(verbosity=2).run(systemTestSuite)
    unittest.TextTestRunner(verbosity=2).run(randomTestSuite)
    unittest.TextTestRunner(verbosity=2).run(genomeTestSuite)

if __name__ == '__main__':
    run_tests()
