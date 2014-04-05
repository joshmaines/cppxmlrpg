/*
    CPPXMLRPG
	XML-powered text adventure game engine written in C++
    by Josh Maines.

    Default story by Josh Maines.

    Upcoming features:
    - Ability to add stories to a main menu!
    - Graphical menu!
    - full-screen GUI!

    Required libraries:
    - TinyXML2 for XML loading and parsing. (zlib license)
*/
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <tinyxml2.h>

using namespace std;
using namespace tinyxml2;

int playerHP,playerMaxHP;
int timesPlayed = 0; //count how many times the player has replayed.
string playerName,replayYN;
bool game_running = true;
XMLDocument doc;
XMLElement* storyContainer;
XMLElement* storyChild;

std::string operator+(std::string const &a, int b){
  std::ostringstream oss;
  oss<<a<<b;
  return oss.str();
}
void waitForPlayerInput() {
    getline (cin,replayYN);
}
void playerStatus() {
    if (timesPlayed > 0) {
        cout << "Times replayed this session: " << timesPlayed << "\n";
    }
    cout << "Player: " << playerName << "\n" << "\tPlayerHP: " << playerHP << "/" << playerMaxHP << "\nwww.getlives.com\n";
}
void resetGame() {
    if (doc.LoadFile( "adventures/default.xml" ) != tinyxml2::XML_SUCCESS) {
        cout << "Cannot read XML file.";
        waitForPlayerInput();
        exit(0);
    }
    playerMaxHP = 10;
    playerHP = playerMaxHP;
    cout << "\n";
    cout << "Insert your name and press enter: ";
    getline (cin,playerName);
    playerStatus();
    cout << "You are " << playerName << ", ";
    storyContainer = doc.FirstChildElement("story");
    storyChild = storyContainer->FirstChildElement();
}
void gameover() {
    replayYN = "";
    while (replayYN != "y" && replayYN != "Y" && replayYN != "Yes" && replayYN != "yes" && replayYN != "n" && replayYN != "N" && replayYN != "no" && replayYN != "No") {
        cout << "Game over! Play again? y/n?";
        getline (cin,replayYN);
    }
    if (replayYN != "y" && replayYN != "Y" && replayYN != "Yes" && replayYN != "yes") {
        game_running = false;
        exit(0);
    } else {
        timesPlayed++;
        resetGame();
    }
}
void hurt(int dmg) {
    playerHP -= dmg;
    if (playerHP < 1) {
        gameover();
    }
}
void say(string storyText) {
    cout << storyText << "\n";
    waitForPlayerInput();
}
int main() {
    resetGame();
    while (storyChild != NULL) {
        string tempString = "";
        if (string(storyChild->Value()) == "say") {
            tempString += storyChild->Attribute("text");
            say(tempString);
        } else if (string(storyChild->Value()) == "hurt") {
            if (storyChild->Attribute("notice") != NULL) {
                say(tempString + storyChild->Attribute("notice") + " (HP -" + storyChild->IntAttribute( "dmg" ) + ")");
            } else {
                say(tempString + "HP -" + storyChild->IntAttribute( "dmg" ) + ")");
            }
            hurt(storyChild->IntAttribute( "dmg" ));
        } else if (string(storyChild->Value()) == "fork") {
            say("Fork feature coming soon.");
        }
        storyChild = storyChild->NextSiblingElement();
    }
    return 0;
}
