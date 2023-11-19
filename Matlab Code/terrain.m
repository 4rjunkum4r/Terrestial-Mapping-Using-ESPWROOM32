% ThingSpeak Channel ID and Read API Key
channelID = 2332155;
readAPIKey = 'FIZT5F9N257PMZBG';

% Number of data points to fetch
numPoints = 2;

% Fetch data from ThingSpeak
data = thingSpeakRead(channelID, 'Fields', [1, 2, 3], 'NumPoints', numPoints, 'ReadKey', readAPIKey);

% Extract data into separate arrays
xRotation = data(1:numPoints, 1);
yRotation = data(1:numPoints, 2);
zRotation = data(1:numPoints, 3);

x = xRotation;
y = yRotation;
[X, Y] = meshgrid(x, y); % Creating a meshgrid
Z = sin(sqrt(X.^2 + Y.^2)); % Generating sample terrain data (you'd use your actual data here)

% Creating the terrain plot
figure;
surf(X, Y, Z); % Plotting the terrain
title('Terrestrial Terrain');
xlabel('X-axis');
ylabel('Y-axis');
zlabel('Z-axis');
shading interp
