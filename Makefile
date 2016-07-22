APP=scalam
VERSION=0.1
RELEASE=1
PREFIX?=/usr/local

CC=gcc
LIBS='-lm -fopenmp'

all:
	rm -f *.plist src/*.plist src/*.c~ src/*.h~ ${APP}
	$(CC) -o ${APP} src/* ${LIBS}
debug:
	rm -f *.plist src/*.plist src/*.c~ src/*.h~ ${APP}
	$(CC) -o ${APP} -g src/* ${LIBS}
clean:
	rm -f *.plist src/*.plist src/*.c~ src/*.h~ ${APP}
source:
	tar -cvf ../${APP}_${VERSION}.orig.tar ../${APP}-${VERSION} --exclude-vcs
	gzip -f9n ../${APP}_${VERSION}.orig.tar
install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	install -m 755 ${APP} ${DESTDIR}${PREFIX}/bin
	mkdir -m 755 -p ${DESTDIR}${PREFIX}/share/man/man1
	install -m 644 man/${APP}.1.gz ${DESTDIR}${PREFIX}/share/man/man1
uninstall:
	rm -f ${PREFIX}/bin/${APP} ${DESTDIR}${PREFIX}/share/man/man1/${APP}.1.gz
