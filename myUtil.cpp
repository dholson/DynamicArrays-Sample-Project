//  Useful functions:
//                    bool yesOrNo();
//                    bool inRange(int ichk, int min, int max);
//                    void getString(char str[]);
//                    int getInt();
//                    void pause();
//
#include <iostream>
#include "Song.h"
#include "myUtil.h"

using namespace std;

bool yesOrNo()
{
	char reply;

	while (true) {
		cin >> reply;
		while (!cin) {
			cin.clear();
			cin.ignore(MAX_CHAR, '\n');
			cout << "Please answer 'y' or 'n'. ";
			cin >> reply;
		}
		cin.ignore(MAX_CHAR, '\n');

		switch (reply) {
		case 'y':
		case 'Y':
			return true;           //  user replied yes, return true
			break;
		case 'n':
		case 'N':
			return false;         //  user replied no, return false
			break;
		default:
			cout << "Please answer 'y' or 'n'. ";
			continue;
			break;
		}
	}
}
bool inRange(int ichk, int min, int max)
{
	if (ichk >= min && ichk <= max) {
		return true;
	}
	else {
		cout << ichk << " is out of range (" << min << "-" << max << "). Try again." << endl;
		return false;
	}
}
/* The following functions are taken from examples written by instructor Li Liang for PCC CS162  */
void getString(char str[])
{
	cin.get(str, MAX_CHAR, '\n');
	while (!cin) {
		cin.clear();
		cin.ignore(MAX_CHAR, '\n');
		cout << "Please try again: ";
		cin.get(str, MAX_CHAR, '\n');
	}
	cin.ignore(MAX_CHAR, '\n');
	return;
}
int getInt()
{
	int n;
	cin >> n;
	while (!cin) {
		cin.clear();
		cin.ignore(MAX_CHAR, '\n');
		cout << "Illegal integer. Please try again: ";
		cin >> n;
	}
	cin.ignore(MAX_CHAR, '\n');
	return n;
}
void pause()
{
	char ch[MAX_CHAR];

	cout << "Press any key to continue ...";
	cin.get(ch, MAX_CHAR, '\n');
	cin.clear();
	cin.ignore(MAX_CHAR, '\n');
}
