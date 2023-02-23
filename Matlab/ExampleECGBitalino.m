%% Example of Measuring Heart Rate from Acquired ECG Signals
% This example demonstrates the use of a Bitalino to acquire data into 
% MATLAB and to process the raw ADC data to measure heart rate and to
% visualize some ECG measurements.

%% Requirements
% In order to execute the example you will need:
%
% # a Bitalino with the ECG sensor connected to the A2 channel
% # MATLAB
% # Instrument Control Toolbox
% # Signal Processing Toolbox

%% Connect to a Bitalino Object and acquire 20 seconds of data

% Create the object
b = Bitalino('BITalino-95-5F');
%%
% Start background acquisition
b.startBackground;
% Pause to acquire data for 20 seconds 
pause(10);
% Read the data from the device
data = b.read;
% Stop background acquisition of data
b.stopBackground;
% Clean up the bitalino object
%delete(b)
%%
for c=8 %channel 7:A2, 8:A3
   % if c == 8
    figure(c)
    plot(data(:,c))
    %end
end


%% Plot the Acquired Data
ECG_raw = data(:,8);
load('ECG_raw.mat'); % Comment this line to use live data
figure;
plot(ECG_raw);

%% Process the Data to Make Measurements and Visualize Signals

% Scale the signal per the specifications of the ECG sensor
ECG_adj = ((((ECG_raw./((2.^10)-1))-0.5) .* 3.3)./ 1100) .* 1000;

% Filter the scaled signal using a Savitzky-Golay filter
ECG_data = sgolayfilt(ECG_adj, 7, 41);

t = 1:length(ECG_data);
[~,locs_Rwave] = findpeaks(ECG_data,'MinPeakHeight',0.8,...
                                    'MinPeakDistance',500);

% Remove Edge Wave Data                                
locs_Rwave(locs_Rwave < 150 | locs_Rwave > (length(ECG_data) - 150)) = [];
locs_Qwave = zeros(length(locs_Rwave),1);
locs_Swave = zeros(length(locs_Rwave),1);
locs_Qpre  = zeros(length(locs_Rwave),1);
locs_Spost = zeros(length(locs_Rwave),1);
QRS = zeros(length(locs_Rwave),1);

% Find Q and S waves in the signal
for ii = 1:length(locs_Rwave)
    window = ECG_data((locs_Rwave(ii)-80):(locs_Rwave(ii)+80));
    [d_peaks, locs_peaks] = findpeaks(-window, 'MinPeakDistance',40);
    [d,i] = sort(d_peaks, 'descend');
    locs_Qwave(ii) = locs_peaks(i(1))+(locs_Rwave(ii)-80);
    locs_Swave(ii) = locs_peaks(i(2))+(locs_Rwave(ii)-80);
    [d_QRS, locs_QRS] = findpeaks(window, 'MinPeakDistance', 10);
    [max_d, max_i] = max(d_QRS);
    locs_Q_flat = locs_QRS(max_i-1);
    locs_S_flat = locs_QRS(max_i+1);
    locs_Qpre(ii)  = locs_Q_flat+(locs_Rwave(ii)-80);
    locs_Spost(ii) = locs_S_flat+(locs_Rwave(ii)-80);    
    QRS(ii) = locs_S_flat - locs_Q_flat;
end

% Calculate the heart rate
myqrs = median(QRS);
myheartrate = 60 ./ (median(diff(locs_Rwave)) ./ 1000);

locs_all = [locs_Qwave; locs_Rwave; locs_Swave; locs_Qpre; locs_Spost];
ECG_all  = ECG_data(locs_all);

[d,i] = sort(locs_all);
ECG_sort = ECG_all(i);

%% Visualize the Raw Data and Measured Heart Rate
figure
hold on
plot(t,ECG_data);
plot(locs_Qwave,ECG_data(locs_Qwave),'rs','MarkerFaceColor','g');
plot(locs_Rwave,ECG_data(locs_Rwave),'rv','MarkerFaceColor','r');
plot(locs_Swave,ECG_data(locs_Swave),'rs','MarkerFaceColor','b');
plot(locs_Qpre, ECG_data(locs_Qpre), 'r>','MarkerFaceColor','c');
plot(locs_Spost,ECG_data(locs_Spost),'r<','MarkerFaceColor','m');
grid on
% Adjust the plot to show 8 seconds worth of measurements
ylim([-1 2]);
xlim([0 8000]);
title(sprintf('QRS = %f ms,  Heart Rate = %f / min', myqrs, myheartrate));
xlabel('Samples'); ylabel('Voltage(mV)')
legend('ECG signal','Q-wave','R-wave','S-wave','Q-pre','S-post');
