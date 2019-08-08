
cli_app:
	@mkdir -p bin/
	make -C src/cli
	mv src/cli/program bin/ad9850_cli

gui_app:
	@mkdir -p bin/
	qmake -o src/gui/Makefile src/gui/ad9850_gui.pro
	make -C src/gui
	mv src/gui/program bin/ad9850_gui

test_gui: gui_app
	./src/gui/program

install:
	install -D -t $(DESTDIR)$(PREFIX)/bin bin/ad9850_gui

clean:
	-make -C src/gui/ clean
	-make -C src/cli/ clean
	-rm src/gui/Makefile
	-rm src/gui/program
	-rm -rf bin
