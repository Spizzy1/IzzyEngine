Import('env')

src_files = [
    "src/cwmath.c",
    "src/cwstring.c",
    "src/logger.c"
]

env.Append(CPPPATH="#firstparty/CWE/include")
env.Library("CWE", src_files)
