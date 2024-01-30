classdef Factory < Entity
    %FACTORY Creates instances of CMACs

    % Method types as uint32
    properties(Hidden, Constant)
        METHOD_NEW uint32 = 0;
        METHOD_DELETE uint32 = 1;
        METHOD_CREATE_CMAC uint32 = 100;
        METHOD_CREATE_MARSHALLER uint32 = 101;
    end

    methods
        function obj = Factory()
            %FACTORY Construct an instance of this class
            handle = FactoryMex(Factory.METHOD_NEW);
            obj@Entity("FactoryMex", handle, Factory.METHOD_DELETE);
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
            cmacHandle = FactoryMex(Factory.METHOD_CREATE_CMAC ...
                , obj.handle ...
                , numQ, numLayers, maxMem, numOut ...
                , upper, lower, beta, nu);

            cmac = Cmac(cmacHandle);
        end
    end
end

