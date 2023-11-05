% ThingSpeak Channel ID and Read API Key
channelID = 2332155;
readAPIKey = 'FIZT5F9N257PMZBG';

% Create a figure for the 3D surface plot
figure;
hold on;
grid on;
xlabel('X-axis');
ylabel('Y-axis');
zlabel('Z-axis');
title('Dynamic 3D Surface Plot');

% Initialize surface data
[X, Y, Z] = peaks(25); % You can initialize with any surface data you like

% Create the initial surface plot
surface(X, Y, Z, 'FaceColor', 'interp', 'EdgeColor', 'none');
view(3);
axis equal;

% Set the initial view angle
az = 30;
el = 30;

% Start an animation loop
while true
    % Fetch data from ThingSpeak
    data = thingSpeakRead(channelID, 'Fields', [4, 5, 6], 'NumPoints', 1, 'ReadKey', readAPIKey);

    % Extract data into separate variables
    xRotation = data(1, 1);
    yRotation = data(1, 2);
    zRotation = data(1, 3);

    % Update the surface plot based on the rotation data
    Z = peaks(25);  % Replace this with the surface data based on your rotation
    surf(X, Y, Z, 'FaceColor', 'interp', 'EdgeColor', 'none');
    
    % Update the view angle based on the rotation data
    az = zRotation; % Adjust this mapping based on your specific sensor data
    el = yRotation; % Adjust this mapping based on your specific sensor data
    view(az, el);
    
    % Add a pause to control the animation speed
    pause(1);
end

