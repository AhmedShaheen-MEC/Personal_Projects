import unittest
from unittest.mock import patch, Mock, MagicMock
import os
import sys
import csv
import glob

''' ***** Set up path***** '''
path = "D:/Eng.Progrmas/Hammer/UnitTests"
path_classes = path + "/classes"
path_modules = path + "/modules"
path_templates = path + "/templates"
sys.path.append(path)
sys.path.append(path_classes)
sys.path.append(path_modules)
sys.path.append(path_templates)
os.chdir(path)
''' ***** Import test module *****'''
from database import DataBaseAdministrator

'''VIP: class decorator should be passed to all the defined function ! '''
''' **** Mock not relevant modules **** '''

@patch('pso.OptimizationManager', autospec=True)
@patch('pso.Particle')
class TestDataBaseAdministrator(unittest.TestCase):

    ''' Create dataBaseAdministrator object when the class is created '''

    @classmethod
    def setUpClass(cls):

        print('setupClass')
        with patch('database.DataBaseAdministrator._get_path_file') as mock__get_path_file:
            mock__get_path_file.return_value = path + '/input_optimization.csv'
            cls.dbTestObject = DataBaseAdministrator(path)
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
        print('teardownClass')
        # remove files and clean test area
        [os.remove(file) for file in glob.glob("test_*.csv")]


    def test_read_input_file(self,mock_Particle, mock_OptimizationManager):

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
        self.assertEqual(self.dbTestObject.input_optimization["initial_position_file"], "automatic")
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
        with open('initial_positions/automatic_initial_position.csv', 'r') as position_file:
            position_file = csv.reader(position_file)
            for line in position_file:
                for p in range(0,len(max_values)):
                    self.assertGreater(float(line[p]),min_values[p])
                    self.assertLess(float(line[p]),max_values[p])

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
            self.assertEqual(case_1[0], "step "+ str(10)+"\n")
            self.assertEqual(case_1[1], "target value: " + str(200)+"\n")
            self.assertEqual(case_1[2], "steps without improvement: " + str(3)+"\n")
            self.assertEqual(case_1[3], "steps without change: " + str(1)+"\n")

            # check the if condition: false
            mock_OptimizationManager.current_step = 0
            self.dbTestObject.write_log(mock_OptimizationManager)
            test_file = open('test_file.csv', 'r+')
            case_2 = test_file.readlines()
            # clear the test file each time
            test_file.truncate(0)
            test_file.close()

            self.assertEqual(case_2[0], "step "+ str(0)+"\n")
            self.assertEqual(case_2[1],  "target value: " + str(200)+"\n")
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
        expected_line_1 = "step: 1, position: "+ self.dbTestObject._convert_to_string_for_log_file(mock_Particle.position)
        expected_line_2 = "step: 1, velocity, "+ self.dbTestObject._convert_to_string_for_log_file(mock_Particle.velocity)
        expected_line_3 = "step: 1, best_cognitive_position, "+ self.dbTestObject._convert_to_string_for_log_file(mock_Particle.best_position )
        expected_line_4 = "step: 1, best_social_position, "+ self.dbTestObject._convert_to_string_for_log_file(mock_OptimizationManager.best_position_current_step)

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

        self.assertEqual(self.dbTestObject._get_path_file(self.dbTestObject.name_input_file),path+"/"+self.dbTestObject.name_input_file)

    def test_add_line(self, mock_OptimizationManager, mock_Particle):

        with patch('database.DataBaseAdministrator._get_path_file') as mocked_path:
            mocked_path.return_value = path+ '/virtual_folder'
            with patch('database.open') as open_mocked:
                self.dbTestObject._add_line(mocked_path(),'This is line')
                open_mocked.assert_called_with(path+'/virtual_folder', "a+")

    def test_convert_to_string_for_log_file(self, mock_OptimizationManager, mock_Particle):

        self.assertEqual(self.dbTestObject._convert_to_string_for_log_file(25),'25')
        self.assertEqual(type(self.dbTestObject._convert_to_string_for_log_file([1,1.8,3.6,4,5,5])), str)



if __name__ == '__main__':
    unittest.main()

