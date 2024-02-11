classdef (Hidden) Result < CmacLib.Interfaces.IResult
    %RESULT Summary of this class goes here
    %   Detailed explanation goes here
   
    % Constructor
    methods(Access=protected)
        function obj = Result()
            %RESULT Construct an instance of this class
            %   Detailed explanation goes here
            obj@CmacLib.Interfaces.IResult();
        end
    end

    % Setters
    methods
        function SetIsSuccessful(obj, value)
            arguments
                obj Result
                value logical
            end
            obj.IsSuccessful = value;
        end

        function SetMessage(obj, value)
            arguments
                obj Result
                value string
            end
            obj.Message = value;
        end
    end

    % Converters
    methods
        function objIResult = IResult(obj)
            objIResult = CmacLib.Interfaces.IResult();
            objIResult.IsSuccessful = obj.IsSuccessful;
            objIResult.Message = obj.Message;
        end
    end
end

