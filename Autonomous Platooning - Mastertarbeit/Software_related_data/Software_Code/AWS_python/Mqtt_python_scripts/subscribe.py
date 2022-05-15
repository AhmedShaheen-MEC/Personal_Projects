#################################################################################
#                                                                               # 
#  subscribe.py - provide remotr control funcionality                           # 
#                                                                               # 
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

# Import packages
import time as t
import json
import AWSIoTPythonSDK.MQTTLib as AWSIoTPyMQTT
import re
import os

# Define ENDPOINT, CLIENT_ID, PATH_TO_CERT, PATH_TO_KEY, PATH_TO_ROOT, MESSAGE, TOPIC, and RANGE
ENDPOINT = "a1zidheuopaxeb-ats.iot.us-west-2.amazonaws.com"
CLIENT_ID = "PC"
PATH_TO_CERT = "aa2364537e-certificate.pem.crt"
PATH_TO_KEY = "aa2364537e-private.pem.key"
PATH_TO_ROOT = "root-CA.crt"
SECURED_PORT = 8883
# Control options over the platoon
status_dict = {"START_LEADER_ONLY": 0,
               "STOP": 1,
               "CACC_START": 2,
               "ACC": 3,
               "START_TIMEOUT": 4,
               "RESTART_DELAY": 5,
               "RESTART_IMMEDIATE": 6}
print("Welcome to platoon remote controller")
print("Available commands are:\n1. START_LEADER_ONLY\n2. Stop\n3. CACC_START\n4. ACC")
print("5. START_TIMEOUT\n6. RESTART_DELAY\n7. RESTART_IMMEDIATE\n")
# Adjust this message according to user input:
cmd = input("Please enter a command to be sent from the above options: ")
print("\nYour selected action command is", cmd)
CMD = {"cmd": status_dict[cmd]}
# We send our commands via this MQTT topic:
TOPIC = "esp32/pub"

CSV_HEADER = "Platoon Member, Time stamp, Velocity, Displacement, Acceleration, Target Velocity, Target Displacement, Target Acceleration\n"

# Received data will be handled in this function
try:
    os.remove("platoon_logged_data.csv")
except:
    print("\nNo previous data were found...!")

def custom_callback(client, userdata, message):

    with open("platoon_logged_data.csv", "a") as pData:
        pData.write(str(message.payload))
        pData.write("\n")

# Define Client specifications


myAWSIoTMQTTClient = AWSIoTPyMQTT.AWSIoTMQTTClient(CLIENT_ID)
myAWSIoTMQTTClient.configureEndpoint(ENDPOINT, SECURED_PORT)
myAWSIoTMQTTClient.configureCredentials(PATH_TO_ROOT, PATH_TO_KEY, PATH_TO_CERT)
myAWSIoTMQTTClient.subscribe("esp32/pub", 1, custom_callback)
myAWSIoTMQTTClient.connect()
print('\nBegin Publish')

# Send the starting message to the platoon:
myAWSIoTMQTTClient.publish("esp32/sub", json.dumps(CMD), 1)

print("\nPlatoon is currently running...")
print("please Press one of the following:")
print("     1. to make changes according to the above command list")
print("     Q. to quit python...")
while True:
    if input() == "1":
        _cmd = {"cmd": status_dict[input("Please enter you action command\n")]}
        myAWSIoTMQTTClient.publish("esp32/sub", json.dumps(_cmd), 1)
    elif input() == "Q" or "q":
        print("Analyze the received data")
        try:
            with open("platoon_logged_data.csv", "r") as dLogged:
                leader = open("leader_logged_data.csv", "a")
                leader.write(CSV_HEADER)
                vOne = open("vOne_logged_data.csv", "a")
                vOne.write(CSV_HEADER)
                vTwo = open("vTwo_logged_data.csv", "a")
                vTwo.write(CSV_HEADER)
                lines = dLogged.readlines()
                for line in lines:
                    if line.startswith("b'Leader"):
                        data = line.split("'")
                        data = data[1]
                        leader.write(data + "\n")
                    elif line.startswith("b'VOne"):
                        data = line.split("'")
                        data = data[1]
                        vOne.write(data + "\n")
                    elif line.startswith("b'VTwo"):
                        data = line.split("'")
                        data = data[1]
                        vTwo.write(data + "\n")
        except:
            print("No file found to analyze!, quiting...")
        print("\nDone...")
        myAWSIoTMQTTClient.disconnect()
        quit()
