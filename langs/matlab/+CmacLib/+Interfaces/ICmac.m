classdef ICmac < CmacLib.Interfaces.ISerializable
    %ICMAC Summary of this class goes here
    %   Detailed explanation goes here
    
    methods(Abstract)
        Predict(object, input);
        Adjust(obj, correction, prediction, damping);
        Zeroize(obj);
    end
end

