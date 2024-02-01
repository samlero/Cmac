# Cerebellar Model Articulation Controller (CMAC)
An artificial neural network based on a human cerebellum. It is mostly used in control systems applications due to its fast calculation and training; it does so by only activating or operating on a subset of the weights at a time, thus minimizing the amount of multiplication and addition operations. 

The core implementation is written in C++ and packaged using CMake. Other API wrappers include:
1. MATLAB: must be manually rebuilt,
2. Python: in-progress,
3. Julia: in-progress.

The APIs are a work in progress and more will come. If a specific language API is needed for an application, feel free to open an issue about it. We will get to it as soon as we can. 

# Capabilities
The CMAC implementation can do the following:
1. Predict: calculates the output of a CMAC by accumulating all active weights scaled by their corresponding basis function values.
2. Adjust: trains the active weights based on a corrective term, while also providing a damping term to avoid overlearning (or bursting). 
3. Save: writes the contents of a CMAC to a file.
4. Load: loads the contents of a CMAC-saved file. 

The Predict and Adjust capabilities are available in the ICmac interface while the Save and Load capabilities in IMarshaller. 

# Usage
The following example illustrates how the capabilities mentioned above could be used. 

> TODO: PUT CODE HYPERLINK HERE

# Stats
> TODO: ADD BUILD AND TEST RESULTS HERE





