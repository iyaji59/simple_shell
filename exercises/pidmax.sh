#!/bin/bash
pid_max=$(cat /proc/sys/kernel/pid_max)
echo"The maximum process ID value is: $pid_max"
