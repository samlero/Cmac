classdef Prediction < Result
    %PREDICTION Prediction result.

    properties(Hidden, Constant, Access=private)
        METHOD_DELETE uint32 = 0;
        METHOD_GET_VALUES uint32 = 100;
        METHOD_GET_ACTIVE_WEIGHT_INDICES = 101;
        METHOD_GET_ACTIVE_WEIGHTS = 102;
        METHOD_GET_BASIS_VALUES = 103;
        METHOD_IS_SUCCESSFUL uint32 = 104;
        METHOD_GET_MESSAGE uint32 = 105;
    end
    
    methods
        function obj = Prediction(handle)
            %PREDICTION Construct an instance of this class
            arguments
                handle uint64
            end
            obj@Result(handle, "PredictionMex" ...
                , Prediction.METHOD_DELETE ...
                , Prediction.METHOD_IS_SUCCESSFUL ...
                , Prediction.METHOD_GET_MESSAGE);
        end
        
        function values = GetValues(obj)
            %GETVALUES Gets the resulting operation of the prediction.
            arguments
                obj Prediction
            end
            vals = PredictionMex(Prediction.METHOD_GET_VALUES ...
                , obj.handle);
            values = reshape(vals, [numel(vals) 1]);
        end

        function weightIdx = GetActiveWeightIndices(obj)
            %GETACTIVEWEIGHTINDICES Get the indices of the active weights
            %in memory.
            arguments
                obj Prediction
            end
            idx = PredictionMex(Prediction.METHOD_GET_ACTIVE_WEIGHT_INDICES ...
                , obj.handle);
            weightIdx = reshape(idx, [numel(idx), 1]);
        end

        function weights = GetActiveWeights(obj)
            %GETACTIVEWEIGHTS Get the active weights associated with the
            %prediction.
            arguments
                obj Prediction
            end
            [w, nrows, ncols] = PredictionMex(Prediction.METHOD_GET_ACTIVE_WEIGHTS ...
                , obj.handle);
            weights = reshape(w, [nrows, ncols]);
        end

        function basis = GetBasisValues(obj)
            %GETBASISVALUES Get the calculated basis values.
            arguments
                obj Prediction
            end
            bf = PredictionMex(Prediction.METHOD_GET_BASIS_VALUES ...
                , obj.handle);
            basis = reshape(bf, [numel(bf) 1]);
        end
    end
end

