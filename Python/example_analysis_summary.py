import os
import sys
import logging

#main folders directory
path_files = 'C:\Users\ckl1184\Downloads\optimization-code'
sys.path.append(path_files)

#log files path and logger files 
path_optimization_code = 'C:\Users\ckl1184\Downloads\Log_swarm_files'


path_log_file = path_optimization_code

sys.path.append(path_files)
sys.path.append(path_files + '\classes')
 
from database import DataPostprocessor



'''
The logging basicConfig added in the example not in the main file, so it does not conflict with the main file after merging it.
'''

# define the logging file path 
logging.basicConfig(filename=path_optimization_code + "/" +'logger_file.log'
					, format= '%(asctime)s %(levelname)s: %(message)s', level=logging.DEBUG)

#input the log files path *Note: results file will be created in the same directory 
testObject = DataPostprocessor(path_log_file)
print 'program started'
testObject.analyzer()
