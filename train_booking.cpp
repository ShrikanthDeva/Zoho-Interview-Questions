#include<bits/stdc++.h>
using namespace std;

int t_id = 1;
int p_id = 1;
int b_id = 1;



class Passenger {

    public:
        int Passenger_id;
        string Passenger_name;
        string Seat_type;
        string Source;
        string Destination;
        int Booking_id;
        int Ride_fare;
        int Seat_id;
        int Date;

        Passenger(string Passenger_name, string Seat_type, string Source, string Destination, int Date){

            this->Passenger_id = p_id;
            this->Passenger_name = Passenger_name;
            this->Seat_type = Seat_type;
            this->Source = Source;
            this->Destination = Destination;
            this->Ride_fare = 0;
            this->Seat_id = 0;
            this->Date = Date;

            p_id++;

        }

        void printDetails(){
            cout<<"Passenger_id    = " << this->Passenger_id << endl;
            cout<<"Passenger_name  = " << this->Passenger_name << endl;
            cout<<"Booking_id      = " << this->Booking_id << endl;
            cout<<"Date            = " << this->Date << endl;
            cout<<"Source          = " << this->Source << endl;
            cout<<"Destination     = " << this->Destination << endl;
            cout<<"Seat_id         = " << this->Seat_id << endl;
            cout<<"Ride_fare       = " << this->Ride_fare << endl;
        }
};


class Train {
    public:
        int Train_id;
        string Train_name;

        // map<int,vector<int>> Seats;
        int Total_stations;
        map<string,int> Stations;
        vector<int> Premium_seats;
        vector<int> Normal_seats;
        int Premium_surge;
        int Premium_base;
        int Normal_base;
        int Total_revenue;

        vector<Passenger> passengers_list;

        Train(string Train_name, int Premium_tickets, int Normal_tickets, int Total_stations){

            this->Train_id = t_id;
            this->Train_name = Train_name;
            this->Premium_surge = 0;
            this->Premium_base = 20;
            this->Normal_base = 10;
            this->Total_revenue = 0;
            this->Total_stations = Total_stations;
            
            for(int station = 0; station < Total_stations; station++ ){
                this->Premium_seats.push_back(Premium_tickets);
                this->Normal_seats.push_back(Normal_tickets);
            }

            getStationDetail(Total_stations);
            t_id++;
        }

        void bookTicket(Passenger &passenger){
            

            if( passenger.Seat_type == "Premium"){

                int from_station_id = this->Stations[passenger.Source]-1;
                if (this->Premium_seats[from_station_id] >= 1){
                    cout << "\n\nPremimum Seat Alloted\n";
                    int to_station_id = this->Stations[passenger.Destination]-1;
                    for(int i = from_station_id; i <= to_station_id-1; i++){
                        this->Premium_seats[i] -= 1;
                    }
                    passenger.Seat_id = this->Premium_seats[from_station_id]+1;
                    passenger.Booking_id = b_id;
                    passenger.Ride_fare = abs(from_station_id - to_station_id)* this->Premium_base + this->Premium_surge;
                    this->Premium_surge += 5;
                    this->Total_revenue += abs(from_station_id - to_station_id)* this->Premium_base + this->Premium_surge;
                    b_id++;
                    passenger.printDetails();
                    this->passengers_list.push_back(passenger);
                }
                else{
                    cout <<"\nSorry No Premium Tickets Available\n ";
                }
            }
            else{
                int from_station_id = this->Stations[passenger.Source]-1;
                if (this->Normal_seats[from_station_id] >= 1){
                    cout << "\n\nNormal Seat Alloted\n";
                    int to_station_id = this->Stations[passenger.Destination]-1;
                    for(int i = from_station_id; i <= to_station_id-1; i++){
                        this->Normal_seats[i] -= 1;
                    }
                    passenger.Seat_id = this->Normal_seats[from_station_id]+1;
                    passenger.Booking_id = b_id;
                    passenger.Ride_fare = abs(from_station_id - to_station_id)*this->Normal_base;
                    this->Total_revenue += abs(from_station_id - to_station_id)*this->Normal_base;
                    b_id++;
                    passenger.printDetails();
                    this->passengers_list.push_back(passenger);

                }
                else{
                    cout <<"\nSorry No Normal Tickets Available\n ";
                }
            }
        }

        void cancelTicket(int booking_id){
            
            for(auto &it: passengers_list){
                if (it.Booking_id == booking_id){

                    int from_station_id = this->Stations[it.Source]-1;
                    int to_station_id = this->Stations[it.Destination]-1;
                    for(int i = from_station_id; i <= to_station_id-1; i++){
                        if(it.Seat_type == "Normal"){
                            this->Normal_seats[i] += 1;
                        }
                        else{
                            this->Premium_seats[i] += 1;   
                        }

                    }
                    it.Seat_id = 0;
                    it.Ride_fare = 0;
                    if(it.Seat_type == "Normal"){

                        this->Total_revenue -= abs(from_station_id - to_station_id)*this->Normal_base;
                    }
                    else{
                        this->Total_revenue -= abs(from_station_id - to_station_id)*this->Premium_base;   
                    }
                    
                    cout<<"\nTicket Successfully Cancelled\n"<<endl;
                    it.printDetails();
                }
            }
            
        }

        void getStationDetail(int Total_stations){

            cout << "Enter the Station_Names\n";
            for(int i = 0; i < Total_stations; i++){
                string station_name;
                cin >> station_name;
                this->Stations[station_name] = i+1;
            }

        }

        void printDetails(){
            cout<<"\n\nTrain_id          = " << this->Train_id << endl;
            cout<<"Train_name        = " << this->Train_name << endl;
            if (this->Stations.size() >= 1){
                cout<<"Stations : " << endl;            
                for(auto &it: this-> Stations){
                    cout<< it.second << "  " << it.first << endl;
                }
            }
            
            cout<<"Premium_base      = " << this->Premium_base << " Rs/-" << endl;
            cout<<"Premium_surge     = " << this->Premium_surge << " Rs/-" << endl;
            cout<<"Normal_base       = " << this->Normal_base << " Rs/-" << endl;
            cout<<"Total_revenue     = " << this->Total_revenue << " Rs/-\n\n" << endl;
        }

};



int main(){

    
    // int total_num_of_trains;
    // cout<<"Enter the number of trains\n";
    // cin >> total_num_of_trains;

    // vector<Train> trains;
    // for(int i = 0; i < total_num_of_trains; i++){}

    int id,p_seats,n_seats,stations;
    string name;

    cout<<"Enter Train name : \n";
    cin >> name;
    cout<<"Enter Train date : \n";
    cin >> id;
    cout<<"Enter the no of premium seats : \n";
    cin >> p_seats;
    cout<<"Enter the no of normal seats : \n";
    cin >> n_seats;
    cout<<"Enter the no of station : \n";
    cin >> stations;
    Train t(name, p_seats, n_seats, stations);
    cout<<"Train created Successfully\n";
    t.printDetails();

    
    


    string pname,source,destination,seat_type;
    int date;
    cout<<"Passenger name : ";
    cin >> pname;
    cout<<"Travel date : ";
    cin >> date;
    cout<<"Source : ";
    cin >> source;
    cout<<"Destination : ";
    cin >> destination;
    cout<<"Seat type : ";
    cin >> seat_type;
    Passenger P1(pname, seat_type, source, destination, date);
    t.bookTicket(P1);
    t.printDetails();
    t.cancelTicket(P1.Booking_id);
    t.printDetails();


    cout<<"\n\nPassenger name : ";
    cin >> pname;
    cout<<"Travel date : ";
    cin >> date;
    cout<<"Source : ";
    cin >> source;
    cout<<"Destination : ";
    cin >> destination;
    cout<<"Seat type : ";
    cin >> seat_type;
    Passenger P2(pname, seat_type, source, destination, date);
    t.bookTicket(P2);

    t.printDetails();

    return 0;
}