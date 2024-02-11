classdef (Hidden) Result < handle
    %RESULT Summary of this class goes here
    %   Detailed explanation goes here
   
    properties(GetAccess=public, SetAccess=protected)
        IsSuccessful logical = false
        Message string = ""
    end

    %% Constructor
    methods
        function obj = Result()
            %RESULT Construct an instance of this class
            %   Detailed explanation goes here
        end
    end

    %% Setters
    methods(Access={?CmacLib.Cmac})
        function SetIsSuccessful(obj, value)
            arguments
                obj CmacLib.Result
                value logical
            end
            obj.IsSuccessful = value;
        end

        function SetMessage(obj, value)
            arguments
                obj CmacLib.Result
                value string
            end
            obj.Message = value;
        end
    end
end

