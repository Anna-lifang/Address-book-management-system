#include <iostream>
#include <string>
#define MAX 1000
using namespace std;

struct Person
{
  string m_Name;
  int m_Sex; //1 male 2 female
  int m_Age;
  string m_Phone;
  string m_Addr;

};

struct Addressbooks
{
  // array to put contacts
  struct Person personArray[MAX];
  // number of contacts now
  int m_Size;
};

// add infomation of the perosn
void addInfo(Addressbooks *abs, int n)
{
   //add name
        string name;
        cout << "Please input the name: " <<endl;
        cin>> name;
        abs->personArray[n].m_Name = name;
   
    // add sex
        cout << "Please input the sex: " <<endl;
        cout <<"1 -- male" << endl;
        cout <<"2 -- female" << endl;
        int sex = 0;
        while(1){
        cin >> sex;  
        if(sex == 1 || sex == 2)
        {
            abs->personArray[n].m_Sex = sex;
            break;
        }
        cout << "Please input sex again, 1--male; 2--female " <<endl;
        }

     // add age
    cout << "Please input the age: " << endl;
    int age = 0;
    cin >> age;
    abs->personArray[abs->m_Size].m_Age = age;
    
    //add phone number
    cout << "Please input the phone mumber: " << endl;
    string phone;
    cin >> phone;
    abs->personArray[abs->m_Size].m_Phone = phone;

    // add address
    cout << "Please input the addree: " << endl;
    string address;
    cin >> address;
    abs->personArray[abs->m_Size].m_Addr = address;
    


}


// add contacts
void addPerson(Addressbooks *abs)
{
    if(abs->m_Size == MAX)
    {
        cout << " Addressbook is full,you can add any more" <<endl;
        return;
    }
    else
    {   
         addInfo(abs, abs->m_Size);
    }

    //update the number of contacts
    abs->m_Size++;
    cout << " add contact successfully"<< endl;

    system("pause"); // press any key to continue
    system("cls"); // claer the screen

}

// display contacts
void showPerson(Addressbooks *abs)
{
    if(abs->m_Size == 0)
    {
        cout << "The contacts are empty" <<endl;
    }
    else
    {
       for(int i = 0; i < abs->m_Size ;i++ )
       {
        cout << " Name: " <<abs->personArray[i].m_Name <<"\t"
        " Age: " <<abs->personArray[i].m_Age <<"\t"
        " Sex: " <<(abs->personArray[i].m_Sex == 1 ? "male" : "female") <<"\t"
        " Phone: " <<abs->personArray[i].m_Phone<<"\t"
        " address: " <<abs->personArray[i].m_Addr <<endl;
       }

    }
system("pause"); // press any key to continue
system("cls"); // claer the screen
}

// check if the person is in the contacts. if yes, return the index of the person, otherwise, return -1
int isExist(Addressbooks *abs, string name)
{
   for(int i = 0; i < abs->m_Size ;i++ )
   {
       if(abs->personArray[i].m_Name == name)
       {
           return i;
       }
   }
   return -1;
}

//delete contact
void deletePerosn(Addressbooks *abs)
{
    string name;
    cout << "Please input the name which is going to be deleted" <<endl;
    cin >> name;
    int ret = isExist(abs,name);

    if(ret != -1)
    {
      for(int i = ret; i < abs->m_Size; i++ )
      {
        abs->personArray[i] = abs->personArray[i + 1];
      }
      abs->m_Size--;
      cout << "delete successfully" << endl;
    }
    else
    {
       cout << "No that person" <<endl;
    }
system("pause"); // press any key to continue
system("cls"); // claer the screen
   
}

// search contact

void findPerson(Addressbooks *abs)
{
    cout << "Please input the name to search " << endl;
    string name;
    cin >> name;
    int ret = isExist(abs,name);

    if(ret != -1)
    {
      cout << " Name: " <<abs->personArray[ret].m_Name <<"\t"
        " Age: " <<abs->personArray[ret].m_Age <<"\t"
        " Sex: " <<(abs->personArray[ret].m_Sex == 1 ? "male" : "female") <<"\t"
        " Phone: " <<abs->personArray[ret].m_Phone<<"\t"
        " address: " <<abs->personArray[ret].m_Addr <<endl;
      cout << "search successfully" << endl;
    }
    else
    {
       cout << "No that person" <<endl;
    }

 system("pause"); // press any key to continue
 system("cls"); // claer the screen
}

//modify the contact
void modifyPerson(Addressbooks *abs)
{
    cout << "Please input the name to modify " << endl;
    string name;
    cin >> name;
    int ret = isExist(abs,name);

    if(ret != -1)
    {
      addInfo(abs, ret);
    }
    
    else
    {
       cout << "No that person" <<endl;
    }

 system("pause"); // press any key to continue
 system("cls"); // claer the screen
}

//clear all contacts
void clearPerson(Addressbooks *abs)
{
   abs->m_Size = 0;
   cout << "Clear all the contacts" <<endl;
   system("pause");
   system("cls");
}



// menu display
void showMenu()
{
  cout << "*******************************" <<  endl;  
  cout << "***** 1. add contacts     *****" <<  endl;
  cout << "***** 2. display contacts *****" <<  endl;
  cout << "***** 3. delete contacts  *****" <<  endl;
  cout << "***** 4. search contacts  *****" <<  endl;
  cout << "***** 5. modify contacts  *****" <<  endl;
  cout << "***** 6. clear contacts   *****" <<  endl;
  cout << "***** 0. exit contacts    *****" <<  endl;
  cout << "*******************************" <<  endl;  
}

int main(){
    // create contact struct
    Addressbooks abs;
    abs.m_Size = 0;
    int select = 0;

    while(true){
        showMenu();
    cout << "Please choose the mune number:" << endl;
    cin >> select;
    switch(select)
    {
        case 1:    // add contacts 
            addPerson(&abs);
            break;
        case 2:
            showPerson(&abs);
            break; // display contacts
        case 3:    // delete contacts
        
           deletePerosn(&abs);
           break;   
        case 4:   // search contacts
            findPerson(&abs);
            break;
        case 5:   // modify contacts
            modifyPerson(&abs);
            break; 
        case 6:    // clear contacts
            clearPerson(&abs);
            break;
        case 0:  //exit contacts
            cout << " welcome to use it again" << endl;
            system("pause");
            return 0;
            break;
        default:
            break;
    }
    } 
    system("pause");
    return 0;
}