#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) {
    /* TODO */
    Passenger newp(firstname, lastname);
    if(!searchPassenger(firstname, lastname))
        passengers.insert(newp);
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname) {
    /* TODO */
    Passenger newp(firstname, lastname);
    if(passengers.search(newp))
        return &(passengers.search(newp) -> data);
    else
        return NULL;
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    /* TODO */
    if(!there_is_f(flights.getRoot(), flightCode)){
        Flight newf(flightCode, departureTime, arrivalTime, departureCity, arrivalCity, economyCapacity, businessCapacity);
        flights.insert(newf);
    }
}

std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) {
    /* TODO */
    std::vector<Flight *> v;
    search_f_help(v, flights.getRoot(), departureCity, arrivalCity);
    return v;
}

void AirlineReservationSystem::search_f_help(std::vector<Flight *> &v, BSTNode<Flight> *root, const std::string departureCity, const std::string arrivalCity){
    if(root == NULL)
        return;
    if((root -> data).getDepartureCity() == departureCity && (root -> data).getArrivalCity() == arrivalCity){
        v.push_back(&(root -> data));
    }
    search_f_help(v, root -> left, departureCity, arrivalCity);
    search_f_help(v, root -> right, departureCity, arrivalCity);
}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    /* TODO */
    Passenger *p = searchPassenger(firstname, lastname);
    Flight *f = &(findFlight(flights.getRoot(), flightCode) -> data);
    if(p && f){
        Ticket t(p, f, ticketType);
        f -> addTicket(t);
    }
}

BSTNode<Flight> *AirlineReservationSystem::findFlight(BSTNode<Flight> *root, const std::string flightCode){
    if(root == NULL)
        return NULL;
    if((root -> data).getFlightCode() == flightCode){
        return root;
    }
    else if(there_is_f(root -> left, flightCode)){
        return findFlight(root -> left, flightCode);
    }
    else if(there_is_f(root -> right, flightCode)){
        return findFlight(root -> right, flightCode);
    }
    else{
        return NULL;
    }
}

bool AirlineReservationSystem::there_is_f(BSTNode<Flight> *root, const std::string flightCode){
    if(root == NULL){
        return false;
    }
    if((root -> data).getFlightCode() == flightCode){
        return true;
    }
    return there_is_f(root -> left, flightCode) || there_is_f(root -> right, flightCode);
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    /* TODO */
    Passenger *p = searchPassenger(firstname, lastname);
    Flight *f = &(findFlight(flights.getRoot(), flightCode) -> data);
    if(p && f){
        Ticket t(p, f, ticketType);
        freeTicketRequests.enqueue(t);
    }
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode) {
    /* TODO */
    Flight *f = &(findFlight(flights.getRoot(), flightCode) -> data);
    bool change = 0;
    int i, size = freeTicketRequests.size();
    for(i = 0; i < size; i++){
        Ticket t = freeTicketRequests.dequeue();
        if(t.getFlight() == f){
            if(f -> addTicket(t)){
                change = 1;
            }
        }
        if(!change){
            freeTicketRequests.enqueue(t);
        }
        change = 0;
    }
    f -> setCompleted(1);
}


void AirlineReservationSystem::print() const {
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}
