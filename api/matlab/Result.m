classdef Result < Entity
    %RESULT CMAC operation result.
    %   If not successful, additional message is provided of the failure.

    % Method types as uint32
    properties(Hidden, Constant)
        METHOD_DELETE uint32 = 0;
        METHOD_IS_SUCCESSFUL uint32 = 100;
        METHOD_GET_MESSAGE uint32 = 101;
    end

    methods
        function obj = Result(handle, mexname, deleteId)
            %RESULT Construct an instance of this class
            arguments
                handle uint64
                mexname string = "ResultMex";
                deleteId uint32 = Result.METHOD_DELETE
            end
            obj@Entity(mexname, handle, deleteId);
        end
        
        function success = IsSuccessful(obj)
            %ISSUCCESSFUL Indicates if the operation was successful.
            arguments
                obj Result
            end
            success = feval(obj.mexName ...
                , Result.METHOD_IS_SUCCESSFUL, obj.handle);
        end

        function msg = GetMessage(obj)
            %GETMESSAGE Acquires the message for any unsuccessful
            %operation.
            arguments
                obj Result
            end
            msg = feval(obj.mexName ...
                , Result.METHOD_GET_MESSAGE, obj.handle);
        end
    end
end

