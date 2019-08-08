
gui_program:
	qmake -o gui/Makefile gui/ad9850_gui.pro
	make -C gui

test:gui_program
	./gui/program

clean:
	-make -C gui/ clean
	-rm gui/Makefile
	-rm gui/program
