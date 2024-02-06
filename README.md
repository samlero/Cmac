<h2 align="center">
🧠
Cerebellar Model Articulation Controller (CMAC)
🎛️
</h2>

<a href="./LICENSE"
    style="display: block; text-align: center;">
    <img src="https://img.shields.io/badge/License-GPL--3.0-blue.svg" alt="License: GPL-3.0">
</a>

###
An artificial neural network based on a human cerebellum. It is mostly used in control systems applications due to its fast calculation and training; it does so by only activating or operating on a subset of the weights at a time, thus minimizing the amount of multiplication and addition operations. 

The core implementation is written in C++ and packaged using CMake. Other API wrappers include:
1. MATLAB (must be manually built)
2. Python
3. Julia (in-progress)

The APIs are a work in progress and more will come. If a specific language API is needed for an application, feel free to open an issue about it. We will get to it as soon as we can. 

## 🌟 CAPABILITIES
The CMAC implementation can do the following:
1. Predict: calculates the output of a CMAC by accumulating all active weights scaled by their corresponding basis function values.
2. Adjust: trains the active weights based on a corrective term, while also providing a damping term to avoid overlearning (or bursting). 
3. Save: writes the contents of a CMAC to a file.
4. Load: loads the contents of a CMAC-saved file.
5. Zeroize: sets all the weights back to zero, untraining the CMAC.

The Predict and Adjust capabilities are available in the ICmac interface while the Save and Load capabilities in IMarshaller. 

Predict and Adjust are used for near continuous calculation of CMAC outputs for feedforward control, and weight training for adaptive capabilities. The speed limitation will depend on the number of Predict inputs and number of layers (or active weights). The more of either the slower the calculation gets, so tune the CMAC parameters properly. 

Save and Load are functions are typically used when the user wants to save a trained CMAC for later use. 

## 📦 INSTALLATION
### Windows
Download the latest [CmacLib-x.x.x-win64.exe](https://github.com/samlero/Cmac/releases) and follow the installation wizard.

### Linux
Download the latest [CmacLib-x.x.x-Linux.tar.gz](https://github.com/samlero/Cmac/releases) and unzip.

## 🏗️ BUILD
A couple of build scripts were generated to ease building the installers. Scripts with *_win_* are used under the Windows environment and the others under Linux. 

## 💻 USAGE
The following example illustrates how the capabilities mentioned above could be used. 
### C++
See the unit tests in [tests/CmacTests.cpp](tests/CmacTests.cpp) and [tests/MarshallerTests.cpp](tests/MarshallerTests.cpp). 
### Matlab
See the unit tests in [api/matlab/usage.m](api/matlab/usage.m).
### Python
See the unit tests in [api/python/tests/test_cmac.py](api/python/tests/test_cmac.py) and [api/python/tests/test_serializable.py](api/python/tests/test_serializable.py).

## ⚠️ DISCLAIMER
The repository is thoroughly tested and utilized by the authors in a Windows environment using the MATLAB API for control systems research.
This is also a good indication that the core C++ is functional under a Windows environment. 
Linux works in theory, more testing to be done on it.