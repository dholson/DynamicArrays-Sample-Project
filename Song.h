#ifndef SONG_H
#define SONG_H

const int MAX_CHAR = 100;           //  maximum #characters in song, artist or album name

class SongLength
{
public:
	// constructor
	SongLength();
	SongLength(int mm, int ss);

	// accessor functions
	int getMinutes() const;
	int getSeconds() const;
	void printSongLength() const;

	// mutator function
	void setSongLength(const int mm, const int ss);


private:
	int minutes;
	int seconds;	
};

class Song
{
public:	
	// constructors
	Song();
	Song(const char a[], const char b[], int mm, int ss, const char c[]);

	// destructor
	~Song();

	// copy constructor
	Song(const Song &asong);

	// accessor functions
	void getArtist(char str[]) const;
	void getAlbum(char str[]) const;
	void getSongInfo(char a[], char b[], int& mm, int& ss, char c[]) const;
	void printSong() const;

	// mutator function
	void setSong(const char a[], const char b[], int mm, int ss, const char c[]);
private:
	char * title;
	char * artist;
	SongLength duration;
	char * album;
};
#endif