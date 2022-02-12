#include "Passenger.h"

Passenger::Passenger(std::string firstname, std::string lastname) {
    this->firstname = firstname;
    this->lastname = lastname;
}

const std::string &Passenger::getFirstname() const {
    return firstname;
}

const std::string &Passenger::getLastname() const {
    return lastname;
}

bool Passenger::operator<(const Passenger &rhs) const {
    /* TODO */
    int i = 0;
    while(lastname[i]){
        if(!rhs.lastname[i]){
            return false;
        }
        else if(lastname[i] < rhs.lastname[i]){
            return true;
        }
        else if(lastname[i] > rhs.lastname[i]){
            return false;
        }
        i++;
    }
    if(rhs.lastname[i]){
        return true;
    }
    i = 0;
    while(firstname[i]){
        if(!rhs.firstname[i]){
            return false;
        }
        else if(firstname[i] < rhs.firstname[i]){
            return true;
        }
        else if(firstname[i] > rhs.firstname[i]){
            return false;
        }
        i++;
    }
    if(rhs.firstname[i]){
        return true;
    }
}

bool Passenger::operator>(const Passenger &rhs) const {
    return rhs < *this;
}

bool Passenger::operator==(const Passenger &rhs) const {
    return firstname == rhs.firstname && lastname == rhs.lastname;
}

bool Passenger::operator!=(const Passenger &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Passenger &passenger) {
    os << "Passenger(firstname: " << passenger.firstname;
    os << ", lastname: " << passenger.lastname << ")";
    return os;
}
