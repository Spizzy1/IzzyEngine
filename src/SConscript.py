import glob
Import('env')
src_files = [
    "Events/events.c",
    "shaders/shaders.c",
    "characters/characters.c",
    "meshes/meshes.c",
    "textures/textures.c",
    "Physics/physics.c",
    "main.c"
]

LIBS =["GLEW", "glfw", "CWE"]+env["LIBS"]
print("Starting build process!")
print(env['CPPPATH'])

env.Tool('compilation_db')
env.CompilationDatabase()

engine = env.Program("IzzyEngine", src_files, LIBS=LIBS)

print("Copying extra dependent files")
ext = glob.glob("../resources/*")
print(f"files: {ext}")
env.Install("./",ext)
