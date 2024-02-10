classdef ISerializable < handle
    %ISERIALIZABLE Summary of this class goes here
    %   Detailed explanation goes here
    
    properties(SetAccess=protected, GetAccess=public)
        Extension string
    end
    
    methods(Abstract)
        Serialize(obj);
        Deserialize(obj, content);
    end
end

