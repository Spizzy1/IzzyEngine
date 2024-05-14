import glob
Import('env')
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
print(env['CPPPATH'])
engine = env.Program("IzzyEngine", src_files)

print("Copying extra dependent files")
ext = glob.glob("../resources/*")
print(f"files: {ext}")
env.Install("./",ext)
