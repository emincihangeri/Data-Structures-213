#include "Profile.h"

Profile::Profile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    this->email = email;
    this->username = username;
    this->plan = plan;
}

const std::string &Profile::getUsername() const {
    return this->username;
}

const std::string &Profile::getEmail() const {
    return this->email;
}

SubscriptionPlan Profile::getPlan() const {
    return this->plan;
}

LinkedList<Playlist> &Profile::getPlaylists() {
    return this->playlists;
}

LinkedList<Profile *> &Profile::getFollowings() {
    return this->following;
}

LinkedList<Profile *> &Profile::getFollowers() {
    return this->followers;
}

void Profile::setPlan(SubscriptionPlan plan) {
    this->plan = plan;
}

void Profile::followProfile(Profile *profile) {
    /* TODO */
    following.insertAtTheEnd(profile);
    (profile -> getFollowers()).insertAtTheEnd(this);
}

void Profile::unfollowProfile(Profile *profile) {
    /* TODO */
    following.removeNode(profile);
    (profile -> getFollowers()).removeNode(this);
}

void Profile::createPlaylist(const std::string &playlistName) {
    /* TODO */
    Playlist npl(playlistName);
    playlists.insertAtTheEnd(npl);
}

void Profile::deletePlaylist(int playlistId) {
    /* TODO */
    Node<Playlist> *cur = playlists.getFirstNode();
    int s = playlists.getSize();
    for(int i = 0; i < s; i++){
        if((cur -> data).getPlaylistId() == playlistId){
            playlists.removeNode(cur);
            break;
        }
        cur = cur -> next;
    }
}

void Profile::addSongToPlaylist(Song *song, int playlistId) {
    /* TODO */
    Node<Playlist> *cur = playlists.getFirstNode();
    int s = playlists.getSize();
    for(int i = 0; i < s; i++){
        if((cur -> data).getPlaylistId() == playlistId){
            (cur -> data).addSong(song);
            break;
        }
        cur = cur -> next;
    }
}

void Profile::deleteSongFromPlaylist(Song *song, int playlistId) {
    /* TODO */
    getPlaylist(playlistId) -> dropSong(song);
}

Playlist *Profile::getPlaylist(int playlistId) {
    /* TODO */
    Node<Playlist> *cur = playlists.getFirstNode();
    int s = playlists.getSize();
    for(int i = 0; i < s; i++){
        if((cur -> data).getPlaylistId() == playlistId)
            return &(cur -> data);
        cur = cur -> next;
    }
}

LinkedList<Playlist *> Profile::getSharedPlaylists() {
    /* TODO */
    LinkedList<Playlist *> shpl;
    Node<Profile *> *cur = following.getFirstNode();
    if(cur != NULL){
        do{
            Node<Playlist> *cur1 = ((cur -> data) -> getPlaylists()).getFirstNode();
            if(cur1 != NULL){
                do{
                    if((cur1 -> data).isShared()){
                        shpl.insertAtTheEnd(&(cur1 -> data));
                    }
                    cur1 = cur1 -> next;
                }while(cur1 != ((cur -> data) -> getPlaylists()).getFirstNode());
            }
            cur = cur -> next;
        }while(cur != following.getFirstNode());
    }
    return shpl;
}

void Profile::shufflePlaylist(int playlistId, int seed) {
    /* TODO */
    getPlaylist(playlistId) -> shuffle(seed);
}

void Profile::sharePlaylist(int playlistId) {
    /* TODO */
    getPlaylist(playlistId) -> setShared(1);
}

void Profile::unsharePlaylist(int playlistId) {
    /* TODO */
    getPlaylist(playlistId) -> setShared(0);
}

bool Profile::operator==(const Profile &rhs) const {
    return this->email == rhs.email && this->username == rhs.username && this->plan == rhs.plan;
}

bool Profile::operator!=(const Profile &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Profile &profile) {
    os << "email: " << profile.email << " |";
    os << " username: " << profile.username << " |";
    if (profile.plan == free_of_charge) {
        os << " plan: " << "free_of_charge" << " |";
    } else if (profile.plan == premium) {
        os << " plan: " << "premium" << " |";
    } else {
        os << " plan: " << "undefined" << " |";
    }

    os << " playlists: [";
    Node<Playlist> *firstPlaylistNode = profile.playlists.getFirstNode();
    Node<Playlist> *playlistNode = firstPlaylistNode;
    if (playlistNode) {
        do {
            os << playlistNode->data;
            if (playlistNode->next != firstPlaylistNode) os << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != firstPlaylistNode);
    }
    os << "] |";
    os << " following: [";
    Node<Profile *> *firstProfileNode = profile.following.getFirstNode();
    Node<Profile *> *profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "] |";
    os << " followers: [";
    firstProfileNode = profile.followers.getFirstNode();
    profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "]";

    return os;
}
