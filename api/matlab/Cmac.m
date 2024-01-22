classdef Cmac < ACmacLibEntity
    %CMAC Summary of this class goes here
    %   Detailed explanation goes here
    
    methods
        function obj = Cmac(handle)
            %CMAC Construct an instance of this class
            %   Detailed explanation goes here
            arguments
                handle uint64
            end
            obj@ACmacLibEntity(handle, "CmacMex");
        end
        
        function prediction = Predict(obj, inputs)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            arguments
                obj Cmac
                inputs (:,1) double
            end
            predictionHandle = CmacMex(obj.objectHandle, 'Predict', inputs);
            prediction = Prediction(predictionHandle);
        end

        function adjustment = Adjust(obj, correction, prediction, damping)
            arguments
                obj Cmac
                correction (:,1) double
                prediction Prediction
                damping double
            end
            adjustmentHandle = CmacMex(obj.objectHandle, 'Adjust' ...
                , correction, prediction.objectHandle, damping);
            adjustment = Adjustment(adjustmentHandle);
        end
    end
end

