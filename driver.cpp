/* This program reads a data file ("songs.txt") of songs and prompts user with menu options:
	a - Add a new song
	b - Search by band/artist
	c - Search by CD/album
	d - Delete a song
	l- List all songs
	q - Quit 
   
   Written by: Debbie Olson
   Last Modified: 02/22/2017 to use dynamic arrays

   Sources: cs162 sample classroom code and videos 
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Song.h"
#include "SongList.h"
#include "myUtil.h"

 // memory leak detection tool headers
#define _CRT_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

char menuPrompt();
void addSong(SongList& alist);
void deleteSong(SongList& alist);
void findArtist(const SongList& alist);
void findAlbum(const SongList& alist);

int main()
{
	// enable memory leak detection tools
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	char filename[] = "songs.txt";
	char option;

	//  Read in the data base
	SongList songDB(5, filename);			// constructs a SongList variable songDB and reads data from filename

	// User menu:
	option = tolower(menuPrompt());		// get user menu choice in lower case
	while (option != 'q') {
		switch (option) {
			case 'a' :                        // add a song
				addSong(songDB);
				break;
			case 'b' :                        // search by band/artist
				findArtist(songDB);
				break;
			case 'c' :                        // search by CD/album
				findAlbum(songDB);
				break;
			case 'd' :                        // delete a song
				deleteSong(songDB);
				break;
			case 'l' :                        // list all songs
				songDB.printAll();
				break;
			default :
				cout << "That is not a valid option." << endl;
				break;
		}
		pause();
		option = tolower(menuPrompt());
	}

	//  Save the data base file
	songDB.saveDB(filename);
	return 0;
}

char menuPrompt()
{
	char reply;

	cout << endl << endl << " Menu for accessing Song data base" << endl << endl;
	cout << right;
	cout << setw(5) << 'a' << '\t' << "Add a new song" << endl;
	cout << setw(5) << 'b' << '\t' << "Search by band/artist" << endl;
	cout << setw(5) << 'c' << '\t' << "Search by CD/album" << endl;
	cout << setw(5) << 'd' << '\t' << "Delete a song" << endl;
	cout << setw(5) << 'l' << '\t' << "List all songs" << endl;
	cout << setw(5) << 'q' << '\t' << "Quit" << endl << endl;

	cout << " Which menu option do you choose? ";
	cin >> reply;
	cin.ignore(100, '\n');
	return reply;
}
void addSong(SongList& alist)
/* adds a record to the data file (if there is room) and increments the counter*/
{
	Song asong;
	char strTitle[MAX_CHAR], strArtist[MAX_CHAR], strAlbum[MAX_CHAR];
	int mm, ss;

	cout << endl << "Add a new song:" << endl;
	cout << "Enter the song title: ";
	getString(strTitle);

	cout << "Enter the artist's name: ";
	getString(strArtist);

	cout << "Please enter the song duration: First enter the minutes then the seconds." << endl;
	do {
		cout << "  How many minutes does the song run? ";
		mm = getInt();
	} while (! inRange(mm, 0, 60));
		
	do {
		cout << "  plus how many seconds? ";
		ss = getInt();
	} while (! inRange(ss, 0, 60));

	cout << "Enter the album title: ";
	getString(strAlbum);

	cout << endl << "Do you want to add song: \""
		    << strTitle << "\" by " << strArtist << " (y/n) ? ";
	if (yesOrNo()) {						// returns true for "yes"
		asong.setSong(strTitle, strArtist, mm, ss, strAlbum);
		alist.addToDB(asong);
	}
	return;
}
void findArtist(const SongList& alist)
{
	SongList matches;
	char searchKey[MAX_CHAR];

	cout << endl << "Search by Band or Artist:" << endl;
	cout << "Enter the artist's name: ";
	getString(searchKey);
	if (alist.searchDBForArtist(searchKey, matches))
	{
		matches.printAll();
	}
	else
	{
		cout << endl << "That artist is not in the database." << endl;
	}
}
void findAlbum(const SongList& alist)
{
	SongList matches;
	char searchKey[MAX_CHAR]; 

	cout << endl << "Search for CD or Album:" << endl;
	cout << "Enter the name of the album: ";
	getString(searchKey);
	if (alist.searchDBForAlbum(searchKey, matches))
	{
		matches.printAll();
	}
	else
	{
		cout << endl << "That album is not in the database." << endl;
	}
	return;
}
void deleteSong(SongList& alist)
/* removes a record in the database and decrements the counter*/
{
	Song asong;
	char title[MAX_CHAR], artist[MAX_CHAR], album[MAX_CHAR];
	int mm, ss;
	int userIndex, size;

	alist.printAll();     // display the songs in the data base
	size = alist.getSize();

	cout << endl << "Enter the index of the song you want to delete. (enter 0 to exit) ";
	userIndex = getInt();
	while (userIndex > size || userIndex < 0){
		cout << endl << "Invalid song index. Try again: " << endl;
		cout << "Enter the index of the song you want to delete. (enter 0 to exit) ";
		userIndex = getInt();
	}
	if ( userIndex == 0) {					// exit without deleting a file
		return;
	}
	alist.getSong(userIndex-1, asong);
	asong.getSongInfo(title, artist, mm, ss, album);
	cout << "Do you want to delete song \"" << title << "\" by " << artist << " (y/n) ? ";
	if (yesOrNo()) {						// returns true for "yes"
		alist.removeFromDB(userIndex-1);
	}
	else {
		cout << endl << "\"" << title << "\" by " << artist;
		cout << " will NOT be deleted." << endl;
	}
	return;
}
