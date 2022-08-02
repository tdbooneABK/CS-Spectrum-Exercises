#include "CityGraph.h"

int main()
{
    CityGraph graph = CityGraph();
    graph.AddCity("Phoenix", -112.406f, 33.6057f);
    graph.AddCity("Los Angeles", -118.693f, 34.0207f);
    graph.AddCity("San Diego", -117.390f, 32.8248f);
    graph.AddCity("Irvine", -117.844f, 33.6866f);
    graph.AddCity("Tucson", -111.024f, 32.1561f);
    graph.AddCity("Las Vegas", -115.315f, 36.1252f);
    graph.AddCity("Denver", -104.996f, 39.7645f);
    graph.AddCity("Dallas", -96.8720f, 32.8209f);
    graph.AddCity("St. Louis", -90.3839f, 38.6533f);

    graph.AddTwoWayConnection("Phoenix", "Los Angeles", 373.0f);
    graph.AddTwoWayConnection("Phoenix", "San Diego", 355.0f);
    graph.AddTwoWayConnection("Phoenix", "Tucson", 112.0f);
    graph.AddTwoWayConnection("Phoenix", "Las Vegas", 302.0f);
    graph.AddTwoWayConnection("Phoenix", "Los Angeles", 373.0f);
    graph.AddTwoWayConnection("Phoenix", "Denver", 822.0f);
    graph.AddTwoWayConnection("Phoenix", "Dallas", 1065.0f);
    graph.AddTwoWayConnection("San Diego", "Los Angeles", 120.0f);
    graph.AddTwoWayConnection("Las Vegas", "Los Angeles", 270.0f);
    graph.AddTwoWayConnection("Irvine", "Los Angeles", 40.0f);
    graph.AddTwoWayConnection("San Diego", "Tucson", 405.0f);
    graph.AddTwoWayConnection("Tucson", "Dallas", 959.0f);
    graph.AddTwoWayConnection("Denver", "Dallas", 795.0f);
    graph.AddTwoWayConnection("Denver", "St. Louis", 851.0f);
    graph.AddTwoWayConnection("St. Louis", "Dallas", 630.0f);

    graph.GetPathBetweenCities("Los Angeles", "St. Louis");

    graph.GetPathBetweenCities("Irvine", "Denver");

    graph.GetPathBetweenCities("Las Vegas", "Tucson");

    graph.GetPathBetweenCities("St. Louis", "San Diego");
}
