#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Train 
{
public:
    int number;
    string departureTime;
    string destination;

    Train(int num, string time, string dest) : number(num), departureTime(time), destination(dest) {}

    friend ostream& operator<<(ostream& os, const Train& train);
    friend istream& operator>>(istream& is, Train& train);
};

ostream& operator<<(ostream& os, const Train& train) 
{
    os << train.number << " " << train.departureTime << " " << train.destination;
    return os;
}

istream& operator>>(istream& is, Train& train) 
{
    is >> train.number >> train.departureTime >> train.destination;
    return is;
}

class RailwayStation 
{
private:
    vector<Train> trains;

public:
    void addTrain(const Train& train) 
    {
        trains.push_back(train);
    }

    void printAllTrains() const 
    {
        for (const auto& train : trains) 
        {
            cout << train << endl;
        }
    }

    void printTrainByNumber(int number) const 
    {
        for (const auto& train : trains) 
        {
            if (train.number == number) 
            {
                cout << train << endl;
                return;
            }
        }
        cout << "Train not found" << endl;
    }

    void editDepartureTime(int number, const string& newTime) 
    {
        for (auto& train : trains) 
        {
            if (train.number == number) 
            {
                train.departureTime = newTime;
                return;
            }
        }
        cout << "Train not found" << endl;
    }

    void sortTrainsByTime() 
    {
        for (size_t i = 0; i < trains.size(); ++i) 
        {
            for (size_t j = i + 1; j < trains.size(); ++j) 
            {
                if (trains[i].departureTime > trains[j].departureTime) 
                {
                    swap(trains[i], trains[j]);
                }
            }
        }
    }

    void printTrainsByDestination(const string& destination) const 
    {
        for (const auto& train : trains) 
        {
            if (train.destination == destination) 
            {
                cout << train << endl;
            }
        }
    }

    void saveToFile(const string& filename) const 
    {
        ofstream outFile(filename);
        for (const auto& train : trains) 
        {
            outFile << train << endl;
        }
    }

    void loadFromFile(const string& filename) 
    {
        ifstream inFile(filename);
        Train train(0, "", "");
        while (inFile >> train) 
        {
            trains.push_back(train);
        }
    }
};

int main() 
{
    RailwayStation station;

    station.addTrain(Train(101, "12:30", "Kyiv"));
    station.addTrain(Train(102, "15:45", "Lviv"));
    station.addTrain(Train(103, "10:00", "Odessa"));

    cout << "All trains:" << endl;
    station.printAllTrains();

    cout << "\nTrain with number 102:" << endl;
    station.printTrainByNumber(102);

    station.editDepartureTime(102, "16:00");
    cout << "\nTrain with number 102 after editing time:" << endl;
    station.printTrainByNumber(102);

    station.sortTrainsByTime();
    cout << "\nAll trains after sorting by time:" << endl;
    station.printAllTrains();

    cout << "\nTrains going to Lviv:" << endl;
    station.printTrainsByDestination("Lviv");

    station.saveToFile("trains.txt");

    RailwayStation newStation;
    newStation.loadFromFile("trains.txt");
    cout << "\nAll trains from file:" << endl;
    newStation.printAllTrains();
}
