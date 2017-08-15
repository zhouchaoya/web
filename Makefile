ROOT_PATH=$(shell pwd)
CONF=$(ROOT_PATH)/conf
PLUGIN=$(ROOT_PATH)/plugin
WWWROOT=$(ROOT_PATH)/wwwroot
SQL=$(ROOT_PATH)/conn_mysql
FLAGS=-D_STDOUT_ #D_DEBUG_#
LDFLAGS=-lpthread
src=httpd.c main.c
cc=gcc
bin=httpd
obj=$(shell echo $(src) | sed 's/\.c/\.o/g')

.PHONY:all
all:$(bin) cgi

$(bin):$(obj)
	$(cc) -o $@ $^ $(LDFLAGS)
%.o:%.c
	$(cc) -c $< $(FLAGS)
cgi:
	cd $(WWWROOT)/cgi_bin;make;cp math_cgi $(ROOT_PATH);cd -
	cd $(SQL);make;cp insert_cgi $(ROOT_PATH);cp select_cgi $(ROOT_PATH);cd -

.PHONY:clean
clean:
	rm -rf $(bin) *.o output;cd $(WWWROOT)/cgi_bin;make clean;cd -
	cd $(SQL);make clean;cd -;rm -f insert_cgi select_cgi math_cgi
#.PHONY:debug
#debug:
#	@echo $(src)

.PHONY:output
output:
	mkdir -p output/wwwroot/cgi_bin
	mkdir -p output/conf
	cp httpd output
	cp math_cgi output/wwwroot/cgi_bin
	cp insert_cgi output/wwwroot/cgi_bin
	cp select_cgi output/wwwroot/cgi_bin
	cp wwwroot/index.html output/wwwroot
	cp -rf wwwroot/imag output/wwwroot
	cp $(PLUGIN)/ctl_server.sh output
