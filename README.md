# Real-Time Ride Matching System

## Overview
A C++ simulation of a ride-sharing platform that matches riders with nearby drivers using spatial indexing. The system leverages a K-D Tree for efficient nearest-driver search, Dijkstra's Algorithm for shortest route computation, and a Priority Queue for surge pricing management.

## Features
- Nearest Driver Search using K-D Tree
- Real-Time Rider-Driver Matching
- Shortest Route Calculation using Dijkstra's Algorithm
- Surge Pricing Simulation using Min Heap
- Efficient Spatial Query Processing 

## Data Structures & Algorithms
- **K-D Tree** -> Spatial indexing and nearest-neighbor search
- **Graph** -> Road network representation
- **Dijkstra's Algorithm** -> Route optimization
- **Priority Queue (Min Heap)** -> Surge pricing management
- **Vectors & Structures** -> Driver and location management

## Compilation & Execution
g++ ride_matching.cpp -o ride_matching  
./ride_matching

## Sample Output
===== REAL TIME RIDE MATCHING =====  

Rider Location: (4, 5)  
Matched Driver ID: 3  

Shortest Route Distance: 15  

Base Fare: 100  
Surge Multiplier: 1.5x  
Final Fare: 150  

## Applications
- Ride-Sharing Platforms (Uber,Lyft,Ola)
- Food Delivery Services
- Logistics & Fleet Management
- Location-Based Services

## Future Enhancements
- A* Search for faster routing
- Multiple rider requests
- Driver availability tracking
- Dynamic traffic conditions
- Real-world map integration

## Author
Varnika Shukla
