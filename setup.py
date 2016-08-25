import os

from setuptools import find_packages, setup
from distutils.core import setup, Extension

wikitext = Extension('Wikitext',
                     include_dirs = ['deltas/tokenizers'],
                     sources = ['deltas/tokenizers/ctokenize/wikitext_split.c',
                                'deltas/tokenizers/ctokenize/wikitext_split_create.c',
                                'deltas/tokenizers/ctokenize/wikitext_split_tokenfuns.c',
                                'deltas/tokenizers/ctokenize/iterator.c'
                     ])

def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()

def requirements(fname):
    return [line.strip()
            for line in open(os.path.join(os.path.dirname(__file__), fname))]

setup(
    name = "deltas",
    version = "0.3.10",
    author = "Aaron Halfaker",
    author_email = "ahalfaker@wikimedia.org",
    description = "An experimental diff library for generating " + \
                  "operation deltas that represent the " + \
                  "difference between two sequences of comparable items.",
    license = "MIT",
    url = "https://github.com/halfak/Deltas",
    packages=find_packages(),
    long_description = read('README.rst'),
    install_requires = ['yamlconf'],
    ext_modules = [wikitext],
    classifiers=[
        "Programming Language :: Python",
        "Programming Language :: Python :: 3",
        "Development Status :: 3 - Alpha",
        "License :: OSI Approved :: MIT License",
        "Topic :: Software Development :: Libraries :: Python Modules",
        "Intended Audience :: Developers",
        "Operating System :: OS Independent",
        "Topic :: Text Processing :: Linguistic",
        "Topic :: Text Processing :: General",
        "Topic :: Utilities",
        "Topic :: Scientific/Engineering"
    ]
)
