#!/bin/sh

### MY ADDS ###
# bash $HOME/.config/.fehbg
feh --bg-scale /home/kvl/Pictures/wallpapers/Spaceman-gruvbox.png &
# nitrogen --restore &
xset r rate 350 75 &
setxkbmap -option caps:escape &
picom -b &
xrandr --output HDMI-0 --mode 1920x1080 --rate 144 &
kitty -e sudo intel-undervolt apply &
brightnessctl -d "intel_backlight" set 0% &
xinput disable "SYNA7DB5:01 06CB:CD41 Touchpad" &
xinput disable "AT Translated Set 2 keyboard" &
xinput disable "HD User Facing: HD User Facing" &
xsetroot -cursor_name cross & 
nvidia-settings -a "DigitalVibrance=300" &
# tdrop -ma -w -4 -y "12" -s dropdown kitty &
