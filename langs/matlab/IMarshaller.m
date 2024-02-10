classdef IMarshaller < handle
    %IMARSHALLER Summary of this class goes here
    %   Detailed explanation goes here
    methods(Abstract)
        Save(obj, serializable, directory, filename);
        Load(obj, serializable, filepath);
    end
end

