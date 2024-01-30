classdef Cmac < Entity
    %CMAC Summary of this class goes here
    %   Detailed explanation goes here
    
    properties(Hidden, Constant, Access=private)
        METHOD_DELETE uint32 = 0;
        METHOD_PREDICT uint32 = 100;
        METHOD_ADJUST uint32 = 101;
        METHOD_SERIALIZE uint32 = 102;
        METHOD_DESERIALIZE uint32 = 103;
    end

    methods
        function obj = Cmac(handle)
            %CMAC Construct an instance of this class
            %   Detailed explanation goes here
            arguments
                handle uint64
            end
            obj@Entity("CmacMex", handle, Cmac.METHOD_DELETE);
        end
        
        function prediction = Predict(obj, inputs)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            arguments
                obj Cmac
                inputs (:,1) double
            end
            predictionHandle = CmacMex(Cmac.METHOD_PREDICT, obj.handle, inputs);
            prediction = Prediction(predictionHandle);
        end

        function adjustment = Adjust(obj, correction, prediction, damping)
            arguments
                obj Cmac
                correction (:,1) double
                prediction Prediction
                damping double
            end
            adjustmentHandle = CmacMex(Cmac.METHOD_ADJUST, obj.handle ...
                , correction, prediction.handle, damping);
            adjustment = Adjustment(adjustmentHandle);
        end

        function serialization = Serialize(obj)
            arguments
                obj Cmac
            end
            handle = CmacMex(Cmac.METHOD_SERIALIZE, obj.handle);
            serialization = Serialization(handle);
        end

        function result = Deserialize(obj, content)
            arguments
                obj Cmac
                content string
            end
            handle = CmacMex(Cmac.METHOD_DESERIALIZE ...
                , obj.handle, convertStringsToChars(content));
            result = Result(handle);
        end
    end
end

