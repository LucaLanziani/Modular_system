cmake_minimum_required(VERSION 2.6)

SET(lib_src primo.c)
ADD_DEFINITIONS(-fPIC)

ADD_LIBRARY(primo MODULE ${lib_src})
