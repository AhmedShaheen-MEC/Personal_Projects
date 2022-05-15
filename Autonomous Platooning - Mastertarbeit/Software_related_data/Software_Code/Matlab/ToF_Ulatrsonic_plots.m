%% 
%  @Author: Ahmed Shaheen
%  @file: ToF_Ulatrsonic_plots.m
%  @Breif: Compare between ToF and US sensors recorded data.
%  
%  Copyright (C) 2021  Institute of Communication Networks (ComNets), 
%                       Hamburg University of Technology (TUHH)
%             (C) 2021  <author1>, <author2>
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
%% Clear workspace
close all
clc 
clear all 

%% Set working directory
cd 'E:\Mechatronics_master\Third semester\MA\Software_related_data\Software_Code\Matlab'

%% Import data
% Read data tables:
ulatrsonic_samples = "Ultrasonic.xlsx";
tof_samples = "ToF.xlsx";
latency_comparison = "Latency comparison.xlsx";

us_file = readtable(ulatrsonic_samples);
tof_tile = readtable(tof_samples);
lat_file = readtable(latency_comparison);


%% Prapre plotting figure
figure('Name','ToF vs Us','Position',get(0, 'Screensize'))
% Ultrasonic
subplot(2,1,1) 
hold on
ylabel('Distance (mm)');
xlabel('Accumulated time (ms)');
xticks(0:15:1140)
xtickangle(45)
xlim([0 1060])
ylim([70 95])
grid on 
title('(A) Ultrasonice: 1000 samples, total time: 1045.716 ms  , average: 87.3395 (mm), actual distance:86 measured for the Ultrasonice tip')
plot(us_file.timeAcc_ms_, us_file.Distance_mm_)
hold off

% ToF
subplot(2,1,2) 
hold on
ylabel('Distance (mm)');
xlabel('Accumulated time (ms)');
xticks(0:500:23500)
xtickangle(45)
xlim([0 23500])
grid on 
title('(B) ToF: 1000 samples, total time: 22936.81 ms , average (mm): 83.604   , actual distance: ~= 86 mm')
plot(tof_tile.timeAcc_ms_, tof_tile.Distance_mm_)
hold off
comparisonPlot=gcf

%% Latency combined
figure('Name','Update rate comparison', 'position' ,get(0, 'Screensize'))
subplot(2,1,1) 
hold on
ylabel('Distance (mm)');
xlabel('Accumulated time (ms)');
xticks(0:20:1500)
xtickangle(90)
xlim([0 1500])
grid on 
title('(A): Sampling with 1 ms time interval, total time is 1500 ms')
plot(lat_file.Time, lat_file.us_dist_mm)
plot(lat_file.Time, lat_file.tof_mm)
legend({'Ultrasonics sampels', 'ToF samples'})
hold off

% ToF
subplot(2,1,2) 
hold on
ylabel('Distance (mm)');
xlabel('Accumulated time (ms)');
xticks(0:10:1000)
xtickangle(90)
xlim([0 1000])
grid on 
title('(B): ToF & Ultrasonice readings over 1000 samples')
plot((1:1:1000), tof_tile.Distance_mm_)
plot((1:1:1000), us_file.Distance_mm_)
legend({'ToF samples','Ultrasonics sampels'})
hold off
performancePlot=gcf
%% Save plots

cd 'E:\Mechatronics_master\Third semester\MA\Docs'


delete "Distance_measurement_comparison_noise_and_latency.png"
saveas(comparisonPlot,'Distance_measurement_comparison_noise_and_latency.png')


delete 'Noise clear comparison.png'
saveas(performancePlot,'Noise clear comparison.png')

