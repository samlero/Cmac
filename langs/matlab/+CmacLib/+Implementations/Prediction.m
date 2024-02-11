classdef (Hidden,Sealed) Prediction < CmacLib.Interfaces.IPrediction & CmacLib.Implementations.Result
    %PREDICTION Summary of this class goes here
    %   Detailed explanation goes here

    %% Constructor
    methods
        function obj = Prediction()
            %PREDICTION Construct an instance of this class
            %   Detailed explanation goes here
            obj@CmacLib.Implementations.Result();
            obj@CmacLib.Interfaces.IPrediction();
        end
    end

    %% Setters
    methods
        function SetValues(obj, values)
            arguments
                obj Prediction
                values (:,1) double
            end
            obj.Values = values;
        end

        function SetActiveWeightIndices(obj, indices)
            arguments
                obj Prediction
                indices (:,1) uint32
            end
            obj.ActiveWeightIndices = indices;
        end

        function SetActiveWeights(obj, weights)
            arguments
                obj Prediction
                weights (:,:) double
            end
            obj.ActiveWeights = weights;
        end

        function SetBasisValues(obj, basis)
            arguments
                obj Prediction
                basis (:,1) double
            end
            obj.BasisValues = basis;
        end

    end
    
    %% Converters
    methods
        function objIResult = IResult(obj)
            objIResult = CmacLib.Interfaces.IResult();
            objIResult.IsSuccessful = obj.IsSuccessful;
            objIResult.Message = obj.Message;
        end

        function objIPrediction = IPrediction(obj)
            objIPrediction = CmacLib.Interfaces.IPrediction();
            objIPrediction.IsSuccessful = obj.IsSuccessful;
            objIPrediction.Message = obj.Message;
            objIPrediction.Values = obj.Values;
            objIPrediction.ActiveWeightIndices = obj.ActiveWeightIndices;
            objIPrediction.ActiveWeights = obj.ActiveWeights;
            objIPrediction.BasisValues = obj.BasisValues;
        end
    end
end

