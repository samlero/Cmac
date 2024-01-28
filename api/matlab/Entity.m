classdef Entity < handle
    %ENTITY Summary of this class goes here
    %   Detailed explanation goes here
    
    properties(SetAccess=immutable, GetAccess=public)
        mexName string
        handle uint64     
        deleteId uint32
    end

    properties(Hidden)
        cleanup
    end
        
    methods
        function obj = Entity(mexName,handle,deleteId)
            %ENTITY Construct an instance of this class
            %   Detailed explanation goes here
            arguments
                mexName string
                handle uint64
                deleteId uint32
            end
            obj.mexName = mexName;
            obj.handle = handle;
            obj.deleteId = deleteId;
            obj.cleanup = onCleanup(@()delete(obj));
        end
    end

    methods(Access=private)
        function delete(obj)
            feval(obj.mexName, obj.deleteId, obj.handle);
        end
    end
end

