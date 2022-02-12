#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    /* TODO */
    Profile np(email, username, plan);
    profiles.insertAtTheEnd(np);
}

void MusicStream::deleteProfile(const std::string &email) {
    /* TODO */
    Node<Profile> *cur = profiles.getFirstNode();
    while((cur -> data).getEmail() != email){
        cur = cur -> next;
    }
    while(!((cur -> data). getFollowings()).isEmpty()){
        unfollowProfile(email, (((cur -> data).getFollowings()).getFirstNode() -> data) -> getEmail());
    }
    while(!((cur -> data). getFollowers()).isEmpty()){
        unfollowProfile((((cur -> data).getFollowers()).getFirstNode() -> data) -> getEmail(), email);
    }
    while(!((cur -> data).getPlaylists()).isEmpty()){
        (cur -> data).deletePlaylist((((cur -> data).getPlaylists()).getFirstNode() -> data).getPlaylistId());
    }
    profiles.removeNode(cur);
}

void MusicStream::addArtist(const std::string &artistName) {
    /* TODO */
    Artist nar(artistName);
    artists.insertAtTheEnd(nar);
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) {
    /* TODO */
    Album nal(albumName);
    albums.insertAtTheEnd(nal);
    Node<Artist> *cur = artists.getFirstNode();
    while((cur -> data).getArtistId() != artistId){
        cur = cur -> next;
    }
    (cur -> data).addAlbum(&(albums.getLastNode() -> data));
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId) {
    /* TODO */
    Song nsong(songName, songDuration);
    songs.insertAtTheEnd(nsong);
    Node<Album> *cur = albums.getFirstNode();
    while((cur -> data).getAlbumId() != albumId){
        cur = cur -> next;
    }
    (cur -> data).addSong(&(songs.getLastNode() -> data));
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) {
    /* TODO */
    Node<Profile> *cur1 = profiles.getFirstNode(), *cur2 = profiles.getFirstNode();
    int s = profiles.getSize();
    for(int i = 0; i < s; i++){
        if((cur2 -> data).getEmail() == email2)
            break;
        cur2 = cur2 -> next;
    }
    for(int i = 0; i < s; i++){
        if((cur1 -> data).getEmail() == email1){
            (cur1 -> data).followProfile(&(cur2 -> data));
            break;
        }
        cur1 = cur1 -> next;
    }
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) {
    /* TODO */
    Node<Profile> *cur1 = profiles.getFirstNode(), *cur2 = profiles.getFirstNode();
    int s = profiles.getSize();
    for(int i = 0; i < s; i++){
        if((cur2 -> data).getEmail() == email2)
            break;
        cur2 = cur2 -> next;
    }
    for(int i = 0; i < s; i++){
        if((cur1 -> data).getEmail() == email1){
            (cur1 -> data).unfollowProfile(&(cur2 -> data));
            break;
        }
        cur1 = cur1 -> next;
    }
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) {
    /* TODO */
    Node<Profile> *cur = profiles.getFirstNode();
    int s = profiles.getSize();
    for(int i = 0; i < s; i++){
        if((cur -> data).getEmail() == email){
            (cur -> data).createPlaylist(playlistName);
            break;
        }
        cur = cur -> next;
    }
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    Node<Profile> *cur = profiles.getFirstNode();
    int s = profiles.getSize();
    for(int i = 0; i < s; i++){
        if((cur -> data).getEmail() == email){
            (cur -> data).deletePlaylist(playlistId);
            break;
        }
        cur = cur -> next;
    }
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) {
    /* TODO */
    Node<Profile> *cur = profiles.getFirstNode();
    int s = profiles.getSize();
    for(int i = 0; i < s; i++){
        if((cur -> data).getEmail() == email){
            Node<Song> *cur1 = songs.getFirstNode();
            while((cur1 -> data).getSongId() != songId){
                cur1 = cur1 -> next;
            }
            (cur -> data).getPlaylist(playlistId) -> addSong(&(cur1 -> data));
            break;
        }
        cur = cur -> next;
    }
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) {
    /* TODO */
    Node<Profile> *cur = profiles.getFirstNode();
    int s = profiles.getSize();
    for(int i = 0; i < s; i++){
        if((cur -> data).getEmail() == email){
            Node<Song> *cur1 = songs.getFirstNode();
            while((cur1 -> data).getSongId() != songId){
                cur1 = cur1 -> next;
            }
            (cur -> data).getPlaylist(playlistId) -> dropSong(&(cur1 -> data));
            break;
        }
        cur = cur -> next;
    }
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) {
    /* TODO */
    Node<Profile> *cur = profiles.getFirstNode();
    LinkedList<Song *> stream;
    while((cur -> data).getEmail() != email){
        cur = cur -> next;
    }
    stream = ((((cur -> data).getPlaylists()).getNode(*playlist)) -> data).getSongs();
    if((cur -> data).getPlan() == premium){
        return stream;
    }
    else{
        stream.insertAsEveryKthNode(&(Song::ADVERTISEMENT_SONG), 2);
        return stream;
    }
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) {
    /* TODO */
    Node<Profile> *cur = profiles.getFirstNode();
    int s = profiles.getSize();
    for(int i = 0; i < s; i++){
        if((cur -> data).getEmail() == email)
            return (cur -> data).getPlaylist(playlistId);
        cur = cur -> next;
    }
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email) {
    /* TODO */
    Node<Profile> *cur = profiles.getFirstNode();
    int s = profiles.getSize();
    for(int i = 0; i < s; i++){
        if((cur -> data).getEmail() == email)
            return (cur -> data).getSharedPlaylists();
        cur = cur -> next;
    }
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed) {
    /* TODO */
    (getPlaylist(email, playlistId)) -> shuffle(seed);
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    getPlaylist(email, playlistId) -> setShared(1);
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    getPlaylist(email, playlistId) -> setShared(0);
}

void MusicStream::subscribePremium(const std::string &email) {
    /* TODO */
    Node<Profile> *cur = profiles.getFirstNode();
    while((cur -> data).getEmail() != email){
        cur = cur -> next;
    }
    (cur -> data).setPlan(premium);
}

void MusicStream::unsubscribePremium(const std::string &email) {
    /* TODO */
    Node<Profile> *cur = profiles.getFirstNode();
    while((cur -> data).getEmail() != email){
        cur = cur -> next;
    }
    (cur -> data).setPlan(free_of_charge);
}

void MusicStream::print() const {
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << this->profiles.getSize() << ":" << std::endl;
    this->profiles.print();

    std::cout << "# Number of artists is " << this->artists.getSize() << ":" << std::endl;
    this->artists.print();

    std::cout << "# Number of albums is " << this->albums.getSize() << ":" << std::endl;
    this->albums.print();

    std::cout << "# Number of songs is " << this->songs.getSize() << ":" << std::endl;
    this->songs.print();

    std::cout << "# Printing is done." << std::endl;
}
