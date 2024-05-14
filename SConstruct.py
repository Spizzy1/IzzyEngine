import os
import sys
env = Environment(CPPPATH=["#include"])

selected_platform = ""
if selected_platform == "":
    # Missing `platform` argument, try to detect platform automatically
    if (
        sys.platform.startswith("linux")
        or sys.platform.startswith("dragonfly")
        or sys.platform.startswith("freebsd")
        or sys.platform.startswith("netbsd")
        or sys.platform.startswith("openbsd")
    ):
        selected_platform = "linuxbsd"
    elif sys.platform == "darwin":
        selected_platform = "macos"
    elif sys.platform == "win32":
        selected_platform = "windows"
    print(f"System platform: {sys.platform}")

if selected_platform != "":
    print(f"Automatically detected platform: {selected_platform}")

libpath = ["." , "#thirdparty/glew", "#thirdparty/glfw"]
session = ""
env['selected_platform'] = selected_platform
if selected_platform == "windows":
    env["LIBS"] = ["glfw", "GLEW", "opengl32", "User32", "Gdi32", "Shell32"]
    env.Append(LIBPATH=["C:\lib", "D:\lib"]+libpath)
elif selected_platform == "linuxbsd":
    env["LIBS"] = ["glfw", "GLEW", "GL", "m"]
    env.Append(LIBPATH=['/usr/lib','/usr/local/lib']+libpath)
Export('env')
SConscript('thirdparty/glfw/SConscript')
SConscript('thirdparty/glew/SConscript')

SConscript('src/SConscript.py', variant_dir='build')



