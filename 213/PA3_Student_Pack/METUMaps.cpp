#include "METUMaps.h"
#include "GraphExceptions.h"

#include <iostream>

void METUMaps::PrintNotInJourney() const
{
    std::cout << "Device is not in a journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeDestination() const
{
    std::cout << "Cannot change Destination during journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeStartingLoc() const
{
    std::cout << "Cannot change Starting Location during journey!" << std::endl;
}

void METUMaps::PrintAlreadyInJourney() const
{
    std::cout << "Device is already in a journey!" << std::endl;
}

void METUMaps::PrintJourneyIsAlreadFinished() const
{
    std::cout << "Journey is already finished!" << std::endl;
}

void METUMaps::PrintLocationNotFound() const
{
    std::cout << "One (or both) of the locations are not found in the maps!" << std::endl;
}

void METUMaps::PrintJourneyCompleted() const
{
    std::cout << "Journey Completed!" << std::endl;
}

void METUMaps::PrintCachedLocationFound(const std::string& location0,
                                        const std::string& location1) const
{
    std::cout << "Route between \""
              << location0 << "\" and \""
              << location1 << "\" is in cache, using that..."
              << std::endl;
}

void METUMaps::PrintCalculatingRoutes(const std::string& location0,
                                      const std::string& location1) const
{
    std::cout << "Calculating Route(s) between \""
              << location0 << "\" and \""
              << location1 << "\"..."
              << std::endl;
}

std::string METUMaps::GenerateKey(const std::string& location0,
                                  const std::string& location1)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    return location0 + "/" + location1;
}


METUMaps::METUMaps(int potentialPathCount,
                   const std::string& mapFilePath)
{   
    
    map= Graph(mapFilePath);
    this->potentialPathCount=potentialPathCount;
    this->inJourney=false;
    std::string startingLoc;
    std::string currentLoc;
    std::string destination;
    std::vector<int>currentRoute;
    this->startingLoc=startingLoc;
    this->currentLoc=currentLoc;
    this->destination=destination;
    this->currentRoute=currentRoute;
    cachedPaths=KeyedHashTable(potentialPathCount*map.TotalVertexCount());
    
   

  
    // TODO
}

void METUMaps::SetDestination(const std::string& name)
{    
    if(inJourney==true){
       PrintUnableToChangeDestination();
    }
    else{
        destination=name;
    }

    // TODO
}

void METUMaps::SetStartingLocation(const std::string& name)
{ 
    if (inJourney==true)
    {
        PrintUnableToChangeStartingLoc();
    }
    else{
        startingLoc=name;
    }

    // TODO
}

void METUMaps::StartJourney()
{   
   
    std::vector<std::vector <int> > list; 
    if(inJourney==true){
        PrintAlreadyInJourney();
    } 

    else
    {   
        bool start,dest;
        
        start=location_exist(startingLoc);
        dest=location_exist(destination);

        if(start==false || dest==false)
        {   PrintCalculatingRoutes(startingLoc,destination);
            PrintLocationNotFound();
        }

        else
        {   
            inJourney=true;
            PrintCalculatingRoutes(startingLoc,destination);
            map.MultipleShortPaths(list,startingLoc,destination,potentialPathCount);
            
            for(int i=0;i<potentialPathCount;i++)
            {   
                if(list[i].size()==0)
                    break;

                else
                {   std::vector<int> temp;
                    cachedPaths.Insert(GenerateKey(startingLoc,destination),list[i]);
                    temp=list[i];
                    
                    for(int j=1;j<list[i].size()-1;j++)
                    {   
                        
                        std::string new_location;     
                        temp=helper(temp);
                        new_location=map.VertexName(list[i][j]);
                        cachedPaths.Insert(GenerateKey(new_location,destination),temp);                       
                    }

                }    
                
            }
            currentLoc=startingLoc;
            currentRoute=list[0];
        
        }

    }

    
    // TODO
}

void METUMaps::EndJourney()
{ 
    if(inJourney==false){
        PrintJourneyIsAlreadFinished();
    }
    else{

    cachedPaths.ClearTable();
    std::string startingLoc;
    std::string currentLoc;
    std::string destination;
    this->startingLoc=startingLoc;
    this->currentLoc=currentLoc;
    this->destination=destination;       
    }
    // TODO
}

void METUMaps::UpdateLocation(const std::string& name)
{   
std::vector<int> list;

    if (inJourney==false){
        PrintNotInJourney();
    }
    else if (location_exist(name)==false){
        PrintLocationNotFound();
    }
    else if (name==destination){
        PrintJourneyCompleted();
    }
    else if(cachedPaths.Find(list,GenerateKey(name,destination))){
        currentLoc=name;
        if(name==destination){
            PrintJourneyCompleted);
        }
        else{
        PrintCachedLocationFound(name,destination);
        currentRoute= list;
        
        }

    }

    else{
        std::vector<std::vector<int> > paths;
        PrintCalculatingRoutes(name,destination);
        map.MultipleShortPaths(paths,name,destination,potentialPathCount);
        currentLoc=name;
            for(int i=0;i<potentialPathCount;i++)
            {
                if(paths[i].size()==0)
                    break;

                else
                {   std::vector<int> temp;
                    cachedPaths.Insert(GenerateKey(startingLoc,destination),paths[i]);
                    temp=paths[i];
                    
                    for(int j=1;j<paths[i].size()-1;j++)
                    {   
                        
                        std::string new_location;     
                        temp=helper(temp);
                        new_location=map.VertexName(paths[i][j]);
                        cachedPaths.Insert(GenerateKey(new_location,destination),temp);                       
                    }

                }    
                
            }        


    }   
    // TODO
}

void METUMaps::Display()
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    if(!inJourney)
    {
        // We are not in journey, this function
        // shouldn't be called
        PrintNotInJourney();
        return;
    }

    int timeLeft = map.TotalWeightInBetween(currentRoute);

    // Print last known location
    std::cout << "Journey         : " << startingLoc << "->"
              << destination << "\n";
    std::cout << "Current Location: " << currentLoc << "\n";
    std::cout << "Time Left       : " << timeLeft << " minutes\n";
    std::cout << "Current Route   : ";
    map.PrintPath(currentRoute, true);

    std::cout.flush();
}