classdef Factory < handle
    %FACTORY Creates instances of CMACs
    
    properties(SetAccess=private, Hidden=true)
        objectHandle uint64     % Factory object handle
    end
    
    methods
        function obj = Factory()
            %FACTORY Construct an instance of this class
            obj.objectHandle = FactoryMex('New');
        end
        
        function delete(obj)
            FactoryMex(obj.objectHandle, 'Delete');
        end

        function cmac = CreateCmac(obj)
            arguments
                obj Factory
            end

        end
    end
end

