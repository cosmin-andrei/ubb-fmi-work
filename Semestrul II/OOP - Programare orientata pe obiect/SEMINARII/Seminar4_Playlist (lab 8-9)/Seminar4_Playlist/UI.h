#pragma once
#include "Service.h"
class ConsoleUI {
private:
	SongStore& srv;
public:
	ConsoleUI(SongStore& srv) :srv{ srv } {};
	ConsoleUI(const ConsoleUI& ot) = delete;

	void printMenu();
	void printPlaylistMenu();
	void uiAdd();
	void uiSort();
	void uiFilter();
	void uiPlayList();
	void uiAddToPlaylist();
	void uiAddRandomToPlaylist();
	void uiEmptyPlaylist();
	void addDefaultSongs();
	void printSongs(const vector<Song>& allSongs);
	void run();
};
