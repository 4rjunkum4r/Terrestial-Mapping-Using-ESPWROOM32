% Define car shape
carLength = 2;
carWidth = 1;
carHeight = 0.5;

% Coordinates for the car shape
carX = [-carLength/2, carLength/2, carLength/2, -carLength/2, -carLength/2];
carY = [-carWidth/2, -carWidth/2, carWidth/2, carWidth/2, -carWidth/2];
carZ = [0, 0, 0, 0, 0];

% Create the initial surface plot for the car
h = fill3(carX, carY, carZ, 'b');
view(3);
axis equal;

% ThingSpeak Channel ID and Read API Key
channelID = 2332155;
readAPIKey = 'FIZT5F9N257PMZBG';

% Start an animation loop
while ishandle(h)  % Check if the figure is still open
    % Fetch the latest data point from ThingSpeak
    data = thingSpeakRead(channelID, 'Fields', [4, 5, 6], 'NumPoints', 1, 'ReadKey', readAPIKey);

    % Extract data into separate variables
    xRotation = data(1, 1);
    yRotation = data(1, 2);
    zRotation = data(1, 3);

    % Update the orientation of the car based on the rotation data
    rotatedCar = rotateCar(carX, carY, carZ, xRotation, yRotation, zRotation);

    % Update the car plot
    set(h, 'XData', rotatedCar(1, :), 'YData', rotatedCar(2, :), 'ZData', rotatedCar(3, :));

    % Add a pause to control the animation speed
    pause(0.1);
end

% Function to rotate the car shape
function rotatedCar = rotateCar(carX, carY, carZ, xRotation, yRotation, zRotation)
    % Homogeneous coordinates
    carCoordinates = [carX; carY; carZ; ones(1, 5)];

    % 3D rotation matrices
    Rx = [1, 0, 0; 0, cos(xRotation), -sin(xRotation); 0, sin(xRotation), cos(xRotation)];
    Ry = [cos(yRotation), 0, sin(yRotation); 0, 1, 0; -sin(yRotation), 0, cos(yRotation)];
    Rz = [cos(zRotation), -sin(zRotation), 0; sin(zRotation), cos(zRotation), 0; 0, 0, 1];

    % Combined rotation matrix
    rotationMatrix = Rz * Ry * Rx;

    % Apply rotation
    rotatedCar = rotationMatrix * carCoordinates;

    % Extract rotated coordinates
    rotatedCar = rotatedCar(1:3, :);
end
