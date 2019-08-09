README
======


Description
-----------

*ad9850_rpi* containst CLI and GUI application for interfacing ad9850 module with RaspberryPi.

WiringPi is used for accessing GPIO pins <http://wiringpi.com/>.

CLI application is written around cxxopts parser library <https://github.com/jarro2783/cxxopts>.

GUI application is written in qt5 <https://www.qt.io/>.


Compilation and installation
----------------------------

- To compile type: `make`
- Optionally use `sudo make install` to install to /bin/


Usage
-----

Both CLI and GUI applications provide the same functionality.

### CLI application

CLI application is written around cxxopts argument parser libraries, but it is included, so no installation is needed.

WiringPi is used for GPIO access.

To see available commands of ad9850_cli type:

	ad9850_cli --help

Available options are:

    --start arg  start with frequency
    --time arg   run for time in ms
    --stop       stop ad9850
    --help       Print help

Example of usage:

    ad9850_cli --start 1000 --time 500

### GUI application

GUI application is written in qt5 framework.

Qt must be installed for builing.

WiringPi is used for GPIO access.

![GUI run](https://github.com/Risto97/ad9850_rpi/blob/master/docs/img/ad9850_gui_run.png)
![GUI run for](https://github.com/Risto97/ad9850_rpi/blob/master/docs/img/ad9850_gui_run_for.png)
![GUI sweep](https://github.com/Risto97/ad9850_rpi/blob/master/docs/img/ad9850_gui_sweep.png)
