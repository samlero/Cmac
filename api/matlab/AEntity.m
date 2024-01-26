classdef AEntity < handle
    %AENTITY Summary of this class goes here
    %   Detailed explanation goes here
    
    properties(SetAccess=private, GetAccess=public)
        objectHandle uint64
        mexName string
    end

    properties(Hidden)
        cleanup
    end
    
    methods(Access=public)
        function obj = AEntity(handle,mexname)
            %ACMACLIBENTITY Construct an instance of this class
            %   Detailed explanation goes here
            arguments
                handle uint64
                mexname string
            end
            obj.objectHandle = handle;
            obj.mexName = mexname;
            obj.cleanup = onCleanup(@()delete(obj));
        end
    end

    methods(Access=private)
        function delete(obj)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            feval(obj.mexName, 'Delete', obj.objectHandle);
        end
    end
end

