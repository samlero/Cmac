classdef Adjustment < CmacLib.IAdjustment & CmacLib.Implementations.Result
    %ADJUSTMENT Summary of this class goes here
    %   Detailed explanation goes here
    
    methods
        function obj = Adjustment()
            %ADJUSTMENT Construct an instance of this class
            %   Detailed explanation goes here
            obj@CmacLib.Implementations.Result();
        end
        
        function SetWeightChanges(obj, value)
            arguments
                obj Adjustment
                value (:,:) double
            end
            obj.WeightChanges = value;
        end
    end
end

