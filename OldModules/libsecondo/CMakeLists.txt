cmake_minimum_required(VERSION 2.8)

SET(lib secondo)
ADD_DEFINITIONS(-fPIC)

ADD_LIBRARY(${lib} MODULE ${lib}.c)
