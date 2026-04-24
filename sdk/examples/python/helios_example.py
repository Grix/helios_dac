# -*- coding: utf-8 -*-
"""
Example for using Helios DAC libraries in Python (using C library with ctypes).

This module provides a unified interface for both Windows and Linux platforms.

NB: If you haven't set up udev rules on Linux, you need to use sudo to run 
the program for it to detect the DAC.
"""

import ctypes
import platform


class HeliosPoint(ctypes.Structure):
    """Point structure for Helios DAC frames."""
    _fields_ = [('x', ctypes.c_uint16),
                ('y', ctypes.c_uint16),
                ('r', ctypes.c_uint8),
                ('g', ctypes.c_uint8),
                ('b', ctypes.c_uint8),
                ('i', ctypes.c_uint8)]


def load_library():
    """
    Load the appropriate Helios DAC library for the current platform.
    
    Returns:
        ctypes.CDLL: The loaded library instance
        
    Raises:
        OSError: If the library cannot be found or loaded
    """
    system = platform.system()
    
    if system == "Windows":
        lib_path = ".\\HeliosLaserDAC.dll"
    elif system == "Linux":
        lib_path = "./libHeliosDacAPI.so"
    else:
        raise OSError(f"Unsupported platform: {system}")
    
    try:
        lib = ctypes.cdll.LoadLibrary(lib_path)
        return lib
    except OSError as e:
        raise OSError(f"Failed to load Helios DAC library from {lib_path}: {e}")


def create_sample_frames(num_frames=30, points_per_frame=1000):
    """
    Generate sample animation frames with a sawtooth pattern.
    
    Creates frames where:
    - Y coordinate varies across frames (0 to 0xFFF)
    - X coordinate traces a triangle wave within each frame
    - All points are white with full intensity
    
    Args:
        num_frames (int): Number of frames to generate. Default: 30
        points_per_frame (int): Points per frame. Default: 1000
        
    Returns:
        list: List of frame arrays, each containing HeliosPoint structures
    """
    frames = [0 for _ in range(num_frames)]
    frame_type = HeliosPoint * points_per_frame
    
    for i in range(num_frames):
        y = round(i * 0xFFF / num_frames)
        frames[i] = frame_type()
        
        for j in range(points_per_frame):
            # Triangle wave pattern for X coordinate
            if j < points_per_frame // 2:
                x = round(j * 0xFFF / (points_per_frame // 2))
            else:
                x = round(0xFFF - ((j - points_per_frame // 2) * 0xFFF / (points_per_frame // 2)))
            
            frames[i][j] = HeliosPoint(int(x), int(y), 255, 255, 255, 255)
    
    return frames


def play_frames(lib, frames, num_iterations=150, points_per_frame=1000, pps=30000):
    """
    Play frames on all connected Helios DAC devices.
    
    Args:
        lib (ctypes.CDLL): The loaded Helios DAC library
        frames (list): List of frame arrays to play
        num_iterations (int): Number of times to cycle through all frames. Default: 150
        points_per_frame (int): Points per frame. Default: 1000
        pps (int): Points per second playback speed. Default: 30000
    """
    num_devices = lib.OpenDevices()
    print(f"Found {num_devices} Helios DACs")
    
    if num_devices == 0:
        print("No devices found. Exiting.")
        lib.CloseDevices()
        return
    
    try:
        for i in range(num_iterations):
            for j in range(num_devices):
                status_attempts = 0
                # Make 512 attempts for DAC status to be ready
                while status_attempts < 512 and lib.GetStatus(j) != 1:
                    status_attempts += 1
                
                # Send the frame
                lib.WriteFrame(j, pps, 0, ctypes.pointer(frames[i % len(frames)]), points_per_frame)
    finally:
        lib.CloseDevices()


def main():
    """Run the example."""
    lib = load_library()
    frames = create_sample_frames(num_frames=30, points_per_frame=1000)
    play_frames(lib, frames, num_iterations=150, points_per_frame=1000)


if __name__ == "__main__":
    main()
