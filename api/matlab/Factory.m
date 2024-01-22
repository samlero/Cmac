classdef Factory < ACmacLibEntity
    %FACTORY Creates instances of CMACs
    
    methods
        function obj = Factory()
            %FACTORY Construct an instance of this class
            handle = FactoryMex('New');
            obj@ACmacLibEntity(handle, "FactoryMex");
        end
        
        function cmac = CreateCmac(obj, numQ, numLayers, maxMem, numOut ...
                , upper, lower, beta, nu)
            arguments
                obj Factory
                numQ uint32
                numLayers uint32
                maxMem uint32
                numOut uint32
                upper (:,1) double
                lower (:,1) double
                beta double
                nu double
            end
            cmacHandle = FactoryMex(obj.objectHandle, 'CreateCmac' ...
                , numQ, numLayers, maxMem, numOut ...
                , upper, lower, beta, nu);

            cmac = Cmac(cmacHandle);
        end
    end
end

