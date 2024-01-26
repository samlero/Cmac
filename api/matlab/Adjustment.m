classdef Adjustment < AEntity
    %ADJUSTMENT Summary of this class goes here
    %   Detailed explanation goes here
    
    methods
        function obj = Adjustment(handle)
            %ADJUSTMENT Construct an instance of this class
            %   Detailed explanation goes here
            arguments
                handle uint64
            end
            obj@AEntity(handle, "AdjustmentMex");
        end
        
        function dw = GetWeightChanges(obj)
            %METHOD1 Get change in active weights when adjusted.
            arguments
                obj Adjustment
            end
            [change, nrows, ncols] = AdjustmentMex('GetWeightChanges' ...
                , obj.objectHandle);
            dw = reshape(change,[nrows, ncols]);
        end
    end
end

