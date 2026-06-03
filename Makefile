all:
	gcc x_wrapper.c -o x_wrapper
	sudo setcap cap_sys_admin+ep x_wrapper

install: all
	install -m 755 x_wrapper /usr/local/bin/x_wrapper
	sudo setcap cap_sys_admin+ep /usr/local/bin/x_wrapper
