#include "MatchThread.h"


using namespace std;
using namespace esg;

/*
    Battleplan:
        Program takes in inputs from the user and formats it
        into a reddit format for the /r/esg subreddit. The output
        is put into a text file.
        inputs:
            Opposing team name (If known)
            Opposing team tag
            bool values if opposing teams or strings set to NULL
            bool value if time is tentative or not.
            map name
                a bool value for cp maps on whether they are 5cp or not.
            time and date
            Future version: take in player names, and formats them into table
        variable:
            consts including map name beginnings.
            consts of strings for different maps.
            consts of reddit formatting including
                bullet points
                Big line thingy
                Bolds
        Future variations:
            Automatically enter in resources for previous matchs. These would be given with a file, that the program can read and look for the map. Once found, it would enter in the information about that map.
            
*/

void displayMatch(Match);
void acquireMatchDate(Match& Pres);
void acquireOpTeam(Match& Pres);
void acquireMap(Match& Pres);





int main()
{
    string str;

  

   esg::Match PresentMatch;

    system("cls");

    acquireMatchDate(PresentMatch);
    system("cls");
    getline(cin, str);

    acquireOpTeam(PresentMatch);
    system("cls");

    acquireMap(PresentMatch);

    system("cls");
    
    
    displayMatch(PresentMatch);
    cout << endl << endl;

    string gerald = esg::createString(PresentMatch);

    cout << gerald;

    getline(cin, str);

    esg::writeToFile(gerald);

   
    return 0;
}

void displayMatch(Match Pres)
{
    cout << Pres.day << " " << Pres.month << " " << Pres.mapName << " " << endl;
    if(Pres.Tentative)
        cout << "The date is tentative." << endl;
    if(Pres.OpponentsKnown)
    {
        cout << "The opposing team is " << Pres.opponents << ". Their tag is " << Pres.opponentTag << "." << endl;
    }
    else
    {
        cout << "The opposing team is unknown, the match server is unknown." << endl;
    }    
     
}

void acquireMatchDate(Match& Pres)
{
    system("cls");
    string str;
    string inputmo;
    int inputnumb;
    do{
    cout << "Please input the day the match will occur: ";
    cin >> inputnumb;
    getline(cin, str);
    if(inputnumb <= 0 || inputnumb > 31)
    {
        cout << endl << endl << "Please enter a valid input."<< endl;
        getline(cin, str);
        system("cls");
    }


    }while(inputnumb <=0 || inputnumb >31);
    Pres.day = inputnumb;

    do
    {
    system("cls");

    cout << "Match Date: " << Pres.day << endl << endl;
    cout << "Please enter the numerical month of the match: ";
    getline(cin, inputmo);


    if(validInputMo(inputmo) == mapError)
        cout << endl <<  "Please enter a valid month.";
        getline(cin, str);

    }while(validInputMo(inputmo) == mapError);
    Pres.month = validInputMo(inputmo);
}

void acquireOpTeam(Match& Pres)
{
    char input;
    string str;

    do
    {
    cout <<"Do you know your opposing team? Y/N: ";
    cin >> input;
    input =tolower(input);
    getline(cin, str);
    if(input !='y' && input != 'n')
        {
        cout << endl << endl << "Invalid input, try again.";
        getline(cin, str);
        }
    }while(input !='y' && input !='n');

    if(input =='y')
        Pres.OpponentsKnown = true;
    else
    {
        Pres.OpponentsKnown= false;
        Pres.opponents = "NONE";
        Pres.opponentTag = "NONE";
        Pres.Visiting=false;
        return;
    }
    system("cls");
    cout << "Please enter the enemy team name: ";
    getline(cin, Pres.opponents);
    getline(cin, str);

    system("cls");
    cout << "Opposing Team: " << Pres.opponents << endl << endl;
    cout << "Please enter the enemy team tag: ";
    cin >> Pres.opponentTag;
    getline(cin, str);
    system("cls");

    do
    {
    system("cls");
    cout << "Enemy team: " << Pres.opponents << "  " << Pres.opponentTag << endl << endl;
    cout <<"Are you the visiting team? Y/N: ";
    cin >> input;
    getline(cin, str);
    input= tolower(input);
    if(input !='y' && input != 'n')
    {
        cout << endl << endl << "Invalid input, try again.";
        getline(cin, str);
    }
    }while(input !='y' && input !='n');
    if(input == 'y')
        Pres.Visiting =true;
    else
        Pres.Visiting = false;

    return;

}
void acquireMap(Match& Pres)
{
    string str;
    string maptest;
    char input;

       
    do
    {
        system("cls");
        cout << "Please enter the map you are playing: ";
        cin >> Pres.mapName;
        getline(cin, str);
        if(esg::MapType(Pres.mapName) ==esg::mapError)
        {
            cout << endl << "Invalid map name.";
            getline(cin, str);
            continue;
        }
        else if(esg::MapType(Pres.mapName) == esg::CpStr)
        {
            do
            {
                
                cout << "Is the cp map 5cp? Y/N: ";
                cin >> input;
                input =tolower(input);
                getline(cin, str);
                if(input != 'y' && input !='n')
                {
                    cout << endl << endl << "Invalid input. Y/N.";
                    getline(cin, str);
                }   
            }while(input != 'y' && input !='n');
            

            if(input == 'y')
                Pres.map5cp = true;
            else
                Pres.map5cp = false;
               
        }

        
    }while(esg::MapType(Pres.mapName) == esg::mapError);
    
    return;
}    