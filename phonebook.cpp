#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <cctype>

using namespace std;

//colors

const string RESET = "\033[0m";
const string BLACK = "\033[30m";      //Black
const string RED = "\033[31m";      //Red
const string GREEN = "\033[32m";      //Green
const string YELLOW = "\033[33m";      //Yellow
const string BLUE = "\033[34m";      //Blue
const string MAGENTA = "\033[35m";      //Magenta
const string CYAN = "\033[36m";      //Cyan
const string WHITE = "\033[37m";      //White
const string BOLDBLACK = "\033[1m\033[30m";      //Bold Black
const string BOLDRED = "\033[1m\033[31m";      //Bold Red
const string BOLDGREEN = "\033[1m\033[32m";      //Bold Green
const string BOLDYELLOW = "\033[1m\033[33m";      //Bold Yellow
const string BOLDBLUE = "\033[1m\033[34m";      //Bold Blue */
const string BOLDMAGENTA = "\033[1m\033[35m";      //Bold Magenta
const string BOLDCYAN = "\033[1m\033[36m";      //Bold Cyan
const string BOLDWHITE = "\033[1m\033[37m";      //Bold White

//structure to hold contact information
struct contact{
    int id;
    char fName[50];
    char lName[50];
    char gen[10];
    char phNum[20];
};

const char* validGenders[] = {"M", "m", "F", "f"};

//All the functions in this program
void display(contact contact1);
int prompt();
void viewContacts();
bool isAlpha(char a[]);
bool isTen(char b[]);
void findContact();
void createContact();
bool remContact(int idNum);
void modContact();
char continueQue(string c);


void display(contact contact1) {
    //Format of displaying contacts when prompted
    cout<<BOLDMAGENTA<<"----------------------------------------------------------"<<RESET<<endl;
    cout<<BLUE<<"ID:\t"<<setw(9)<<contact1.id<<endl;
    cout<<YELLOW<<"----------------------------------------------------------"<<RESET<<endl;
    cout<<CYAN<<"Full Name:\t"<<setw(4)<<contact1.fName<<" "<<contact1.lName<<endl;
    cout<<"Gender:\t"<<setw(9)<<contact1.gen<<endl;
    cout<<"Phone Number:\t"<<setw(9)<<contact1.phNum<<RESET<<endl;
    cout<<BOLDMAGENTA<<"----------------------------------------------------------"<<RESET<<endl;
    cout<<endl;
}

int prompt() {
    //ask the user what they want to do

    int choice;
    cout<<CYAN<<"MENU: "<<RESET<<endl;
    cout<<YELLOW<<"  1) View all contacts"<<endl;
    cout<<"  2) Search for a contact"<<endl;
    cout<<"  3) Add a new contact"<<endl;
    cout<<"  4) Modify existing contact"<<endl;
    cout<<"  5) Remove existing contact"<<endl;
    cout<<"  6) Close Phone book"<<RESET<<endl;
    cout<<"Enter choice: ";
    cin>>choice;
    return choice;
}

void viewContacts() {
    //view all the contacts in phone book

    ifstream input("C:\\Users\\ADI\\Desktop\\phonebook.bin",ios::binary);
    if (!input.is_open()) {
        cout<<RED<<"Error opening file";
        return;
    }

    contact contact1;
    while (input.read((char*)&contact1, sizeof(contact))) {
        display(contact1);
    }
    input.close();
}

bool isAlpha(char a[]) {
    //Checks if all the characters are alphabets
    for (int i = 0; i < strlen(a); i++) {
        if (!isalpha(a[i])) return false;
    }
    return true;
}

bool isTen(char b[]) {
    //Checks the length of the phone number and that no alphabets are included
    if ((strlen(b) != 10) || (isAlpha(b))) {
        return false;
    }
    else return true;
}

char continueQue(string c) {
    char yN;
    cout<<MAGENTA<<"Do you want to "<<c<<" another contact?(y/n)"<<RESET<<endl;
    cin>>yN;

    return yN;
}

void findContact() {

    ifstream input("C:\\Users\\ADI\\Desktop\\phonebook.bin",ios::binary);
    contact contact2;

    bool found = false;

    char contactName[100];
    cout<<BOLDMAGENTA<<"Enter Contact Full Name to search: "<<RESET;
    cin.ignore();
    cin.getline(contactName, 100);

    while (input.read((char*)&contact2, sizeof(contact))) {
        char fullName[100];
        strcpy(fullName, contact2.fName);
        strcat(fullName, " ");
        strcat(fullName, contact2.lName);

        if (strcmp(contactName, fullName) == 0) {
            display(contact2);
            found = true;
        }
    }
    if (!found) {
        cout<<RED<<"Contact with name "<<contactName<<" not found!"<<RESET<<endl;
    }
    input.close();
    char cont = continueQue("find");

    if ((cont == 'y') || (cont == 'Y')) {
        system("cls");
        findContact();
    } else {
        system("cls");
    }
}


void createContact() {
    fstream myFile("C:\\Users\\ADI\\Desktop\\phonebook.bin",ios::in|ios::out|ios::binary|ios::app);

    //add a new contact to the phone book
    contact newContact;

    fName:
    cout<<"Enter contact's first name:  "<<BOLDMAGENTA;
    cin>>newContact.fName;

    if (!isAlpha(newContact.fName)) {
        cout<<RED<<"The first name you entered contains invalid characters. Please enter an appropriate first name"<<RESET<<endl;
        goto fName;
    }

    lName:
    cout<<RESET<<"Enter contact's last name:  "<<BOLDMAGENTA;
    cin>>newContact.lName;


    if (!isAlpha(newContact.lName)) {
        cout<<RED<<"The last name you entered contains invalid characters. Please enter an appropriate last name"<<RESET<<endl;
        goto lName;
    }

    gen:
    //char temp[10];
    cout<<RESET<<"Enter contact's gender:  "<<BOLDMAGENTA;
    cin>>newContact.gen;

    bool valid = false;
    for (const char* validGender : validGenders) {
        if (strcmp(newContact.gen, validGender) == 0) {
            valid = true;
            newContact.gen[0] = toupper(newContact.gen[0]);
            break;
        }
    }

    if (!valid) {
        cout<<RED<<"Invalid gender entered."<<RESET<<endl;
        goto gen;
    }

    phNum:
    cout<<RESET<<"Enter contact's phone number:  "<<BOLDMAGENTA;
    cin>>newContact.phNum;

    cout<<RESET;

    if (!isTen(newContact.phNum)) {
        cout<<RED<<"Invalid phone number entered. Please enter a 10 digit phone number."<<RESET<<endl;
        goto phNum;
    }

    for (int i = 0; i < strlen(newContact.phNum); i++) {
        if (!isdigit(newContact.phNum[i])) {
            cout<<RED<<"Invalid phone number entered. Please enter only digits."<<RESET<<endl;
            break;
        }
        break;
    }

    if (newContact.phNum[0] != '0') {
        cout<<RED<<"Invalid phone number entered. Please enter a phone number that starts with 09 or 07"<<RESET<<endl;
        goto phNum;
    }

    if (myFile) {
        myFile.seekg(0, ios::end);
        int total = myFile.tellg();
        if (total > 0) {
            int lastId = (total / sizeof(contact));
            newContact.id = lastId + 1;
        } else {
            newContact.id = 1;
        }
    } else {
        newContact.id = 1;
    }


    myFile.write((char*)&newContact, sizeof(contact));
    myFile.close();
    cout<<BOLDGREEN<<"Contact successfully created"<<RESET<<endl;

    char cont = continueQue("add");

    if ((cont == 'y') || (cont == 'Y')) {
        system("cls");
        createContact();
    } else {
        system("cls");
        viewContacts();
        //prompt();
    }
}

bool remContact(int idNum) {


    ifstream inFile("C:\\Users\\ADI\\Desktop\\phonebook.bin", ios::binary);
    if (!inFile) {
        cout<<RED<<"Error opening file for reading."<<RESET<<endl;
    }

    contact contact3;
    bool found = false;

    ofstream tempFile("C:\\Users\\ADI\\Desktop\\temp.bin",ios::binary);
    int newId = 1;

    while (inFile.read((char*)&contact3, sizeof(contact))) {
        if (contact3.id == idNum) {
            found = true;
        } else {
            contact3.id = newId++;
            tempFile.write((char*)&contact3, sizeof(contact));
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove("C:\\Users\\ADI\\Desktop\\phonebook.bin");
        rename("C:\\Users\\ADI\\Desktop\\temp.bin", "C:\\Users\\ADI\\Desktop\\phonebook.bin");
    } else {
        remove("C:\\Users\\ADI\\Desktop\\temp.bin");
        cout << "Contact with ID " << idNum << " not found." << endl;
    }
    return found;
}


void modContact() {
    //alter the contact information

    fstream modfile("C:\\Users\\ADI\\Desktop\\phonebook.bin",ios::in|ios::out|ios::binary);
    if (!modfile.is_open()) cout<<"file not open"<<endl;

    contact contact2;
    bool found = false;

    int idNum, choice, curPos = 0;
    cout<<BOLDMAGENTA<<"Enter Id number of the contact information you want to edit: "<<RESET<<endl;
    cin>>idNum;

    while (modfile.read((char*)&contact2, sizeof(contact))) {
        if (contact2.id == idNum - 1) {
            curPos = modfile.tellg();
        }
        if (contact2.id == idNum) {
            found = true;
            break;
        }
    }

    if (found) {
        remContact(idNum);
        cout<<CYAN<<"1. Edit first name"<<endl;
        cout<<"2. Edit last name"<<endl;
        cout<<"3. Edit Gender"<<endl;
        cout<<"4. Edit Phone Number"<<endl;
        cout<<"5. Exit"<<RESET<<endl;
        cin>>choice;

        modfile.seekg(curPos,ios::beg);
        bool valid = false;

        switch(choice) {
        case 1:
            //edit first name
            editfName:
            cout<<BOLDMAGENTA<<"Enter new first name: "<<RESET<<endl;
            cin>>contact2.fName;

            if (!isAlpha(contact2.fName)) {
                cout<<RED<<"The last name you entered contains invalid characters. Please enter an appropriate last name"<<RESET<<endl;
                goto editfName;
            }
            break;
        case 2:
            //edit last name
            editlName:
            cout<<BOLDMAGENTA<<"Enter new last name: "<<RESET<<endl;
            cin>>contact2.lName;

            if (!isAlpha(contact2.lName)) {
                cout<<RED<<"The last name you entered contains invalid characters. Please enter an appropriate last name"<<RESET<<endl;
                goto editlName;
            }
            break;
        case 3:
            //edit gender
            editGen:
            char temp[10];
            cout<<BOLDMAGENTA<<"Enter new gender: "<<RESET<<endl;
            cin>>contact2.gen;

            for (const char* validGender : validGenders) {
                if (strcmp(contact2.gen, validGender) == 0) {
                    valid = true;
                    contact2.gen[0] = toupper(contact2.gen[0]);
                    break;
                }
            }

            if (!valid) {
                cout<<RED<<"Invalid gender entered."<<RESET<<endl;
                goto editGen;
            }
            break;
        case 4:
            //edit phone number
            editphNum:
            cout<<BOLDMAGENTA<<"Enter new phone number: "<<RESET<<endl;
            cin>>contact2.phNum;

            if (!isTen(contact2.phNum)) {
                cout<<RED<<"Invalid phone number entered. Please enter a 10 digit phone number."<<RESET<<endl;
                goto editphNum;
            }

            for (int i = 0; i < strlen(contact2.phNum); i++) {
                if (!isdigit(contact2.phNum[i])) {
                    cout<<RED<<"Invalid phone number entered. Please enter only digits."<<RESET<<endl;
                    goto editphNum;
                }
            }

            if (contact2.phNum[0] != '0') {
                cout<<RED<<"Invalid phone number entered. Please enter a phone number that starts with 09 or 07"<<RESET<<endl;
                goto editphNum;
            }
            break;
        case 5:
        //clear screen
            system("CLS");
            prompt();
            break;
        }
        modfile.write((char*)&contact2, sizeof(contact));
    }
    else {
        cout<<"Contact with ID "<<idNum<<" not found."<<endl;
    }
    modfile.close();

    char cont = continueQue("modify");

    if ((cont == 'y') || (cont == 'Y')) {
        system("cls");
        modContact();
    }
}


int main() {
    int choice;
    char cont;
    bool del;
    Start:
    choice = prompt();

    //string myFile = "C:\\Users\\ADI\\Desktop\\phonebook.bin";


    switch(choice) {
    case 1:
        system("CLS");
        viewContacts();
        goto Start;
        break;
    case 2:
        system("CLS");
        findContact();
        goto Start;
        break;
    case 3:
        system("CLS");
        createContact();
        goto Start;
        break;
    case 4:
        system("CLS");
        modContact();
        goto Start;
        break;
    case 5:
        system("CLS");
        id:
        int idNum;
        cout<<BOLDMAGENTA<<"Enter the Id number of the contact information you want to delete: "<<RESET<<endl;
        cin>>idNum;
        del = remContact(idNum);
        if (del) cout<<GREEN<<"Contact with Id number "<<idNum<<" successfully deleted."<<RESET<<endl;
        cont = continueQue("delete");
        if ((cont == 'y') || (cont == 'Y')) {
            system("cls");
            goto id;
        }
        goto Start;
        break;
    case 6:
        break;
    default:
        cout<<RED<<"Invalid choice. Please try again."<<RESET<< endl;
        goto Start;
        break;
    }
    return 0;
}
