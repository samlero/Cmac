classdef Cmac < Serializable
    %CMAC Summary of this class goes here
    %   Detailed explanation goes here
    
    properties(Hidden, Constant, Access=private)
        METHOD_DELETE uint32 = 0;
        METHOD_PREDICT uint32 = 100;
        METHOD_ADJUST uint32 = 101;
        METHOD_ZEROIZE uint32 = 102;

        METHOD_SERIALIZE uint32 = 200;
        METHOD_DESERIALIZE uint32 = 201;
    end

    methods
        function obj = Cmac(handle)
            %CMAC Construct an instance of this class
            %   Detailed explanation goes here
            arguments
                handle uint64
            end
            obj@Serializable("CmacMex", handle ...
                , Cmac.METHOD_DELETE, Cmac.METHOD_SERIALIZE ...
                , Cmac.METHOD_DESERIALIZE);
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

        function result = Zeroize(obj)
            arguments
                obj Cmac
            end
            resultHandle = CmacMex(Cmac.METHOD_ZEROIZE, obj.handle);
            result = Result(resultHandle);
        end
    end
end

