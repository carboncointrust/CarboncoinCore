
Debian
====================
This directory contains files used to package carboncoind/carboncoin-qt
for Debian-based Linux systems. If you compile carboncoind/carboncoin-qt yourself, there are some useful files here.

## carboncoin: URI support ##


carboncoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install carboncoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your carboncoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin128.png` to `/usr/share/pixmaps`

carboncoin-qt.protocol (KDE)

