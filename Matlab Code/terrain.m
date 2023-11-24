
% ThingSpeak Channel ID and Read API Key
channelID = 2332155;
readAPIKey = 'FIZT5F9N257PMZBG';

% Number of data points to fetch
numPoints = 100;

% Fetch data from ThingSpeak
data = thingSpeakRead(channelID, 'Fields', [1, 2, 3, 4, 5, 6], 'NumPoints', numPoints, 'ReadKey', readAPIKey);

% Extract data into separate arrays
xAcceleration = data(1:numPoints, 1);
yAcceleration = data(1:numPoints, 2);
zAcceleration = data(1:numPoints, 3);
xRotation = data(1:numPoints, 4);
yRotation = data(1:numPoints, 5);
zRotation = data(1:numPoints, 6);

% Creating a meshgrid
[X, Y] = meshgrid(xRotation, yRotation); 
Z = sin((X.^2 + Y.^2));

% Create a new figure
figure;

% Set the position and size of the first plot (3D Acceleration Visualization)
ax1 = axes('Position',[0.1 0.55 0.35 0.35]);
plot3(ax1, xAcceleration, yAcceleration, zAcceleration);
title(ax1, 'MPU6050 3D Acceleration Visualization');
xlabel(ax1, 'X Acceleration (m/s)');
ylabel(ax1, 'Y Acceleration (m/s)');
zlabel(ax1, 'Z Acceleration (m/s)');
grid(ax1, 'on');

% Set the position and size of the second plot (3D Rotation Visualization)
ax2 = axes('Position',[0.55 0.55 0.35 0.35]);
plot3(ax2, xRotation, yRotation, zRotation);
title(ax2, 'MPU6050 3D Rotation Visualization');
xlabel(ax2, 'X Rotation (degrees)');
ylabel(ax2, 'Y Rotation (degrees)');
zlabel(ax2, 'Z Rotation (degrees)');
grid(ax2, 'on');

% Set the position and size of the third plot (Terrestrial Terrain)
ax3 = axes('Position',[0.25 0.1 0.5 0.35]);
surf(ax3, X, Y, Z);
title(ax3, 'Terrestrial Terrain');
xlabel(ax3, 'X-axis');
ylabel(ax3, 'Y-axis');
zlabel(ax3, 'Z-axis');
shading(ax3, 'interp');
