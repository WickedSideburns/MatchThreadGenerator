#include <string>
#include <iostream>
#include <fstream>
#include <locale>
#include <ctime>



using namespace std;

namespace esg
{


const string lineSeg = "------------------------------------------------";
const string PayloadStr="pl_";
const string CpStr = "cp_";
const string CtfStr = "ctf_";
const string KothStr = "koth_";
const string mapError = "ERR0R";
const string roles[10] = {"Pyro", "Scout", "Soldier", "Demo", "Engineer", "Medic", "Sniper", "Spy", "Heavy", "Backup"};
const string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

struct Match
{
    string opponents;
    string opponentTag;
    string mapName;
    bool map5cp;
    bool OpponentsKnown;
    bool Tentative;
    bool Visiting;
   string month;
    int day;
};

string MapType(string MapInput)
{   
    locale loc;
    for(int i = 0; i < MapInput.length(); i++)
       MapInput[i]= tolower(MapInput[i]);
    if(PayloadStr.compare(MapInput.substr(0,3))==0)
        return PayloadStr;
    else if(CpStr.compare(MapInput.substr(0,3))==0)
        return CpStr;
    else if(CtfStr.compare(MapInput.substr(0,4))==0)
        return CtfStr;
    else if(KothStr.compare(MapInput.substr(0,5))==0)
        return KothStr;
    else
        return mapError;
    
    return mapError;
}
string convertInt(int number)
{
   if(number == 1)
    return "1st";
   else if(number == 2)
    return "2nd";
   else if(number ==3)
    return "3rd";
   else if(number ==4)
    return "4th";
   else if(number ==5)
    return "5th";
   else if(number == 6)
    return "6th";
else if(number == 7)
    return "7th";
   else if(number ==8)
    return "8th";
   else if(number ==9)
    return "9th";
   else if(number ==10)
    return "10th";
   else if(number == 11)
    return "11th";
    else if(number == 12)
    return "12th";
   else if(number ==13)
    return "13th";
   else if(number ==14)
    return "14th";
   else if(number ==15)
    return "15th";
   else if(number == 16)
    return "16th";
    else if(number == 17)
    return "17th";
   else if(number ==18)
    return "18th";
   else if(number ==19)
    return "19th";
   else if(number ==20)
    return "20th";
   else if(number == 21)
    return "21st";
   else if(number == 22)
    return "22nd";
   else if(number ==23)
    return "23rd";
   else if(number ==24)
    return "24th";
   else if(number ==25)
    return "25th";
   else if(number == 26)
    return "26th";
else if(number == 27)
    return "27th";
   else if(number ==28)
    return "28th";
   else if(number ==29)
   return "29th";
   else if(number == 30)
   return "30th";
   else if(number == 31)
   return "31st";
   else
   return "ERR0R";
}

string validInputMo(string month)
{
   
   if(month == "1"|| month =="01") return months[0];
   else if (month=="2" ||month =="02") return months[1];
   else if (month=="3" ||month =="03") return months[2];
   else if (month=="4" ||month =="04") return months[3];
   else if (month=="5" ||month =="05") return months[4];
   else if (month=="6" ||month =="06") return months[5];
   else if (month=="7" ||month=="07") return months[6];
   else if (month=="8" ||month =="08") return months[7];
   else if (month=="9" ||month=="09") return months[8];
   else if (month=="10" ||month =="10") return months[9];
   else if (month=="11") return months[10];
   else if (month=="12") return months[11];
   else return mapError;

return mapError;
}

string createString(Match& Pres)
{
    string result;
    result = "";
    result.append("**MATCH INFO** \n\n");

    if(Pres.OpponentsKnown == true)
    {
        result.append("Our opposing team is ");
        result.append(Pres.opponents);
        result.append("(");result.append(Pres.opponentTag); result.append(").");
        if(Pres.Visiting == true)
            result.append("We will be the visiting team.\n\n");
        else
            result.append("We will be the home team.\n\n");
    }
    else
    {
        result.append("Our enemy team is unknown.\n\n");
    }

    result.append("The time and date is the ");
    result.append(esg::convertInt(Pres.day));
    result.append(" of ");
    result.append(Pres.month);
    result.append(" Monday at 8:30EST.");
    if(Pres.Tentative){
        result.append(" These date and times are the tentative for now.\n\n");
    }
    else
        result.append("\n\n");

    result.append("\n\n");
    result.append(esg::lineSeg);
    result.append("\n\n");

    result.append("**ROLL CALL**\n\n");
    for(int i =0; i < 10; i++)
    {
        result.append("* **");
        result.append(esg::roles[i]);
        result.append("** - \n");
    }
    result.append("\n\n");
    result.append(esg::lineSeg);
    result.append("\n\n");
    
    result.append("* **Not Available** - \n");
    result.append("* **Groupie** - \n");

    result.append("\n\n");
    result.append(esg::lineSeg);
    result.append("\n\n");


    result.append("**MAP RESOURCES AND INFO**\n\n");


    if(esg::MapType(Pres.mapName) == esg::CpStr)
    {
        if(Pres.map5cp == true)
        {
            result.append("The map is ");
            result.append(Pres.mapName);
            result.append(", a 5cp map. The match will be determined with a best out of 5 with 30 minute halfs. This is standard for 5cp.\n\n");
        }
        else
        {
            result.append("The map is ");
            result.append(Pres.mapName);
            result.append(", an attack/defend map. The match will be played in an ABBA format, standard for attack/defend cp maps.\n\n");
        }
    }
    else if(esg::MapType(Pres.mapName) == esg::CtfStr)
    {
        result.append("The map is ");
        result.append(Pres.mapName);
        result.append(", a capture the flag map. The first team to achieve 10 captures in two 20 minute rounds wins.\n\n");
    }
    else if(esg::MapType(Pres.mapName) == esg::KothStr)
    {
        result.append("The map is ");
        result.append(Pres.mapName);
        result.append(", a king of the hill map. The first team to win 4 rounds wins the match.\n\n");
    }
    else if(esg::MapType(Pres.mapName) == esg::PayloadStr)
    {
        result.append("The map is ");
        result.append(Pres.mapName);
        result.append(", a payload map. The map will be played in stop-watch ABBA format, with one team attacking and the other team defending.\n\n");
    }
    else
        result.append("The map is unknown at the moment.\n\n");
		
	result.append("\n\nCheck out the [Scrim Thread]() here!");

    result.append("\n\n");
    result.append(esg::lineSeg);
    result.append("\n\n");

    result.append("**INSPIRATIONAL WORDS/BEATS**\n\n");

    return result;
}

void writeToFile(string Pres)
{
    ofstream outputFile;
    outputFile.open("matchlist.txt");
    outputFile << Pres;
    outputFile.close();
    return;    
}


}