#!/usr/bin/env bash

MY_TOPO=./lvk_triangle.py
CONTROLLER_IP=0.0.0.0
CONTROLLER_PORT=6653

sudo mn --custom $MY_TOPO \
        --topo mytopo \
        --switch ovsk,protocols=OpenFlow13 \
        --controller remote,ip=$CONTROLLER_IP,port=$CONTROLLER_PORT
