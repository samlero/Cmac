classdef Result < AEntity
    %RESULT CMAC operation result.
    %   If not successful, additional message is provided of the failure.

    methods
        function obj = Result(handle)
            %RESULT Construct an instance of this class
            arguments
                handle uint64
            end
            obj@AEntity(handle, "ResultMex");
        end
        
        function success = IsSuccessful(obj)
            %ISSUCCESSFUL Indicates if the operation was successful.
            arguments
                obj Result
            end
            success = ResultMex('IsSuccessful', obj.objectHandle);
        end

        function msg = GetMessage(obj)
            %GETMESSAGE Acquires the message for any unsuccessful
            %operation.
            arguments
                obj Result
            end
            msg = ResultMex('GetMessage', obj.objectHandle);
        end
    end
end

