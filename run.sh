#! /bin/sh

sudo ./bin/backend &
sudo node ./

sudo pkill backend
sudo pkill node
