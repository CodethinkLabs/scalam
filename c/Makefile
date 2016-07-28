APP=scalam
VERSION=0.1
RELEASE=1
PREFIX?=/usr/local

CC=gcc

all:
	rm -f *.plist src/*.plist tests/*.plist src/*.c~ tests/*~ src/*.h~ ${APP}
	$(CC) -o ${APP} src/* tests/* -lm -fopenmp
debug:
	rm -f *.plist src/*.plist tests/*.plist src/*.c~ tests/*~ src/*.h~ ${APP}
	$(CC) -O0 -o ${APP} -g3 src/* tests/* -lm -fopenmp
clean:
	rm -f *.plist src/*.plist tests/*.plist tests/*.plist src/*.c~ tests/*~ src/*.h~ ${APP}
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
