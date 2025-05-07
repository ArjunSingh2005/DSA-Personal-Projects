#include <iostream>
#include <limits>

// Include Playlist Header
#include "Playlist.h"

// Include std libraries to use
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::numeric_limits;
using std::string;
using std::streamsize;

// Menu to print out a User Interface
void PlaylistMenu(string title){
  cout << title << " PLAYLIST MENU" << endl;
  cout << "a - Add song" << endl;
  cout << "d - Remove song" << endl;
  cout << "c - Change position of song" << endl;
  cout << "s - Output songs by specific artist" << endl;
  cout << "t - Output total time of playlist (in seconds)" << endl;
  cout << "o - Output full playlist" << endl;
  cout << "q - Quit\n" << endl;
  cout << "Choose an option:" << endl;
}

// Functionability of command calls
void PrintMenu(Playlist& SongPlaylist, const string& title) {
  string command; 
  // Get command and stay in while loop until user wants to quit
  while (cin >> command and command != "q") {
    // ignore characters until we get to a newline or end-of-file
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    
    // Add Song command. Prompts user for Song ID, song name, artist name, song length and then creates a PlaylistNode object and adds it to Playlist
    if (command == "a") {
      cin.clear();
      string UniqueIdOfSong;
      string songName;
      string artistName;
      int songLength;
      cout << "ADD SONG" << endl;
      cout << "Enter song's unique ID:" << endl;
      getline(cin, UniqueIdOfSong);
      // Checks that input stream is in good state
      if (not cin.good()){
        throw std::runtime_error("Please input a valid unique ID");
      }
      cout << "Enter song's name:" << endl;
      getline(cin, songName);
      // Checks that input stream is in good state
      if (not cin.good()){
        throw std::runtime_error("Please input a valid song name");
      }
      cout << "Enter artist's name:" << endl;
      getline(cin, artistName);
      // Checks that input stream is in good state
      if (not cin.good()){
        throw std::runtime_error("Please input a valid artist name");
      }
      cout << "Enter song's length (in seconds):\n" << endl;
      cin >> songLength;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      // Checks that input stream is in good state
      if (not cin.good()){
        throw std::runtime_error("Please input a valid song length");
      }
      SongPlaylist.AddSong(UniqueIdOfSong, songName, artistName, songLength); // Add Song to Playlist
      cin.clear(); // Clear input stream
      PlaylistMenu(title); // Print Out Menu Again
    }
    //Removes song from Playlist. Prompt's user for unique ID and outputs the removed song's name
    else if (command == "d") {
      string UniqueIdOfSong; 
      string SongName;
      cout << "REMOVE SONG" << endl;
      cout << "Enter song's unique ID:" << endl;
      getline(cin, UniqueIdOfSong);
      // Checks that input stream is in good state
      if (not cin.good()){
        throw std::runtime_error("Please input a valid ID");
      }
      // Call function to remove Song and store song name is SongName and print that the song was removed succesfully.
      SongName = SongPlaylist.RemoveSong(UniqueIdOfSong);
      cout << '"' << SongName << '"' << " removed.\n" << endl;
    }
    // Changes Position of Song. Prompts user for song's current Position and New Position and returns the name of the song and to which position the song was moved towards
    else if (command == "c") {
      int OldPos;
      int NewPos;
      PlaylistNode* Node = nullptr;
      cout << "CHANGE POSITION OF SONG" << endl;
      cout << "Enter song's current position:" << endl;
      cin >> OldPos;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      // Ensures that input stream is good
      if (not cin.good()){
        throw std::runtime_error("Please input a valid position for the song");
      }
      cout << "Enter new position for song:" << endl;
      cin >> NewPos;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      // Ensures that input stream is good
      if (not cin.good()){
        throw std::runtime_error("Please input a valid position for the song");
      }
      // Change Position of Song and store the Node that was moved
      Node = SongPlaylist.ChangePosOfSong(OldPos, NewPos); 
      // Output where the Node was moved to
      cout << '"' << Node->GetSongName() << '"' << " moved to position " << NewPos << "\n" << endl;
      PlaylistMenu(title); // Print Out Menu Again
      
    }
    // Outputs song by specific Artist. Prompts user for Artist Name then prints contents of songs based off Artist Name
    else if (command == "s") {
    string ArtistName;
    cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
    cout << "Enter artist's name:\n" << endl;
    getline(cin, ArtistName);
    // Ensures that input stream is good
      if (not cin.good()){
        throw std::runtime_error("Please input a valid possible Artist");
      }
    // Call function to output Songs by Artist
    SongPlaylist.OutputSongsByArtist(ArtistName);
    }

    // Print out total time Playlist
    else if (command == "t") {
      cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
    // Call function to print out toal time of Playlist
      SongPlaylist.OutputTimeOfPlaylist();
    }

  // Traverse through Playlsit and print out contents of each Song
    else if (command == "o") {
      SongPlaylist.PrintPlaylist();
    }
  }
  // Repeat the menu and wait for another command
  PlaylistMenu(title);
}

  
int main() {
  string title;
  string command;

  // Prompt for and read the title for the playlist (may contain spaces)
  cout << "Enter playlist's title:\n" << endl;
  getline(cin, title);
  // Ensure that input stream is good
  if (not cin.good()){
    throw std::runtime_error("Please input something valid");
  }
  // Create Playlist
  Playlist SongPlaylist(title);

  // Read the next "token".  Will stop on EOF or a q
  PrintMenu(SongPlaylist, title);


  // Return 0 to insure it returned properly
  return 0;
}
