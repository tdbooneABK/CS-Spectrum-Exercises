#include <iostream>
#include "CityGraph.h"
#include "City.h"
#include "Link.h"
#include "math.h"

CityGraph::CityGraph()
{}

CityGraph::~CityGraph()
{
	m_CitiesMap.clear();
}

void CityGraph::AddCity(std::string name, float longitude, float latitude) {
	m_CitiesMap.insert(std::pair<std::string, City>(name, City(name, latitude, longitude)));
}

void CityGraph::AddTwoWayConnection(std::string city1, std::string city2, float distance) {
	City* firstCity = &(m_CitiesMap.at(city1));
	City* secondCity = &(m_CitiesMap.at(city2));
	firstCity->AddLink(secondCity, distance);
	secondCity->AddLink(firstCity, distance);
}

float estDistanceBetweenCities(City* city1, City* city2) {
    return (sqrtf(powf(abs(city1->GetLat() - city2->GetLat()), 2.0f)
		+ powf(abs(city1->GetLong() - city2->GetLong()), 2.0f))) * 52.5f;
}

void CityGraph::GetPathBetweenCities(std::string city1, std::string city2) {
	std::cout << "Finding path from " << city1 << " to " << city2 << std::endl;

    City* startCity = &(m_CitiesMap.at(city1));
    City* endCity = &(m_CitiesMap.at(city2));

	struct PathSoFar {
		float distanceSoFar;
		float distanceWithHeuristicValue;
        City* thisCity;
        City* prevCity;
		PathSoFar(float distance, float totalDistance, City* thisCity, City* prevCity = nullptr)
            : distanceSoFar(distance)
            , distanceWithHeuristicValue(totalDistance)
            , thisCity(thisCity)
            , prevCity(prevCity)
        {
        }
	};

    struct Node {
        PathSoFar value;
        Node* next;
        Node(PathSoFar value, Node* next = nullptr)
            : value(value)
            , next(next)
        {}
        ~Node()
        {}
    };

    class LinkedList {
        Node* head;
        int size;
    public:
        LinkedList()
            : head(nullptr)
            , size(0)
        {}
        ~LinkedList()
        {
            Node* currentNode = head;
            while (currentNode != nullptr) {
                Node* nodeToDelete = currentNode;
                currentNode = currentNode->next;
                delete nodeToDelete;
            }
        }
        Node* GetHead() { return head; }
        int GetSize() { return size; }
        void AddNode(PathSoFar value) {
            // If the list is empty, then the new node is the new head
            if ((head == nullptr) || (value.distanceWithHeuristicValue < head->value.distanceWithHeuristicValue)) {
                head = new Node(value, head);
                size++;
            }
            else {
                Node* currentNode = head;
                bool insertedNew = false;
                while (currentNode != nullptr) {
                    // If a node with a lower score for the same destination already exists, then don't add it again
                    if (currentNode->value.thisCity == value.thisCity && currentNode->value.distanceWithHeuristicValue <= value.distanceWithHeuristicValue) {
                        break;
                    }
                    // If we reach the end of the list and haven't found a higher node, then add this node to the very end
                    else if (!insertedNew && currentNode->next == nullptr) {
                        currentNode->next = new Node(value);
                        size++;
                        break;
                    }
                    // Insert the new node just before the net highest node on the list
                    else if (!insertedNew && currentNode->next->value.distanceWithHeuristicValue >= value.distanceWithHeuristicValue) {
                        Node* temp = currentNode->next;
                        currentNode->next = new Node(value, temp);
                        currentNode = currentNode->next;
                    }
                    // The linked list should yank out any matching nodes with a HIGHER score after finding one with a lower score.
                    else if (insertedNew && currentNode->next->value.thisCity == value.thisCity) {                        
                        Node* nodeToDelete = currentNode->next;
                        currentNode->next = currentNode->next->next;
                        delete nodeToDelete;
                        break;
                    }
                    else {
                        currentNode = currentNode->next;
                    }
                }
            }
        };
        PathSoFar PopHead() {
            if (head) {
                PathSoFar returnValue = head->value;
                head = head->next;
                size--;
                return returnValue;
            }
        }
    };

    LinkedList openList = LinkedList();
    std::map<std::string, PathSoFar> closedList;

    PathSoFar start = PathSoFar(0.0f, estDistanceBetweenCities(startCity, endCity), startCity);
    openList.AddNode(start);
    bool destinationFound = false;

    while (openList.GetSize() > 0) {
        PathSoFar topNode = openList.PopHead();
        //std::cout << "Evaluating paths from:" << topNode.thisCity->GetName() << std::endl;

        // Look through all connected nodes
        std::vector<Link*> linksFromTopNode = topNode.thisCity->GetLinks();
        for (std::vector<Link*>::iterator it = linksFromTopNode.begin(); it < linksFromTopNode.end(); it++) {
            City* nodeToCheck = (*it)->GetDestination();
            // If it's the goal, then print out the winning path and distance, then return.
            std::map<std::string, PathSoFar>::iterator cityInClosed = closedList.find(nodeToCheck->GetName());
            // TODO: see if this works by comparing the pointers instead of the names?
            if (nodeToCheck->GetName() == city2) {
                std::cout << "Destination found!" << std::endl;
                closedList.insert({
                    city2,
                    PathSoFar(
                        topNode.distanceSoFar + (*it)->GetDistance(),
                        topNode.distanceSoFar + (*it)->GetDistance() + estDistanceBetweenCities(nodeToCheck, endCity),
                        nodeToCheck,
                        topNode.thisCity
                    )
                    });
                destinationFound = true;
                break;
            }
            // If it's not on the closed list, then add it to the open list
            else if (cityInClosed == closedList.end()) {
                //std::cout << "Evaluating step to " << destination->GetName() << std::endl;
                openList.AddNode(PathSoFar(
                    topNode.distanceSoFar + (*it)->GetDistance(),
                    topNode.distanceSoFar + (*it)->GetDistance() + estDistanceBetweenCities(nodeToCheck, endCity),
                    nodeToCheck,
                    topNode.thisCity
                ));
            }
        }

        // Add the node we just checked through to the closed list
        closedList.insert({ topNode.thisCity->GetName(), PathSoFar(topNode) });
        if (destinationFound) {
            break;
        }
    }

    if (destinationFound) {
        std::map<std::string, PathSoFar>::iterator currentJourneyStep = closedList.find(city2);
        std::cout << "Final Distance: " << currentJourneyStep->second.distanceSoFar << "mi" << std::endl;
        std::vector<std::string> pathFromDestination;
        // Reconstruct the path to the destination by going backwards
        while (currentJourneyStep != closedList.end()) {
            pathFromDestination.push_back(currentJourneyStep->second.thisCity->GetName());
            if (currentJourneyStep->second.prevCity) {
                currentJourneyStep = closedList.find(currentJourneyStep->second.prevCity->GetName());
            }
            else {
                currentJourneyStep = closedList.end();
            }
        }
        std::cout << "Path to destination: " << std::endl;
        // Iterate through pathFromDestination backwards to print out the path from start to finish
        for (std::vector<std::string>::reverse_iterator i = pathFromDestination.rbegin(); i < pathFromDestination.rend(); i++) {
            std::cout << *i << std::endl;
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Cannot connect those two cities!" << std::endl << std::endl;
    }
}