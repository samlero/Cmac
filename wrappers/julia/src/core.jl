#!/usr/bin/julia

export cmaclib_core
"""
The path to the cmac shared library.
"""
cmaclib_core::String = ""

# The file paths for the shared library depending on the operating system.
if Sys.islinux()
    cmaclib_core = "./libCmacLibD.so"
elseif Sys.iswindows()
    cmaclib_core = "./CmacLibD.dll"
elseif Sys.isapple() || Sys.isbsd()
    cmaclib_core = "./libCmacLibD.dylib"
end