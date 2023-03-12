#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) {
    
    Passenger mamiris_grubu(firstname,lastname);
    
    if(passengers.search(mamiris_grubu) == NULL)  
        passengers.insert(mamiris_grubu);
    
    /* TODO */
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname) {
    BSTNode<Passenger> *tree=passengers.getRoot();
    Passenger *ptr= &tree->data;
    

          for(;tree!=NULL;){
            
            if(ptr->getFirstname()==firstname && ptr->getLastname()==lastname)
                break;        
            tree=passengers.getSuccessor(tree,preorder);              
            ptr=&tree->data;          
        }

        if(tree!=NULL){
        if(ptr->getFirstname()==firstname && ptr->getLastname()==lastname)
                return ptr;
        }
                
        return NULL;
    /* TODO */
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    BSTNode<Flight> *tree=flights.getRoot(); 
    Flight *ptr=&tree->data;
  
    Flight new_flight (flightCode,departureTime,arrivalTime,departureCity,arrivalCity,economyCapacity,businessCapacity);

        for(;tree!=NULL;){
            
            if(ptr->getFlightCode()==flightCode)
                break;
            
            tree=flights.getSuccessor(tree,preorder);
            ptr=&tree->data;           

        }
    if(tree==NULL)
            flights.insert(new_flight);            
    /* TODO */
}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    Passenger pass(firstname,lastname);
    BSTNode<Flight> *tree;
    Flight *ptr=&tree->data;
    
    if(passengers.search(pass) == NULL)  
        ;
    else{
        for(;tree!=NULL;){
            
            if(ptr->getFlightCode()==flightCode)
                break;        
            tree=flights.getSuccessor(tree,preorder);
            ptr=&tree->data;           

        }
        if(Flight::addTicket()==false||tree=NULL)
            ;
        else{
            Ticket::(pass,flightCode,ticketType);
        }
    }


    /* TODO */
}



void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    
    /* TODO */
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode) {
    
    /* TODO */
}

std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) {
    
    /* TODO */
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
