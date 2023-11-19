% Open a serial connection to the ESP32
port = 'COM4'; % Replace 'COMX' with the appropriate COM port
s = serialport(port, 115200);
configureTerminator(s, "LF");

% Initialize variables for plotting
figure;
hold on;
grid on;
xlabel('Time');
ylabel('Acceleration');
title('Real-time Acceleration Data from MPU6050');

% Initialize a counter for time
time = 0;

% Read and plot real-time data
while ishandle(gcf) % Continue until the figure is closed
    data = read(s, 1, 'double');
    
    if ~isempty(data)
        % Extract data
        acceleration = data(1:3);
        rotation = data(4:6);
        
        % Plot data
        plot3(time, acceleration(1), acceleration(2), 'o');
        drawnow;
        
        % Increment time
        time = time + 1;
    end
end

% Close the serial connection
closePort(s);
