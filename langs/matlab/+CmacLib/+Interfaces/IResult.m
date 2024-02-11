classdef IResult < handle
    %IRESULT Summary of this class goes here
    %   Detailed explanation goes here
    properties(GetAccess=public, SetAccess=protected)
        IsSuccessful logical
        Message string
    end
    
    methods(Access=protected)
        function obj = IResult()
        end
    end

end

