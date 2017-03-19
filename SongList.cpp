#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Song.h"
#include "SongList.h"

using namespace std;

// Constructor and Function Definitions for Class SongList:
SongList::SongList()
{
	capacity = MAX_SONGS;
	list = new Song[capacity];
	size = 0;
}
SongList::SongList(int initCapacity, const char filename[])
{
	capacity = initCapacity;
	list = new Song[capacity];
	size = 0;
	loadDB(filename);
	cout << endl << this->getSize() << " records were loaded from file \"" << filename << "\".";
}

//  copy constructor
SongList::SongList(const SongList& alist)
{
	char title[MAX_CHAR], artist[MAX_CHAR], album[MAX_CHAR];
	int mm, ss;
	
	// allocate space for copy of SongList
	capacity = alist.capacity;
	list = new Song[capacity];
	size = alist.size;
	// deep copy of songs in the member "list" dynamic array
	for (int i = 0; i < size; i++)
	{
		alist.list[i].getSongInfo(title, artist, mm, ss, album);
		list[i].setSong(title, artist, mm, ss, album);
	}
}

SongList::~SongList()
{
	if (list != NULL)
	{
		delete [] list;
	}

}
void SongList::addToDB(const Song& asong)
{
	char title[MAX_CHAR], artist[MAX_CHAR], album[MAX_CHAR];
	int mm, ss;

	if (size == capacity)
	{
		expandList();
	}
	asong.getSongInfo(title, artist, mm, ss, album);
	list[size].setSong(title, artist, mm, ss, album);
	size++;
}
void SongList::expandList()
{
// this function doubles(GROW_FACTOR=2) the size of the memory allocated to store songs from the database 
	Song * tempList;
	char title[MAX_CHAR], artist[MAX_CHAR], album[MAX_CHAR];
	int mm, ss;

	// allocate more space for additional songs in SongList
	capacity = capacity * GROW_FACTOR;
	tempList = new Song[capacity];
	// deep copy of songs in the member "list" dynamic array
	for (int i = 0; i < this->size; i++)
	{
		list[i].getSongInfo(title, artist, mm, ss, album);
		tempList[i].setSong(title, artist, mm, ss, album);
	}
	// release memory for old list
	delete[] list;
	// store address of new expanded memory list in the original list pointer
	list = tempList;
//  disassociate the temporary pointer (reinitialize)
	tempList = 0;
}

bool SongList::searchDBForArtist(const char searchKey[], SongList& matchings) const
{
	char title[MAX_CHAR], artist[MAX_CHAR], album[MAX_CHAR];
	int mm, ss;
	char str[MAX_CHAR];
	int numFound;
	numFound = 0;
	for (int i = 0; i < size; i++)
	{
		this->list[i].getArtist(str);
		if (strcmp(str, searchKey) == 0)
		{
			list[i].getSongInfo(title, artist, mm, ss, album);
			matchings.list[numFound].setSong(title, artist, mm, ss, album);
			numFound++;
		}
	}
	matchings.size = numFound;
	if (numFound > 0)
	{
		return true;
	}
	return false;
}
bool SongList::searchDBForAlbum(const char searchKey[], SongList& matchings) const
{
	char title[MAX_CHAR], artist[MAX_CHAR], album[MAX_CHAR];
	int mm, ss;
	char str[MAX_CHAR];
	int numFound;
	numFound = 0;
	for (int i = 0; i < size; i++)
	{
		list[i].getAlbum(str);
		if (strcmp(str, searchKey) == 0)
		{
			list[i].getSongInfo(title, artist, mm, ss, album);
			matchings.list[numFound].setSong(title, artist, mm, ss, album); 
			numFound++;
		}
	}
	matchings.size = numFound;
	if (numFound > 0)
	{
		return true;
	}
	return false;
}
void SongList::removeFromDB(int index)
{
	char title[MAX_CHAR], artist[MAX_CHAR], album[MAX_CHAR];
	int mm, ss;

	for (int i = index; i < size - 1; i++)
	{
		this->list[i+1].getSongInfo(title, artist, mm, ss, album);
		this->list[i].setSong(title, artist, mm, ss, album);

	}
	size--;
}
int SongList::getSize() const
{
	return size;
}
void SongList::getSong(int idx, Song& asong) const
{
//	copySong(asong, list[idx]);
	char title[MAX_CHAR], artist[MAX_CHAR], album[MAX_CHAR];
	int mm, ss;

	list[idx].getSongInfo(title, artist, mm, ss, album);
	asong.setSong(title, artist, mm, ss, album);
}
void SongList::printSongHeadings() const
{
	cout << endl << left << "#   " << setw(32) << "Title";
	cout << setw(19) << "Artist" << "Duration    Album" << endl;
}
void SongList::printAll() const
// formatted print of the complete SongList object
{
	printSongHeadings();
	for (int i = 0; i < size; i++)
	{
		cout << left << setw(3) << i + 1 << " ";
		list[i].printSong();
	}
}
int SongList::loadDB(const char filename[])
{
	ifstream infile;
	Song asong;
	char title[MAX_CHAR], artist[MAX_CHAR], album[MAX_CHAR];
	int mm, ss;
	int num;

	infile.open(filename);
	if (!infile) {
		cerr << endl << "File " << filename << " failed to open." << endl << endl;
		exit(1);
	}

	num = 0;
	infile.get(title, MAX_CHAR, ';');
	while (infile) {
		infile.get();					// skip data separator ';'
		infile.get(artist, MAX_CHAR, ';');
		infile.get();					// skip data separator ';'
		infile >> mm;
		infile.get();					// skip data separator ';'
		infile >> ss;
		infile.get();					// skip data separator ';'
		infile.get(album, MAX_CHAR, '\n');
		infile.ignore(100, '\n');		// skip end of record

		asong.setSong(title, artist, mm, ss, album);
		addToDB(asong);
		num = num + 1;
		infile.get(title, MAX_CHAR, ';');
	}
	infile.close();
	return num;						// return number of songs in data file
}

void SongList::saveDB(const char filename[]) const
{
	ofstream outfile;
	Song asong;
	char title[MAX_CHAR], artist[MAX_CHAR], album[MAX_CHAR];
	int mm, ss;

	outfile.open(filename);
	if (!outfile) {
		cerr << endl << "Error in writing file " << filename << endl << endl;
		exit(1);
	}

	for (int i = 0; i < size; i++){
		getSong(i, asong);
		asong.getSongInfo(title, artist, mm, ss, album);
		outfile << title << ';'
			<< artist << ';'
			<< mm << ';'
			<< ss << ';'
			<< album << endl;
	}
	outfile.close();
	return;
}
