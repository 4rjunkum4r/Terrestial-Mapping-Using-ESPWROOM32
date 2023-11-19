% ThingSpeak Channel ID and Read API Key
channelID = 2332155;
readAPIKey = 'FIZT5F9N257PMZBG';

% Number of data points to fetch
numPoints = 20;

% Fetch data from ThingSpeak
data = thingSpeakRead(channelID, 'Fields', [1, 2, 3], 'NumPoints', numPoints, 'ReadKey', readAPIKey);

% Extract data into separate arrays
xAcceleration = data(1:numPoints, 1);
yAcceleration = data(1:numPoints, 2);
zAcceleration = data(1:numPoints, 3);

% Create a 3D plot
figure;
plot3(xAcceleration, yAcceleration, zAcceleration);
title('MPU6050 3D Acceleration Visualization');
xlabel('X Acceleration (m/s)');
ylabel('Y Acceleration (m/s)');
zlabel('Z Acceleration (m/s)');
grid on;