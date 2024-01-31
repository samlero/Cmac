clear all; close all; clc;

dt = 0.01;
T = 100.0;
num_dts = int32(T/dt);
num_cycles = int32(1);

% mass-damp system
M = 0.1*eye(2);
B = 0.001*eye(2);
x = [0;0];
xdot = [0;0];

% reference
xr = [1;-1];
xrdot = [0;0];

% control gains
kp = 1.0;
kd = 1.0;

% record data
record_e = zeros(2, num_dts);
record_nn = zeros(2, num_dts);

% create CMAC instance
factory = Factory();
cmac = factory.CreateCmac(10, 100, 1e5, 2, [10 10], -[10 10], dt*0.01, 1e-5);

% serialize 
ser = cmac.Serialize();
if ~ser.IsSuccessful()
    disp(ser.GetMessage());
    error('Serialization failed.');
end
serializedString = ser.GetString();

% create default CMAC instance and deserialize
cmac = factory.CreateDefaultCmac();
result = cmac.Deserialize(serializedString);
if ~result.IsSuccessful()
    disp(result.GetMessage());
    error('Serialization failed.');
end

% save and load using the marshaller
marshaller = factory.CreateMarshaller();
result = marshaller.Save(cmac, cd, "test_save");
if ~result.IsSuccessful()
    disp(result.GetMessage());
    error('Save failed.');
end
cmac = factory.CreateDefaultCmac();
filepath = append(cd, "\test_save.cmac");
result = marshaller.Load(cmac, filepath);
if ~result.IsSuccessful()
    disp(result.GetMessage());
    error('Load failed.');
end

% cycles
for cycle = 1 : num_cycles
% loop
for i = 1 : num_dts
    e = x - xr;
    edot = xdot - xrdot;
    z = (kp/kd)*e + edot;

    % predict
    prediction = cmac.Predict(x);
    if ~prediction.IsSuccessful()
        disp(prediction.GetMessage());
        error('Prediction failed.');
    end

    % train
    adjustment = cmac.Adjust(z, prediction, norm(z));
    if ~adjustment.IsSuccessful()
        disp(adjustment.GetMessage());
        error('Adjustment failed.');
    end
    nn = prediction.GetValues();
    u = -kd*z - nn;

    xddot = M\(u - B*xdot) - 9.81*ones(2,1);
    xdot = xdot + xddot*dt;
    x = x + xdot*dt;

    record_e(:,i) = e;
    record_nn(:,i) = nn;
end
end

% graph
figure(1);
subplot(2,1,1);
plot(dt:dt:T, record_e(1,:));
title('e');
subplot(2,1,2);
plot(dt:dt:T, record_e(2,:));

figure(2);
subplot(2,1,1);
plot(dt:dt:T, record_nn(1,:));
title('nn');
subplot(2,1,2);
plot(dt:dt:T, record_nn(2,:));

