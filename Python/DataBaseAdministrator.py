import csv
import sys
import logging
import os
import re
import random
import datetime
import glob

class DataBaseAdministrator():

    name_input_file = "input_optimization.csv"  

    log_file_base_name = "log_file"
    log_file_base_name_particle = log_file_base_name + "_particle_"
    log_file_base_name_shape = "log_shape_particle_"
    file_name_summary = "summary.log"
    file_data_recorder = "record.log"
    file_name_time = "time.csv"
    first_target_value = 0

    def __init__(self, path):

        self.working_directory = path

        logging.debug("DataBaseAdministrator: Set working directory to %s" % self.working_directory)



        self.read_input_file()

        if self.input_optimization['initial_position_file'] == "automatic":

            num_particles = self.input_optimization['num_particles']
            parameter_max = self.input_optimization['max_parameters']
            parameter_min = self.input_optimization['min_parameters']
            #Generate csv file contains the new initial position and set the file name accordingly
            self._set_initial_position_file(num_particles, parameter_max, parameter_min)
            self.name_file_initial_positions = 'initial_positions/automatic_initial_position.csv'


        else:
            self.name_file_initial_positions = self.input_optimization['initial_position_file']

        logging.info("DataBaseAdministrator: Initial position taken from file %s" % self.name_file_initial_positions)

    def create_summary_log(self):

        currentDT = datetime.datetime.now()
        date = currentDT.strftime("%Y-%m-%d %H:%M:%S")
        info = date + ": Optimization started with the following input parameters: "
        self._add_line(self.file_name_summary, info)
        self._input_file_summary()



    def _set_initial_position_file(self,num_particles, parameters_max, parameters_min):

        cwd = os.getcwd()
        position_path = cwd + "/initial_positions"
        logging.info("DataBaseAdministrator: current path %s" % cwd)
        os.chdir(position_path)
        with open('automatic_initial_position.csv', 'w') as position_file:
            csv_write = csv.writer(position_file, lineterminator='\n')
            for particle in range(0, num_particles):
                add_new = []
                for p in range(0, len(parameters_max)):
                    add_new.append(round(random.uniform(parameters_min[p], parameters_max[p]), 3))
                csv_write.writerow(add_new)
        os.chdir(cwd)
        logging.info("DataBaseAdministrator: Automatic generation of initial position is done..")


    def record_current_position(self, particle,optimizationManager, edge_flag):

        if edge_flag == 'start':
            self._add_line(self.file_data_recorder, '-------------------------------------------')
            line = 'Step: '+ str(optimizationManager.current_step) +' particle number: ' + str(particle.identifier)+' started'
        else:
            line = 'Step: '+str(optimizationManager.current_step)+\
                    ' particle number: '+str(particle.identifier) + ' ended '+\
                    '\nParticle velocity:'+ self._convert_to_string_for_log_file(particle.velocity) +\
                    '\ntarget_value:'+str(particle.target_value)+\
                    '\nposition:'+self._convert_to_string_for_log_file(particle.position)+\
                    '\nBest position:' + str(self._convert_to_string_for_log_file(particle.best_position))+\
                    '\nBest target value:'+ str(particle.best_target_value)
            if self.first_target_value == 0: # Only executed at the beginning !
                self.first_target_value = particle.target_value

        self._add_line(self.file_data_recorder, line)

    def check_last_position(self):

        self._add_line(self.file_name_summary,'Resume Optimization..')
        steps = []
        particles = []
        self.saved_data = {}
        saved_best_target_values = {}
        saved_best_position = {}
        saved_velocity = {}
        saved_target_values = {}
        saved_positions = {}
        ended_particles = []
        step_was_not_complete = True

        file = open(self.file_data_recorder, 'r')
        summaryFile = file.readlines()

        # Search for the last step:
        for line in summaryFile:
            if line.startswith('Step: '):
                #steps list will contain a duplicate number for each step represents beginning and starting
                steps.append(re.findall('[0-9]+', line)[0])
                particle_i = 'particle_' + str(re.findall('[0-9]+', line)[1]) # return (particle) in that step
                continue
            elif line.startswith('Particle velocity:'):
                saved_velocity[particle_i] = [float(i) for i in line.rstrip().split(':')[1].split(',')]
                continue
            elif line.startswith('Best position:'):
                saved_best_position[particle_i] = [float(i) for i in line.rstrip().split(':')[1].split(',')]
                continue
            elif line.startswith('Best target value:') :
                saved_best_target_values[particle_i]= float(line.rstrip().split(':')[1])
                continue
            elif line.startswith('target_value'):
                saved_target_values[particle_i] = float(line.rstrip().split(':')[1])
            elif line.startswith('position'):
                saved_positions[particle_i] = [float(i) for i in line.rstrip().split(':')[1].split(',')]

        last_step = int(max(steps))
        self._add_line(self.file_name_summary,'Last step is'+ str(last_step))
        # Search for the last particle in the last step:
        for line in summaryFile:
            if line.startswith('Step: ' + str(max(steps))):
                if line.rstrip().endswith('ended'):
                    ended_particles.append(int(re.findall('[0-9]+', line)[1]))
                else:
                    particles.append(int(re.findall('[0-9]+', line)[1]))

        removed = []
        particles = list(set(particles))
        ended_particles = list(set(ended_particles))
        for p in particles:
            if p not in ended_particles:
                removed.append(p)
                self._add_line(self.file_name_summary,'particle_'+str(p)+' interrupted')
                particles.remove(p)

        self._add_line(self.file_name_summary,'Sucssesfully created paricles'+str(particles))
        max_steps = self.input_optimization['max_steps']
        n_particles = self.input_optimization['num_particles']

        #check the max number of steps and particle to validate input file:
        if last_step >= max_steps and (len(particles) == n_particles):
            logging.exception("Wrong mode selected, please check input file..! ")
            raise ValueError
        elif len(particles) == (n_particles):
            step_was_not_complete = False
            self._add_line(self.file_name_summary,'Last step was complete')

        #Last saved values for each particle
        self.saved_data['created_particle'] = particles
        self.saved_data['saved_best_target_values'] = saved_best_target_values
        self.saved_data['saved_best_position'] = saved_best_position
        self.saved_data['saved_velocity'] = saved_velocity
        self.saved_data['target_values'] = saved_target_values
        self.saved_data['positions'] = saved_positions

        return (last_step,particles,step_was_not_complete)

    def correct_optimization_data(self, swarm):

        for subSwarm in swarm.sub_swarms:

            for particle in subSwarm.particles:
                #assign best values to the particles
                index = 'particle_' + str(particle.identifier)
                try:
                    particle.best_target_value = self.saved_data['saved_best_target_values'][index]
                    particle.best_position = self.saved_data['saved_best_position'][index]
                    particle.velocity = self.saved_data['saved_velocity'][index]
                except:
                    self._add_line(self.file_name_summary,'no data recovered for '+index)
                if len(self.saved_data['created_particle']) != (self.input_optimization['num_particles']) :
                    #last step was not complete, prepare the particles:
                    if particle.identifier in self.saved_data['created_particle']:
                        particle.target_value = self.saved_data['target_values'][index]
                        particle.position = self.saved_data['positions'][index]
                        self._add_line(self.file_name_summary,index+' prepared for repeated step')
                logging.info("DataBaseAdministrator: Particle %d has been corrected"%particle.identifier)

