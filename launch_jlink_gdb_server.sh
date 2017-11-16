#!/usr/bin/env bash

JLinkGDBServer -device MK64FN1M0XXX12 -endian little -if swd -speed 4000 -vd -ir -localhostonly 1  -strict -timeout 0