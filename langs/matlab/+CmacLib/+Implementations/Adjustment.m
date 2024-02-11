classdef (Hidden) Adjustment < CmacLib.Interfaces.IAdjustment & CmacLib.Implementations.Result
    %ADJUSTMENT Summary of this class goes here
    %   Detailed explanation goes here

    % Constructor
    methods
        function obj = Adjustment()
            obj@CmacLib.Implementations.Result();
            obj@CmacLib.Interfaces.IAdjustment();
        end
    end

    % Setters
    methods
        function SetWeightChanges(obj, value)
            arguments
                obj Adjustment
                value (:,:) double
            end
            obj.WeightChanges = value;
        end
    end

    % Converters
    methods
        function objIResult = CmacLib.Intefaces.IResult(obj)
            arguments
                obj Adjustment
            end
            objIResult = CmacLib.Interfaces.IResult();
            objIResult.IsSuccessful = obj.IsSuccessful;
            objIResult.Message = obj.Message;
        end

        function objIAdjustment = CmacLib.Interfaces.IAdjustment(obj)
            arguments
                obj Adjustment
            end
            objIAdjustment = CmacLib.Interfaces.IAdjustment();
            objIAdjustment.IsSuccessful = obj.IsSuccessful;
            objIAdjustment.Message = obj.Message;
            objIAdjustment.WeightChanges = obj.WeightChanges;
        end
    end
end

