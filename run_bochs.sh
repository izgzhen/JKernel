if [ -z $BXBOOT ]; then
    export BXBOOT="cdrom"
fi

sudo -E bochs -f bochsrc.txt -q