classdef Result < Entity
    %RESULT CMAC operation result.
    %   If not successful, additional message is provided of the failure.

    % Method types as uint32
    properties(Hidden, Constant, Access=private)
        METHOD_DELETE uint32 = 0;
        METHOD_IS_SUCCESSFUL uint32 = 100;
        METHOD_GET_MESSAGE uint32 = 101;
    end

    properties(SetAccess=immutable, GetAccess=public)
        isSuccessfulMethodId uint32
        getMessageMethodId uint32
    end

    methods
        function obj = Result(handle ...
                , mexname, deleteId, successId ...
                , messageId)
            %RESULT Construct an instance of this class
            arguments
                handle uint64
                mexname string = "ResultMex";
                deleteId uint32 = Result.METHOD_DELETE
                successId uint32 = Result.METHOD_IS_SUCCESSFUL
                messageId uint32 = Result.METHOD_GET_MESSAGE
            end
            obj@Entity(mexname, handle, deleteId);
            obj.isSuccessfulMethodId = successId;
            obj.getMessageMethodId = messageId;
        end
        
        function success = IsSuccessful(obj)
            %ISSUCCESSFUL Indicates if the operation was successful.
            arguments
                obj Result
            end
            success = feval(obj.mexName ...
                , obj.isSuccessfulMethodId, obj.handle);
        end

        function msg = GetMessage(obj)
            %GETMESSAGE Acquires the message for any unsuccessful
            %operation.
            arguments
                obj Result
            end
            msg = feval(obj.mexName ...
                , obj.getMessageMethodId, obj.handle);
        end
    end
end

