# -lsqlcipher
OBJECTS = build/db_manager.o build/entry.o

CFLAGS = -Iinclude -Ithird/sqlcipher/include -fPIC 
LDFLAGS = -lsqlcipher

final: setup $(OBJECTS)
	gcc $(OBJECTS) $(LDFLAGS) -shared -o lib/libazkaban-core.so.0.1

clean:
	@if [ -d build ]; then \
		rm -r build;\
	fi
	@if [ -d azkaban-core ]; then \
		rm -r azkaban-core;\
	fi

setup: clean
	@mkdir build
	@mkdir azkaban-core
	@mkdir azkaban-core/lib
	@mkdir azkaban-core/includes

build/db_manager.o: src/db_manager.c
	gcc $(CFLAGS) -c src/db_manager.c -o build/db_manager.o

build/entry.o: src/entry.c
	gcc $(CFLAGS) -c src/entry.c -o build/entry.o


