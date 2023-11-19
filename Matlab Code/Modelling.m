% Set up ThingSpeak parameters
channelID = 2332155;
readAPIKey = 'FIZT5F9N257PMZBG';

% Define number of data points to plot
numPoints = 50;

% Initialize figure and plot
figure;
h = plot3(zeros(1, numPoints), zeros(1, numPoints), zeros(1, numPoints));
title('Real-time 3D Surface Plot');
xlabel('X-axis');
ylabel('Y-axis');
zlabel('Z-axis');
grid on;

% Real-time update loop
while ishandle(h)
    % Read data from ThingSpeak channel
    % data = thingSpeakRead(channelID, 'ReadKey', readAPIKey, 'NumPoints', numPoints);
    % 
    % % Extract relevant data (adjust based on your channel field names)
    % xData = data.Field1;
    % yData = data.Field2;
    % zData = data.Field3;


    data = thingSpeakRead(channelID, 'Fields', [4, 5, 6], 'NumPoints', 1, 'ReadKey', readAPIKey);

    % Extract data into separate variables
    xData = data(1, 1);
    yData = data(1, 2);
    zData = data(1, 3);

    % Update the plot
    set(h, 'XData', xData, 'YData', yData, 'ZData', zData);

    % Pause to control the update rate (adjust as needed)
    pause(5);
end
