classdef Marshaller < Entity
    %MARSHALLER Summary of this class goes here
    %   Detailed explanation goes here
    
    properties(Hidden, Constant, Access=private)
        METHOD_DELETE uint32 = 0;
        METHOD_SAVE uint32 = 100;
        METHOD_LOAD uint32 = 101;

        SERIALIZABLE_CMAC uint32 = 1000;
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
                serializable Serializable
                directory string
                filename string
            end

            handle = MarshallerMex(Marshaller.METHOD_SAVE ...
                , obj.handle, serializable.handle ...
                , convertStringsToChars(directory) ...
                , convertStringsToChars(filename) ...
                , Marshaller.SERIALIZABLE_CMAC);
            result = Result(handle);
        end

        function result = Load(obj, serializable, filepath)
            arguments
                obj Marshaller
                serializable Serializable
                filepath string
            end
            handle = MarshallerMex(Marshaller.METHOD_LOAD ...
                , obj.handle, serializable.handle ...
                , convertStringsToChars(filepath)...
                , Marshaller.SERIALIZABLE_CMAC);
            result = Result(handle);
        end
    end
end

