classdef Result < AEntity
    %RESULT CMAC operation result.
    %   If not successful, additional message is provided of the failure.

    methods
        function obj = Result(handle, mexname)
            %RESULT Construct an instance of this class
            arguments
                handle uint64
                mexname string = "ResultMex";
            end
            obj@AEntity(handle, mexname);
        end
        
        function success = IsSuccessful(obj)
            %ISSUCCESSFUL Indicates if the operation was successful.
            arguments
                obj Result
            end
            success = feval(obj.mexName, 'IsSuccessful', obj.objectHandle);
        end

        function msg = GetMessage(obj)
            %GETMESSAGE Acquires the message for any unsuccessful
            %operation.
            arguments
                obj Result
            end
            msg = feval(obj.mexName, 'GetMessage', obj.objectHandle);
        end
    end
end

