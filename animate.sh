#!/bin/bash
rm frames/*
make && ./rendgine && mv a*.png frames && xdg-open frames/a0.png

