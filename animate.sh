#!/bin/bash
rm frames/*
make && ./rendgine && mv a*.png frames
cd frames
ffmpeg -framerate 24 -i a%03d.png video.mp4
xdg-open video.mp4


