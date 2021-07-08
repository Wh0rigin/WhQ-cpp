#!/bin/bash
gcc -I ../include -o Build_SH ../src/TaskQueue.cpp ../src/ThreadPool.cpp ../src/main.cpp -lstdc++ -lpthread