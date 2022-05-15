%% 
%
%  generate_vel_profile.m - generate PWM values for leader vehicle 
%                     @platoon/include/platoon_leader_velocity_trajectory.h.
%  
%  
%  Copyright (C) 2021  Institute of Communication Networks (ComNets), 
%                       Hamburg University of Technology (TUHH)
%             (C) 2021  Ahmed Shaheen
%   
%   This program is free software: you can redistribute it and/or modify
%   it under the terms of the GNU General Public License as published by
%   the Free Software Foundation, either version 3 of the License, or
%   (at your option) any later version.
%   
%   This program is distributed in the hope that it will be useful,
%   but WITHOUT ANY WARRANTY; without even the implied warranty of
%   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%   GNU General Public License for more details.
%   
%   You should have received a copy of the GNU General Public License
%   along with this program.  If not, see <https://www.gnu.org/licenses/>.
%%
% Prepare workspace:
cd 'E:\Mechatronics_master\Third semester\MA\Software_related_data\Software_Code\Matlab\Test'
clc
clear all
close all
%% Convert Velocity profile To PWM value. 
% Import profile data...

load('Leader_vel_profile.mat')
M_S = estimatedVelocityProfile_MPS;

MAX_LINEAR_VELOCITY = 28.8

PWM = (M_S(1:680)/MAX_LINEAR_VELOCITY)*100.0;
plot(PWM)
writematrix(round(PWM,2)','leader_vel_profile.csv')

%% Modify platoonSDK.h file.
system ('python profile_parser.py'); 
    
 
