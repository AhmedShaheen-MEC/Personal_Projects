import random
import math
import numpy as np
import logging

class Particle:
        
    def set_optimization_info(self, dataBaseAdministrator):

        self.num_points = dataBaseAdministrator.input_optimization['num_parameters'] #TODO different for impact weight and anvil
        self.w = dataBaseAdministrator.input_optimization['inertia']
        self.c1 = dataBaseAdministrator.input_optimization['social_factor']
        self.c2 = dataBaseAdministrator.input_optimization['cognitive_factor']
        self.parameter_min = dataBaseAdministrator.input_optimization['min_parameters']
        self.parameter_max = dataBaseAdministrator.input_optimization['max_parameters']
        self.threshold_craziness = dataBaseAdministrator.input_optimization['threshold_craziness']
        self.mass_impact_weight_max = dataBaseAdministrator.input_optimization['mass_impact_weight_max']
        self.mass_anvil_max = dataBaseAdministrator.input_optimization['mass_anvil_max']
        self.efficiency_min = dataBaseAdministrator.input_optimization['efficiency_min']
        self.max_stress_max = dataBaseAdministrator.input_optimization['max_stress_max']
        self.v_peak_min = dataBaseAdministrator.input_optimization['v_peak_min']

        penalty_property_list = ['mass', 'stress', 'velocity', 'efficiency']
        types_dict = {}
        try:
            if 'penalties_type' in dataBaseAdministrator.input_optimization.keys():
                same_type = self._set_penalty_type(dataBaseAdministrator.input_optimization['penalties_type'])
                for word in penalty_property_list:
                    types_dict[word] = same_type
                logging.info("Particle: All penalties have the same type")
            else:
                for property in penalty_property_list:
                    key_word = 'penalty_type_' + property
                    types_dict[property] = self._set_penalty_type(dataBaseAdministrator.input_optimization[key_word])
                logging.info("Particle: Penalty types entered individually")
        except:
                logging.exception("Wrong penalty type has been entered, execution will be stopped..! ")
                raise ValueError

        factors_dict = {}
        try:
            if 'penalties_factor' in dataBaseAdministrator.input_optimization.keys():
                same_factor = dataBaseAdministrator.input_optimization['penalties_factor']
                for word in penalty_property_list:
                    factors_dict[word] = same_factor
                logging.info("Particle: All penalties have the same factors")
            else:
                for property in penalty_property_list:
                    key_word = 'penalty_factor_' + property
                    factors_dict[property] = dataBaseAdministrator.input_optimization[key_word]
                logging.info("Particle: Penalty factors entered individually")
        except:
                logging.exception("Wrong penalty factor has been entered, execution will be stopped..! ")
                raise ValueError

        self.penalty_dict = {'types': types_dict, 'factors': factors_dict}
        self._set_reference_velocity()

    def _set_penalty_type(self, type):
        if type == 'linear':
            order = 1
        elif type == 'quadratic':
            order = 2
        else:
            order = 2
            logging.warning("Particle: Wrong type entered, type has been set to Quadratic")
        return order

    def _calculate_penalty(self, penalty_property, current_value, limiting_value, flag):
        penalty_order = self.penalty_dict['types'][flag]
        penalty_factor = self.penalty_dict['factors'][flag]
        delta_relative = round((abs(current_value - limiting_value)), 2) / limiting_value
        penalty_property = penalty_property + penalty_factor * delta_relative ** penalty_order

        return penalty_property

    def _set_penalties(self):

        self.penalty_mass = 0
        mask = 0

        if self.mass_impact_weight > self.mass_impact_weight_max:
            self.penalty_mass = self._calculate_penalty(self.penalty_mass, self.mass_impact_weight,
                                                        self.mass_impact_weight_max, 'mass')

        if self.mass_anvil > self.mass_anvil_max:
            self.penalty_mass = self._calculate_penalty(self.penalty_mass, self.mass_anvil, self.mass_anvil_max, 'mass')

        logging.debug("Particle: Total penalty (impact weight and anvil) for mass is: %0.2f", self.penalty_mass)

        self.penalty_stress = 0

        if self.max_stress_impact_weight > self.max_stress_max:  # TODO Terrible variable name

            self.penalty_stress = self._calculate_penalty(self.penalty_stress, self.max_stress_impact_weight,
                                                          self.max_stress_max, 'stress')

        if self.max_stress_anvil > self.max_stress_max:  # TODO Terrible variable name

            self.penalty_stress = self._calculate_penalty(self.penalty_stress, self.max_stress_anvil,
                                                          self.max_stress_max,
                                                          'stress')

        logging.debug("Particle: Total penalty (impact weight and anvil) for stress is: %0.2f", self.penalty_stress)

        self.penalty_v = 0

        if self.peak_pile_head_velocity > self.v_peak_min:
            self.penalty_v = self._calculate_penalty(self.penalty_v, self.peak_pile_head_velocity, self.v_peak_min,
                                                     'velocity')

        logging.debug("Particle: Penalty for peak pile head velocity is: %0.2f", self.penalty_v)

        if self.efficiency < self.efficiency_min:

            self.penalty_efficiency = self._calculate_penalty(mask, self.efficiency, self.efficiency_min, 'efficiency')

        else:

            self.penalty_efficiency = 0

        logging.debug("Particle: Penalty for efficiency is: %0.2f", self.penalty_efficiency)

        self.sum_penalties = self.penalty_mass + self.penalty_stress + self.penalty_efficiency + self.penalty_v

        logging.debug("Particle: Total penalty is: %0.2f", self.sum_penalties)
        