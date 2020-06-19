function plotEnergies( iParticle, iStep, component )       

try
    
    fileName = sprintf("internal_energy_%s_job_impact_h_%i_s_%i.csv", component, iParticle, iStep);
    
    internal_energy = csvread(fileName);
    
    fileName = sprintf("kinetic_energy_%s_job_impact_h_%i_s_%i.csv", component, iParticle, iStep);
    
    kinetic_energy = csvread(fileName);

    plot(kinetic_energy(:, 1), kinetic_energy(:, 2))
    
    hold on
    
    plot(internal_energy(:, 1), internal_energy(:, 2))
    
    plot(kinetic_energy(:, 1), internal_energy(:, 2) + kinetic_energy(:, 2), '--')
    
    legend('kinetic', 'internal', 'total')
    
    ylim([0, 3.5e6])
    
catch
    
    text( 0.1, 0.5, 'error: non existing file?')

end

end
