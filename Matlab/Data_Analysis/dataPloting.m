function dataPloting(paramters,plot_rows,n_figures)
%%
[target_values,eta,iw_mass,iw_rad,iw_height,anvil_mass,...
    anvil_rad,anvil_height]=getParameters(paramters,0)
anvil_parameters=[anvil_rad anvil_height];
iw_parameters=[iw_rad iw_height];
[shapePlot,energy_table]= hammerPlot(anvil_parameters,iw_parameters,target_values,eta,plot_rows,n_figures,'General');
%% Energy plotting
energy_table
 index=1;
for k=1:n_figures
    figure('Name','Energy plot','Position',get(0, 'Screensize'))
    hold on
   
        for s=1:2:plot_rows*2
        subplot(plot_rows,2,s)
        plotEnergies(energy_table(index,2),energy_table(index,1),'anvil')
        title("Anvil energy plot for particle "+int2str(energy_table(index,2))+" and step: " +num2str(energy_table(index,1)))
        hold off
        subplot(plot_rows,2,s+1)
        plotEnergies(energy_table(index,2),energy_table(index,1),'impact_weight')
        title("Impact weight energy plot for particle "+int2str(energy_table(index,2))+" and step: " +num2str(energy_table(index,1)))
        hold off
        index= index+1;
        end
        energyplotsObject(k,1)=gcf;
   
end

%%
%% Plot results
figure('Name','Efficiency vs Weight mass','Position',get(0, 'Screensize'))
axis tight;
yyaxis left
subplot(3,1,1)
ylabel('Target values');
grid on;hold on;
scatter(iw_mass,target_values,15,'b','+')
title('Target values vs iw mass')
set(gca,'xTick',[0:40:140,150:20:240,250:50:max(iw_mass)]);
yyaxis right
scatter(iw_mass,eta,10)
legend('iw weight','Efficiency','Best')
hold off


subplot(3,1,2)
yyaxis left
ylabel('Target values');
grid on;hold on;
scatter(anvil_mass,target_values,10,'filled','d')
title('Target values vs anvil mass')
set(gca,'xTick',[0:40:140,150:20:240,250:50:max(iw_mass)]);
yyaxis right
scatter(anvil_mass,eta,10)
legend('Anvil Mass','Efficiency','Location','Best')
hold off


subplot(3,1,3)
scatter(target_values,eta,15)
ylabel('Efficiency');
legend('target values','Location','Best')
title('Efficiency vs Target Values')
set(gca,'xTick',[0:40:140,150:20:240,250:50:max(iw_mass)]);
grid on
hold off;

optimizationPlot=gcf;


%% Best Results plot    
[target_values_b,eta_b,iw_mass_b,iw_rad_b,iw_height_b,anvil_mass_b,...
    anvil_rad_b,anvil_height_b]=getParameters(paramters,1)
anvil_parameters_b=[anvil_rad_b anvil_height_b];
iw_parameters_b=[iw_rad_b iw_height_b];
[shapePlot_b,mask]= hammerPlot(anvil_parameters_b,iw_parameters_b,target_values_b,eta_b,plot_rows,n_figures,'Best');

%% Plot results
figure('Name','Best Efficiency vs Weight mass','Position',get(0, 'Screensize'))
axis tight;

subplot(3,1,1)

scatter(iw_mass_b,eta_b,15,'b','+')
hold on;grid on
scatter(target_values_b,eta_b,10,'filled','d')
legend('iw mass','target values','Location','Best')
title('Efficiency vs iw mass & target values')
ylabel('Efficiency');
set(gca,'xTick',[0:20:190,200:30:450,500:100:max(iw_mass_b)]);

subplot(3,1,2)

scatter(iw_height_b,eta_b,15,'filled')
title('Efficiency vs Anvil height')
ylabel('Efficiency');
lgd1_e=legend('Impact weight height','Location','Best')
hAx(1)=gca;
hAx(2)=axes('Position',hAx(1).Position,'XAxisLocation','top','YAxisLocation','right','color','none','title','none');
hold(hAx(2),'on')
scatter(hAx(2),anvil_height_b,eta_b,10,'filled','d','r')
lgd1_e2=legend('Anvil height','Location','Best')
grid on

subplot(3,1,3)
scatter(iw_height_b,target_values_b,15,'filled')
title('Target values vs iw height')
ylabel('Target values');
lgd1= legend('Impact weight height','Location','Best')
hAxx(1)=gca;
hAxx(2)=axes('Position',hAxx(1).Position,'XAxisLocation','top','YAxisLocation','right','color','none');
hold(hAxx(2),'on')
scatter(hAxx(2),anvil_height_b,target_values_b,10,'filled','d','r')
lgd2=legend('Anvil height','position',lgd1.Position+[-0.0 -0.0255 0.0 0])
meshgrid(hAxx(2))
%lgd2 = legend('location','Best');
%Legend=cell(2,1)%  two positions Legend{2}=' FFF data 2';legend(Legend);
bestResultplot=gcf;

grid on
hold off;

%% Plot the best one

min_tv= min(target_values_b)
best_row= find(target_values_b == min_tv);
for p=1:length(best_row)
eta_f = eta_b(p);
iw_parameters_f = [iw_rad_b(p) iw_height_b(p)];
anvil_rad_f = [anvil_rad_b(p) anvil_height_b(p)];
[a_r1_f,a_r2_f,a_h_f]= setParameters(anvil_rad_f);
[iw_r1_f,iw_r2_f,iw_h_f]= setParameters(iw_parameters_f);
figure('Name','Beat hammer over all','Position',get(0, 'Screensize'))
sketch(a_r1_f,a_r2_f,a_h_f,...
       iw_r1_f,iw_r2_f,iw_h_f,...
       min_tv,eta_f,0,0);
   
 bestHamerOverall(p)= gcf 
end

%% Save plots in the same working directory! 
saveas(bestResultplot,'Bestresult_plot.png')

saveas(optimizationPlot,'OptimizationPlot.png')

for i=1:length(shapePlot)
  saveas(shapePlot(i),"hammerDesign"+int2str(i)+"_plot.png") 
end
for i=1:length(shapePlot_b)
    saveas(shapePlot(i),"best_hammerDesign"+int2str(i)+"_plot.png") 
end

for n=1:length(energyplotsObject)
    saveas(energyplotsObject(n),"Energy plot"+int2str(n)+"_plot.png") 
end


for p=1:length(bestHamerOverall)
 saveas(bestHamerOverall(p),"Best_hammer_overall_"+int2str(p)+".png")   
end    

