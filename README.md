# scalam
Smart search for upgrade paths

## About

When building large software systems, such as an operating system, typically figuring out dependencies and getting everything installed in the appropriate sequence is something done manually and which can be quite time consuming. This is an experimental project to see if sampled search can be applied to the problem of determining dependency structure within a heterogeneous software system. You could also say that it's an attempt to get to the latest commits for each program within a system without breaking anything and with some semi-automated resolution of issues.

The basic parameters are:

 - All programs are git repositories
 - Use a genetic algorithm to represent systems of programs and their commit checkouts, possibly being installed in multiple stages
 - Apply sampled search with online dependency matrix probability updates to bias selection
 - Parallelize as much as possible, so this could be run on many computers simultaneously
 - Integrate with a build system which returns compilation status, and preferably also unit test results

In the longer term future a combination of continuous integration plus sampled search for resolutions of issues where possible may be the way that large software systems are constructed. Of course, there will always be compile issues which are nothing to do with missing or inappropriate dependencies and so this type of search is not a panacea, but it might be a useful assistant.

Compiling large software systems is slow. Improvements can be made with artifact caches, but even so this will still be evolution at a glacial pace. With enough compute power though maybe it's feasible compared to having human experts do the same thing.

## Installation

On a Debian based system:

``` bash
sudo apt-get install python3-pip
sudo pip3 install ez_setup
```

Install GitPython:

``` bash
git clone https://github.com/gitpython-developers/GitPython
cd GitPython
sudo python3 setup.py install
```

## To run unit tests

``` bash
cd tests
python3 tests.py
```
