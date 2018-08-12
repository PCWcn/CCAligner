#!/bin/sh
find /home/wpc/sample/1 -type d -exec mkdir -p /home/wpc/Pctool3/token/{} \;
./bin/c1c /home/wpc/sample/1
