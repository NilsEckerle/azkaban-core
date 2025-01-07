# -lsqlcipher
OBJECTS = build/db_manager.o build/entry.o

CFLAGS = -Iinclude -Ithird/sqlcipher/include -fPIC 
LDFLAGS = -lsqlcipher

final: setup $(OBJECTS)
	gcc $(OBJECTS) $(LDFLAGS) -shared -o lib/libazkaban-core.so
	gcc $(OBJECTS) $(LDFLAGS) -shared -o lib/libazkaban-core.dylib -install_name @rpath/libazkaban-core.dylib

clean:
	@if [ -d build ]; then \
		rm -r build;\
	fi
	@if [ -d lib ]; then \
		rm -r lib;\
	fi

setup: clean
	@mkdir build
	@mkdir lib

build/db_manager.o: src/db_manager.c
	gcc $(CFLAGS) -c src/db_manager.c -o build/db_manager.o

build/entry.o: src/entry.c
	gcc $(CFLAGS) -c src/entry.c -o build/entry.o


