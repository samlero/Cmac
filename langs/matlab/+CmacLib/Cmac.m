classdef (Sealed) Cmac < CmacLib.Serializable
    %CMAC Summary of this class goes here
    %   Detailed explanation goes here
    
    %% Properties
    properties(Hidden, SetAccess=private)
        NumQ int32 % number of quantizations/cells per layer
        NumLayers int32 % number of layers
        NumOutput int32 % number of outputs
        NumInput int32 % number of inputs
        InputUpperLimit (:,1) double % upper input limit
        InputLowerLimit (:,1) double % lower input limit
        Memory (:,:) double % memory storage
        Hashtable (:,1) int32
        Memsize int32
        Offsets (:,:) double % offsets

        Beta double % learning rate
        Nu double % forgetting/damping coefficient
    end

    properties(Access=private)
        InputNormalizingDenominator (:,1) double
    end
    
    %% Cmac Methods
    methods
        function obj = Cmac(nout,nq,nlayers,maxq,minq,beta,nu,maxmemsize)
            %CMAC Construct an instance of this class
            arguments
                nout (1,1) {mustBeNumeric} = 1
                nq (1,1) {mustBeNumeric} = 1
                nlayers (1,1) {mustBeNumeric} = 1
                maxq (:,1) double = 1
                minq (:,1) double = -1
                beta double = 1
                nu double = 1
                maxmemsize (1,1) {mustBeNumeric} = 1e5
            end

            obj@CmacLib.Serializable("cmac");

            obj.NumQ = nq;
            obj.NumLayers = nlayers;
            obj.InputUpperLimit = maxq;
            obj.InputLowerLimit = minq;
            obj.Beta = beta;
            obj.Nu = nu;
            obj.NumOutput = nout;
            obj.NumInput = numel(maxq);

            if numel(maxq) ~= numel(minq)
                error('Limit sizes must match');
            end
            obj.InputNormalizingDenominator = maxq - minq;

            % create hashtable
            hashsize = obj.NumInput*nlayers*nq + nq*nlayers + nq;
            obj.Hashtable = int32(double(maxmemsize)/double(obj.NumInput)*rand(hashsize,1));
            obj.Memsize = max(max(obj.Hashtable));

            % create memory
            obj.Memory = zeros(nout, obj.Memsize);

            % offset
            obj.Offsets = rand(obj.NumInput, nlayers);
        end
        
        function predict = Predict(obj,input)
            %PREDICT Calculates the cmac output.
            arguments
                obj CmacLib.Cmac % Cmac instance object
                input (:,1) double % input
            end

            if sum(size(input) ~= size(obj.InputUpperLimit))
                error("Invalid input size.");
            end

            % normalize input
            input = (input - obj.InputLowerLimit)./obj.InputNormalizingDenominator;
            input = min(input, ones(size(input)));
            input = max(input, zeros(size(input)));

            indices = int32(zeros(obj.NumLayers, 1));
            gammas = zeros(obj.NumLayers, 1);

            % get weight locations and gammas
            for i = 1 : obj.NumLayers
                location = 0.0;
                for j = 1 : obj.NumInput
                    % find the active cell/neuron
                    place = input(j)*double(obj.NumQ - 1) + obj.Offsets(j,i);
                    cell = floor(place);
                    h = place - cell;

                    % calculate basis function
                    if h > 1.0 || h < 0.0
                        error('spline input is outside the range.');
                    end
                    fspline = 16.0*(h^2 - 2.0*h^3 + h^4);
                    gammas(i) = gammas(i) + fspline;

                    % acquire hash for the weights
                    v = cell + 1 + obj.NumQ*(i-1) ...
                        + obj.NumQ*obj.NumLayers*(j-1);
                    location = location + double(obj.Hashtable(int32(v)));
                end
                indices(i) = int32(floor(mod(location,obj.Memsize-1)))+1;
            end
            gammas = gammas/double(obj.NumInput);

            % get the weights
            weights = obj.Memory(:, indices);

            % calculate output
            out = weights*gammas;

            predict = CmacLib.Prediction();
            predict.SetValues(out);
            predict.SetActiveWeightIndices(indices);
            predict.SetActiveWeights(weights);
            predict.SetBasisValues(gammas);
        end

        function adjust = Adjust(obj, e, prediction, d)
            %TRAIN Trains the weights.
            arguments
                obj CmacLib.Cmac % Cmac object
                e (:,1) double % error/correction
                prediction CmacLib.Prediction
                d double % damping
            end
            dw = obj.Beta*(prediction.BasisValues'.*e - obj.Nu*d*prediction.ActiveWeights);
            nw = prediction.ActiveWeights + dw;
            obj.Memory(:, prediction.ActiveWeightIndices) = nw;

            adjust = CmacLib.Adjustment();
            adjust.SetWeightChanges(dw);
        end

        function Zeroize(obj)
            arguments
                obj CmacLib.Cmac
            end
            obj.Memory(:,:) = 0.0;
        end
    end

    %% Serializable Implementation
    methods
        function serialization = Serialize(obj)
            arguments
                obj CmacLib.Cmac
            end
            serialization = CmacLib.Serialization();
            serialization.SetString("TO BE IMPLEMENTED");
        end

        function Deserialize(obj, content)
            arguments
                obj CmacLib.Cmac
                content string
            end
        end
    end
end

