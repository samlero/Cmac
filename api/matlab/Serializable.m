classdef Serializable < Entity
    %SERIALIZABLE Summary of this class goes here
    %   Detailed explanation goes here
    
    properties(Hidden, Constant, Access=private)
        METHOD_DELETE uint32 = 0;
        METHOD_SERIALIZE uint32 = 104;
        METHOD_DESERIALIZE uint32 = 105;
    end

    properties(SetAccess=immutable, GetAccess=public)
        serializeMethodId uint32
        deserializeMethodId uint32
    end
    
    
    methods
        function obj = Serializable(mexName, handle ...
                ,deleteId, serializeId, deserializeId)
            %SERIALIZABLE Construct an instance of this class
            %   Detailed explanation goes here
            arguments
                mexName string
                handle uint64
                deleteId uint32 = Serializable.METHOD_DELETE
                serializeId uint32 = Serializable.METHOD_SERIALIZE
                deserializeId uint32 = Seralizable.METHOD_DESERIALIZE
            end
            obj@Entity(mexName, handle, deleteId);
            obj.serializeMethodId = serializeId;
            obj.deserializeMethodId = deserializeId;
        end
        
        function serialization = Serialize(obj)
            arguments
                obj Serializable
            end
            serializationHandle = feval(obj.mexName ...
                , obj.serializeMethodId ...
                , obj.handle);
            serialization = Serialization(serializationHandle);
        end

        function result = Deserialize(obj, content)
            arguments
                obj Serializable
                content string
            end
            handle = feval(obj.mexName ...
                , obj.deserializeMethodId ...
                , obj.handle ...
                , convertStringsToChars(content));
            result = Result(handle);
        end
    end
end

