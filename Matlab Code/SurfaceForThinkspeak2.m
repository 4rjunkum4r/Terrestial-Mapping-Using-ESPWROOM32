function SurfaceForThinkspeak2()
% ThingSpeak Channel ID and Write API Key
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

% Initialize a plain surface
[X, Y] = meshgrid(-2:0.2:2, -2:0.2:2);
Z = zeros(size(X));

% Create the initial surface plot
h = surf(X, Y, Z, 'FaceColor', 'interp', 'EdgeColor', 'none');
view(3);
axis equal;

% Set the initial view angle
az = 30;
el = 30;

% Start an animation loop
while ishandle(h)  % Check if the figure is still open
    % Fetch the latest data point from ThingSpeak
    data = thingSpeakRead(channelID, 'Fields', [4,5,6], 'NumPoints', 1, 'ReadKey', readAPIKey);


    xRotation = data(1, 1);
    yRotation = data(1, 2);
    zRotation = data(1, 3);

    % Display the rotation data for debugging
    fprintf('xRotation: %.2f, yRotation: %.2f, zRotation: %.2f\n', xRotation, yRotation, zRotation);

    % Update the view angle based on the rotation data
    az = zRotation; % Adjust this mapping based on your specific sensor data
    

    % Display the view angles for debugging
    fprintf('az: %.2f, el: %.2f\n', az, el);

    % Update the view only if az and el are valid (not NaN)
    if ~isnan(az) && ~isnan(el)
        view(az, el);
    end

    % Add a pause to control the animation speed
    pause(0.5);
end



