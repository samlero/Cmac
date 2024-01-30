classdef Adjustment < Result
    %ADJUSTMENT Summary of this class goes here
    %   Detailed explanation goes here

    properties(Hidden, Constant)
        METHOD_DELETE uint32 = 0;
        METHOD_GET_WEIGHT_CHANGES uint32 = 100;
        METHOD_IS_SUCCESSFUL uint32 = 101;
        METHOD_GET_MESSAGE uint32 = 102;
    end
    
    methods
        function obj = Adjustment(handle)
            %ADJUSTMENT Construct an instance of this class
            %   Detailed explanation goes here
            arguments
                handle uint64
            end
            obj@Result(handle, "AdjustmentMex" ...
                , Adjustment.METHOD_DELETE ...
                , Adjustment.METHOD_IS_SUCCESSFUL ...
                , Adjustment.METHOD_GET_MESSAGE);
        end
        
        function dw = GetWeightChanges(obj)
            %METHOD1 Get change in active weights when adjusted.
            arguments
                obj Adjustment
            end
            [change, nrows, ncols] = AdjustmentMex(Adjustment.METHOD_GET_WEIGHT_CHANGES ...
                , obj.handle);
            dw = reshape(change,[nrows, ncols]);
        end
    end
end

