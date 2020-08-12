#!/bin/bash

APP=lab2
BSP_DIR=../../bsp
BSP=lab2
CORE_DIR=../../hardware/de2_nios2_mpsoc
SOPCINFO=nios2_mpsoc
SOF=de2_nios2_mpsoc
CPU=cpu_0

# Create ELF-file
make

# Download Hardware to Board
#
#echo ""
#echo "***********************************************"
#echo "Download hardware to board"
#echo "***********************************************"
#echo ""
#
#nios2-configure-sof $CORE_DIR/$SOF.sof
#
# Start Nios II Terminal

echo ""
echo "Start NiosII terminal ..."

gnome-terminal -e "nios2-terminal -i 0" &

echo ""
echo "***********************************************"
echo "Download software to board"
echo "***********************************************"
echo ""

nios2-download -g $APP.elf --cpu_name $CPU --jdi $CORE_DIR/$SOF.jdi
