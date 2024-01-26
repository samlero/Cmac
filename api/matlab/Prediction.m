classdef Prediction < AEntity
    %PREDICTION Prediction result.
    
    methods
        function obj = Prediction(handle)
            %PREDICTION Construct an instance of this class
            arguments
                handle uint64
            end
            obj@AEntity(handle, "PredictionMex");
        end
        
        function values = GetValues(obj)
            %GETVALUES Gets the resulting operation of the prediction.
            arguments
                obj Prediction
            end
            vals = PredictionMex('GetValues', obj.objectHandle);
            values = reshape(vals, [numel(vals) 1]);
        end

        function weightIdx = GetActiveWeightIndices(obj)
            %GETACTIVEWEIGHTINDICES Get the indices of the active weights
            %in memory.
            arguments
                obj Prediction
            end
            idx = PredictionMex('GetActiveWeightIndices', obj.objectHandle);
            weightIdx = reshape(idx, [numel(idx), 1]);
        end

        function weights = GetActiveWeights(obj)
            %GETACTIVEWEIGHTS Get the active weights associated with the
            %prediction.
            arguments
                obj Prediction
            end
            [w, nrows, ncols] = PredictionMex('GetActiveWeights', obj.objectHandle);
            weights = reshape(w, [nrows, ncols]);
        end

        function basis = GetBasisValues(obj)
            %GETBASISVALUES Get the calculated basis values.
            arguments
                obj Prediction
            end
            bf = PredictionMex('GetBasisValues', obj.objectHandle);
            basis = reshape(bf, [numel(bf) 1]);
        end
    end
end

