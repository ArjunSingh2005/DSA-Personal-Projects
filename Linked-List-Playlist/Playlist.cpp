#include "Playlist.h"
#include <iostream>

// Include Playlist Header so we can access functions

//Default Constructor for Playlist Node
PlaylistNode::PlaylistNode() 
    : uniqueID("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(nullptr) {}

//Paramaterized Constructor. Assigns variables to corresponding input
PlaylistNode::PlaylistNode(const std::string& uniqueID, const std::string& songName, const std::string& artistName, int songLength, PlaylistNode* nextNodePtr)
    : uniqueID(uniqueID), songName(songName), artistName(artistName), songLength(songLength), nextNodePtr(nextNodePtr) {}

// Inserts a node after the current node
void PlaylistNode::InsertAfter(PlaylistNode* nextNode){
    PlaylistNode* tempcurrnext = this->nextNodePtr; // Temporary Node Pointer that contains the Node that the current Node (Node we are inserting the new node after) points towards
    this->nextNodePtr = nextNode; // Sets the Current Node Pointer to the Inserted Node
    nextNode->nextNodePtr = tempcurrnext; // Sets the Inserted Node's pointer to temp, ensuring that the Playlist's connection remains intact, Essentially Inserting the Node into the Playlist.
}

//Sets the Next Node Pointer
void PlaylistNode::SetNext(PlaylistNode* nextNode){
    this->nextNodePtr = nextNode;
}

//Getters

// Returns ID of the Node
std::string PlaylistNode::GetID() const{
    return uniqueID;
}

// Returns Song Name of the Node
std::string PlaylistNode::GetSongName() const{
    return songName;
}

// Returns Artist Name of the Node
std::string PlaylistNode::GetArtistName() const{
    return artistName;
}

// Returns Song Length of the Node
int PlaylistNode::GetSongLength() const{
    return songLength;
}

// Returns a Pointer to the Next Node of the current Node
PlaylistNode* PlaylistNode::GetNext() const{
    return nextNodePtr;
}


// Prints Current Details (Unique ID, Song Name, Artist Name, Song Length (in seconds)) of the Node. Calls Getters
void PlaylistNode::PrintPlaylistNode() const{
    std::cout << "Unique ID: " << GetID() << "\n";
    std::cout << "Song Name: " << GetSongName() << "\n";
    std::cout << "Artist Name: " << GetArtistName() << "\n";
    std::cout << "Song Length (in seconds): " << GetSongLength() << "\n" << std::endl;  
}

// Constructor for Playlist. Initializes the title and automatically sets head and tail to nullptr before any songs are added
Playlist::Playlist(std::string title)
    : title(title), head(nullptr), tail(nullptr) {}

// Playlist Destructor. Ensures all Nodes are properly deleted to prevent memory leaks.
Playlist::~Playlist() {
    PlaylistNode* current = head;
    while(current!= nullptr){ // Traverses Playlist
        PlaylistNode* tempnextNode = current->GetNext(); // Store next node before deletion
        delete current;  // Free the current node
        current = tempnextNode;// Move onto next Node
    }
}

// Appends Song to Playlist. Adds them to the end and updates tail to reflect it.
void Playlist::AddSong(const std::string &uniqueID, const std::string &songName, const std::string& artistName, int songLength){
    PlaylistNode* newSong = new PlaylistNode(uniqueID, songName, artistName, songLength); // Dynamically Create the Song 
    // Scenario where list is empty, both head and tail are the newSong
    if (head == nullptr && tail == nullptr){
        head = newSong;
        tail = newSong;
    }

    else{
        tail->SetNext(newSong); // Have the Old Tail Point towards the New Song
        tail = newSong; // Set the New Song to the Tail
        // Node Automatically Points Towards nullptr upon creation of newSong so no need to set to nullptr
    }
}

// Removes Song from Playlist. Updates head and tail pointers depending on which node is removed.
std::string Playlist::RemoveSong(const std::string &RemoveID) {
    std::string removedSongName;
    // Case 1: If the head is the node to remove. Checks that the ID of the head is the same as the passed in ID
    if (head != nullptr && head->GetID() == RemoveID) {
        PlaylistNode* tempHead = head;  // Store head in a temporary pointer
        head = head->GetNext();  // Move the head pointer to the next node

        // If list becomes empty after removal, update the tail pointer
        if (head == nullptr) {
            tail = nullptr;
        }
        tempHead->SetNext(nullptr);  // Set Temp Head to nullptr (disconnects it from list)
        removedSongName = tempHead->GetSongName(); // Get the name of the Song to return
        delete tempHead; // Delete the Removed Node to free up memory
        return removedSongName;  // Return the removed node
    }

    // Case 2: Traverse the list to find the node to remove
    PlaylistNode* curr = head;
    PlaylistNode* prev = nullptr;

    while (curr != nullptr) {
        // if ID of curr equals the ID that was passed in
        if (curr->GetID() == RemoveID) {
            // Remove the node (curr) by bypassing it and setting the previous Node's next Pointer to the curr's next Pointer
            prev->SetNext(curr->GetNext());

            // If the node to remove is the tail, update the tail pointer
            if (curr == tail) {
                tail = prev;
            }

            curr->SetNext(nullptr);  // Set curr to nullptr (Disconnect the node from the list)
            removedSongName = curr->GetSongName(); // Get the name of the song that is being Removed
            delete curr;  // Delete the Removed Node to free up memory
            return removedSongName; // Return the name of the Removed Song
        }
        prev = curr; //Set prev to curr (will be our new curr)
        curr = curr->GetNext(); // Move to next Node
    }

    // If the song with RemoveID is not found, return "No Song Found"
    return "No Song Found";
}

// Print Entire Playlist. Traverses list and calls PrintPlaylistNode() on every Node
void Playlist::PrintPlaylist() const{
    std::cout << title << " - OUTPUT FULL PLAYLIST" << std::endl;
    PlaylistNode* curr = head;
    // Checks if Playlist is empty and prints "Playlist is empty" if it is
    if (curr == nullptr){
        std::cout << "Playlist is empty\n" << std::endl;
        return;
    }

    int counter = 1; // Counter to keep Track of the Number Song we are on
    // Traverse Through List until we reach the end
    while(curr != nullptr){
        std::cout << counter << "." << std::endl; // Print out number song we are on 
        curr->PrintPlaylistNode(); // Call the currentNode's PrintPlaylistNode() function to print out the contents of the Node 
        curr = curr->GetNext(); // Go to Next Node
        counter++; // Increments Node to reflect we've moved on to the next song
    }
}

// Changes Position of Song from the Old Position to the New Position
PlaylistNode* Playlist::ChangePosOfSong(int OldPos, int NewPos) {
    // If OldPos and NewPos are the same, no movement is required
    if (OldPos == NewPos) {
        return nullptr;
    }

    // Step 1: Find the node at OldPos
    int OldCounter = 1;
    PlaylistNode* CurrOld = head; // Pointer of the Old Position'd node 
    PlaylistNode* PrevOld = nullptr; // Pointer of the Node Before The Old Position'd node

    // Traverse List until we either reach the end of the Playlist, or find the Old Position'd node
    while (CurrOld != nullptr && OldCounter != OldPos) {
        OldCounter++;
        PrevOld = CurrOld; 
        CurrOld = CurrOld->GetNext(); // Goes to next Node 
    }

    // Edge case: If OldPos is out of bounds
    if (CurrOld == nullptr) {
        return nullptr;  // Invalid OldPos
    }

    // Step 2: Remove the node from the old position
    // Ensures that CurrOld is the head and sets the nextNodePtr of the one before curr to the node after CurrOld
    if (PrevOld != nullptr) {
        PrevOld->SetNext(CurrOld->GetNext());
    } else {
        // If CurrOld is the head, update the head pointer
        head = CurrOld->GetNext();
    }

    // If CurrOld is the tail, update the tail pointer
    if (CurrOld == tail) {
        tail = PrevOld;
    }
    
    // Step 3: Find the node at NewPos
    int NewCounter = 1; 
    PlaylistNode* CurrNew = head; // Pointer of the New Position'd node
    PlaylistNode* PrevNew = nullptr; // Pointer of the Node before the New Position'd Node

    // Traverse list until we either reach the end of the Playlist, or find the New Position'd Node
    while (CurrNew != nullptr && NewCounter != NewPos) {
        NewCounter++;
        PrevNew = CurrNew;
        CurrNew = CurrNew->GetNext(); // Goes to the next Node
    }
    
    // Step 4: Insert the node at the new position
    
    // If NewPos is 1 or if the user enters a position less than 1, insert at the head
    if (NewPos <= 1) {
        CurrOld->SetNext(head);
        head = CurrOld;

        // If the list was empty or we're moving the node to be the only node, update the tail
        if (tail == nullptr) {
            tail = CurrOld;
        }
        return CurrOld;
    }

    // If inserting at the tail (when CurrNew is nullptr) or the New Position is greater than the amount of nodes in the list 
    if (CurrNew == nullptr or NewPos > NewCounter) {
        PrevNew->SetNext(CurrOld);
        CurrOld->SetNext(nullptr);
        tail = CurrOld;
    } else {
        // Normal case: inserting in between nodes. Set the Old Position'd Node to point towards where New Position used to Point (CurrNew) and have it so the Previous Node before the New Position'd node (PrevNew) points towards our Inserted Node.
        CurrOld->SetNext(CurrNew);
        PrevNew->SetNext(CurrOld);
    }

    return CurrOld; // Return the Moved Node
}


// Outputs song based off Artist Name
void Playlist::OutputSongsByArtist(const std::string& ArtistName) const{
    PlaylistNode* curr = head;
    int counter = 1; // Number of Song we are on

    // Traverse List until we reach end of list
    while(curr!= nullptr){
        if (ArtistName == curr->GetArtistName()){
            std::cout << counter << "." << std::endl;
            curr->PrintPlaylistNode(); // Call PrintPlaylistNode() on Nodes that match the Artist Name
        }
        curr = curr->GetNext(); // Move to next Node
        counter++;
    }
}

// Output Playlist based off Total Time
void Playlist::OutputTimeOfPlaylist() const{
    PlaylistNode* curr = head;
    int TotalSecs = 0; // Initialize total time to 0
    // Traverse List until we reach end of list
    while(curr!= nullptr){
        TotalSecs += curr->GetSongLength(); // Add length of song to TotalSecs until we reach end of list
        curr = curr->GetNext(); // Move to next Playlist
    }

    // Output Result
    std::cout << "Total time: " << TotalSecs << " seconds" << "\n" << std::endl;
}



