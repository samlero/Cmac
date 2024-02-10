classdef Prediction < CmacLib.IPrediction & CmacLib.Implementations.Result
    %PREDICTION Summary of this class goes here
    %   Detailed explanation goes here

    methods
        function obj = Prediction()
            %PREDICTION Construct an instance of this class
            %   Detailed explanation goes here
            obj@CmacLib.Implementations.Result();
        end

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
end

