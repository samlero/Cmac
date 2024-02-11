classdef (Hidden, Sealed) Serialization < CmacLib.Result
    %SERIALIZATION Summary of this class goes here
    %   Detailed explanation goes here

    properties(SetAccess=protected, GetAccess=public)
        String string
    end

    %% Constructor
    methods
        function obj = Serialization()
            obj@CmacLib.Result()
        end
    end

    %% Setters
    methods
        function SetString(obj, str)
            arguments
                obj CmacLib.Serialization
                str string
            end
            obj.String = str;
        end
    end
end

