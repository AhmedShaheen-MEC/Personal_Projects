import unittest
import os
import sys
import csv
import glob
import datetime
import time
import numpy
import shutil
import logging
import math

# Import abaqus modules

from part import *
from material import *
from section import *
from assembly import *
from step import *
from interaction import *
from load import *
from mesh import *
from optimization import *
from job import *
from sketch import *
from visualization import *
from connectorBehavior import *

''' ***** Set up path***** '''
'''
    Get current directory, and return it to the main optmization directory
    This is important, in order to have access to the whole classes
    Additionally, to avoid redundancy, of entering the path twice. 
'''

TEST_DIR_NAME_LENGTH = 11 # i.e. /unit_tests
path = (os.getcwd()[0:(len(os.getcwd())- TEST_DIR_NAME_LENGTH)])

path_classes = path + "/classes"
path_modules = path + "/modules"
path_templates = path + "/templates"
path_unit_test = path + "/unit_tests"
path_parameterization = path_classes + "/parameterization_package"
sys.path.append(path_unit_test)
sys.path.append(path)
sys.path.append(path_classes)
sys.path.append(path_modules)
sys.path.append(path_templates)
sys.path.append(path_parameterization)
''' 
    The mock module is included manually, inside the test directory
    this was done to avoid changing Abaqus internal data. 
'''
sys.path.append(path_unit_test+'/mock-1.0.1')
sys.path.append(path_unit_test+'/mock-1.0.1/docs')
sys.path.append(path_unit_test+'/mock-1.0.1/html')
sys.path.append(path_unit_test+'/mock-1.0.1/mock.egg-info')
sys.path.append(path_unit_test+'/mock-1.0.1/tests')


os.chdir(path)

from mock import patch, Mock

''' ***** Import test modules *****'''
from database import DataBaseAdministrator, DataPostprocessor
from pso import OptimizationManager, SubSwarm, Particle

''' ***** Import Abaqus  test modules *****'''
from minimal import  HammerComponent, Anvil, ImpactWeight
from connect_simulation import AbaqusSolverConnector, AbaqusOutput
from modelling import AbaqusImpactModel, AbaqusPropagationModel

'''VIP: class decorator should be passed to all the defined function ! '''
''' **** Mock not relevant modules **** '''

@patch('pso.OptimizationManager', autospec=True)
@patch('pso.Particle')
class TestDataBaseAdministrator(unittest.TestCase):

    ''' Create dataBaseAdministrator object when the class is created '''

    @classmethod
    def setUpClass(cls):

        os.chdir(path_unit_test)
        with patch('database.DataBaseAdministrator._get_path_file') as mock__get_path_file:
            mock__get_path_file.return_value = path_unit_test + '/input_optimization.csv'
            cls.dbTestObject = DataBaseAdministrator(path_unit_test)
            cls.dbTestObject.name_input_file = "input_optimization.csv"
            # define test files
            cls.dbTestObject.log_file_base_name = 'test_file'
            cls.dbTestObject.log_file_base_name_particle = cls.dbTestObject.log_file_base_name + "_particle_"
            cls.dbTestObject.log_file_base_name_shape = "test_log_shape_particle_"
            cls.dbTestObject.file_name_summary = "test_summary.log"
            cls.dbTestObject.file_name_time = "time_test_file.csv"
            mock__get_path_file.assert_called_once()
            mock__get_path_file.assert_called_with("input_optimization.csv")

    @classmethod
    def tearDownClass(cls):

        # remove files and clean test area
        [os.remove(file) for file in glob.glob("test_*.csv")]
        os.chdir(path)

    def test_read_input_file(self, mock_Particle, mock_OptimizationManager):

        self.dbTestObject.read_input_file()
        self.assertEqual(self.dbTestObject.input_optimization["num_particles"],2)
        self.assertEqual(self.dbTestObject.input_optimization["num_sub_swarms"], 1)
        self.assertEqual(self.dbTestObject.input_optimization["max_steps"], 2)
        self.assertEqual(self.dbTestObject.input_optimization["inertia"], 0.8)
        self.assertEqual(self.dbTestObject.input_optimization["social_factor"], 2)
        self.assertEqual(self.dbTestObject.input_optimization["cognitive_factor"], 2)
        self.assertEqual(self.dbTestObject.input_optimization["threshold_craziness"], 0.95)
        self.assertEqual(self.dbTestObject.input_optimization["impact_energy"], 3500e3)
        self.assertEqual(self.dbTestObject.input_optimization["num_cpus"], 1)
        self.assertEqual(self.dbTestObject.input_optimization["element_size_components"], 0.05)
        self.assertEqual(self.dbTestObject.input_optimization["element_size_contact_surface"],0.05)
        self.assertEqual(self.dbTestObject.input_optimization["mass_impact_weight_max"], 350e3)
        self.assertEqual(self.dbTestObject.input_optimization["mass_anvil_max"], 200e3)
        self.assertEqual(self.dbTestObject.input_optimization["efficiency_min"], 0.8)
        self.assertEqual(self.dbTestObject.input_optimization["max_stress_max"], 1e9)
        self.assertEqual(self.dbTestObject.input_optimization["v_peak_min"], -2.7)
        self.assertEqual(self.dbTestObject.input_optimization["parameterization"], "hull_iw_12_a_5")
        self.assertEqual(self.dbTestObject.input_optimization["initial_position_file"], "initial_position_iw_12_a_5_p_15_test.csv")
        self.assertEqual(self.dbTestObject.input_optimization["num_parameters"], 17)
        self.assertEqual(self.dbTestObject.input_optimization["min_parameters"], [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1])
        self.assertEqual(self.dbTestObject.input_optimization["max_parameters"], [2, 16, 2, 16, 2, 16, 2, 16, 2, 16, 2, 16, 1, 4, 4, 1, 1])
        self.assertEqual(self.dbTestObject.input_optimization["time_impact_simulation"], 5e-4)
        self.assertEqual(self.dbTestObject.input_optimization["time_propagation_simulation"], 1e-5)

    def test_set_initial_position_file(self,mock_Particle, mock_OptimizationManager):

        num_particles = 2
        max_values = [2, 16, 2, 16, 2, 16, 2, 16, 2, 16, 2, 16, 1, 4, 4, 1, 1]
        min_values = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1]
        self.dbTestObject._set_initial_position_file(num_particles,max_values, min_values)
        with open('initial_positions/initial_position_iw_12_a_5_p_15_test.csv', 'r') as position_file:
            position_file = csv.reader(position_file)
            for line in position_file:
                for p in range(0,len(max_values)):
                    self.assertGreaterEqual(float(line[p]),min_values[p])
                    self.assertLessEqual(float(line[p]),max_values[p])

    def test_read_initial_position(self, mock_OptimizationManager,mock_Particle):

        actual_initial_values=[[0.52,13.92,1.88,2.4,1.7,3.68,1.94,2.4,0.36,12.64,1.84,8.16,0.59,2.72,0.68,0.4,0.02],
                               [0.7,1.12,0.1,7.2,0.62,1.28,0.94,15.84,1.08,7.04,0.04,11.52,0.96,3.24,2,0.31,0.8]]
        initial_position_path = '/initial_positions/initial_position_iw_12_a_5_p_15_test.csv'
        with patch('database.DataBaseAdministrator._get_path_file') as mocked_file_path:
            self.dbTestObject.name_file_initial_positions = initial_position_path
            mocked_file_path.return_value = path + self.dbTestObject.name_file_initial_positions

            for particle_number in range(0,self.dbTestObject.input_optimization['num_particles']):
                self.assertEqual(self.dbTestObject.read_initial_position(particle_number),actual_initial_values[particle_number])

            mocked_file_path.assert_called_with("/initial_positions/initial_position_iw_12_a_5_p_15_test.csv")

    def test_write_log_particle_header(self, mock_OptimizationManager,mock_Particle):

        test_particle_number = 1
        with patch('database.DataBaseAdministrator._add_line') as mocked_add_line:
            self.dbTestObject.write_log_particle_header(test_particle_number,'This is header')
            mocked_add_line.assert_called_once()
            mocked_add_line.assert_called_with('test_file_particle_'+str(test_particle_number)+'.csv', 'This is header')

    def test_write_log(self,mock_Particle, mock_OptimizationManager):

        # apply arbitrary values to the mocked object
        mock_OptimizationManager.best_target_value_all_steps = 200
        mock_OptimizationManager.steps_without_improvement = 3
        mock_OptimizationManager.steps_without_change = 1
        mock_OptimizationManager.delta_time_all_particles = 1e5

        ''' mock the called function and check weither its called right or not '''
        with patch('database.DataBaseAdministrator._write_log_time') as mocked_method:

            # check the if condition: true
            mock_OptimizationManager.current_step = 10
            self.dbTestObject.write_log(mock_OptimizationManager)
            mocked_method.assert_called_with(1e5)
            test_file = open('test_file.csv', 'r+')
            case_1 = test_file.readlines()
            # clear the test file each time
            test_file.truncate(0)
            test_file.close()

            # check if the arbitrary files reached safely to the test file
            self.assertEqual(case_1[0], "step "+ str(10.0)+"\n")
            self.assertEqual(case_1[1], "target value: " + str(200.0)+"\n")
            self.assertEqual(case_1[2], "steps without improvement: " + str(3.0)+"\n")
            self.assertEqual(case_1[3], "steps without change: " + str(1.0)+"\n")

            # check the if condition: false
            mock_OptimizationManager.current_step = 0
            self.dbTestObject.write_log(mock_OptimizationManager)
            test_file = open('test_file.csv', 'r+')
            case_2 = test_file.readlines()
            # clear the test file each time
            test_file.truncate(0)
            test_file.close()

            self.assertEqual(case_2[0], "step "+ str(0.0)+"\n")
            self.assertEqual(case_2[1],  "target value: " + str(200.0)+"\n")
            self.assertLessEqual(len(case_2),2)

    def test_write_log_particle(self, mock_Particle, mock_OptimizationManagere):

        actual_line = ['0.52, 13.92, 1.88, 2.4, 1.7, 3.68, 1.94, 2.4, 0.36, 12.64, 1.84,' \
                        ' 8.16, 0.59, 2.72, 0.68, 0.4, 0.02, 0.0, 0.0, 67.45, 317.16, 1618.16' \
                        ', 275.42, -0.0, 518.5\n']

        ''' ****apply arbitrary values to the mocked object**** '''
        mock_Particle.identifier = 5
        mock_Particle.position = [0.52, 13.92, 1.88, 2.4, 1.7, 3.68, 1.94, 2.4, 0.36, 12.64, 1.84, 8.16, 0.59, 2.72, 0.68, 0.4, 0.02]
        mock_Particle.mean_sel = 0.0
        mock_Particle.efficiency = 0.0
        mock_Particle.mass_anvil = 67.45/ 1e-3
        mock_Particle.mass_impact_weight = 317.16 / 1e-3
        mock_Particle.max_stress_impact_weight = 1618.16 / 1e-6
        mock_Particle.max_stress_anvil = 275.42 / 1e-6
        mock_Particle.peak_pile_head_velocity = -0.0
        mock_Particle.target_value = 518.5
        # execute the function
        self.dbTestObject.write_log_particle(mock_Particle)
        # read the test file
        test_file = open('test_file_particle_5.csv', 'r+')
        read_test_file = test_file.readlines()
        # clear the test file each time
        test_file.truncate(0)
        test_file.close()
        self.assertEqual(read_test_file, actual_line)

    '''
    This is a small function so the test will just check weither
    the inside called function called properly or not.
    '''
    def test_write_log_time(self, mock_OptimizationManager,mock_Particle):

        ''' Define the expected value: '''
        delta_time_all_particles = 100.0
        with patch('database.DataBaseAdministrator._add_line') as mock_add_line:
            self.dbTestObject._write_log_time(delta_time_all_particles)
            mock_add_line.assert_called_with('time_test_file.csv',"100.0")

    def test_write_detailed_log_particle(self,mock_Particle, mock_OptimizationManager):

        ''' Define acutal values taken from prev. optimization to test the function '''
        mock_OptimizationManager.current_step = 1
        mock_OptimizationManager.best_position_current_step =[0.7, 1.12, 0.1, 7.2, 0.62,
                                                              1.28, 0.94, 15.84, 1.08,7.04,
                                                              0.04, 11.52, 0.96, 3.24, 2.0,
                                                              0.31, 0.8]
        mock_Particle.position = [0.53, 13.55, 1.83, 2.54, 1.67,
                                  3.61, 1.91, 2.79, 0.38,12.48,
                                  1.79, 8.26, 0.6, 2.73, 0.72,
                                  0.4, 0.04]
        mock_Particle.best_position = [0.53, 13.55, 1.83, 2.54, 1.67,
                                       3.61, 1.91, 2.79, 0.38, 12.48,
                                       1.79, 8.26, 0.6, 2.73, 0.72,
                                       0.4, 0.04]
        mock_Particle.velocity = [-0.17, 12.43, 1.73, -4.66, 1.05,
                                  2.33, 0.97, -13.05, -0.7, 5.44,
                                  1.75, -3.26, -0.36, -0.51, -1.28,
                                  0.09, -0.76]
        mock_Particle.identifier = 5

        # execute the function
        self.dbTestObject.write_detailed_log_particle(mock_OptimizationManager,mock_Particle)
        # read the rest file then clear it
        test_file = open('test_file_particle_5detailed.csv', 'r+')
        read_test_file = test_file.readlines()
        test_file.truncate(0)
        test_file.close()

        # prepare expected file's content
        expected_line_1 = "step: 1.0, position: "+ self.dbTestObject._convert_to_string_for_log_file(mock_Particle.position)
        expected_line_2 = "step: 1.0, velocity, "+ self.dbTestObject._convert_to_string_for_log_file(mock_Particle.velocity)
        expected_line_3 = "step: 1.0, best_cognitive_position, "+ self.dbTestObject._convert_to_string_for_log_file(mock_Particle.best_position )
        expected_line_4 = "step: 1.0, best_social_position, "+ self.dbTestObject._convert_to_string_for_log_file(mock_OptimizationManager.best_position_current_step)

        # check the content
        self.assertEqual(read_test_file[0], expected_line_1+"\n")
        self.assertEqual(read_test_file[1], expected_line_2+"\n")
        self.assertEqual(read_test_file[2], expected_line_3+"\n")
        self.assertEqual(read_test_file[3], expected_line_4+"\n")

    ''' Easier to test the calling arguments to the _add_line function'''

    def test_write_log_shape(self, mock_Particle, mock_OptimizationManager):

        # define arbitrary value to check it
        mock_Particle.identifier = 1
        anvil_test_file_name = self.dbTestObject.log_file_base_name_shape + \
                        str(mock_Particle.identifier) + '_anvil.csv'
        hammer_test_file_name = self.dbTestObject.log_file_base_name_shape + \
                        str(mock_Particle.identifier) + '_impact_weight.csv'
        ''' 
            x,y assigned to list due to the following reason:
            Problem: inside another function, which is not the scope of the test.
            Explanation: MagicMock object does not accept to be rounded, so to avoid 
            mocking the round builtin function, list has been used to validate the if condition
            method name: _convert_to_string_for_log_file
        '''
        mock_Particle.anvil.x = [[2.6, 3.3]]
        mock_Particle.anvil.y = [[2.6, 3.3]]
        mock_Particle.impactWeight.x = [[2.6, 3.3]]
        mock_Particle.impactWeight.y = [[2.6, 3.3]]
        with patch('database.DataBaseAdministrator._add_line') as mocked_add_line:

            self.dbTestObject.write_log_shape(mock_Particle)
            mocked_add_line.assert_any_call(anvil_test_file_name, '2.6, 3.3' )
            mocked_add_line.assert_any_call(anvil_test_file_name, '2.6, 3.3')
            mocked_add_line.assert_any_call(hammer_test_file_name, '2.6, 3.3')
            mocked_add_line.assert_any_call(hammer_test_file_name, '2.6, 3.3')

    ''' Small method, testing through test the correct calls inside it'''
    def test_write_summary(self, mock_OptimizationManager, mock_Particle):

        self.dbTestObject._add_line = Mock()
        self.dbTestObject._add_line.side_effect = ["Optimization stopped after 10 steps."
                                                   ,"Best target value is: 200"
                                                   ,"Reason the optimization stopped: Too many steps"]
        self.dbTestObject.write_summary(10,200,"Too many steps")

        self.dbTestObject._add_line.assert_any_call(self.dbTestObject.file_name_summary,"Optimization stopped after 10 steps.")
        self.dbTestObject._add_line.assert_any_call(self.dbTestObject.file_name_summary,"Best target value is: 200")
        self.dbTestObject._add_line.assert_any_call(self.dbTestObject.file_name_summary,"Reason the optimization stopped: Too many steps")

    def test_get_path_file(self, mock_OptimizationManager, mock_Particle):

        self.assertEqual(self.dbTestObject._get_path_file(self.dbTestObject.name_input_file),path_unit_test+"/"+self.dbTestObject.name_input_file)

    def test_add_line(self, mock_OptimizationManager, mock_Particle):

        with patch('database.DataBaseAdministrator._get_path_file') as mocked_path:
            mocked_path.return_value = path+ '/virtual_folder'
            with patch('__builtin__.open')as open_mocked:
                self.dbTestObject._add_line(mocked_path(),'This is line')
                open_mocked.assert_called_with(path+'/virtual_folder', "a+")

    def test_convert_to_string_for_log_file(self, mock_OptimizationManager, mock_Particle):

        self.assertEqual(self.dbTestObject._convert_to_string_for_log_file(25),'25.0')
        self.assertEqual(type(self.dbTestObject._convert_to_string_for_log_file([1,1.8,3.6,4,5,5])), str)


''' The entire class depends on external files, so test files will be created during the test
    and will be removed at the end'''
class TestDataPostprocessor(unittest.TestCase):

    TEST_LOG_PARTICLES = 2
    TEST_STEPS = 2

    @classmethod
    def setUpClass(cls):

        os.chdir(path_unit_test)
        ''' Initialize test files:4 parameters log files will be used as a sample '''
        ''' 2 particles with 2 steps will be tested '''
        header = 'p1, p2, p3, p4, mean_sel [dB], efficiency, mass_anvil [t], mass_impact_weight [t],' \
                 ' max_stress_impact_weight [MPa], max_stress_anvil [MPa], peak pile head velocity [m/s],' \
                 ' target_value'

        file_name = 'log_file_particle_'
        particle_0 = [
                    ['0.8234, 5.7635, 4.3292, 0.5315, 192.58, 0.12, 245.66, 96.37, 461.31, 673.12, -2.6, 351.7'],
                    ['1.37, 10.76, 3.67, 0.64, 190.48, 0.91, 212.58, 498.05, 318.55, 375.47, -2.61, 209.3']
                        ]
        particle_1 = [
            ['0.4903, 3.7846, 4.3989, 0.2131, 170.25, 0.01, 101.69, 22.44, 642.09, 1238.02, -0.4, 466.2'],
            ['1.43, 10.93, 3.72, 0.73, 191.05, 0.9, 249.13, 551.2, 304.42, 379.54, -2.82, 230.6']
                    ]
        cls.particles = [particle_0 ,particle_1]

        for log_file in range(0, cls.TEST_LOG_PARTICLES):
            with open(file_name + str(log_file)+'.csv', 'w') as test_file:
                test_file.write(header)
                test_file.write('\n')
                for step in range(cls.TEST_STEPS):
                    for item in cls.particles[log_file][step]:
                        test_file.write(str(item))
                    test_file.write('\n')

        cls.data_post_processor_test_object = DataPostprocessor(path_unit_test)


    @classmethod
    def tearDownClass(cls):

        # remove files and clean test area
        [os.remove(file) for file in glob.glob("log_file_particle*.csv")]
        [os.remove(file) for file in glob.glob("Best_results_file.csv")]
        os.chdir(path)

    def test__get_files(self):

        expected_files = ['log_file_particle_0.csv','log_file_particle_1.csv']
        self.data_post_processor_test_object._DataPostprocessor__get_files()
        self.assertEqual(self.data_post_processor_test_object.log_files, expected_files)

    def test__get_data(self):

        ''' 3 rows each file'''
        expected_max_rows = [3,3]
        target_values = [('0',[' target_value', ' 351.7', ' 209.3']),('1',[' target_value', ' 466.2', ' 230.6'])]
        self.data_post_processor_test_object.log_files = ['log_file_particle_0.csv','log_file_particle_1.csv']
        self.data_post_processor_test_object._DataPostprocessor__get_data()
        self.assertEqual(self.data_post_processor_test_object.max_rows, expected_max_rows)
        self.assertEqual(self.data_post_processor_test_object.targets_collector, target_values)

    def test__get_min(self):

        expected_result = {1: '0', 2: '0'}
        self.data_post_processor_test_object.max_rows = [3,3]
        self.data_post_processor_test_object.targets_collector = [('0',[' target_value', ' 351.7', ' 209.3']),('1',[' target_value', ' 466.2', ' 230.6'])]
        self.data_post_processor_test_object._DataPostprocessor__get_min()
        self.assertEqual(self.data_post_processor_test_object.sample_number, expected_result)

    def test__create_file(self):

        ''' Test Best resutls file: '''
        best_results = [
                    '0.8234, 5.7635, 4.3292, 0.5315, 192.58, 0.12, 245.66, 96.37, 461.31, 673.12, -2.6, 351.7\n',
                    '1.37, 10.76, 3.67, 0.64, 190.48, 0.91, 212.58, 498.05, 318.55, 375.47, -2.61, 209.3\n'
                        ]
        read_best_results = []
        self.data_post_processor_test_object.sample_number = {1: '0', 2: '0'}
        self.data_post_processor_test_object._DataPostprocessor__create_file()
        with open('Best_results_file.csv', 'r') as test_file:
            test_file_lines = test_file.readlines()

        read_best_results.append(test_file_lines[1])
        read_best_results.append(test_file_lines[2])

        self.assertEqual(read_best_results, best_results)

@patch('database.DataBaseAdministrator', autospec=True)
class TestOptimizationManager(unittest.TestCase):

    @classmethod
    def setUpClass(cls):

        ''' Create optimization manager object only once at the beginning  '''
        input  ={
                'num_particles':3,
                'num_sub_swarms':1,
                'num_parameters':17,
                'max_steps':2
                }
        mock_DataBaseAdministrator= Mock(name ='DataBaseAdministrator')
        mock_DataBaseAdministrator.input_optimization = input
        # Mock the functions called in the initialization of the object
        with patch('pso.OptimizationManager._initialize_log_files') as mock__initialize_log_file:
            cls.opt_manager_object = OptimizationManager(mock_DataBaseAdministrator)
            mock__initialize_log_file.assert_called_with(input['num_parameters'],mock_DataBaseAdministrator)

    @classmethod
    def tearDownClass(cls):

        del cls.opt_manager_object
    ''' This test is not really useful in Unit test'''
    @patch('pso.SubSwarm')
    def test_reorganize_swarm(self,mock_Swarm, mock_DataBaseAdministrator):

        '''Create mock object resembles the swarm class'''
        ''' This function creates instaces of the Swarm class based on num_sub_swarms
            in this case its ONE '''
        swarm = Mock()
        particle_0 = Mock()
        particle_1 = Mock()
        particle_2 = Mock()
        swarm.particles = [particle_0, particle_1, particle_2]
        return_value = self.opt_manager_object.reorganize_swarm(swarm)
        ''' Check whether the return object is the same as the passed '''
        self.assertEqual(return_value , swarm)

    ''' The initialize_swarm has been neglected, as it deals with objects which will be mocked in
        the Unit-test, nothing logical to be checked, it will be the same as reorganize_swarm '''

    def test_initialize_current_step(self, mock_DataBaseAdministrator):

        time_list = [float('nan') for i in range(self.opt_manager_object.num_particles)]
        self.opt_manager_object.initialize_current_step()
        for i in range(len(self.opt_manager_object.delta_time_all_particles)):
            self.assertTrue(math.isnan(self.opt_manager_object.delta_time_all_particles[i]))
        self.opt_manager_object.current_step = self.opt_manager_object.max_steps_allowed
        self.opt_manager_object.initialize_current_step()
        self.assertTrue(self.opt_manager_object.convergence)

    def test_set_best_position(self, mock_DataBaseAdministrator):

        ''' Ceate 3 object of type particel and set their Target Value:'''
        particle_0 = Mock()
        particle_1 = Mock()
        particle_2 = Mock()
        particles = [particle_0, particle_1, particle_2]
        target_values = [220, 400, 600]
        positions = [
                        [0.52, 13.92, 1.88, 2.4, 1.7, 3.68, 1.94, 2.4, 0.36, 12.64, 1.84, 8.16, 0.59, 2.72, 0.68, 0.4, 0.02],
                        [0.7, 1.12, 0.1, 7.2, 0.62, 1.28, 0.94, 15.84, 1.08, 7.04, 0.04, 11.52, 0.96, 3.24, 2.0, 0.31, 0.8],
                        [0.53, 13.55, 1.83, 2.54, 1.67, 3.61, 1.91, 2.79, 0.38, 12.48, 1.79, 8.26, 0.6, 2.73, 0.72, 0.4, 0.04],
                    ]
        index = 0
        for particle in particles:
            particle.identifier = index
            particle.target_value = target_values[index]
            particle.position = positions[index]
            index = index +1

        self.opt_manager_object.set_best_position(particles)
        self.assertEqual(self.opt_manager_object.best_target_value_current_step, target_values[0])
        self.assertEqual(self.opt_manager_object.best_position_current_step, positions[0])

    ''' 
        The method "check_for_convergence" has been neglected due to the following:
        If I want to test it, I would patch 4 methods and check whether they
        have been called in the write context or not, and its very
        simple for that.
    '''
    def test_save_time(self, mock_DataBaseAdministrator):

        delta_time = 2.0 #2 seconds
        self.opt_manager_object.delta_time_all_particles = range(0,3)
        time_particle_start = datetime.datetime.now()
        time.sleep(delta_time)
        time_particle_end = datetime.datetime.now()
        expected_resutle = (round((2.0/60),2))

        identifier = 1
        self.opt_manager_object.save_time(identifier,time_particle_start,time_particle_end)

        self.assertEqual(self.opt_manager_object.delta_time_all_particles[identifier], expected_resutle)

    def test_write_summary(self, mock_DataBaseAdministrator):

        self.opt_manager_object.current_step = 1
        self.opt_manager_object.best_target_value_all_steps = 200
        self.opt_manager_object.reason_optimization_stopped = "Too many steps."
        self.opt_manager_object.write_summary(mock_DataBaseAdministrator)

        mock_DataBaseAdministrator.write_summary.assert_called_with(1,200,"Too many steps.")


    def test__initialize_log_files(self, mock_DataBaseAdministrator):

        num_parameters = 4
        called_with_header = "p1, p2, p3, p4, mean_sel [dB], efficiency, mass_anvil [t], mass_impact_weight [t], max_stress_impact_weight [MPa], max_stress_anvil [MPa], peak pile head velocity [m/s], target_value"

        self.opt_manager_object._initialize_log_files(num_parameters, mock_DataBaseAdministrator)
        mock_DataBaseAdministrator.write_log_particle_header.assert_any_call(0, called_with_header)
        mock_DataBaseAdministrator.write_log_particle_header.assert_any_call(1, called_with_header)
        mock_DataBaseAdministrator.write_log_particle_header.assert_any_call(2, called_with_header)

    def test__initialize_info_best_values(self, mock_DataBaseAdministrator):

        check_value = 10
        self.opt_manager_object.best_target_value_current_step = check_value

        self.opt_manager_object._initialize_info_best_values()

        self.assertEqual(self.opt_manager_object.best_target_value_last_step,check_value)
        self.assertEqual(self.opt_manager_object.best_target_value_all_steps, check_value)

    def test__set_change_info(self, mock_DataBaseAdministrator):

        ''' Test 1 condition: (contains Or )'''
        conditions = [(float('NaN'), 200), (200, 200), (200, 400)]
        index = 0
        for (self.opt_manager_object.best_target_value_current_step, self.opt_manager_object.best_target_value_last_step) in conditions:
            self.opt_manager_object.steps_without_change = 0
            self.opt_manager_object._set_change_info()
            if index == 2:
                self.assertEqual(self.opt_manager_object.steps_without_change, 0)
                self.assertEqual(self.opt_manager_object.best_target_value_last_step,
                                 self.opt_manager_object.best_target_value_current_step)
            else:
                self.assertEqual(self.opt_manager_object.steps_without_change, 1)
            index = index + 1

    def test__set_improvement_info(self, mock_DataBaseAdministrator):

        ''' Test 1 condition: (contains Or )'''
        conditions = [(float('NaN'),200), (400,200), (200,400)]
        index = 0
        for (self.opt_manager_object.best_target_value_current_step, self.opt_manager_object.best_target_value_all_steps) in conditions:
            self.opt_manager_object.steps_without_improvement = 0
            self.opt_manager_object._set_improvement_info()
            if index == 2:
                self.assertEqual(self.opt_manager_object.steps_without_improvement, 0)
                self.assertEqual(self.opt_manager_object.best_target_value_all_steps,self.opt_manager_object.best_target_value_current_step)
            else:
                self.assertEqual(self.opt_manager_object.steps_without_improvement,1)
            index = index + 1

    def test_set_convergence_info(self,mock_DataBaseAdministrator):

        arbitraty_value = 1
        ''' Test the 3 conditions:'''

        expected = ["Target value did not change anymore.",
                    "Best target value did not improve anymore.",
                    "Too many steps."]
        conditions = [[15,arbitraty_value,arbitraty_value],
                      [arbitraty_value,100,arbitraty_value],
                      [arbitraty_value,arbitraty_value, self.opt_manager_object.max_steps_allowed]]
        index = 0
        for condition in conditions:

            self.opt_manager_object.steps_without_change = condition[0]
            self.opt_manager_object.steps_without_improvement = condition[1]
            self.opt_manager_object.current_step = condition[2]
            out_put = expected[index]
            index = index + 1
            self.opt_manager_object._set_convergence_info()

            self.assertEqual(self.opt_manager_object.reason_optimization_stopped, out_put)

        '''Test the common variable:'''
        self.assertTrue(self.opt_manager_object.convergence)


class TestSubSwarm(unittest.TestCase):

    @classmethod
    def setUpClass(cls):

        ''' Apply a 3 particles test '''
        test_target_values = [100,200,300]
        test_positions = [
                        [0.52, 13.92, 1.88, 2.4, 1.7, 3.68, 1.94, 2.4, 0.36, 12.64, 1.84, 8.16, 0.59, 2.72, 0.68, 0.4, 0.02],
                        [0.7, 1.12, 0.1, 7.2, 0.62, 1.28, 0.94, 15.84, 1.08, 7.04, 0.04, 11.52, 0.96, 3.24, 2.0, 0.31, 0.8],
                        [0.53, 13.55, 1.83, 2.54, 1.67, 3.61, 1.91, 2.79, 0.38, 12.48, 1.79, 8.26, 0.6, 2.73, 0.72, 0.4, 0.04],
                         ]
        # Arbitrary identifier, not used for this class but the parent (Swarm) class
        identifire = 1
        index = 0
        particle_0 = Mock()
        particle_1 = Mock()
        particle_2 = Mock()
        cls.particles = [particle_0, particle_1, particle_2]
        for particle in cls.particles:
            particle.target_value = test_target_values[index]
            particle.identifier = index
            particle.position = test_positions[index]
            index = index + 1
        cls.sub_swarm_test_object = SubSwarm(identifire, cls.particles)

    def test_set_best_position(self):

        ''' Expected result is : best position for the best particle which is 0 '''
        self.sub_swarm_test_object.set_best_position()
        self.assertEqual(self.sub_swarm_test_object.best_position_current_step, self.particles[0].position)

class TestParticle(unittest.TestCase):

    @classmethod
    def setUpClass(cls):

        cls.parameterization = Mock()
        cls.parameterization.anvil = Mock()
        cls.parameterization.ImpactWeight = Mock()
        identifire = 0

        penalty_test_factors ={ 'mass': 100, 'stress':100, 'velocity':100, 'efficiency':100}
        penalty_test_type = {'mass':2,'stress':2,'velocity':2,'efficiency':2}

        key_words = ['num_parameters', 'inertia', 'social_factor', 'cognitive_factor', 'min_parameters',
                     'max_parameters', 'threshold_craziness', 'mass_impact_weight_max', 'mass_anvil_max',
                     'efficiency_min', 'max_stress_max', 'v_peak_min', 'penalties_type', 'penalty_factor_mass',
                     'penalty_factor_stress', 'penalty_factor_velocity', 'penalty_factor_efficiency']
        cls.corresponding_values = [17, 0.8, 2, 2, [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1],
                                [2, 16, 2, 16, 2, 16, 2, 16, 2, 16, 2, 16, 1, 4, 4, 1, 1], 0.95, 350e3,
                                200e3, 0.8, 1e9, -2.7, 'quadratic', 100,100,100,100]
        cls.initial_positon_particle_0 = [0.571, 1.744, 0.167, 4.095,
                                      0.616, 12.078, 0.808,13.282,
                                      1.641, 11.204, 0.512, 1.824,
                                      0.932, 1.842,2.702, 0.461, -0.339]
        with patch('database.DataBaseAdministrator', autospec= True) as mock_databaseAdmin:

            mock_databaseAdmin.input_optimization = {}
            index = 0
            for word in key_words:
                mock_databaseAdmin.input_optimization[word] = cls.corresponding_values[index]
                index += 1
            mock_databaseAdmin.read_initial_position.return_value = cls.initial_positon_particle_0


            cls.parameterization.anvil.generate_component.return_value = mock_databaseAdmin.read_initial_position
            cls.parameterization.ImpactWeight.generate_component.return_value = mock_databaseAdmin.read_initial_position
            cls.reference_velocity =[0.3*(a-b) for a, b in zip(mock_databaseAdmin.input_optimization['max_parameters'],
                                                           mock_databaseAdmin.input_optimization['min_parameters'])]

            cls.particleTestOb = Particle(identifire,cls.parameterization,mock_databaseAdmin)
            cls.particleTestOb.penalty_dict = {'types': penalty_test_type, 'factors': penalty_test_factors}

    ''' This method tests 4 methods; set_optimization_info, initialize_position,
        _renew_components, and _set_reference_velocity as they all called in the initialization,
        therefore they tested in one shot
    '''
    def test_initialized_attributes(self):

        # Create a temp. test instance
        self.particleTestOb.test_attributes = [self.particleTestOb.num_points, self.particleTestOb.w,self.particleTestOb.c1,
                                               self.particleTestOb.c2,self.particleTestOb.parameter_min, self.particleTestOb.parameter_max,
                                               self.particleTestOb.threshold_craziness,self.particleTestOb.mass_impact_weight_max,
                                               self.particleTestOb.mass_anvil_max, self.particleTestOb.efficiency_min,
                                               self.particleTestOb.max_stress_max, self.particleTestOb.v_peak_min]
        index = 0
        for i in range(0, len(self.particleTestOb.test_attributes)):
            self.assertEqual(self.particleTestOb.test_attributes[index], self.corresponding_values[index])
            index += 1

        self.assertEqual(self.particleTestOb.position, [0.571, 1.744, 0.167, 4.095,
                                      0.616, 12.078, 0.808,13.282,
                                      1.641, 11.204, 0.512, 1.824,
                                      0.932, 1.842,2.702, 0.461, -0.339])
        self.assertEqual(self.particleTestOb.velocity, [0 for p in range(0, self.corresponding_values[0])])
        self.assertEqual(self.particleTestOb.reference_velocity, self.reference_velocity)

        self.parameterization.anvil.assrt_called_with(self.initial_positon_particle_0)
        self.parameterization.ImpactWeight.assrt_called_with(self.initial_positon_particle_0)

        '''
            Clean test environment, remove test attributes, they are already
            saved correctly in the test object since they passed the test.
        '''
        delattr(self.particleTestOb, 'test_attributes')
        delattr(self.__class__, 'parameterization')
        delattr(self.__class__, 'initial_positon_particle_0')

    def test__set_penalty_type(self):

        type = 'quadratic'
        order = self.particleTestOb._set_penalty_type(type)
        self.assertEqual(order,2)

    def test_set_best_target_value(self):


        # Check the values when the condition is False.
        self.particleTestOb.target_value = test_t_v = 2e3

        self.particleTestOb.set_best_target_value()
        self.assertEqual(self.particleTestOb.best_position, self.particleTestOb.best_position )
        self.assertEqual(self.particleTestOb.best_target_value, self.particleTestOb.best_target_value )

        # Check the values when the condition is true.
        self.particleTestOb.target_value = test_t_v = 300
        self.particleTestOb.position = [0.53, 13.55, 1.83, 2.54, 1.67,
                                        3.61, 1.91, 2.79, 0.38, 12.48,
                                        1.79, 8.26, 0.6, 2.73, 0.72, 0.4, 0.04]

        self.particleTestOb.set_best_target_value()
        self.assertEqual(self.particleTestOb.best_position, self.particleTestOb.position)
        self.assertEqual(self.particleTestOb.best_target_value, test_t_v)

    def test_set_target_value_test(self):

        test_t_v = 200
        self.particleTestOb.set_target_value_test(test_t_v)
        self.assertEqual(self.particleTestOb.target_value, test_t_v)

    def test__calculate_penalty(self):

        penalty_value = 0
        current_value = 200
        max_value = 300
        property = 'mass'
        ''' Result = 0 + (abs(200-300)/300)^2 *100'''
        expected_value = 11.11
        return_calculated_penalty = self.particleTestOb._calculate_penalty(penalty_value,current_value,
                                                                           max_value, property)
        self.assertEqual(round(return_calculated_penalty,2) , expected_value)

    def test__set_penalties(self):

        #Initialize the attributes that should be used inside the function:

        self.particleTestOb.penalty_v = 0
        self.particleTestOb.mass_anvil = 300e3
        self.particleTestOb.efficiency = 0.7
        self.particleTestOb.penalty_mass = 0
        self.particleTestOb.penalty_stress = 0
        self.particleTestOb.max_stress_anvil = 3e6
        self.particleTestOb.mass_impact_weight = 200e3
        self.particleTestOb.peak_pile_head_velocity = -2.5
        self.particleTestOb.max_stress_impact_weight = 2e9
        '''
            Expected results: Order = 2, penalty factors = 100, calculated manually! 
        '''
        Penalty_mass =  25 # 0 (I.W) , 25 (A)
        Penalty_stress = 100 # 100, 0
        Penalty_velocity = 0.55
        Penalty_efficiency = 1.56
        Penalties_sum = 127.11

        self.particleTestOb._set_penalties()

        self.assertEqual(round(self.particleTestOb.penalty_mass,2), Penalty_mass)
        self.assertEqual(round(self.particleTestOb.penalty_stress,2), Penalty_stress)
        self.assertEqual(round(self.particleTestOb.penalty_v,2), Penalty_velocity)
        self.assertEqual(round(self.particleTestOb.penalty_efficiency,2), Penalty_efficiency)

        self.assertEqual(round(self.particleTestOb.sum_penalties,2), Penalties_sum)

    def test_move(self):

        '''
            1. Fix the randomly generated number to verify the test.
            2. Test all conditions, and notice the changes.
        '''
        with patch('pso.random') as mock_random:

            # Case 1:
            mock_random.random.return_value = 2 # craziness < threshold_craziness (true)
            expected_position = [1.77, 11.34, 1.37, 13.7, 1.82, 16.0, 2.0, 16.0, 2.0, 16.0, 1.71, 11.42, 1.0, 4.0, 4.0, 1.0,0.86]
            expected_velocity = [1.2, 9.6, 1.2, 9.6, 1.2, 3.92, 1.19, 2.72, 0.36, 4.8, 1.2, 9.6, 0.07, 2.16, 1.3, 0.54, 1.2]
            best_position_current_step = [200 for i in range(0,self.particleTestOb.num_points)]
            self.particleTestOb.move(best_position_current_step)
            self.assertEqual(self.particleTestOb.position, expected_position)
            self.assertEqual(self.particleTestOb.velocity, expected_velocity)

            # Case 2:
            mock_random.random.return_value = 0.8 # craziness < threshold_craziness (false)
            # Case 2.1:
            expected_position = [2.0, 16.0, 2.0, 16.0, 2.0, 16.0, 2.0, 16.0, 2.0, 16.0, 2.0, 16.0, 1.0, 4.0, 4.0, 1.0,1.0]
            expected_velocity = [0.23, 4.66, 0.63, 2.3, 0.18, 0.0, 0.0, 0.0, 0.0, 0.0, 0.29, 4.58, 0.0, 0.0, 0.0, 0.0, 0.14]
            self.particleTestOb.target_value = float('nan') # isnan condition (true)
            self.particleTestOb.move(best_position_current_step)
            self.assertEqual(self.particleTestOb.position, expected_position)
            self.assertEqual(self.particleTestOb.velocity, expected_velocity)
            # Case 2.2:
            expected_position = [2.0, 16.0, 2.0, 16.0, 2.0, 16.0, 2.0, 16.0, 2.0, 16.0, 2.0, 16.0, 1.0, 4.0, 4.0, 1.0, 1.0]
            expected_velocity = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
            self.particleTestOb.target_value = 180          # isnan condition (false)
            self.particleTestOb.move(best_position_current_step)
            self.assertEqual(self.particleTestOb.position, expected_position)
            self.assertEqual(self.particleTestOb.velocity, expected_velocity)

    def test__get_valid_velocity(self):

        new_position = [-0.17, 12.43, 1.73, -4.66, 1.05, 2.33,
                        0.97, -13.05, -0.7, 5.44, 1.75, -3.26,
                        -0.36, -0.51, -1.28, 0.09, -0.76]
        new_velocity = [0.53, 13.55, 1.83, 2.54, 1.67, 3.61,
                        1.91, 2.79, 0.38, 12.48, 1.79, 8.26,
                        0.6, 2.73, 0.72, 0.4, 0.04]
        ''' 
            Result: compare each element in the new position with its min and max value
            and adjust the results accordingly 
        '''
        return_corrected_velocity = self.particleTestOb._get_valid_velocity(new_velocity, new_position)
        expected_result = [0.7, 13.55, 1.83, 7.2, 1.67, 3.61,
                           1.91, 15.84, 1.08, 12.48, 1.79, 11.52,
                           0.96, 3.24, 2.0, 0.4, 0.04]
        self.assertEqual(return_corrected_velocity, expected_result)



'''  
    In the following test: the ImpactWeight and Anvil, since they are childs of the HammerComponent class
    and the HammerComponent class is child of AbaqusSolverConnector, both will be tested at once 
    The Pile class dose not have any methods so testing it will not have any benefits
    Testing will be done through the minimal parameterization.  
    * Note: the test module sorts the test classes alphabetically, the 0x0 numbering is used to keep the order.
'''
class Test010Minimal_Inheritance(unittest.TestCase):

    @classmethod
    def setUpClass(cls):

        cls.anvil_test_ob = Anvil('anvil')
        cls.iw_test_ob = ImpactWeight('impact_weight')
        parameters = [2,3,1] #minimal parameters: iw width, iw height, anvil height
        cls.anvil_test_ob._set_coordinates(parameters)
        cls.iw_test_ob._set_coordinates(parameters)

    ''' The sketch_part method was ignored as it requires some visualization to check the sketch itself'''
    ''' Unittest tends to sort the test methods, this 0x0 naming to prevent that in this particular test'''
    def test_010_set_height(self):

        # test the coordinates set by _set_coordinates first "Implicit test"

        anvil_x                       = [[0, 3.5, 3.5, 0]]
        anvil_y                       = [[0, 0, 1, 1]]
        iw_x                          = [[0, 2, 2, 0]]
        iw_y                          = [[0, 0.1, 3, 3]]
        anvil_height                  = 1
        iw_height                     = 3
        anvil_height_at_symmetry_line = 1
        iw_height_at_symmetry_line    = 3
        self.assertEqual(self.anvil_test_ob.y, anvil_y)
        self.assertEqual(self.anvil_test_ob.x, anvil_x)
        self.assertEqual(self.iw_test_ob.y, iw_y)
        self.assertEqual(self.iw_test_ob.x, iw_x)

        self.iw_test_ob._set_height()
        self.anvil_test_ob._set_height()

        self.assertEqual(self.anvil_test_ob.height, anvil_height)
        self.assertEqual(self.anvil_test_ob.height_at_symmetry_line,anvil_height_at_symmetry_line)
        self.assertEqual(self.iw_test_ob.height, iw_height)
        self.assertEqual(self.iw_test_ob.height_at_symmetry_line, iw_height_at_symmetry_line)

    def test_020_close_shape(self):

        anvil_x_closed = [[0, 3.5, 3.5, 0, 0]]
        anvil_y_closed = [[0, 0, 1, 1, 0]]
        iw_x_closed    = [[0, 2, 2, 0]]
        iw_y_closed    = [[0, 0.1, 3, 3]]
        self.anvil_test_ob._close_shape()
        self.assertEqual(self.anvil_test_ob.x, anvil_x_closed)
        self.assertEqual(self.anvil_test_ob.y, anvil_y_closed)
        self.assertEqual(self.iw_test_ob.x, iw_x_closed)
        self.assertEqual(self.iw_test_ob.y, iw_y_closed)

    ''' The method generate_component has been neglected, as it only calls other functions.'''

''' 
    This class calls all it's methods inside the init method therefore, the test will be done by checking the attributes
    rather executing the functions, (i.e. Already called during the initialization).
'''
class Test020AbaqusImpactModel(unittest.TestCase):

    @classmethod
    def setUpClass(cls):



        #Prepare class constructors:
        element_size_components      = 0.05
        element_size_contact_surface = 0.05
        impact_energy                = 3500e3
        time_impact_simulation       = 5e-4
        parameters                   = [2, 3, 1]
        # prepare models
        mdb.Model(name='impact', objectToCopy=mdb.models['Model-1'])
        test_impact_model = mdb.models['impact']
        cls.anvil_test_ob = Anvil('anvil')
        cls.anvil_test_ob.generate_component(parameters)
        cls.iw_test_ob = ImpactWeight('impact_weight')
        cls.iw_test_ob.generate_component(parameters)

        cls.modelling_test_ob = AbaqusImpactModel(test_impact_model, cls.anvil_test_ob, cls.iw_test_ob,
                                                  time_impact_simulation, impact_energy, element_size_components,
                                                  element_size_contact_surface)

    ''' 
        The class "AbaqusImpactModel" will be tested, instead of mocking all the class
        which will result in a unrealistic test and a bunch of mocking object, 
        a test model has been set and performed by Abaqus, and the result of the model(i.e. attributes) has been tested afterwords. 
        The model is based on the minimal parameterization
        
        (*Note: the minimal module has been tested and verified before!) 
    '''
    def test_all_attributes(self):

            area_anvil = 1 * 3.5 # as set in the initialization "Rectangular"
            centroid_anvil = [1.75, 0.5, 0] # X,Y,Z
            area_iw = (2*3) - (0.1 *0.5 * 2) #5.9 Rectangular - Small triangle
            centroid_iw = [0.994350254535675, 1.52485871315002, 0.0] # X,Y,Z
            rho = 7850 # Material density?
            anvil_mass = round(2*3.14159265359*centroid_anvil[0]*area_anvil*rho ,2)
            iw_mass = round(2*3.14159265359*centroid_iw[0]*area_iw*rho, 2)
            # Pile dimensions as declared in the parts module
            inner_radius = round((3.25 - 0.08),2)
            outer_radius = round(3.25,2)
            length = 70
            ''' Velocity = Square root(2*KE/(mass))'''
            iw_velocity = round((math.sqrt((2*self.modelling_test_ob.impact_energy) / iw_mass)),2)


            self.assertEqual(round(self.modelling_test_ob.mass_anvil,2), anvil_mass)
            self.assertEqual(round(self.modelling_test_ob.mass_impact_weight,2), iw_mass)
            self.assertEqual(round(self.modelling_test_ob.pile.outer_radius,2), outer_radius)
            self.assertEqual(round(self.modelling_test_ob.pile.inner_radius,2) , inner_radius)
            self.assertEqual(round(self.modelling_test_ob.pile.length,2), length)
            self.assertEqual(round(self.modelling_test_ob.velocity_impact_weight,2) , iw_velocity,)

''' 
    Class AbaqusPropagationModel modify the temp. input file, it has only one function
    called in the initialization, therefore one test is required, scince it deals with files
    so, the test is done through modifying the file with previously know values, and check
    whether the new file in correct or not
'''
class Test030AbaqusPropagationModel(unittest.TestCase):

    @classmethod
    def setUpClass(cls):

        os.chdir(path_unit_test)
        # Since the class does not interface with Abaqus classes, mocking objects used
        mdb = Mock()
        cls.abaqusOutput = Mock()
        cls.abaqusOutput.time_impact = [0.00000000e+00,   1.01569558e-05,   2.06521709e-05,   3.11265685e-05,\
                                        4.00962163e-05,   5.05549651e-05,   6.10096249e-05,   7.14613634e-05,\
                                        8.04187366e-05,   9.08670045e-05,   1.01314654e-04,   1.10268709e-04]

        cls.abaqusOutput.pile_head_velocity = [ 0.00000000e+00,  1.05195741e-05,   2.11863135e-05,   3.07858500e-05,\
                                                4.03773229e-05,  5.18803827e-05,   6.14620731e-05,   7.10407185e-05,\
                                                8.06168246e-05,  9.01907915e-05,   1.01677229e-04,   1.11247602e-04]
        cls.simulation_time = 5e-4
        cls.prop_test_obj = AbaqusPropagationModel(mdb, cls.abaqusOutput, cls.simulation_time)

    @classmethod
    def tearDownClass(cls):

        # Clear test directory after the test was done
        [os.remove(file) for file in glob.glob("*.inp")]

    def test_propagation_model_parameters(self):

        found_amplitude = False
        found_dynamic = False
        amplitude = []
        dynamic = 0
        line_values = []
        test_file = open('acousticModel_30m_100ms.inp','r')
        test_file = test_file.readlines()
        combined_list = []
        for line in test_file:

            if line.startswith('*Dynamic'):
                found_amplitude = False
                found_dynamic = True
            elif line.startswith('*Amplitude'):
                found_amplitude = True
                found_dynamic = False
            elif found_amplitude:
                line_values = line.strip().split(',')
                for value in line_values:
                    amplitude.append(value)
            elif found_dynamic:
                dynamic = line.split(',')[1]

        for i in range(len(self.abaqusOutput.time_impact)):
            combined_list.append(str(self.abaqusOutput.time_impact[i]))
            combined_list.append(str(self.abaqusOutput.pile_head_velocity[i]))

        self.assertEqual(float(dynamic), float(self.simulation_time))
        self.assertEqual(amplitude, combined_list)

