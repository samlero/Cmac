classdef Marshaller < Entity
    %MARSHALLER Summary of this class goes here
    %   Detailed explanation goes here
    
    properties(Hidden, Constant, Access=private)
        METHOD_DELETE uint32 = 0;
        METHOD_SAVE uint32 = 100;
        METHOD_LOAD uint32 = 101;
    end

    methods
        function obj = Marshaller(handle)
            arguments
                handle uint64
            end
            obj@Entity("MarshallerMex", handle, Marshaller.METHOD_DELETE);
        end
        
        function result = Save(obj, serializable, directory, filename)
            arguments
                obj Marshaller
                serializable uint64
            end
        end
    end
end

