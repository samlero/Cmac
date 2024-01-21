classdef Result < handle
    %RESULT CMAC operation result.
    %   If not successful, additional message is provided of the failure.
    
    properties(SetAccess=private, Hidden=true)
        objectHandle uint32     % IResult object handle
    end
    
    methods
        function obj = Result(objectHandle)
            %RESULT Construct an instance of this class
            arguments
                objectHandle uint32
            end
            obj.objectHandle = objectHandle;
        end
        
        function success = IsSuccessful(obj)
            %ISSUCCESSFUL Indicates if the operation was successful.
            arguments
                obj Result
            end
            success = ResultMex(obj.objectHandle, "IsSuccessful");
        end

        function msg = GetMessage(obj)
            %GETMESSAGE Acquires the message for any unsuccessful
            %operation.
            arguments
                obj Result
            end
            msg = ResultMex(obj.objectHandle, "GetMessage");
        end
    end
end

