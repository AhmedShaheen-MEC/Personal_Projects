
load('LeaderVehicle_Trajectory_values.mat')
time_ms = 1:1:26
relative_velocity = gradient (d_traj (:)) ./ gradient (time_ms (:))
relative_acc =  gradient (relative_velocity (:)) ./ gradient (time_ms (:))

figure('Name','Assumed Readings','Position',get(0, 'Screensize'))

subplot(3,1,1) 
hold on
ylabel('Relative distance (cm)');
xlabel('Time elapsed (ms)');
grid on 
title('Spacing distance vs elapsed time')
plot(time_ms,d_traj)
hold off

subplot(3,1,2) 
hold on
ylabel('Relative velcity (cm/s)');
xlabel('Time elapsed (ms)');
grid on 
title('Spacing error rate vs elapsed time')
plot(time_ms, relative_velocity)
hold off

subplot(3,1,3) 
hold on
ylabel('Relative acceleration (cm/s)');
xlabel('Time elapsed (ms)');
grid on 
title('Relative acceleration vs elapsed time')
plot(time_ms, relative_acc)
hold off