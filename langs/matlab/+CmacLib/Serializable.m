classdef (Abstract,Hidden) Serializable < handle
    %SERIALIZABLE Summary of this class goes here
    %   Detailed explanation goes here
    
    properties(GetAccess=public, SetAccess=protected)
        Extension string = ""
    end

    methods
        function obj = Serializable(ext)
            obj.Extension = ext;
        end
    end

    methods(Abstract)
        serialization = Serialize(obj);
        Deserialize(obj, content);
    end
end

