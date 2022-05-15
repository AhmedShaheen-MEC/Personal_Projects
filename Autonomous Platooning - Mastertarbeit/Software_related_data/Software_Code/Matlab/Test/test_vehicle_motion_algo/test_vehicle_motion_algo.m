%% 
%
%  test_vehicle_motion_algo.m - analysis and validation for own
%                                      vehicle calculations.
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
%Clear everything
clc
clear all
close all 
cd 'E:\Mechatronics_master\Third semester\MA\Software_related_data\Software_Code\Matlab\Test'

%% Test Bench preparation:
% We start by assuming Velocity profile for the moving vehicle. 
% MPS -> meter per second.
% Max linear velocity is 28 m/s. 
startCorrection = 0:0.2:1.115;
test_TotalTrackLength_CM = 680
t = 1:1:test_TotalTrackLength_CM;
test_ShiftValue = 2.1;
velProfile = 6*test_ShiftValue + sin(0.08*t) + 1*sin(0.05*t);
estimatedVelocityProfile_MPS = [startCorrection velProfile velProfile([52:end]) velProfile([52:end]) velProfile([52:end])];
test_ExpTime_MS = 2000; % 10 MCU intervals.

save('../Test/Leader_vel_profile.mat','estimatedVelocityProfile_MPS')
%% Plot first estimation:
% Time vector:
time_ms = 1:1:test_ExpTime_MS; 
estimatedVelocityProfile_MPS = estimatedVelocityProfile_MPS([1:length(time_ms)]);
dispProfile  = cumtrapz((time_ms/1000), estimatedVelocityProfile_MPS);
accProfile = gradient(estimatedVelocityProfile_MPS(:))./ gradient(time_ms (:));
accProfile = accProfile';
figure('Name','Estimated Data vs Sensor Data with error ingection','Position',get(0, 'Screensize'))
plot(time_ms, estimatedVelocityProfile_MPS) 
hold on
title("Estimated velocity profile and displacement for 10 MCU cycles total displacement: "+ num2str(dispProfile(end)) +" m")
subtitle("Average Velocity: "+num2str(mean(estimatedVelocityProfile_MPS))+ " m/s, Average Acceleration: "+num2str(mean(accProfile))+" m/s^2")
xlim([0 2000])
yyaxis left
ylabel('Velocity (m/s)/ Acc (m/s^2)');
plot(time_ms, accProfile)
%set(gca,'XTick',[0:5:20 21:200:2000])
xlabel('Time elapsed (ms)');
yyaxis right
ylabel('Displacement (cm)');
plot(time_ms, (dispProfile*100))
legend({'Velocity Profile', 'Acceleration ','Displacement Profile'},'Location','best')
hold off

EstimatedPrfile =gcf 
%% Assumptions:
%
test_SensorMinError = 1.04;
test_SensorMaxError = 1.32;
test_SamplingInterval = 10;
test_CONTROLLER_INTERVAL_MS = 20;
virtua_Displacement = zeros(1 , length(time_ms));
virtua_Velocity = zeros(1 , length(time_ms));
virtua_Acceleration = zeros(1 , length(time_ms));

% Array buffers:
test_MaxBufferSize = 3;

%Random Error ratio generation:
rng(0)
n = length(time_ms);
R = [test_SensorMinError test_SensorMaxError ];
z = rand (n, 1) * range (R) + min (R);
Z = z';
cnt = 1;
innerIndex = 1;
arrayIndex = 1;
arrayIndexAcc = 1;
lastTime_MS = 1;
lastTime_MCU_MS = 1;
velBuffer = zeros(1 , test_MaxBufferSize);
for t = 1:1:length(time_ms)
    %we sample every 10 ms in the HW side. 
    if (t - lastTime_MS) >= test_SamplingInterval
        % Flush arrary data every controller frequency, keep only the last
        % value to connect cycles. 
        
        if arrayIndex == test_MaxBufferSize
            
            arrayIndex = 1;
        else
            arrayIndex = arrayIndex + 1;
        end
        instDisplacement = Z(cnt)* (dispProfile(cnt)- dispProfile(innerIndex));
        velBuffer(arrayIndex) = instDisplacement/ ((t - lastTime_MS)/1000);
        newAcc= (velBuffer(arrayIndex) - virtua_Velocity(innerIndex))/((t - lastTime_MS)/1000);
        virtua_Displacement(cnt) =  instDisplacement + virtua_Displacement(cnt-1);
        lastTime_MS = t;
        innerIndex = innerIndex + test_SamplingInterval;
    
        virtua_Velocity(cnt) = averageValue(velBuffer(arrayIndex), velBuffer);
        virtua_Acceleration(cnt) = averageValue(newAcc, virtua_Acceleration);
    else
        try
            virtua_Displacement(cnt) = virtua_Displacement((cnt-1));
            virtua_Velocity(cnt) = virtua_Velocity((cnt-1));
            %virtua_Acceleration(cnt) = virtua_Acceleration((cnt-1));
        catch 
            virtua_Displacement(cnt) = Z(cnt)* dispProfile(cnt);
        end
    end
    cnt = cnt + 1;
end
    
%% Save test data:

%% Plot final results:
figure('Name','Estimated Data vs Sensor Data with error ingection','Position',get(0, 'Screensize'))
subplot(3,1,1) 
hold on
ylabel('Displacement profile analysis (cm)');
xlabel('Time elapsed (ms)');
grid on 
title('Estimated and sensor distance measurements with error ingection')
plot(time_ms,dispProfile*100)
plot(time_ms,virtua_Displacement*100)
hold on
legend({'Estimated Profile','Sensor Data Profile'},'Location','best')
hold off

subplot(3,1,2) 
hold on
ylabel('Velocity profile analysis (m/s)');
xlabel('Time elapsed (ms)');
grid on 
title('Estimated and sensor  velocity measurements with error ingection')

plot(time_ms, estimatedVelocityProfile_MPS)
plot(time_ms, virtua_Velocity)
legend({'Estimated Profile','Sensor Data Profile'},'Location','best')
hold off

subplot(3,1,3) 
hold on
ylabel('Acceleration profile analysis (m/s^2)');
xlabel('Time elapsed (ms)');
grid on 
title('Estimated and sensor  acceleration measurements with error ingection')
plot(time_ms, accProfile, 'LineWidth', 0.5)
% plot(time_ms,virtua_Acceleration, 'LineWidth', 0.001)

plot(find(virtua_Acceleration), virtua_Acceleration(find(virtua_Acceleration)), 'Color', 'Green')

%set(gca,'ytick',[-200:80:-40,-39:20:39,40:80:200]);
legend({'Estimated Profile','Sensor Data Profile'},'Location','best')
hold off

EstimatedVsSensorData=gcf

%% Save Plots data:

cd 'E:\Mechatronics_master\Third semester\MA\Docs'
delete EstimatedPrfile.png
saveas(EstimatedPrfile,'EstimatedPrfile.png')

delete "EstimatedVsSensorData_Sampling_Interval_" +num2str(test_SamplingInterval)+"_Buffer_"+num2str(test_MaxBufferSize)+".png"
saveas(EstimatedVsSensorData,"EstimatedVsSensorData_Sampling_Interval_" +num2str(test_SamplingInterval)+"_Buffer_"+num2str(test_MaxBufferSize)+".png")
