
cli_program:
	make -C cli

gui_program:
	qmake -o gui/Makefile gui/ad9850_gui.pro
	make -C gui

test_gui:gui_program
	./gui/program

clean:
	-make -C gui/ clean
	-make -C cli/ clean
	-rm gui/Makefile
	-rm gui/program
