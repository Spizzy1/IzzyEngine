env = Environment()
LIBPATH = '/usr/lib:/usr/local/lib'
# Building CWE
print("Building CWE library")
cpath = "CWE/"
env.Library("CWE", [cpath+"cwstring.c"])

src_files = [
    "Events/events.c",
    "shaders/shaders.c",
    "characters/characters.c",
    "meshes/meshes.c",
    "textures/textures.c",
    "CWE/logger.c",
    "main.c"
]

print("Starting build process!")
env.Program("IzzyEngine", src_files, LIBS=['CWE','glfw', 'GLEW', 'GL', 'm'], LIBPATH=[".", LIBPATH], CPPPATH="#include")
