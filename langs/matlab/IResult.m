classdef IResult < handle
    %IRESULT Summary of this class goes here
    %   Detailed explanation goes here

    properties(SetAccess=protected, GetAccess=public)
        IsSuccessful boolean
        Message string
    end
end

