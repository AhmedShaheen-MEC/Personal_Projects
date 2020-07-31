import sys
import unittest
import os

'''
    * This file is used to run the test, it creates a test runner object. 
    * test_xxxx.py module's path should be included.
    * Usage:it gets all the test Classes inside the target module inside the suite object.
            Then the tests are executed through the unittest class (TestRunner) method
            in this case I am using the TextTestRunner to publish a report at the end.
'''

''' ***** Set up path***** '''
#main pathes:

#path = "C:/Users/mubek/Desktop/optimization-code"
#path = "/home/mubek/opt_12parameters_subSwarms_penalties_3"

path = "/home/ckl1184/Unit_test"
#path = 'D:\Eng.Progrmas\Hammer\UnitTests'
path_unit_test = path + "/unit_tests"
sys.path.append(path)
sys.path.append(path_unit_test)
os.chdir(path_unit_test)

import test_OptimizationClasses

suite = unittest.TestLoader().loadTestsFromModule(test_OptimizationClasses)
with open(path + '/test_results.log', "w") as f:
    unittest.TextTestRunner(f).run(suite)