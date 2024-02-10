classdef IPrediction < IResult
    %IPREDICTION Summary of this class goes here
    %   Detailed explanation goes here 
    properties(SetAccess=protected, GetAccess=public)
        Values (:,1) double
        ActiveWeightIndices (:,1) uint32
        ActiveWeights (:,:) double
        BasisValues (:,1) double
    end
end

