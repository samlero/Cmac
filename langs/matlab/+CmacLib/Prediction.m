classdef (Hidden,Sealed) Prediction < handle
    %PREDICTION Summary of this class goes here
    %   Detailed explanation goes here

    properties(SetAccess=protected, GetAccess=public)
        Values (:,1) double
        ActiveWeightIndices (:,1) uint32
        ActiveWeights (:,:) double
        BasisValues (:,1) double
    end

    %% Constructor
    methods(Access={?CmacLib.Cmac})
        function obj = Prediction()
        end
    end

    %% Setters
    methods(Access={?CmacLib.Cmac})
        function SetValues(obj, values)
            arguments
                obj CmacLib.Prediction
                values (:,1) double
            end
            obj.Values = values;
        end

        function SetActiveWeightIndices(obj, indices)
            arguments
                obj CmacLib.Prediction
                indices (:,1) uint32
            end
            obj.ActiveWeightIndices = indices;
        end

        function SetActiveWeights(obj, weights)
            arguments
                obj CmacLib.Prediction
                weights (:,:) double
            end
            obj.ActiveWeights = weights;
        end

        function SetBasisValues(obj, basis)
            arguments
                obj CmacLib.Prediction
                basis (:,1) double
            end
            obj.BasisValues = basis;
        end

    end
end

