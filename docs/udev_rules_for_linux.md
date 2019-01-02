# How to access the Helios DAC without requiring root privileges

Linux systems normally require running with `sudo` to access USB devices. `udev` rules can be used to allow access without requiring root privileges.


(This solution has been tested on a Raspberry Pi running Raspbian Stretch 2018-06-27. Other flavors of Linux may work differently.)

1. Create a file *heliosdac.rules* in /etc/udev with the contents:

		ACTION=="add", SUBSYSTEM=="usb", ATTRS{idVendor}=="1209", ATTRS{idProduct}=="e500", MODE="0660", GROUP="plugdev"

1. Create a link in /etc/udev/rules.d to *heliosdac.rules*:

		cd /etc/udev/rules.d
		sudo ln -s /etc/udev/heliosdac.rules 011_heliosdac.rules
	
1. Make sure the user account communicating with the DAC is in the *plugdev* group. On a Raspberry Pi, the "pi" user is in the *plugdev* group by default.

1. Issue the command `sudo udevadm control --reload` (or restart the computer).

## Confirming a device's vendor and product IDs

1. Disconnect the device.
1. In a terminal window, run the command `dmesg --follow`.
1. Connect the device.

Example output:

	[ 8239.754638] usb 1-1.4: new full-speed USB device number 16 using dwc_otg
	[ 8244.968718] usb 1-1.4: New USB device found, idVendor=1209, idProduct=e500
	[ 8244.968731] usb 1-1.4: New USB device strings: Mfr=1, Product=2, SerialNumber=0
	[ 8244.968739] usb 1-1.4: Product: Helios Laser DAC
	[ 8244.968748] usb 1-1.4: Manufacturer: Gitle Mikkelsen
	
These are the idVendor and idProduct values used in *heliosdac.rules*.