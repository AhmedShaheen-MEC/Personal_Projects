function [target_values,eta,iw_mass,iw_rad,iw_height,anvil_mass,anvil_rad,anvil_height]=getParameters(paramters,indicator)
iw_height=[];
anvil_height=[];
iw_mass=[];
anvil_mass=[];
eta=[];
target_values=[];
anvil_rad=double.empty(0,2);
iw_rad=double.empty(0,2);


% Import all log files:
step = 0;
figure('Name','Performance of step','Position',get(0, 'Screensize'))
do=true 
while (do)
    if indicator ==0
    hold on
    log_file= "log_file_particle_"+int2str(step)+".csv";
    try
        file = readtable(log_file);
        indv_tv=file.target_value;
  
        if step<5 
            subplot(3,1,1) 
            ylabel('Target values');
            xlabel('Number of Steps');
            legend('Location','eastoutside','NumColumns',3)
            hold on
        elseif step<10
            subplot(3,1,2)
            ylabel('Target values');
            xlabel('Number of Steps');
            legend('Location','eastoutside','NumColumns',3)
            hold on
         else
            subplot(3,1,3)
            ylabel('Target values');
            xlabel('Number of Steps');
            legend('Location','eastoutside','NumColumns',3)
            hold on
        end   
      plot(1:1:length(indv_tv),indv_tv,'DisplayName',"Paticle "+int2str(step))  
      step = step +1; 
     grid on
    hold off
    performancePlot=gcf
    saveas(performancePlot,'PerformancePlot.png')
    
    catch
        display('Finished')
        break; 
    end   
   
    else
        close
        file =  readtable('Best_results_file.csv');
        do=false;
    end


if paramters == "Six"
             iw_height=     [iw_height;file.p3];
             anvil_height=  [anvil_height;file.p6];
             anvil_rad=     [anvil_rad;[file.p4 file.p5]];
             iw_rad=        [iw_rad;[file.p1 file.p2]];
            else
             iw_height=     [iw_height;file.p2];
             anvil_height=  [anvil_height;file.p4];
             anvil_rad=     [anvil_rad;file.p3];
             iw_rad=        [iw_rad;file.p1]
end  

    iw_mass=        [iw_mass;file.mass_impact_weight_t_];
    anvil_mass=     [anvil_mass;file.mass_anvil_t_];
    eta=            [eta;file.efficiency];
    target_values=  [target_values;file.target_value];
      
  indicator     
end 
end
 
            