from parts import AbaqusPartConnector
import logging


class HammerComponent(AbaqusPartConnector):

    X_EDGE_POINT = [0.0]
    Y_FIXED_POINTS = [0.0]

    def generate_component( self, parameters,):

        logging.debug("HammerComponent: Generate component.")

        parameters = [float(p) for p in parameters]

        self._set_parameters(parameters)
        self._set_coordinates()
        self._close_shape()
        self._set_height()

    def _set_parameters(self,parameters):
        
        if len(parameters) < 6:
            self.impactweight_parameters = 2
        else:
            self.impactweight_parameters = 3
        self.iw_parameters = parameters[:self.impactweight_parameters]
        self.a_parameters = parameters[self.impactweight_parameters:]
        self.variable_radius_iw = self.iw_parameters[:-1]
        self.variable_height_iw = [self.iw_parameters[-1]]
        self.variable_radius_a = self.a_parameters[:-1]
        self.variable_height_a = [self.a_parameters[-1]]
        


class Anvil(HammerComponent4):

    def _set_coordinates(self):
        
        if self.impactweight_parameters == 2:
            self.x = [self.X_EDGE_POINT+self.variable_radius_a*2+self.X_EDGE_POINT]
        else:   
            self.x = [self.X_EDGE_POINT+self.variable_radius_a+self.X_EDGE_POINT]
       
        self.y = [self.Y_FIXED_POINTS+self.Y_FIXED_POINTS+ self.variable_height_a*2]


class ImpactWeight(HammerComponent4):

    def _set_coordinates(self):
    
        if self.impactweight_parameters == 2:
            self.x = [self.X_EDGE_POINT+self.variable_radius_iw*2+self.X_EDGE_POINT]
        else:   
            self.x = [self.X_EDGE_POINT+self.variable_radius_iw+self.X_EDGE_POINT]
        self.y = [ self.Y_FIXED_POINTS + self.Y_FIXED_POINTS+ self.variable_height_iw*2]