% Extract data from figures
%clear all
fig = openfig("systemTestFigure5.fig", "invisible");

% Get data objects which contain a YData property
dataObjs = findobj(fig,'-property','YData');

% Get each signal from data objects
for n = 1:length(dataObjs)
    x(:,n) = dataObjs(n).XData;
    y(:,n) = dataObjs(n).YData;
end

%% Extract and plot
clear fig dataObjs
figure

% Ch1
x1 = x(:,3);
y1 = y(:,3);
ax1 = subplot(3, 1, 1);
p1 = plot(x1, y1);
title('Raw EMG - Ch 1')
ylabel('10-bit ADC Value')
xlabel('Time (s)')
ylim(ax1, [0, 1023])
set(p1, 'LineWidth', 0.5, 'Color', 'g')
set(ax1, 'LineWidth', 1)

% Ch2
x2 = x(:,2);
y2 = y(:,2);
ax2 = subplot(3, 1, 2);
p2 = plot(x2, y2);
title('Raw EMG - Ch 2')
ylabel('10-bit ADC Value')
xlabel('Time (s)')
ylim(ax2, [0, 1023])
set(p2, 'LineWidth', 0.8, 'Color', 'c')
set(ax2, 'LineWidth', 1)


% Control Signal
x3 = x(:,1);
y3 = y(:,1);
ax3 = subplot(3, 1, 3);
p3 = plot(x3, y3);
title('Control Signal')
ylabel('Control Velocity')
xlabel('Time (s)')
ylim(ax3, [-1, 1])
set(p3, 'LineWidth', 0.8, 'Color', 'm')
set(ax3, 'LineWidth', 1)



