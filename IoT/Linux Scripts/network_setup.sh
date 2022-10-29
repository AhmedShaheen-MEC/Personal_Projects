#!/bin/bash

if ping -c 1 google.com &> /dev/null; then
    echo "Success"
else
    systemctl restart networking
    echo "Network Interfaces Restarted"
    sleep 10
fi
