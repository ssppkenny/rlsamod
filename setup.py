from distutils.core import setup, Extension
import numpy

extension = Extension(
    "rlsamod", ["rlsa.c", "rlsamod.c"], include_dirs=["include", numpy.get_include()]
)
setup(name="rlsamod", version="0.0.8", ext_modules=[extension])
