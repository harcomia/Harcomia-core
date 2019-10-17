
Debian
====================
This directory contains files used to package hcad/hca-qt
for Debian-based Linux systems. If you compile hcad/hca-qt yourself, there are some useful files here.

## hca: URI support ##


hca-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install hca-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your hcaqt binary to `/usr/bin`
and the `../../share/pixmaps/hca128.png` to `/usr/share/pixmaps`

hca-qt.protocol (KDE)

