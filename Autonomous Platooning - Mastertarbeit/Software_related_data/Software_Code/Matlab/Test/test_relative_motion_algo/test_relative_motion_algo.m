%% 
%
%  test_relative_motion_algo.m - analysis and validation for preceding
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
%% Test Bench preparation:
test_ReductionRatio = 0.6       % 2.8 m/s ~= 10 km/h
test_MaxLinearSpeed_MS = 28 * test_ReductionRatio
test_TotalTrackLength_MS = 2500;
test_TrackLength_M = 6;
t = 1:1:test_TotalTrackLength_MS;
test_ShiftValue_CM = 4;
estimatedReadings_CM = sin(0.002*t) + sin(0.0009*t) + test_ShiftValue_CM;
% Theoretical estimated dynamics
estimatedReadings_vel_M_S_REL =gradient (estimatedReadings_CM (:)/100) ./ gradient (t (:)/1000);
estimatedReadings_vel_M_S = test_MaxLinearSpeed_MS + estimatedReadings_vel_M_S_REL;
estimatedReadings_acc_M_SS =  gradient (estimatedReadings_vel_M_S_REL (:)) ./ gradient (t (:)/1000);
test_TotalTimeTaken_S = ((test_TrackLength_M)/ mean(estimatedReadings_vel_M_S));


figure('Name','Leader Vehicle spacing distance estimation','Position',get(0, 'Screensize'))
plot(t,estimatedReadings_CM)
hold on 
grid on
plot(t,estimatedReadings_vel_M_S_REL)
plot(t,estimatedReadings_vel_M_S)
plot(t,estimatedReadings_acc_M_SS)
legend({'Estimated Spacing distance (cm)','Estimated Relative Velocity (m/s)','Estimated Velocity (m/s)', 'Estimated Acceleration (m/s^2)'},'Location','eastoutside')
title("Total track length of 6 meters with spacing error varies from (" + num2str(min(estimatedReadings_CM))+"-"+num2str(max(estimatedReadings_CM))+") cm")
subtitle("Static spacing shift: " +num2str(test_ShiftValue_CM) +"cm, Assumed average Linear velocity of "+ num2str(test_MaxLinearSpeed_MS)+"m/s total time taken: "+ num2str(test_TotalTimeTaken_S)+" s")
%save('Leader Vehicle spacing error estimation.mat','estimatedReadings')
EstimatedVsMeasured=gcf;

%% Assumptions:
%
% Curret model Max linear speed is 28.8 m/s
% assume that Leader is moving with 0.6*MaxLinearSpeed
test_ALLAWED_TOLERANCE_CM = 0.3;       % allow 5 mm error 
test_SamplingInterval = 10;
virtualReadings_CM = zeros(1 , length(estimatedReadings_CM));
rng(0)
n = length(estimatedReadings_CM);
R = [1.04 1.1];
z = rand (n, 1) * range (R) + min (R);
Z = z';
cnt = 1;
lastTime_MS = 0;
ignore = 0;
for i = 1:1:test_TotalTrackLength_MS
    %we sample every 10 ms in the HW side. 
    
    if (i - lastTime_MS) >= test_SamplingInterval 
        virtualReadings_CM(cnt) = Z(cnt)* estimatedReadings_CM(cnt);
        lastTime_MS = i;
        if (10*abs(virtualReadings_CM((cnt-1)) - (Z(cnt)* estimatedReadings_CM(cnt))))<=test_ALLAWED_TOLERANCE_CM 
            virtualReadings_CM(cnt) = virtualReadings_CM((cnt-1));
            ignore = ignore +1;
        end 
    else
        try
            virtualReadings_CM(cnt) = virtualReadings_CM((cnt-1));
        catch 
            virtualReadings_CM(cnt) = Z(cnt)* estimatedReadings_CM(cnt);
        end
        
    end
    virtualReadings_CM(cnt)
    cnt = cnt + 1;
end
figure('Name','Position analysis','Position',get(0, 'Screensize'))
subplot(2,1,1) 
hold on 
grid on
plot(t,estimatedReadings_CM)
plot(t,virtualReadings_CM)
normalizedDiviation = virtualReadings_CM./estimatedReadings_CM;
ylabel('Relative distance (cm)');
xlabel('Elapsed Time (ms)');
title("Ideal vs Expected profiles")
subtitle("Allow "+ num2str(test_ALLAWED_TOLERANCE_CM) +" cm error in readings total ignored readings: "+ num2str(ignore))
hold off
subplot(2,1,2)
unity = ones(1 , length(estimatedReadings_CM));
plot(normalizedDiviation)
xlabel('Elapsed Time (ms)');
subtitle("Notmalized plot: normalized standard deviation is: "+ num2str(std(normalizedDiviation))+ " cm, mean:"+ num2str(mean(normalizedDiviation))+" cm")
ylim([0 2.5])
hold on 
grid on
plot (unity)
hold off
ComparisonWithNormalization=gcf

%% Test Variables
%
test_startTime = 0.0;
test_currentTime = 0.0;
test_MaxBufferSize = 3; 
test_AccMaxBufferSize = 20;
test_CONTROLLER_INTERVAL_MS = 20;  

test_DefinedCycles = 100;            % we sample for 100 controller cycles, (i.e., 100 * 20 = 2000 ms => almost full track length)

test_EstimatedFrequncy = 1;
test_TaskEstimatedLatency = 10; 
%% Variables
% start evaluation process:
cycle_start_millis = test_startTime;
current_time_MS = test_startTime;

gSpacingDistance_CM = 0.0;
lastSpacingDistance_CM = 0.0;
dispArray = zeros(1, test_MaxBufferSize);
velocityArray = zeros(1, test_MaxBufferSize);
accelerationArray = zeros(1, test_AccMaxBufferSize);
arrayIndex = 0;
accArrayIndex = 0;


save_PlotData_Dist = zeros(1, (test_DefinedCycles*(test_CONTROLLER_INTERVAL_MS/test_TaskEstimatedLatency)));
save_PlotData_Vel = zeros(1, (test_DefinedCycles*(test_CONTROLLER_INTERVAL_MS/test_TaskEstimatedLatency)));
save_PlotData_Acc = zeros(1, (test_DefinedCycles*(test_CONTROLLER_INTERVAL_MS/test_TaskEstimatedLatency)));

last_average_velocity = 0; last_average_acc = 0;          % static
last_average_time_MS = 1;                                    % static
last_average_distance = 0;                                % static

cnt = 0;
for controller_cycles = 1 : 1 : test_DefinedCycles
   
    for dynamics_update_cycles = 1:1: (test_CONTROLLER_INTERVAL_MS/test_TaskEstimatedLatency)
        duration = 0; accumulated_sampling_time = 0;
        
        cnt = cnt + 1;

        
        current_time_MS = current_time_MS + test_TaskEstimatedLatency;      % We take new sampe every 10 ms in the FreeRTOS system 
        % Flush arrary data every controller frequency, keep only the last
        % value to connect cycles. 
        if (current_time_MS - cycle_start_millis) >= test_CONTROLLER_INTERVAL_MS
            %velocityArray = fillArray(arrayIndex, velocityArray);
            %accelerationArray = fillArray(arrayIndex, accelerationArray);
        end
        
        if arrayIndex == test_MaxBufferSize
            
            arrayIndex = 1;
        else
            arrayIndex = arrayIndex + 1;
        end
        if accArrayIndex == test_AccMaxBufferSize
            
            accArrayIndex = 1;
        else
            accArrayIndex = accArrayIndex + 1;
        end
        
        % Set virtual new distance
        gSpacingDistance_CM = virtualReadings_CM(cnt);
        temp = current_time_MS - last_average_time_MS;
        index = 0;
        accIndex = 0;
        
        % if wrraped arround => take the last one
        if((arrayIndex) - 1) == 0
            index = test_MaxBufferSize;
        else
            index = arrayIndex - 1;
        end
        if((accArrayIndex) - 1) == 0
            accIndex = test_AccMaxBufferSize;
        else
            accIndex = accArrayIndex - 1;
        end
        
        dispArray(arrayIndex) = averageValue(gSpacingDistance_CM, dispArray);
        velocityArray(arrayIndex) = averageValue( (10 *( gSpacingDistance_CM - lastSpacingDistance_CM) / temp), velocityArray);
        accelerationArray(arrayIndex) = averageValue( (( velocityArray(arrayIndex) -  velocityArray(index)) / (temp/1000)), accelerationArray);
        save_PlotData_Dist(cnt) = dispArray(arrayIndex);
        lastSpacingDistance_CM = gSpacingDistance_CM;
        last_average_time_MS = current_time_MS;
        
        
        save_PlotData_Vel(cnt) =  velocityArray(arrayIndex) ;
        save_PlotData_Acc(cnt) = accelerationArray(arrayIndex);
    end
    
    cycle_start_millis = cycle_start_millis + test_CONTROLLER_INTERVAL_MS;

end

%% Save test data:
save('distance.mat','save_PlotData_Dist')
save('vel.mat','save_PlotData_Vel')
save('acc.mat','save_PlotData_Acc')

%% Plot final results:
time_ms = 1:1: test_DefinedCycles*(test_CONTROLLER_INTERVAL_MS/test_TaskEstimatedLatency);

figure('Name','Estimated Data vs Sensor Data with error ingection','Position',get(0, 'Screensize'))
subplot(3,1,1) 
hold on
ylabel('Relative distance (cm)');
xlabel('Time elapsed (ms)');
grid on 
title('Estimated and sensor distance measurements with error ingection')
plot(time_ms,estimatedReadings_CM([1:cnt]))
plot(time_ms,save_PlotData_Dist)
hold on
legend({'Estimated','Sensor data'},'Location','best')
hold off

subplot(3,1,2) 
hold on
ylabel('Relative velcity (m/s)');
xlabel('Time elapsed (ms)');
grid on 
title('Estimated and sensor relative velocity measurements with error ingection')
plot(time_ms, estimatedReadings_vel_M_S_REL([1:cnt])')
plot(time_ms,save_PlotData_Vel)
legend({'Estimated','Sensor data'},'Location','best')
hold off

subplot(3,1,3) 
hold on
ylabel('Relative acceleration (m/s^2)');
xlabel('Time elapsed (ms)');
grid on 
title('Estimated and sensor relative acceleration measurements with error ingection')
plot(time_ms, estimatedReadings_acc_M_SS([1:cnt])')
plot(time_ms,save_PlotData_Acc)
legend({'Estimated','Sensor data'},'Location','best')
hold off

OutputDynamics_Estimated_VS_Measured=gcf

%% Normalized Plots
unity = estimatedReadings_CM([1:cnt])./estimatedReadings_CM([1:cnt]);


figure('Name','Normalized plots','Position',get(0, 'Screensize'))
subplot(3,1,1) 
hold on
ylabel('Normalized Distance');
xlabel('Time elapsed (ms)');
grid on 
normalizedDiviation_Dist = save_PlotData_Dist./estimatedReadings_CM([1:cnt]);
title('Estimated vs sensor distance measurements deviation')
subtitle("standard deviation is: "+ num2str(std(normalizedDiviation_Dist))+ " cm, mean:"+ num2str(mean(normalizedDiviation_Dist))+" cm")
plot(unity)
plot(normalizedDiviation_Dist)
legend({'Estimated','Sensor data'},'Location','best')
hold off

unity = (estimatedReadings_vel_M_S_REL([1:cnt])')./(estimatedReadings_vel_M_S_REL([1:cnt]))';
size(unity)
subplot(3,1,2) 
hold on
ylabel('Normalized relative velocity');
xlabel('Time elapsed (ms)');
grid on 
normalizedDiviation_Vel = (save_PlotData_Vel)./((estimatedReadings_vel_M_S_REL([1:cnt]))');
title('Estimated vs sensor relative velocity measurements deviation')
subtitle("standard deviation is: "+ num2str(std(normalizedDiviation_Vel))+ " m/s, mean:"+ num2str(mean(normalizedDiviation_Vel))+" m/s")
plot(unity)
plot(normalizedDiviation_Vel)
legend({'Estimated','Sensor data'},'Location','best')
hold off

unity = (estimatedReadings_acc_M_SS([1:cnt])')./estimatedReadings_acc_M_SS([1:cnt])';

subplot(3,1,3) 
hold on
ylabel('Normalized relative acceleration');
xlabel('Time elapsed (ms)');
grid on 
normalizedDiviation_Acc = save_PlotData_Acc./estimatedReadings_acc_M_SS([1:cnt])';
title('Estimated vs sensor relative acceleration measurements deviation')
subtitle("standard deviation is: "+ num2str(std(normalizedDiviation_Acc(10:end)))+ " m/s^2, mean:"+ num2str(mean(normalizedDiviation_Acc(10:end)))+" m/s^2")
plot(unity(10:end))
plot(normalizedDiviation_Acc(10:end))
xlim([10 200])
legend({'Estimated','Sensor data'},'Location','best')
hold off

OutputDynamics_Estimated_VS_Measured_Normalized=gcf

%% Save plots

cd 'E:\Mechatronics_master\Third semester\MA\Docs'
delete Estimated.png
saveas(EstimatedVsMeasured,'Estimated.png')

delete ComparisonWithNormalization.png
saveas(ComparisonWithNormalization,'ComparisonWithNormalization.png')

delete "OutputDynamics_Estimated_VS_Measured_Interval_"+num2str(test_TaskEstimatedLatency)+".png"
saveas(OutputDynamics_Estimated_VS_Measured,"OutputDynamics_Estimated_VS_Measured_Interval_"+num2str(test_TaskEstimatedLatency)+".png")

delete "OutputDynamics_Estimated_VS_Measured_Normalized_Interval_"+num2str(test_TaskEstimatedLatency)+".png"
saveas(OutputDynamics_Estimated_VS_Measured_Normalized,"OutputDynamics_Estimated_VS_Measured_Normalized_Interval_"+num2str(test_TaskEstimatedLatency)+".png")
