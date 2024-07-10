#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;

class Venue{
public:
string name;
vector<string> dates;

Venue(){}

Venue(string &x){
  name= x;
}

void addDate(string &date){
    for(auto i: dates){
        if(i== date){
            cout<<"Cant add same date twice"<<endl;
            return;
        }
    }
    dates.push_back(date);
    return;
}

bool bookDate(string &date){
    for(int i= 0; i<dates.size(); i++){
       if(dates[i]== date){
        dates.erase(dates.begin() + i);
        return true;
       }
    }
    cout<<"Date can't be booked"<<endl;
    return false;
}
};

class BookingSystem{
   map<string, Venue> venues;

   public:
   void addVenue(string &name){
    venues[name]= Venue(name);
    return ;
   }

   void addDatetoVenue(string &name, string &date){
    venues[name].addDate(date);
    return ;
   }

   bool bookVenue(string &name, string &date){
    return venues[name].bookDate(date);
   }

   void loadFromCSV(string fileName){
    ifstream file(fileName);
    string line;

    while(getline(file, line)){
        istringstream ss(line);
        string Vname, Vdate;
        getline(ss, Vname, ',');
        addVenue(Vname);

        while(getline(ss, Vdate, ',')){
            addDatetoVenue(Vname, Vdate);
        }
    }
    file.close();
    return ;
   }

   void saveToCSV(string filename){
    ofstream file(filename);

    for(auto pr: venues){
        file<<pr.first;
        for(auto dt: pr.second.dates){
            file<<','<<dt;
        }
        file<<'\n';
    }

    file.close();
    return ;
   }

  void printVenues(){
    for(auto pr: venues){
        cout<<pr.first<<" ";
        for(auto dt: pr.second.dates){
            cout<<dt<<" ";
        }
        cout<<endl;
    }
  }
};

int main(){

BookingSystem tmp;
tmp.loadFromCSV("venues.csv");

while(1){
    cout<<"1. Add Venue\n2. Add availability to Venue\n3. Book Venue \n4. Show Venues \n5. Exit\n";

    int n;
    cin>>n;

   if(n== 1){
      string name;
      cout<<"Enter venue name"<<endl;
      getline(cin, name);
      getline(cin, name);
      tmp.addVenue(name);
   }

   else if(n== 2){
    string name, date;
    cout<<"Enter venue name"<<endl;
    getline(cin, name);
    getline(cin, name);
    cout<<"Enter date in format DD-MM-YYYY"<<endl;
    cin>>date;
    tmp.addDatetoVenue(name, date);
   }

   else if(n== 3){
    string name, date;
    cout<<"Enter venue name"<<endl;
    getline(cin, name);
    getline(cin, name);
    cout<<"Enter date"<<endl;
    cin>>date;
    tmp.bookVenue(name, date);
   }

   else if(n== 4){
    tmp.printVenues();
   }

   else{
    tmp.saveToCSV("venues.csv");
    break;
   }
}

return 0;
}
