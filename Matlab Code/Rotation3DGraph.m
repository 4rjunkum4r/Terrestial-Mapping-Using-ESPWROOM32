% ThingSpeak Channel ID and Read API Key
channelID = 2332155;
readAPIKey = 'FIZT5F9N257PMZBG';

% Number of data points to fetch
numPoints = 20;

% Fetch data from ThingSpeak
data = thingSpeakRead(channelID, 'Fields', [4, 5, 6], 'NumPoints', numPoints, 'ReadKey', readAPIKey);

% Extract data into separate arrays
xRotation = data(1:numPoints, 1);
yRotation = data(1:numPoints, 2);
zRotation = data(1:numPoints, 3);

% Create a 3D plot
figure;
plot3(xRotation, yRotation, zRotation);
title('MPU6050 3D Rotation Visualization');
xlabel('X Rotation (degrees)');
ylabel('Y Rotation (degrees)');
zlabel('Z Rotation (degrees)');
grid on;

% Customize the plot as needed (e.g., add labels, adjust colors, etc.)