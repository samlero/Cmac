clear all; close all; clc;
% Set to true if debug statements is wanted
isDebug = false;
% Set the path of the include files relative to the location of this file.
% This is where CmacLib.h is located.
includeDirectory = "..\..\..\..\Program Files\CmacLib\include";
% Set the path of the lib file relative to the location of this file.
% This is where CmacLib.lib is located.
libDirectory = "..\..\..\..\Program Files\CmacLib\lib";

debugArg = "-DDebug=false";
if isDebug
    debugArg = "-DDebug=true";
end
includeDirArg = strcat("-I", '"', includeDirectory, '"');
libDirArg = strcat("-L", '"', libDirectory, '"');

%% Build ResultMex.cpp
fprintf("Build ResultMex ...\n");
feval("mex", "ResultMex.cpp", "-lCmacLib", includeDirArg, libDirArg, debugArg);
fprintf("\n");

%% Build PredictionMex.cpp
fprintf("Build PredictionMex ...\n");
feval("mex", "PredictionMex.cpp", "-lCmacLib", includeDirArg, libDirArg, debugArg);
fprintf("\n");

%% Build AdjustmentMex.cpp
fprintf("Build AdjustmentMex ...\n");
feval("mex", "AdjustmentMex.cpp", "-lCmacLib", includeDirArg, libDirArg, debugArg);
fprintf("\n");

%% Build CmacMex.cpp
fprintf("Build CmacMex ...\n");
feval("mex", "CmacMex.cpp", "-lCmacLib", includeDirArg, libDirArg, debugArg);
fprintf("\n");

%% Build SerializationMex.cpp
fprintf("Build SerializationMex ...\n");
feval("mex", "SerializationMex.cpp", "-lCmacLib", includeDirArg, libDirArg, debugArg);
fprintf("\n");

%% Build MarshallerMex.cpp
fprintf("Build MarshallerMex ...\n");
feval("mex", "MarshallerMex.cpp", "-lCmacLib", includeDirArg, libDirArg, debugArg);
fprintf("\n");

%% Build FactoryMex.cpp
fprintf("Build FactoryMex ...\n");
feval("mex", "FactoryMex.cpp", "-lCmacLib", includeDirArg, libDirArg, debugArg);
fprintf("\n");
