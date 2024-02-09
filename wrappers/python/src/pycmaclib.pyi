# pycmaclib module.

# Python type hint file to provide static type information about pycmaclib module.

class IResult:
    """The interface to the result.
    """

    def IsSuccessful(self) -> bool:
        """Indicates if an operation was successful.

        Returns:
            bool: Success.
        """
        ...

    def GetMessage(self) -> str:
        """If not successful, a failure message is provided.

        Returns:
            str: The failure message.
        """
        ...

class ISerialization (IResult):
    """The interface to the serialization data.
    """

    def GetString(self) -> str:
        """The string from the resulting serialization process.

        Returns:
            str: The serialized string.
        """
        ...

class IPrediction (IResult):
    """The interface to the prediction output.
    """

    def GetValues(self) -> list[float]:
        """Get the calculated multiplication and accumulation \
            of basis and active weights.

        Returns:
            list[float]: The cmac output.
        """
        ...

    def GetActiveWeightIndices(self) -> list[int]:
        """Get the indices of the active weights.

        Returns:
            list[int]: The active weight indices.
        """
        ...

    def GetActiveWeights(self) -> list[list[float]]:
        """Get the values of the active weights.

        Returns:
            list[float]: The active weight values.
        """
        ...

    def GetBasisValues(self) -> list[float]:
        """Get the basis function values.

        Returns:
            list[float]: The basis function values.
        """
        ...

class IAdjustment (IResult):
    """The interface to the weight adjustment data.
    """

    def GetWeightChanges(self) -> list[list[float]]:
        """Get the amount the each active weight changed.

        Returns:
            list[float]: The weight change.
        """
        ...

class ISerializable:
    """An object that can be serialized and de-serialized.
    """

    def Serialize(self) -> ISerialization:
        """Serializes the object in its own unique format.

        Returns:
            ISerialization: The serialized string.
        """
        ...

    def Deserialize(self, content: str) -> IResult:
        """Deserializes the content into its member variables.

        Args:
            content (str): A valid deserializable content.

        Returns:
            IResult: Indicates if the deserialize operation was successful or not.
        """
        ...

    def GetExtension(self) -> str:
        """Gets the extension of the serializable object

        Returns:
            str: The extension of the serializable object
        """
        ...

class IMarshaller:
    """Handles saving and loading of serializable objects
    """

    def Save(self, serializable: ISerializable, directory: str, \
        filename: str) -> IResult:
        """Save the serializable object.

        Args:
            serializable (ISerializable): The object to save.
            directory (str): Folder to save the serializable object in.
            filename (str): The name of the object to save.

        Returns:
            IResult: Indicates if the save operation was successful or not.
        """
        ...

    def Load(self, serializable: ISerializable, filepath: str) -> IResult:
        """Fills the contents of the serialzable object.

        Args:
            serializable (ISerializable): The object to fill.
            filepath (str): The location of the file that contains \
                the serializable object's contents.

        Returns:
            IResult: Indicates if the load operation was successful or not.
        """
        ...

class ICmac (ISerializable):
    """The interface to the Cerebellar Model Articulation Controller (CMAC)
    """

    def Predict(self, input: list[float]) -> IPrediction:
        """Acquires active weights and associated basis values, \
            then multiply and sum to produce an output.

        Args:
            input (list[float]): The states.

        Returns:
            IPrediction: The prediction result.
        """
        ...

    def Adjust(self, correction: list[float], prediction: IPrediction, \
        damping: float) -> IAdjustment:
        """Train the weights of the Cmac.

        Args:
            correction (list[float]): The error of the prediction.
            prediction (IPrediction): Contains indices of weights and basis values.
            damping (float): Additional damping to further reduce chances of overfitting.

        Returns:
            IAdjustment: The adjustment result.
        """
        ...

    def Zeroize(self) -> IResult:
        """Sets all the weights in memory to zero, untraining the Cmac.

        Returns:
            IResult: The operation result.
        """
        ...

class Factory:
    """Creates Cmac objects.
    """

    def CreateCmac(self, numQ: int, numLayers: int, maxmem: int, \
        numOut: int, upper: list[float], lower: list[float], \
        beta: float, nu: float) -> ICmac:
        """Create a raw and untrained Cmac.

        Args:
            numQ (int): The number of quantizations.
            numLayers (int): Number of layers (which would indicate \
                number of active weights)
            maxmem (int): Maximum potential memory index or memory size.
            numOut (int): Number of outputs.
            upper (list[float]): Upper limits of the Predict method inputs.
            lower (list[float]): Lower limits of the Predict method inputs.
            beta (float): Learning rate.
            nu (float): Damping coefficient.

        Returns:
            ICmac: The cmac.
        """
        ...

    def CreateDefaultCmac(self) -> ICmac:
        """Creates a Cmac with default values.

        Returns:
            ICmac: The cmac.
        """
        ...

    def CreateMarshaller(self) -> IMarshaller:
        """Creates an instance of IMarshaller.

        Returns:
            IMarshaller: The marshaller object.
        """
        ...