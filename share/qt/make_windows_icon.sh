#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/testkojn.png
ICON_DST=../../src/qt/res/icons/testkojn.ico
convert ${ICON_SRC} -resize 16x16 testkojn-16.png
convert ${ICON_SRC} -resize 32x32 testkojn-32.png
convert ${ICON_SRC} -resize 48x48 testkojn-48.png
convert testkojn-16.png testkojn-32.png testkojn-48.png ${ICON_DST}

