import os
import sys
'''
    This file is used to run the test, it executes the test class directly
    test_xxxx.py module's path should be included.
    Usage: it resembles the shell command, in order to generate external files
    this file should be used.
'''

''' ***** Set up path***** '''
#main pathes:

#path = "C:/Users/mubek/Desktop/optimization-code"
#path = "/home/mubek/opt_12parameters_subSwarms_penalties_3"

#my path

#path = "/home/ckl1184/Unit_test"
path = "D:\Eng.Progrmas\Hammer\UnitTests"
path_unit_test = path + "/unit_tests"
sys.path.append(path)
sys.path.append(path_unit_test)
os.chdir(path_unit_test)
#execfile('python -m unittest discover')
#os.popen('python -m unittest discover')
os.popen('python test_OptimizationClasses.py')
