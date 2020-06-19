function [plotObject,step_particle] = hammerPlot(anvil_parameters,impact_weight_parameters,tv,eta,n_plots,n_figures,best)

step_particle=int16.empty(0,2);
figure_name=best+" Hammer shape"
for i= 1:n_figures
    figure('Name',figure_name,'Position',get(0, 'Screensize'))
    plotObject(i,1)=gcf;
   
   for j= 1:n_plots
    s=randi([1,30]);
    p=randi([1,15]);
    if best ~= "Best"
        row= p*s
        
    else
        row =s,p=0;
    end
    step_particle=[step_particle;s p];
    length(step_particle)
    ap_step= anvil_parameters(row,:);
    iwp_step= impact_weight_parameters(row,:);
    tv_step= tv(row);
    eta_step=eta(row);
    [a_r1,a_r2,a_h]= setParameters(ap_step);
    [p_r1,p_r2,p_h]= setParameters(iwp_step);
    
    subplot(n_plots,1,j)
    sketch(a_r1,a_r2,a_h,p_r1,p_r2,p_h,tv_step,eta_step,p,s)
    
     
   end
 
 
end


 
end