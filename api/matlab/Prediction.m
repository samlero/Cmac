classdef Prediction < handle
    %PREDICTION Prediction result.
    
    properties(SetAccess=private, Hidden=true)
        objectHandle uint64     % IPrediction object handle
    end
    
    methods
        function obj = Prediction(objectHandle)
            %PREDICTION Construct an instance of this class
            arguments
                objectHandle uint64
            end
            obj.objectHandle = objectHandle;
        end
        
        function values = GetValues(obj)
            %GETVALUES Gets the resulting operation of the prediction.
            arguments
                obj Prediction
            end
            values = PredictionMex(obj.objectHandle, "GetValues");
        end

        function weightIdx = GetActiveWeightIndices(obj)
            %GETACTIVEWEIGHTINDICES Get the indices of the active weights
            %in memory.
            arguments
                obj Prediction
            end
            weightIdx = PredictionMex(obj.objectHandle, "GetActiveWeightIndices");
        end

        function weights = GetActiveWeights(obj)
            %GETACTIVEWEIGHTS Get the active weights associated with the
            %prediction.
            arguments
                obj Prediction
            end
            [w, nrows, ncols] = PredictionMex(obj.objectHandle, "GetActiveWeights");
            weights = reshape(w, [nrows, ncols]);
        end

        function basis = GetBasisValues(obj)
            %GETBASISVALUES Get the calculated basis values.
            arguments
                obj Prediction
            end
            basis = PredictionMex(obj.objectHandle, "GetBasisValues");
        end

        function result = GetResult(obj)
            %GETRESULT Get the result (successful or not, and reason for
            %failures).
            arguments
                obj Prediction
            end
            res = PredictionMex(obj.objectHandle, "GetResult");
            result = Result(res);
        end

        function delete(obj)
            %DELETE Destroy the object handle.
            arguments
                obj Prediction
            end
            PredictionMex(obj.objectHandle, "Delete");
        end
    end
end

