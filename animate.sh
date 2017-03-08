#!/bin/bash
mkdir frames 2> /dev/null
rm frames/*
make && ./MP_2_TEST && mv a*.png frames
cd frames
ffmpeg -framerate 24 -i a%03d.png video.mp4
xdg-open video.mp4


