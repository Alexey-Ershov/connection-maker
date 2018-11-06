#!/usr/bin/env bash

MY_TOPO=./lvk_triangle.py
MAIN_CONTROLLER_IP=0.0.0.0
MAIN_CONTROLLER_PORT=6653
TESTING_CONTROLLER_IP=127.0.0.1
TESTING_CONTROLLER_PORT=6633

sudo mn --custom $MY_TOPO \
        --topo mytopo \
        --switch ovsk,protocols=OpenFlow13 \
        --controller remote,ip=$MAIN_CONTROLLER_IP,port=$MAIN_CONTROLLER_PORT \
        --controller \
                remote,ip=$TESTING_CONTROLLER_IP,port=$TESTING_CONTROLLER_PORT
