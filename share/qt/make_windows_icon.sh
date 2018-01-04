#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/carboncoin.png
ICON_DST=../../src/qt/res/icons/carboncoin.ico
convert ${ICON_SRC} -resize 16x16 carboncoin-16.png
convert ${ICON_SRC} -resize 32x32 carboncoin-32.png
convert ${ICON_SRC} -resize 48x48 carboncoin-48.png
convert carboncoin-16.png carboncoin-32.png carboncoin-48.png ${ICON_DST}

