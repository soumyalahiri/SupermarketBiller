//	Author: Soumya Lahiri [say@soumyalahiri.com]

#include<bits/stdc++.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<iostream>
#include <string>
using namespace std;

int getTerminalSize() {
	struct winsize w;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&w);
	int col = w.ws_col;
	return col;
}

void addItems() {

	ofstream fout;
  	fout.open("items.txt", ios_base::app);

  	int price;
  	string toAppend;
  	string enterItem = "Enter item: ";
  	string enterPrice = "Enter price: ";
	
  	cout << enterItem;
	cin.ignore();
	getline(cin,toAppend);
	cout << enterPrice;
	cin >> price;
	fout << toAppend << endl << price << endl;

	fout.close();
}

void deleteLine(int lineCount) {
	ifstream fin("items.txt"); 
  
    ofstream fout; 
    fout.open("temp.txt", ofstream::out); 
  
    char c; 
    int lineNum = 1; 
    while (fin.get(c)) 
    { 
        if (c == '\n') 
        lineNum++; 
  
        if (lineNum != lineCount) 
            fout << c; 
    } 
  
    fout.close();
    fin.close(); 
  
    remove("items.txt");
    rename("temp.txt","items.txt"); 
}

void removeItems() {
	ifstream fin("items.txt");

	int lineCount = 0;

	string toRemove;
	string dummy;
	string enterRem = "Enter item to remove: ";

	cout << enterRem;
	cin.ignore();
	getline(cin,toRemove);

	while(!fin.eof()) {

		lineCount++;
		getline(fin,dummy);
      
	    if (dummy == toRemove) 
	        break;
	}

	deleteLine(lineCount);
	deleteLine(lineCount);

	fin.close();
}

void modifyItems() {

	int col = getTerminalSize();

	// Choices strings 

	string add = "1. Add Items";
	string rem = "2. Remove Items";
	string choose = "Enter choice: ";

	// Menu 

	int len = add.length();
	cout << setw((col/2)+(len/2)) << right << endl << add << endl;
	len = rem.length();
	cout << setw((col/2)+(len/2)) << right << rem << endl;	

	int op;
	len = choose.length();
	cout << choose;
	cin >> op;

	switch(op) {

		// Add items

		case 1:
			addItems();
			break;

		// Remove items

		case 2:
			removeItems();
			break;
	}
}

void readBill() {

	ifstream fin("bill.txt");

	string dummy;
	string tItems = "Total items: ";
	string tUnique = "Total unique items: ";
	string tAmt = "Total bill amount: ";

	int n,billAmt,qTemp;
	int totalUnits = 0;
	
	getline(fin,dummy);
	stringstream strToInt(dummy); 
    strToInt >> n;

    getline(fin,dummy);
	stringstream strToInt2(dummy); 
    strToInt2 >> billAmt;


    for(int i=0;i<40;i++)
    	cout << "=";

    cout << endl;

    cout << setw(12) << "Item";
    cout << setw(8) << "Price";
    cout << setw(12) << "Quantity";
    cout << setw(8) << "Total";

    cout << endl;

    for(int i=0;i<40;i++)
    	cout << "=";

    cout << endl;

    for(int i=0;i<n;i++) {
    	
    	//	Name
    	getline(fin,dummy);
    	cout << setw(12) << dummy;
    	
    	//	Price
    	getline(fin,dummy);
    	cout << setw(8) << dummy;
    	
    	//	Quantity
    	getline(fin,dummy);
    	cout << setw(12) << dummy;

    	stringstream strToInt3(dummy); 
    	strToInt3 >> qTemp;
    	totalUnits += qTemp;

    	//	Total
    	getline(fin,dummy);
    	cout << setw(8) << dummy;

    	cout << endl;

    }

    for(int i=0;i<40;i++)
    	cout << "=";

    cout << endl << endl;

    cout << tItems << totalUnits << endl << tUnique << n << endl << tAmt << billAmt << endl << endl;

    fin.close();

}

void saveBill(int n,int t,vector<string> items,int *price,int *quantity) {

	ofstream fout("bill.txt");

	fout << n << endl;	// Number of items
	fout << t << endl;	// Bill total

	for(int i=0;i<n;i++) {
		fout << items[i] << endl << price[i] << endl << quantity[i] << endl << price[i]*quantity[i] << endl;
	}

	//	Format:
	//	Item Name
	//	Item Price
	//	Item Quantity
	//	Item Total

	fout.close();

}

void billIt() {

	int n,q,p;
	int priceIter = 0;
	int quantIter = 0;
	int itemIter = 0;
	int billAmt = 0;
	string item;
	string charPrice;
	string enterCount = "Enter no. of items: ";
	string enterQuantity = "Enter quantity of ";

	ifstream fin("items.txt");

	cout << enterCount;
	cin >> n;
	cout << endl;

	int *quantity = new int[n];
	int *price = new int[n];
	vector<string> items;

	for(int i=0;i<n;i++) {
		getline(fin,item);
		getline(fin,charPrice);
		
		cout << enterQuantity << item << ": ";
		cin >> q;

		stringstream priceConv(charPrice); 
    	priceConv >> p;

    	if(q != 0) {
	    	quantity[quantIter++] = q;
	    	price[priceIter++] = p;
	    	items.push_back(item);

	    	billAmt += p * q;
    	}

    	if(q == 0)
    		i--;
	}

	saveBill(n,billAmt,items,price,quantity);
	
	cout << endl << endl;

	readBill();

}

int main() {

	int col = getTerminalSize();

	// Menu strings 

	string header = "Supermarket Biller";
	string underHeader = "============================";
	string firstOp = "1. Start Billing";
	string secondOp = "2. Add/Remove Items";
	string thirdOp = "3. View Last Bill";
	string choose = "Enter choice: ";
	string firstCh = "Starting Billing";
	string secondCh = "Modifying Items";
	string thirdCh = "Viewing Last Bill";

	// Header output

	int len = header.length();
	cout << setw((col/2)+(len/2)) << right << endl << header << endl;
	len = underHeader.length();
	cout << setw((col/2)+(len/2)) << right << underHeader << endl;
	
	while(1) {

		// Menu 

		len = firstOp.length();
		cout << setw((col/2)+(len/2)) << right << endl << firstOp << endl;
		len = secondOp.length();
		cout << setw((col/2)+(len/2)) << right << secondOp << endl;
		len = thirdOp.length();
		cout << setw((col/2)+(len/2)) << right << thirdOp << endl;

		int op;
		len = choose.length();
		cout << choose;
		cin >> op;

		switch(op) {
			case 1:
				len = firstCh.length();
				cout << setw((col/2)+(len/2)) << right << endl << firstCh << endl;
				billIt();
				break;
			case 2:
				len = secondCh.length();
				cout << setw((col/2)+(len/2)) << right << endl << secondCh << endl;
				modifyItems();
				break;
			case 3:
				len = thirdCh.length();
				cout << endl << thirdCh << endl << endl;
				readBill();
				break;
		}

		// Continue (Y/N)

		char exit;
		cout << "Continue? (Y/N) ";
		cin >> exit;
		if(exit == 'N' || exit == 'n')
			break;
	}
	return 0;
}
