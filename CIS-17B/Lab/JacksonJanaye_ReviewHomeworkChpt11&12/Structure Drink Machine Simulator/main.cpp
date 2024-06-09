#include <iostream>
#include<iomanip>

using namespace std;

struct Drink{
  string name;
  int cost;
  int amnt;
    
};

int main(){
	//your code here
	string match, pymnt;
	int total = 0;
	int paid = 0;
	int index;
	const int SIZE = 5;
	Drink drnklst[SIZE] = { {"Cola", 75, 20},
	                        {"Root Beer", 75, 20},
	                        {"Lemon-Lime", 75, 20},
	                        {"Grape Soda", 80, 20},
	                        {"Cream Soda", 80, 20}};
	
	
   while(match != "Quit") {
	    for(int i = 0; i < SIZE; i++){
	        cout<<left<<setw(11)<<drnklst[i].name<<setw(4)<<drnklst[i].cost<<drnklst[i].amnt<<endl;
	    }
	    cout<<"Quit"<<endl;
	    getline(cin,match);
	    getline(cin, pymnt);
	    
	    if(match == drnklst[0].name)
	    {
	       index = 0;
	    }
	    else if(match == drnklst[1].name)
	    {
	        index = 1;
	    }
	    else if(match == drnklst[2].name)
	    {
	        index = 2;
	    }
	    else if(match == drnklst[3].name)
	    {
	        index = 3;
	    }
	    else if(match == drnklst[4].name)
	    {
	       index = 4;
	    }
	    else if(match == drnklst[5].name)
	    {
	        index = 5;
	    }
	     
	    if(index >= 0)
	    {
	        total += drnklst[index].cost;
	        drnklst[index].amnt -= 1;
	        paid = stoi(pymnt);
	        cout<<paid - drnklst[index].cost<<endl;
	    }
	    index = -1;
    }
    
    cout<<total<<endl;
	
	return 0;
}