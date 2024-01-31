clear all; close all; clc;

%% Build ResultMex.cpp
fprintf("Build ResultMex ...\n");
mex -DDebug=true ResultMex.cpp -I"..\..\..\..\Program Files\CmacLib\include" -L"..\..\..\..\Program Files\CmacLib\lib" -lCmacLib
fprintf("\n");

%% Build PredictionMex.cpp
fprintf("Build PredictionMex ...\n");
mex -DDebug=true PredictionMex.cpp -I"..\..\..\..\Program Files\CmacLib\include" -L"..\..\..\..\Program Files\CmacLib\lib" -lCmacLib
fprintf("\n");

%% Build FactoryMex.cpp
fprintf("Build FactoryMex ...\n");
mex -DDebug=true FactoryMex.cpp -I"..\..\..\..\Program Files\CmacLib\include" -L"..\..\..\..\Program Files\CmacLib\lib" -lCmacLib
fprintf("\n");

%% Build AdjustmentMex.cpp
fprintf("Build AdjustmentMex ...\n");
mex -DDebug=true AdjustmentMex.cpp -I"..\..\..\..\Program Files\CmacLib\include" -L"..\..\..\..\Program Files\CmacLib\lib" -lCmacLib
fprintf("\n");

%% Build CmacMex.cpp
fprintf("Build CmacMex ...\n");
mex -DDebug=true CmacMex.cpp -I"..\..\..\..\Program Files\CmacLib\include" -L"..\..\..\..\Program Files\CmacLib\lib" -lCmacLib
fprintf("\n");

%% Build SerializationMex.cpp
fprintf("Build SerializationMex ...\n");
mex -DDebug=true SerializationMex.cpp -I"..\..\..\..\Program Files\CmacLib\include" -L"..\..\..\..\Program Files\CmacLib\lib" -lCmacLib
fprintf("\n");

%% Build MarshallerMex.cpp
fprintf("Build MarshallerMex ...\n");
mex -DDebug=true MarshallerMex.cpp -I"..\..\..\..\Program Files\CmacLib\include" -L"..\..\..\..\Program Files\CmacLib\lib" -lCmacLib
fprintf("\n");
