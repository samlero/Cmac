classdef Result < CmacLib.IResult
    %RESULT Summary of this class goes here
    %   Detailed explanation goes here
   
    % Constructor
    methods
        function obj = Result()
            %RESULT Construct an instance of this class
            %   Detailed explanation goes here
            obj@CmacLib.IResult();
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
        function interfaceResult = CmacLib.IResult(obj)
            interfaceResult = CmacLib.IResult();
            interfaceResult.IsSuccessful = obj.IsSuccessful;
            interfaceResult.Message = obj.Message;
        end
    end
end

