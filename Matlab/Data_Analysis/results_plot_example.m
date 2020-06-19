%%Set up Path
clear all
close all
clc
path= " "
cd(path)
analysis_path= path+"\analysis"
p_4_6_path=analysis_path+"\4_6_parameterization" 
addpath(path)
addpath(analysis_path)
addpath(p_4_6_path)
%% Hammer plot settings:
n_sub_plot= 3;
n_figures=2;
dataPloting("Six",n_sub_plot,n_figures)