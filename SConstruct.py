import os
import sys
env = Environment(LIBS=["glfw", "GLEW", "GL", "m"], CPPPATH=["#include"], LIBPATH=[".", '/usr/lib','/usr/local/lib', "#thirdparty/glew", "#thirdparty/glfw"])

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

    if selected_platform != "":
        print(f"Automatically detected platform: {selected_platform}")

session = ""
env['selected_platform'] = selected_platform

Export('env')
SConscript('thirdparty/glfw/SConscript')
SConscript('thirdparty/glew/SConscript')

SConscript('src/SConscript.py', variant_dir='build')



