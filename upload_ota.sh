#!/bin/bash
# ./upload_ota.sh NAME [IP ADDRESS]

set -e

tools_dir=$HOME/.platformio/packages/framework-arduinoespressif8266/tools
build_dir=.pio/build/$1

pio run -e $1
gzip -9kf $build_dir/firmware.bin

if [ -n "$2" ]; then
  hostip=$(ifconfig $(route | grep default | sed -E 's/.+[0-9]\s+[0-9]\s+[0-9]\s+(.+)$/\1/') | grep -Eo 'inet (addr:)?([0-9]*\.){3}[0-9]*' | grep -Eo '([0-9]*\.){3}[0-9]*')
  python3 $tools_dir/espota.py -i $2 -I $hostip -f $build_dir/firmware.bin.gz
fi
