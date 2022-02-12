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
    // TODO
    this->potentialPathCount = potentialPathCount;
    map = Graph(mapFilePath);
    cachedPaths = KeyedHashTable(potentialPathCount * map.TotalVertexCount());
    inJourney = false;
}

void METUMaps::SetDestination(const std::string& name)
{
    // TODO
    if(inJourney){
        PrintUnableToChangeDestination();
    }
    else{
        destination = name;
    }
}

void METUMaps::SetStartingLocation(const std::string& name)
{
    // TODO
    if(inJourney){
        PrintUnableToChangeStartingLoc();
    }
    else{
        startingLoc = name;
    }
}

void METUMaps::StartJourney()
{
    // TODO
    if(inJourney){
        PrintAlreadyInJourney();
        return;
    }
    currentLoc = startingLoc;
    PrintCalculatingRoutes(startingLoc, destination);
    for(int i = 0; i < map.TotalVertexCount(); i++){
        if(map.VertexName(i) == startingLoc){
            break;
        }
        else if(i == map.TotalVertexCount() - 1){
            PrintLocationNotFound();
            return;
        }
    }
    for(int i = 0; i < map.TotalVertexCount(); i++){
        if(map.VertexName(i) == destination){
            break;
        }
        else if(i == map.TotalVertexCount() - 1){
            PrintLocationNotFound();
            return;
        }
    }
    inJourney = true;
    std::vector<std::vector<int> > paths;
    int path_num = map.MultipleShortPaths(paths, startingLoc, destination, potentialPathCount);
    currentRoute = paths[0];
    for(int i = 0; i < paths.size(); i++){
        for(int j = 0; j < paths[i].size() - 1; j++){
            std::vector<int> cache_p;
            for(int k = j; k < paths[i].size(); k++){
                cache_p.push_back(paths[i][k]);
            }
            cachedPaths.Insert(GenerateKey(map.VertexName(paths[i][j]), map.VertexName(paths[i][paths[i].size() - 1])), cache_p);
        }
    }
}

void METUMaps::EndJourney()
{
    // TODO
    if(!inJourney){
        PrintJourneyIsAlreadFinished();
    }
    cachedPaths.ClearTable();
    startingLoc = "";
    destination = "";
    currentLoc = "";
    inJourney = false;
}

void METUMaps::UpdateLocation(const std::string& name)
{
    // TODO
    currentLoc = name;
    if(!inJourney){
        PrintNotInJourney();
        return;
    }
    for(int i = 0; i < map.TotalVertexCount(); i++){
        if(map.VertexName(i) == name){
            break;
        }
        else if(i == map.TotalVertexCount() - 1){
            PrintLocationNotFound();
            return;
        }
    }
    if(name == destination){
        PrintJourneyCompleted();
        return;
    }
    std::vector<int> to_go;
    if(cachedPaths.Find(to_go, GenerateKey(name, destination))){
        PrintCachedLocationFound(name, destination);
        currentRoute = to_go;
    }
    else{
        PrintCalculatingRoutes(name, destination);
        std::vector<std::vector<int> > paths;
        int path_num = map.MultipleShortPaths(paths, name, destination, potentialPathCount);
        currentRoute = paths[0];
        for(int i = 0; i < paths.size(); i++){
            for(int j = 0; j < paths[i].size() - 1; j++){
                std::vector<int> cache_p;
                for(int k = j; k < paths[i].size(); k++){
                    cache_p.push_back(paths[i][k]);
                }
                cachedPaths.Insert(GenerateKey(map.VertexName(paths[i][j]), map.VertexName(paths[i][paths[i].size() - 1])), cache_p);
            }
        }
    }
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