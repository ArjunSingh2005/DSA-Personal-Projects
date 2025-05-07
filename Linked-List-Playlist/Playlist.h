#include <string>
#ifndef PLAYLISTNODE_H
#define PLAYLISTNODE_H

// PlaylistNode Class. Node functions as an individual song. Defines the Node itself and functions relating to it
class PlaylistNode{
  public:
    // Default Constructor initializes member variables
    PlaylistNode(); 
    // Parameterized Constructor initializes with user given variables
    PlaylistNode(const std::string& uniqueID, const std::string& songName, const std::string& artistName, int songLength, PlaylistNode* nextNodePtr = nullptr); 

    // Inserts a Node after the current Node 
    void InsertAfter(PlaylistNode* nextNode); 
    // Sets the NextNode's Pointer
    void SetNext(PlaylistNode* nextNode); 

    // Getters of PlaylistNode variables
    std::string GetID() const;
    std::string GetSongName() const;
    std::string GetArtistName() const;
    int GetSongLength() const;
    PlaylistNode* GetNext() const;

    //Prints contents of Current Node
    void PrintPlaylistNode() const;

  private:
    std::string uniqueID; // Unique ID of the song. Initialized to "none" in default constructor
    std::string songName; // Name of the song. Initialized to "none" in default constructor
    std::string artistName; // Name of the Artist. Initialized to "none" in default constructor
    int songLength; // Length of the song (in seconds) Initialized to 0 in default constructor
    PlaylistNode* nextNodePtr; // Pointer to the next Node. Initialized to nullptr in default constructor
};

//Playlist Class. Defines the Playlist itself which will contain songs AKA a bunch of PlaylistNodes
class Playlist{
  public:
    // Playlist Constructor to initialize Playlist with a title
    Playlist(std::string title); 

    // Destructor ensuring cleanup goes well
    ~Playlist(); 

    // Define copy constructor and copy assignment operator to preserve Rule of 3
    Playlist(const Playlist&) = delete;
    Playlist& operator=(const Playlist&) = delete;

    // Adds a song to the Playlist
    void AddSong(const std::string &uniqueID, const std::string &songName, const std::string& artistName, int songLength); 

    // Removes a Song From the Playlist and returns the name of the song that was removed
    std::string RemoveSong(const std::string &RemoveID); 

    // Prints out entire Playlist
    void PrintPlaylist() const; 

    // Changes Position of Song in Playlist
    PlaylistNode* ChangePosOfSong(int OldPos, int NewPos);

    // Outputs all Songs by Specific Artist
    void OutputSongsByArtist(const std::string&  ArtistName) const;

    // Outputs the total time of all songs in the Playlist
    void OutputTimeOfPlaylist() const;
  
  private:
    std::string title;   // Title of the Playlist
    PlaylistNode* head;  // Pointer to the head (first node) of the Playlist
    PlaylistNode* tail;  // Pointer to the tail (last node) of the Playlist
};

#endif