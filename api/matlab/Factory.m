classdef Factory < ACmacLibEntity
    %FACTORY Creates instances of CMACs
    
    methods
        function obj = Factory()
            %FACTORY Construct an instance of this class
            handle = FactoryMex('New');
            obj@ACmacLibEntity(handle, "FactoryMex");
        end
        
        function cmac = CreateCmac(obj)
            arguments
                obj Factory
            end

        end
    end
end

