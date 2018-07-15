# -*- coding: utf-8 -*-
"""
Example for using Helios DAC libraries in python (using C library with ctypes)

NB: If you haven't set up udev rules you need to use sudo to run the program for it to detect the DAC.
"""

import ctypes

#Define point structure
class HeliosPoint(ctypes.Structure):
    #_pack_=1
    _fields_ = [('x', ctypes.c_uint16),
                ('y', ctypes.c_uint16),
                ('r', ctypes.c_uint8),
                ('g', ctypes.c_uint8),
                ('b', ctypes.c_uint8),
                ('i', ctypes.c_uint8)]

#Load and initialize library
HeliosLib = ctypes.cdll.LoadLibrary("./libHeliosDacAPI.so")
numDevices = HeliosLib.OpenDevices()
print("Found ", numDevices, "Helios DACs")

#Create sample frames
frames = [0 for x in range(30)]
frameType = HeliosPoint * 1000
x = 0
y = 0
for i in range(30):
    y = round(i * 0xFFF / 30)
    frames[i] = frameType()
    for j in range(1000):
        if (j < 500):
            x = round(j * 0xFFF / 500)
        else:
            x = round(0xFFF - ((j - 500) * 0xFFF / 500))

        frames[i][j] = HeliosPoint(int(x),int(y),255,255,255,255)

#Play frames on DAC
for i in range(150):
    for j in range(numDevices):
        while (HeliosLib.GetStatus(j) == 0): #Wait for ready status
            pass
        HeliosLib.WriteFrame(0, 30000, 0, ctypes.pointer(frames[i % 30]), 1000) #Send the frame


HeliosLib.CloseDevices()
