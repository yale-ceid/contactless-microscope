# Contactless Microscope

## Table of Contents

- [Contactless Microscope](#contactless-microscope)
  - [Table of Contents](#table-of-contents)
  - [Connecting the microscope to a TV display](#connecting-the-microscope-to-a-tv-display)

## Connecting the microscope to a TV display

The digital microscope has a USB-out interface, basically a webcam. We can connect to it using Zoom or VLC. Zoom has some color-adjustment issues so VLC is better.

Showing the webcam in VLC is pretty straight forward. Just go to Media > Open Capture Device and click "Play" and it should open up.

But suppose you don't want to have a dedicated computer to be running at all times, and just want to hookup the webcam feed to a big display. We can do this pretty easily with a Raspberry Pi.

All you need is VLC to execute on startup. You can do this by opening up a Terminal and typing in the following commands:

```bash
cd /etc/xdg/autostart
sudo nano start_microscope.desktop
```

Now, a text editor will open up. Just paste in the following content:

```
[Desktop Entry]
Type=Application
Name=Microscope
Comment=Starts VLC with Microscope
NoDisplay=false
Exec=vlc v4l2:// --fullscreen
NotShowIn=GNOME;KDE;XFCE;
```

The most important part of the above file is `vlc v4l2:// --fullscreen`. We are telling VLC to open the webcam feed (`vl42://`) in fullscreen mode. The webcam feed might NOT always be `vl42://`. In this case, you can go to VLC > Media > Open Capture Device > Show More Options and copy the MRL from there.

To save and close the text editor, first press Ctrl+X and click Y to save changes. Now reboot the Raspberry Pi and VLC should open up with the webcam feed.
