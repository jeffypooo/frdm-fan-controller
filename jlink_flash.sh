#!/usr/bin/env bash

MCU=MK64FN1M0XXX12
INTF=SWD
SPD=4000

echo "*** JLink Configuration ***"
echo "Core: ${MCU}"
echo "Interface: ${INTF}"
echo "Speed (KHz): ${SPD}"

JLinkExe -device $MCU -if $INTF -speed $SPD -CommanderScript flash.jlink
