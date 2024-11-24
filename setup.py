from setuptools import setup, Extension

module = Extension('mymodule', sources=['mymodule.c'])

setup(
    name='mymodule',
    version='1.0',
    description='Example C module for Python',
    ext_modules=[module],
)
