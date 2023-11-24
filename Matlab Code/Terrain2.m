% ThingSpeak Channel ID and Read API Key
channelID = 2332155;
readAPIKey = 'FIZT5F9N257PMZBG';

% Number of data points to fetch
numPoints = 200;

% Fetch data from ThingSpeak
data = thingSpeakRead(channelID, 'Fields', [1, 2, 3, 4, 5, 6], 'NumPoints', numPoints, 'ReadKey', readAPIKey);

% Extract data into separate arrays
xAcceleration = data(1:numPoints, 1);
yAcceleration = data(1:numPoints, 2);
zAcceleration = data(1:numPoints, 3);
xRotation = data(1:numPoints, 4);
yRotation = data(1:numPoints, 5);
zRotation = data(1:numPoints, 6);

% Create a meshgrid for x and y axes
[x, y] = meshgrid(1:size(data, 1), 1:size(data, 2),1:size(data,3 ));

% Create a 3D surface plot for acceleration data
figure;
surf(x, y, data);
title('Terrain based on Acceleration Data');
xlabel('Time/Points');
ylabel('Axis');
zlabel('Acceleration');

% Create a 3D surface plot for rotation data
figure;
surf(x, y, data);
title('Terrain based on Rotation Data');
xlabel('Time/Points');
ylabel('Axis');
zlabel('Rotation');
