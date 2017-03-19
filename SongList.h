#ifndef SONGLIST_H
#define SONGLIST_H
#include "Song.h"

const int MAX_SONGS = 20;
const int GROW_FACTOR = 2;

class SongList
{
public:
 	// constructor
	SongList();
	SongList(int initCapacity, const char filename[]);
 
	// copy constructor
	SongList(const SongList& alist);

	// destructor
	~SongList();

 	//accessor functions
	int getSize() const;
	bool searchDBForArtist(const char searchKey[], SongList& matchings) const;
	bool searchDBForAlbum(const char searchKey[], SongList& matchings) const;
	void getSong(int idx, Song& asong) const;
	void printSongHeadings() const;
	void printAll() const;
	void saveDB(const char filename[]) const;

	// mutator function
	int loadDB(const char filename[]);
	void addToDB(const Song& asong);
	void removeFromDB(int index);

private:
	Song * list;
	int size;
	int capacity;
	void expandList();
};
#endif

