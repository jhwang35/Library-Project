/// Program 1 - Library
/// Brief: This program is a library management system which takes in data such as book title, 
/// isbn number, and checkout status. Using them to display the library's statistics.
/// Author: Justin Hwang 
/// Date: 9/5/2023
/// CS 251, Fall 2023
/// System: Visual Studio Code, Windows


// You cannot use any libraries beyond the ones we have given below.
// You must use output streams, file streams, vectors, and strings.
// You are not allowed to use any other containers or objects.
// You may not use structs, pointers, or dynamic memory allocations.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;


// Function prototypes for all the glorious function decomposition
void printoutCheckout(vector<string> book, vector<string> isbn, vector<int> status){
    int inLibrary = 0;
    int checkedOut = 0;
    int onLoan = 0;
    int unknownState = 0;
    int invalidState = 0;

    for (size_t i = 0; i < book.size(); i++){ 
            if (status.at(i) == 0){
                inLibrary += 1;
            } // if status == 0 end

            else if (status.at(i) == 1){
                checkedOut += 1;

            } // if status == 1 end

            else if (status.at(i) == 2){
                onLoan += 1;

            } //if status == 2 end

            else if (status.at(i) == 3){
                unknownState += 1;

            }

            else{
                invalidState += 1;

            } // if status == unknown

        }

    cout << "Your Current Library's Stats" << endl; 
    cout << "----------------------------"<< endl;
    cout << "Total Books: " << book.size() << endl;
    cout << "   In Library: " << inLibrary << endl;
    cout << "   Checked Out: " << checkedOut << endl;
    cout << "   On Loan: " << onLoan << endl;
    cout << "   Unknown: " << unknownState << endl;
    cout << "   Other: " << invalidState << endl << endl;




};
void addItem(vector<string> &book, vector<string> &isbn, vector<int> &status){
    string name;
    string code;

    //asks for book title then pushes back to the book vector
    cout << "What is the book title? " << endl;
    getline(cin, name);
    if (name.find(",") != string::npos){
        cout << "The book title cannot contain commas." << endl;
    }
    else{
        book.push_back(name);

        //asks for isbn number then pushes back to the isbn vector
        cout << "What is the 13-digit ISBN (with hyphens)? " << endl;
        getline(cin, code);
        isbn.push_back(code);

        status.push_back(0);
        cout << "The Following Entry Was Added" << endl;
        cout << "-----------------------------" << endl;
        cout << name << " --- " << code << " --- In Library" << endl << endl;
    }
    
};

void clearEntries(vector<string> &book, vector<string> &isbn, vector<int> &status){
    //clears all vectors 

    book.clear();
    isbn.clear();
    status.clear();

    cout << "Your library is now empty." << endl;
};
void displayEntries(vector<string> book, vector<string> isbn, vector<int> status){

    //loops through the vector and prints the book title, isbn, and status
    //using if else loop to write status given the status number    
    //0 - In Library (default value)
    //1 - Checked Out
    //2 - On Loan
    //3 - Unknown State
    //All Others - Invalid State

    cout << "Your Current Library" << endl;
    cout << "--------------------" << endl;

   for (size_t i = 0; i < book.size(); i++){
            cout << book.at(i) << " --- " << isbn.at(i) << " --- "; 
            if (status.at(i) == 0){
                cout << "In Library" << endl << endl;
            } // if status == 0 end

            else if (status.at(i) == 1){
                cout << "Checked Out" << endl << endl;

            } // if status == 1 end

            else if (status.at(i) == 2){
                cout << "On Loan" << endl << endl; 

            } //if status == 2 end

            else if (status.at(i) == 3){
                cout << "Unknown State" << endl << endl;

            }

            else{
                cout << "Invalid State" << endl << endl;

            } // if status == unknown

        }

    if (book.empty()){
        cout << "The library has no books." << endl;
    }

};
void listInvalidEntries(vector<string> titles, vector<string> isbn, vector<int> status){
    
};
void loadLibrary(vector<string> &book, vector<string> &isbn, vector<int> &status){
    //loads book information from csv and updates our vectors
    //info is separated by commas, have to take string before comma occurs
    //take the line, then use find() to get comma location, substr() to get a substring and push it back to vector
    //if a special character is the substring, then you can pushback a default value  

    string fileName, line, title, isbnNum, statusNum;
    size_t commaPos = 0;
    size_t commaPos2 = 0;
    int counter = 0;
    ifstream inFS;
    
    cout << "What database to read from? " << endl;
    getline(cin, fileName); // get file name
    
    inFS.open(fileName); //opens file

    //gives error message if file cant be opened
    if (!inFS.is_open()){
        cout << "Could not find the database file." << endl;
    }
   
    while(getline(inFS,line)){
        commaPos = line.find(",");
        title = line.substr(0, commaPos);
        book.push_back(title);
        
        commaPos2 = line.find(",", commaPos + 1); // adding one to account for ending at the previous comma
        if (commaPos == string::npos){ // check if there is an actual string till the end 
            isbn.push_back("000-0-00-000000-0");
            status.push_back(0);
        }
        else{
            isbnNum = line.substr(commaPos + 2, (commaPos2 - commaPos) - 2); // add two to go past the comma and space, subtracting 2 from distance to account for the same space being removed
            isbn.push_back(isbnNum);
            
            if (commaPos2 == string::npos){
                status.push_back(0);
            }
            else{
                statusNum = line.substr(commaPos2 + 2);
                status.push_back(stoi(statusNum));
                
            }


    }
    counter += 1;
    }
    inFS.close();

    if (counter >= 1){
    cout << "Read in " << counter << " lines from the file." << endl;
    }
};
void outputLibrary(vector<string> book, vector<string> isbn, vector<int> status){

    ofstream outFS; //write in file
    string fileName;
    getline(cin, fileName);

    outFS.open(fileName);

    for (size_t i = 0; i < book.size(); i++){
        outFS << book.at(i) << ", " << isbn.at(i) << ", " << status.at(i) << endl;    //writes the title, isbn, and status serparated by commas

    }

    outFS.close();
};
void removeEntry(vector<string> &book, vector<string> &isbn, vector<int> &status){
    // removes latest entry by using either title or isbn

    bool found = 0;  // determines which message is output (missing or not)
    string title, code, choice;


    cout << "Would you like remove by (1) name or (2) ISBN." << endl;
    cout << "Enter the numeric choice: " << endl;

    getline(cin, choice);
    if(choice == "1"){
        cout << "Enter the book name: " << endl;
        getline(cin, title);
        cout << "The Following Entry Was Removed From The Library" << endl ;
        cout << "------------------------------------------------" << endl;
        for (int i = book.size() - 1; i > 0; i--){ //iterating backwards to get the latest entry
            if (book.at(i) == title){
                cout << book.at(i) << " --- " << isbn.at(i) << " --- In Library" << endl;
                book.erase(book.begin()  + i);
                isbn.erase(isbn.begin()  + i);
                status.erase(status.begin()  + i);
                found = 1;
                break;                        //does not need to look further since we have the latest entry
            }
        }

    }
    else if(choice == "2"){
        cout << "Enter the book 13-digit ISBN (with dashes): " << endl;
        getline(cin, code);
        cout << "The Following Entry Was Removed From The Library" << endl;
        cout << "------------------------------------------------" << endl;
        for (int i = isbn.size() - 1; i > 0; i--){ //iterating backwards to get the latest entry
            if (isbn.at(i) == code){
                cout << book.at(i) << " --- " << isbn.at(i) << " --- In Library" << endl;
                book.erase(book.begin() + i);
                isbn.erase(isbn.begin() + i);
                status.erase(status.begin() + i);
                found = 1;
                break;               //does not need to look further since we have the latest entry
            }
        }
        
    }
    else {
        cout << "Invalid remove by choice option." << endl << endl;
        found = 1; //set to 1 so the non match message does not appear 
    }
    if(found == 0){
        cout << "No matching entry found in the library." << endl << endl;
    }

    
};
void searchEntry(vector<string> book, vector<string> isbn, vector<int> status){

    // user can search for book using either name or isbn

    bool found = 0;  // determines which message is output (missing or not)
    string title, code, choice;


    cout << "Would you like to search by (1) name or (2) ISBN." << endl;
    cout << "Enter the numeric choice: " << endl;

    getline(cin, choice);
    if(choice == "1"){
        cout << "Enter the book name: " << endl;
        getline(cin, title);
        cout << "The Following Are Your Search Results" << endl;
        cout << "-------------------------------------" << endl;
        for (int i = book.size() - 1; i > 0; i--){ //iterating backwards to get the latest entry
            if (book.at(i) == title){
                cout << book.at(i) << " --- " << isbn.at(i) << " --- In Library" << endl;
                found = 1;
                break;                        //does not need to look further since we have the latest entry
            }
        }

    }
    else if(choice == "2"){
        cout << "Enter the book 13-digit ISBN (with dashes): " << endl;
        getline(cin, code);
        cout << "The Following Are Your Search Results" << endl;
        cout << "-------------------------------------" << endl;
        for (int i = isbn.size() - 1; i > 0; i--){ //iterating backwards to get the latest entry
            if (isbn.at(i) == code){
                cout << book.at(i) << " --- " << isbn.at(i) << " --- In Library" << endl;
                found = 1;
                break;               //does not need to look further since we have the latest entry
            }
        }
        
    }
    else {
        cout << "Invalid search by choice option." << endl << endl;
        found = 1; //set to 1 so the non match message does not appear 
    }

    if(found == 0){
        cout << "No matching entry found in the library." << endl << endl;
    }
    

};

/// @brief print out the main menu of the management system
void printMenu()
{
    cout << "Library Management Menu" << endl;
    cout << "-----------------------" << endl;
    cout << "A - Add Item To Library" << endl;
    cout << "C - Clear The Library Of All Entries" << endl;
    cout << "D - Display Library Entries" << endl;    
    cout << "I - List Invalid Library Entries" << endl;
    cout << "L - Load Library From File" << endl;    
    cout << "O - Output Library To File" << endl;
    cout << "P - Print Out Checkout Stats" << endl;
    cout << "R - Remove A Library Entry" << endl;      
    cout << "S - Search For A Library Entry" << endl;    
    cout << "X - Exit Program" << endl;
}


int main()
{
    string command;

    // TODO: define your variables
    vector<string> bookTitles; 
    vector<string> isbnNumber;
    vector<int> checkoutStatus;

    cout << "Welcome to the Library Management System" << endl;
    cout << "----------------------------------------" << endl;
    // cout << endl;

    do 
    {
        // Output the menu and acquire a user selection
        printMenu();
        cout << endl << "Enter a command (case does not matter): ";

        // We use getline for all user input to avoid needing to handle
        // input buffer issues relating to using both >> and getline
        getline(cin, command);
        cout << endl;

        // TODO: Execute non-exit commands
        if (command == "a" || command == "A"){
        addItem(bookTitles, isbnNumber, checkoutStatus);
        }
        
        else if(command == "d" || command == "D" ){
        displayEntries(bookTitles, isbnNumber, checkoutStatus);

        }
        else if(command == "c" || command == "C" ){
        clearEntries(bookTitles, isbnNumber, checkoutStatus);

        }
        else if(command == "l" || command == "L" ){
        loadLibrary(bookTitles, isbnNumber, checkoutStatus);

        }
        else if(command == "o" || command == "O" ){
        outputLibrary(bookTitles, isbnNumber, checkoutStatus);

        }
        else if(command == "p" || command == "P" ){
        printoutCheckout(bookTitles, isbnNumber, checkoutStatus);

        }
        else if(command == "s" || command == "S" ){
        searchEntry(bookTitles, isbnNumber, checkoutStatus);

        }
        else if(command == "r" || command == "R" ){
        removeEntry(bookTitles, isbnNumber, checkoutStatus);

        }
        else if(command == "i" || command == "I" ){
        listInvalidEntries(bookTitles, isbnNumber, checkoutStatus);

        }
    
    } while (!(command == "x" || command == "X"));

    return 0;
}

// Function definitions for all the glorious function decomposition
// Tip: alphabetical order makes it easy to find things if you have
//      a lot of function decomposition.

