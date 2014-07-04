import os
from setuptools import setup, find_packages

def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()

def requirements(fname):
	for line in open(os.path.join(os.path.dirname(__file__), fname)):
		yield line.strip()

setup(
	name = "deltas",
	version = read('VERSION').strip(),
	author = "Aaron Halfaker",
	author_email = "ahalfaker@wikimedia.org",
	description = ("A library for performing generating deltas (A.K.A sequences of operations) representing the difference between two sequences of comparable tokens."),
	license = "MIT",
	url = "https://github.com/halfak/Deltas",
	packages=find_packages(),
	long_description = read('README.rst'),
	install_requires = [],
	classifiers=[
		"Development Status :: 4 - Beta",
		"License :: OSI Approved :: MIT License",
		"Topic :: Software Development :: Libraries :: Python Modules"
	],
)
