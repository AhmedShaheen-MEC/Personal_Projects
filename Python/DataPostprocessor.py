import csv
import sys
import logging
import os
import re
import random
import datetime
import glob

'''
This program aim is to create a summary for the best "Min target values"
among a number of Hammer samples with different target values.
'''


class DataPostprocessor:

    log_files = list()
    targets_collector = []
    sample_number = dict()
    file_path = ""
    samples_counter = 0
    max_rows = []

    def __init__(self, file_path):

        self.file_path = file_path
        logging.debug("Working directory: %s" % self.file_path)
        try:
            os.chdir(file_path)
        except:
            logging.error("No such directory exists %s" %self.file_path)
          

    def __get_files(self):

        try:
            for file_name in os.listdir(self.file_path):
                if file_name not in self.log_files and file_name.startswith('log_file_particle'):
                    self.log_files.append(file_name)

            logging.info("Number of files found:" + str(len(self.log_files)))
            if len(self.log_files) < 1:
                raise WrongDirectory("Missing files")

        except WrongDirectory as Error:
            print Error.error
            logging.exception('Missing files %s' %self.file_path)
            

    def __get_data(self):

        for file in self.log_files:
            print file
            self.samples_counter = 0
            target_values = []

            with open(file) as hammer_sample:
                for row in hammer_sample:
                    self.samples_counter += 1
                    target_values.append(row.rstrip().split(',')[-1])

            self.targets_collector.append((re.findall('[0-9]+', file)[0], target_values))
            # get the largest number of rows to avoid omitting any data
            self.max_rows.append(self.samples_counter)
        logging.info('Maximum number of rows is %s'% max(self.max_rows))

    def __get_min(self):

        iteration_variable = 1
        while iteration_variable < max(self.max_rows):
            multiple_values = []

            for (file_number, trials) in self.targets_collector:
                try:
                    # create a tuple contains (target value, file number)
                    multiple_values.append((float(trials[iteration_variable]), file_number))
                except:
                    # create a virtual row, if there is no sufficient row exists
                    logging.warning("Virtual value has been created in file number %s sample number %s"
                                    %(file_number, iteration_variable))
                    multiple_values.append((float("inf"), file_number))
            # set the row (sample number) to the minimum target values
            self.sample_number[iteration_variable] = min(multiple_values)[1]
            iteration_variable += 1

    def __create_file(self):

        header = True
        with open('Best_results_file.csv', 'w') as best_collector:

            logging.info("Best_results_file has been created in %s directory" % os. getcwd())

            for trial_number in self.sample_number:
                # get file's name which corresponds to a best result at this row"sample"
                file_name = self.sample_number[trial_number]

                with open('log_file_particle_' + str(file_name) + '.csv') as minTargetfile:
                    read_file = minTargetfile.readlines()
                    if header: best_collector.write(list(read_file)[0])
                    header = False
                    # extract the required row only and write it in the best particles file
                    best_collector.write(list(read_file)[trial_number])

    def analyzer(self):

        self.__get_files()
        self.__get_data()
        self.__get_min()
        self.__create_file()


class WrongDirectory(Exception):

    def __init__(self, error):

        self.error = error
