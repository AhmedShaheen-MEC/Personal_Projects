#################################################################################
#                                                                               # 
#  generate_vel_profile.m - generate PWM values for leader vehicle              # 
#                     @platoon/include/platoon_leader_velocity_trajectory.h.    # 
#                                                                               # 
#                                                                               # 
#  Copyright (C) 2021  Institute of Communication Networks (ComNets),           # 
#                       Hamburg University of Technology (TUHH)                 # 
#             (C) 2021  Ahmed Shaheen                                           # 
#                                                                               # 
#   This program is free software: you can redistribute it and/or modify        # 
#   it under the terms of the GNU General Public License as published by        # 
#   the Free Software Foundation, either version 3 of the License, or           # 
#   (at your option) any later version.                                         # 
#                                                                               # 
#   This program is distributed in the hope that it will be useful,             # 
#   but WITHOUT ANY WARRANTY; without even the implied warranty of              # 
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               # 
#   GNU General Public License for more details.                                # 
#                                                                               # 
#   You should have received a copy of the GNU General Public License           # 
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.      # 
#################################################################################

#### Import modules ####
import os

#### Constants ####
PROTECTORS = "#ifndef LEADER__VEL_PROFILE_TREJECTORY_H_"+"\n"+"#define LEADER__VEL_PROFILE_TREJECTORY_H_"
velProfile = open("leader_vel_profile.csv", "r")
vel_data = velProfile.readlines()
PRE_AMPLE = "/**\n* @file: leader_vel_profile.h\n* @function: provide PWM values for Leader Vehicle.\n*\n*/"
INCLUDE = "#include <stdint.h>" 
DEFINE_INDEX = "#define PROFILE_LENGTH "+ str(len(vel_data))+ " // Define profile length"
DEFINE = "static const float leader_velocity_profile[PROFILE_LENGTH] = {" +chr(92)
MIN_PWM_VALUE = 30
#### Generate header files ####
with open("../../Platoon/Platoon/include/platoon_leader_vel_trajectory.h", "w",  newline=None) as platoonSDK:
    platoonSDK.write(PROTECTORS+"\n"+"\n")
    platoonSDK.write(PRE_AMPLE+"\n")
    platoonSDK.write(INCLUDE+"\n"+"\n")
    platoonSDK.write(DEFINE_INDEX+"\n"+"\n"+"\n"+"\n")
    platoonSDK.write(DEFINE+"\n")
    width = 0
    prev_value = 0
    #myString = " "*len(DEFINE)*2
    myString = " "*len(DEFINE)
    for val in vel_data:
        if float(val) < MIN_PWM_VALUE or prev_value == val:
            continue
        myString += str(val).strip('\n')+", "
        width += 1
        prev_value = val
        if width == 5:
            width = 0
            platoonSDK.write(myString + chr(92)+"\n")
            myString = " "*len(DEFINE)
    platoonSDK.write(" "*len(DEFINE)+"};"+"\n")
    platoonSDK.write("#endif /* LEADER__VEL_PROFILE_TREJECTORY_H_ */")
       