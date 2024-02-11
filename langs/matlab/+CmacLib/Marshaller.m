classdef Marshaller < handle
    %MARSHALLER Summary of this class goes here
    %   Detailed explanation goes here
    
    methods
        function obj = Marshaller()
        end
        
        function result = Save(obj, serializable, directory, filename)
            arguments
                obj Marshaller
                serializable CmacLib.Serializable
                directory string
                filename string
            end
            result = CmacLib.Result();
            
            % serialize
            serialization = serializable.Serialize();
            
            if ~serialization.IsSuccessful
                result.Message("Serialization failed.");
                return
            end
            
            % concatenate filepath


        end

        function result = Load(obj, serializable, filepath)
            arguments
                obj Marshaller
                serializable CmacLib.Serializable
                filepath string
            end
        end
    end
end

