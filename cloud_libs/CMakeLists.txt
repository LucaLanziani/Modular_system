CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE_DIRECTORIES(../shared_libs)

ADD_LIBRARY(gest_module SHARED gest_module.c)
ADD_LIBRARY(data_exchange SHARED data_exchange.c)
ADD_LIBRARY(gest_thread SHARED gest_thread.c)

