#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
    int visited;
} City;

// Ýki þehir arasýndaki mesafeyi hesapla
double calculateDistance(City city1, City city2) {
    return sqrt((city2.x - city1.x) * (city2.x - city1.x) + (city2.y - city1.y) * (city2.y - city1.y));
}

double nearestNeighborMinDistance(City* cities, int numCities,int x) {
    int i, j;
    int currentCity = x;
    cities[currentCity].visited = 1;
    double totalDistance = 0.0;
    
    for (i = 0; i < numCities - 1; i++) {
        int nearestCity = -1;
        double minDistance = __DBL_MAX__;
        
        // En yakýn þehri bul
        for (j = 0; j < numCities; j++) {
            if (cities[j].visited==0) {
                double distance = calculateDistance(cities[currentCity], cities[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestCity = j;
                }
            }
        }
        
        // En yakýn þehri ziyaret et ve güncelle
        totalDistance += minDistance;
        currentCity = nearestCity;
        cities[currentCity].visited = 1;
    }
    
    // Son olarak baþlangýç þehrine geri dön
    totalDistance += calculateDistance(cities[currentCity], cities[x]);
    for(int i=0;i<numCities;i++){
    		cities[i].visited = 0;
	}
    return totalDistance;
}

void nearestNeighborPath(City* cities, int numCities,int x) {
    int i, j;
    int currentCity = x;
    cities[currentCity].visited = 1;
    printf("Gezilen Sehirler:\n%d ", currentCity);
    
    for (i = 0; i < numCities - 1; i++) {
        int nearestCity = -1;
        double minDistance = __DBL_MAX__;
        
        // En yakýn þehri bul
        for (j = 0; j < numCities; j++) {
            if (cities[j].visited==0) {
                double distance = calculateDistance(cities[currentCity], cities[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestCity = j;
                }
            }
        }
        
        // En yakýn þehri ziyaret et ve güncelle
        currentCity = nearestCity;
        cities[currentCity].visited = 1;
        printf("%d ", currentCity);
    }
    printf("%d\n", x);
}

void tspSolution(City* cities, int numCities){
    double value;
    double enKucukYol=__DBL_MAX__;
    int startCity;
    for(int i=0;i<numCities;i++){
    	value=nearestNeighborMinDistance(cities, numCities,i);
    	if(value<enKucukYol){
    		enKucukYol=value;
    		startCity=i;
		}
	}
    printf("En kucuk maliyet=%.2f\nBaslangic sehri=%d\n\n",enKucukYol,startCity);
    printf("TSP yol : \n");
    nearestNeighborPath(cities,numCities,startCity);
}

int main() {
	/*
	tsp_51_1" / tsp_100_2" / tsp_783_1" / tsp_4461_1" / tsp_85900_1"
	*/
    FILE *file = fopen("Data\\tsp_783_1", "r");
    if (file == NULL) {
        perror("Dosya açýlamadý");
        return 1;
    }
    
    int numCities;
    fscanf(file, "%d", &numCities);
    City* cities = (City* )malloc(numCities * sizeof(City));
    
    for (int i = 0; i < numCities; i++) {
        fscanf(file, "%d %d", &cities[i].x, &cities[i].y);
        cities[i].visited = 0;
    }
    
    fclose(file);
    
    tspSolution(cities,numCities);
    
    free(cities);
    
    return 0;
}

