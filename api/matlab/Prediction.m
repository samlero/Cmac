classdef Prediction < ACmacLibEntity
    %PREDICTION Prediction result.
    
    methods
        function obj = Prediction(handle)
            %PREDICTION Construct an instance of this class
            arguments
                handle uint64
            end
            obj@ACmacLibEntity(handle, "PredictionMex");
        end
        
        function values = GetValues(obj)
            %GETVALUES Gets the resulting operation of the prediction.
            arguments
                obj Prediction
            end
            vals = PredictionMex(obj.objectHandle, 'GetValues');
            values = reshape(vals, [numel(vals) 1]);
        end

        function weightIdx = GetActiveWeightIndices(obj)
            %GETACTIVEWEIGHTINDICES Get the indices of the active weights
            %in memory.
            arguments
                obj Prediction
            end
            idx = PredictionMex(obj.objectHandle, 'GetActiveWeightIndices');
            weightIdx = reshape(idx, [numel(idx), 1]);
        end

        function weights = GetActiveWeights(obj)
            %GETACTIVEWEIGHTS Get the active weights associated with the
            %prediction.
            arguments
                obj Prediction
            end
            [w, nrows, ncols] = PredictionMex(obj.objectHandle, 'GetActiveWeights');
            weights = reshape(w, [nrows, ncols]);
        end

        function basis = GetBasisValues(obj)
            %GETBASISVALUES Get the calculated basis values.
            arguments
                obj Prediction
            end
            bf = PredictionMex(obj.objectHandle, 'GetBasisValues');
            basis = reshape(bf, [numel(bf) 1]);
        end

        function result = GetResult(obj)
            %GETRESULT Get the result (successful or not, and reason for
            %failures).
            arguments
                obj Prediction
            end
            res = PredictionMex(obj.objectHandle, 'GetResult');
            result = Result(res);
        end
    end
end

