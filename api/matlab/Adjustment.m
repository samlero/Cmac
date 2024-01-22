classdef Adjustment < ACmacLibEntity
    %ADJUSTMENT Summary of this class goes here
    %   Detailed explanation goes here
    
    methods
        function obj = Adjustment(handle)
            %ADJUSTMENT Construct an instance of this class
            %   Detailed explanation goes here
            arguments
                handle uint64
            end
            obj@ACmacLibEntity(handle, "AdjustmentMex");
        end
        
        function dw = GetWeightChanges(obj)
            %METHOD1 Get change in active weights when adjusted.
            arguments
                obj Adjustment
            end
            [change, nrows, ncols] = AdjustmentMex(obj.objectHandle ...
                , 'GetWeightChanges');
            dw = reshape(change,[nrows, ncols]);
        end

        function result = GetResult(obj)
            %GETRESULT Get the result (successful or not, and reason for
            %failures).
            arguments
                obj Adjustment
            end
            res = AdjustmentMex(obj.objectHandle, 'GetResult');
            result = Result(res);
        end

    end
end

