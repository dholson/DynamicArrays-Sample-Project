CC=g++
CFLAGS=-c -Wall

all: proj4

proj4: driver.o Song.h SongList.h myUtil.h
	$(CC) -g driver.cpp SongList.cpp Song.cpp myUtil.cpp -o proj4

driver.o: driver.cpp SongList.o Song.o myUtil.o
	$(CC) $(CFLAGS) driver.cpp SongList.cpp Song.cpp myUtil.cpp

SongList.o: SongList.cpp SongList.h Song.cpp Song.h
	$(CC) $(CFLAGS) SongList.cpp Song.cpp

Song.o: Song.cpp Song.h
	$(CC) $(CFLAGS) Song.cpp

myUtil.o: myUtil.cpp myUtil.h Song.h
	$(CC) $(CFLAGS) myUtil.cpp

.PHONEY: clean
clean:
	rm *.o *~ proj4


