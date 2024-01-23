classdef (Abstract) ACmacLibEntity < handle
    %ACMACLIBENTITY Summary of this class goes here
    %   Detailed explanation goes here
    
    properties(SetAccess=private, GetAccess=public)
        objectHandle uint64
        mexName string
    end

    properties(Hidden)
        cleanup
    end
    
    methods(Access=public)
        function obj = ACmacLibEntity(handle,name)
            %ACMACLIBENTITY Construct an instance of this class
            %   Detailed explanation goes here
            arguments
                handle uint64
                name string
            end
            obj.objectHandle = handle;
            obj.mexName = name;
            obj.cleanup = onCleanup(@()delete(obj));
        end
    end

    methods(Access=private)
        function delete(obj)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            feval(obj.mexName, obj.objectHandle, 'Delete');
        end
    end
end

