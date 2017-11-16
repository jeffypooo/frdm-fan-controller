#!/usr/bin/env bash

GDB_INIT=~/.gdbinit

# Check for existing .gdbinit in HOME
if [ -e $GDB_INIT ]
then
    echo "Found existing .gdbinit in ${HOME}, making a copy..."
    mv $GDB_INIT ~/.gdbinit.bak
fi
echo -n "Generating gdb init file..."
touch $GDB_INIT
echo "# Run after connecting with target" >> $GDB_INIT
echo "define target hookpost-remote" >> $GDB_INIT
echo "# Halt and load file" >> $GDB_INIT
echo "monitor halt" >> $GDB_INIT
echo "load" >> $GDB_INIT
echo "# Reset target and set a temporary breakpoint at main" >> $GDB_INIT
echo "monitor reset" >> $GDB_INIT
echo "tbreak main" >> $GDB_INIT
echo "done!"
echo ""
echo "File Contents:"
cat $GDB_INIT


