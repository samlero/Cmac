classdef (Hidden, Sealed) Adjustment < handle
    %ADJUSTMENT Summary of this class goes here
    %   Detailed explanation goes here

    properties(GetAccess=public, SetAccess=protected)
        WeightChanges (:,:) double
    end

    %% Constructor
    methods
        function obj = Adjustment()
        end
    end

    %% Setters
    methods(Access={?CmacLib.Cmac})
        function SetWeightChanges(obj, value)
            arguments
                obj CmacLib.Adjustment
                value (:,:) double
            end
            obj.WeightChanges = value;
        end
    end
end

