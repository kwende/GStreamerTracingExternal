all:
	gcc test.c latency.c -o test `pkg-config --cflags --libs gstreamer-1.0`
clean:
	rm ./test