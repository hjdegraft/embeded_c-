#!/bin/bash

echo 0 > /sys/class/leds/pca963x\:red/brightness
echo 0 > /sys/class/leds/pca963x\:green/brightness
echo 0 > /sys/class/leds/pca963x\:blue/brightness

sleep 10s

echo 55 > /sys/class/leds/pca963x\:red/brightness
echo 255 > /sys/class/leds/pca963x\:green/brightness
echo 255 > /sys/class/leds/pca963x\:blue/brightness

sleep 10s

echo 255 > /sys/class/leds/pca963x\:red/brightness
echo 255 > /sys/class/leds/pca963x\:green/brightness
echo 0 > /sys/class/leds/pca963x\:blue/brightness

sleep 10s

echo 0 > /sys/class/leds/pca963x\:red/brightness
echo 0 > /sys/class/leds/pca963x\:green/brightness
echo 255 > /sys/class/leds/pca963x\:blue/brightness
echo timer > /sys/class/leds/pca963x\:blue/trigger
