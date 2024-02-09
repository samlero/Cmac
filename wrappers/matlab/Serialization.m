classdef Serialization < Result
    %SERIALIZATION Summary of this class goes here
    %   Detailed explanation goes here
    
    properties(Hidden, Constant, Access=private)
        METHOD_DELETE uint32 = 0;
        METHOD_GET_STRING uint32 = 100;
        METHOD_IS_SUCCESSFUL uint32 = 101;
        METHOD_GET_MESSAGE uint32 = 102;
    end
    
    methods
        function obj = Serialization(handle)
            %SERIALIZATION Construct an instance of this class
            %   Detailed explanation goes here
            arguments
                handle uint64
            end
            obj@Result(handle, "SerializationMex" ...
                , Serialization.METHOD_DELETE ...
                , Serialization.METHOD_IS_SUCCESSFUL ...
                , Serialization.METHOD_GET_MESSAGE);
        end
        
        function str = GetString(obj)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            arguments
                obj Serialization
            end
            str = SerializationMex(Serialization.METHOD_GET_STRING ...
                , obj.handle);
        end
    end
end

