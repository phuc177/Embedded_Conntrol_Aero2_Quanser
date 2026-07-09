%% Serial acquisition from Arduino

clear; clc; close all;

% Adjust COM port and baudrate
port = "COM3";
baudrate = 250000;

s = serialport(port, baudrate);
flush(s);

% Number of samples to acquire
N = 10000;

time = zeros(N,1);
yaw = zeros(N,1);
motorVoltage = zeros(N,1);
yaw_desired = zeros(N,1);

disp("Acquiring data...");

k = 0;

while k < N

    try
        line = readline(s);

        % Expected format:
        % millis,yaw,motorVoltage,yaw_desired
        data = sscanf(line,'%f,%f,%f,%f');

        if numel(data) == 4
            k = k + 1;

            time(k)         = data(1)/1000; % convert ms -> s
            yaw(k)          = data(2);
            motorVoltage(k) = data(3);
            yaw_desired(k)  = data(4);
        end

    catch
        % Ignore malformed lines
    end

end

disp("Acquisition complete.");

%% Close serial port

clear s

% Keep only valid samples
time         = time(1:k);
yaw          = yaw(1:k);
motorVoltage = motorVoltage(1:k);
yaw_desired  = yaw_desired(1:k);

%% Plot output and reference
figure;
plot(time, yaw, 'LineWidth', 1.5);
hold on;
plot(time, yaw_desired, '--', 'LineWidth', 1.5);
grid on;
xlabel('Time (s)');
ylabel('Yaw (rad)');
title('Yaw Tracking');
legend('Yaw','Reference');

%% Plot control input
figure;
plot(time, motorVoltage, 'LineWidth', 1.5);
grid on;
xlabel('Time (s)');
ylabel('Motor 1 Voltage (V)');
title('Control Input');
