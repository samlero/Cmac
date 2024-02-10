classdef (Abstract) IAdjustment < CmacLib.IResult
    %IADJUSTMENT Summary of this class goes here
    %   Detailed explanation goes here
    
    properties(GetAccess=public, SetAccess=protected)
        WeightChanges (:,:) double
    end
end

