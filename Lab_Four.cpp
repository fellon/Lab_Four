/*
 * DnD 2.0
 * Author Phil Brock
 * Date started 10/5/04
 *
 */

/**********************************************
* This is a rebuild of the old DOS game called*
* Dungeons of the Necromancers Domain. It was *
* a great game. Very simple and yet horribly  *
* addictive. I do not know the origonal author*
* nor have I been able to find any refference *
* to the program in several years. So all the *
* Code here is scratch written. Just props to *
* the unknown author who gave me months of    *
* cheap entertainment.  -- Fellon             *
**********************************************/

// Boyds sample
/***** SAMPLE USAGE *****
      // storing a player's info to a file
      string n1 = "bt";
      int hp = 25;
      int m = 150.00;
      string saveFile = "bt.dat";
      saveGame(saveFile, n1, hp, m);

      // retrieving a player's info from a file
      string n2;
      int points = 0;
      int money = 0;
      string fromFile = "bt.dat";
      retrieveGame(fromFile, n2, points, money);
      cout << "retrieved player: " << n2 << "\n";
      cout << "who has " << points << " hit points and $"
           << money << " in charGold.\n";
           
      ***** END OF SAMPLE *****/
/*
Change log

Ver 0.1
Added the main menu
Added some holders
created the headers and bodys for almost all the functions
Need to insert the code still
Began work on the town menu
Added three new options. Bard, inn/tavern and fountain.
Began work on the character file loader. I need to mod them to fit all my needs.

Began working on the character generation system
Will be adding in the file load and save sequences on the next session
Must also finish the generator. Its broken into pieces for now.

Finished working on the character generator today
Began work on the training hall and the tavern so people can display there stats
and save their game.
finished work on the character save and load functions.
Added a few new things to the pfile. The ability to add stats and skills..
Will use data handlers like the race and class to string functions to change the skills and
spells to string values for easy human interpitations.

Tavern save and quit was finished.
Training level was finished. Still unbalanced.
Basic ideas for how the combat system are all ready written up.
Spell names and such are written up.

Working on the skilladd function. Skill add function is now working. Quite well.
Added the skills lists to the stat display.

Need to start on the combat system. Basic monster selection, and Then the actual combat code.
Will need a handler to figure out what bonuses are given.

Combat system is now complete. Also mod values is complete. Need to start on shop.
Also need to work on The hears 1 for 1gp healing value.

Skills still on the list to complete thier effects.

*/

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Global variables
 string errorMsg("");

 // Create the pfile
 string charName;								// Character Name
 int charRace;									// Race done as int for race list
 int charClass;									// Class done as int for class list
 int charGender;								// Character Gender processor
 int charStr;									// Strength score
 int charDex;									// Dexterity score
 int charInt;									// Intelligence score
 int charWis;	 								// Wisdom score
 int hitPtsMax;									// Character health max
 int hitPts;									// Character health current
 int staminaPtsMax;								// Skill/Spell gen max
 int staminaPts;								// Skill/Spell gen current
 int charGold;									// Character Gold storage
 int charLevel;									// Character level of experience
 int charExp;									// Character experience points.
 // Possible extended attributes to work on if I have time
 int maxWieght;									// Max carrying capacity
 int skillBonus;								// Bonus for racial skills
 
 // Racial constants
 
 // Pfile stuff part 2
 int statBonus;
 int charAttk;
 int skillPts;
 // Pfile skills list
 int charSkill1;
 int charSkill2;
 int charSkill3;
 int charSkill4;
 int charSkill5;
 // Armor... Duhh
 int charDef;
 int charWeapon; 
 
// Mob variables
string mobStatus("");
string mobName("");
int mobHP(0);
int mobHPMax(0);
int mobAttk(0);										// Mob atk modifier
int mobDef(0);										// Mob Defense Stat. This is a hard number
int mobMod(0);										// Mob damage modifier

bool raceSet; // Local test
bool classSet;  // local test
bool statSet;  // local test
bool genderSet; // Local test
bool quitFlag; // Exit system


// Functions that will be local
bool saveGame (string, string, int, int);		// Save processor
bool retrieveGame (string, string&, int&, int&);	// Load processor
void menuMain (string);								// Main menu for Greet and option
void menuShop ();  									// Menu for the Shopkeeper
void menuTrain (string);								// Menu for the level trainer
void menuHealer(string);									// Menu for the House of healing
void menuArena (string);									// Menu for the monster arena
void menuTown (string);								// Menu for the town main area
void menuTavern (string);							// Menu for the tavern.
void actionFight ();								// Fight processor
void actionFlee ();									// Flee processor
void actionSpell ();								// Spell casting processor
void actionSkill ();								// Skill use processor
void characterGen ();								// Character Creation processor
void characterPreload();							// Load buffer processor
void setRace(int&);									// Set player race
void setStats();									// Stat creation
void setClass();									// Set player class
void setGender();									// Set players gender
void setName();										// Sets the players name
void do_train();								// Raises a players level
void do_stats();									// Display character Info
string calcRace(int);								// convert race number to string
string calcClass(int);								// convert class number to string
string calcGender(int);								// convert gender number to string
void do_drink();									// drink in tavern process
void do_room();										// room renter process
void do_common();									// free logout process
void do_addSkill();									// skill increment
void do_addStat();									// stat increment
string calcSkill(int);								// convert skill number to string
void do_fight();					// The combat system.
int calcStats(int);
void monsterMaker();								// Make a Monster


int main ()
{
//if (quitFlag == false)

  menuMain(errorMsg);
 
        
  return 0;    
}

void monsterMaker()
{
int nameNum;
// Name number
//Lets make a monster
// Start with some base numbers. Like based on the player level.
/*
string mobStatus("");
string mobName("");
int mobHP(0);
int mobHPMax(0);
int mobAttk(0);										// Mob atk modifier
int mobDef(0);										// Mob Defense Stat. This is a hard number
int mobMod(0);
*/

srand(time(NULL));
mobHP = charLevel * (rand()%8 + 1);
mobHPMax = mobHP;
mobAttk = charLevel;
mobDef = charLevel + 10;
mobMod = charLevel;
// Looks to be about it.  Just get some names.

nameNum = charLevel + (rand()%10 + 1);

switch (nameNum)
{
case 1:
mobName = "Kobold";
break;
case 2:
mobName = "Gnomish Pitfighter";
break;
case 3:
mobName = "Orc Warrior";
break;
case 4:
mobName = "Goblin Badass";
break;
case 5:
mobName = "Homicidal Maniac";
break;
case 6:
mobName = "Zombie";
break;
case 7:
mobName = "Rust Monster";
break;
case 8:
mobName = "Ochre Pudding";
break;
case 9:
mobName = "Kobald Ninja of uber power who wants to destroy all living things.";
break;
case 10:
mobName = "Just, a ninja";
break;
case 11:
mobName = "Weystag";
break;
case 12:
mobName = "A warrior";
break;
case 13:
mobName = "Gladiator";
break;
case 14:
mobName = "Knight";
break;
case 15:
mobName = "Grand Warrior";
break;
case 16:
mobName = "Bullete";
break;
case 17:
mobName = "Young Dragon";
break;
case 18:
mobName = "Chimera";
break;
case 19:
mobName = "Manticore";
break;
case 20:
mobName = "Dragon";
break;
}

}

bool saveGame (string toFile, string charName, int hitPtsMax, int charGold)
{
      bool saved = false;
	ofstream fout(toFile.c_str());
	if (!fout.fail())
	{
		// adding in my pfile stuff	
		fout << charName << "\n";								// Character Name
   		fout << charRace << "\n";									// Race done as int for race list
  		fout << charClass << "\n";									// Class done as int for class list
 		fout << charGender << "\n";								// Character Gender processor
  		fout << charStr << "\n";									// Strength score
  		fout << charDex << "\n";									// Dexterity score
 		fout << charInt << "\n";									// Inteligence score
 		fout << charWis << "\n";	 								// Wisdom score
 		fout << hitPtsMax << "\n";									// Character health max
 		fout << hitPts << "\n";									// Character health current
 		fout << staminaPtsMax << "\n";								// Skill/Spell gen max
 		fout << staminaPts << "\n";								// Skill/Spell gen current
 		fout << charGold << "\n";								// Character Gold storage
 		fout << charLevel << "\n";
 		fout << charExp << "\n";
 		fout << statBonus << "\n";
 		fout << charAttk << "\n";
 		fout << skillPts << "\n";
		fout << charSkill1 << "\n";
		fout << charSkill2 << "\n";
 		fout << charSkill3 << "\n";
 		fout << charSkill4 << "\n";
  		fout << charSkill5 << "\n";
 		fout << charDef << "\n";
 		fout << charWeapon << "\n";
 										
 // Possible extended attributes to work on if I have time
 		// fout << maxWieght << "\n";									// Max carrying capacity
 		// fout << skillBonus << "\n";

            saved = true;
	}
	else
		cerr << "Failed to open file: " << toFile << endl;

      return saved;
}

bool retrieveGame (string fromFile, string& charName, int& hitPtsMax, int& charGold)
{
      bool restored = false;
	ifstream fin(fromFile.c_str());
	if (!fin.fail())
	{
		// My pfile settings
		fin >> charName;								// Character Name
   		fin >> charRace;									// Race done as int for race list
  		fin >> charClass;									// Class done as int for class list
 		fin >> charGender;								// Character Gender processor
  		fin >> charStr;									// Strength score
  		fin >> charDex;									// Dexterity score
 		fin >> charInt;									// Inteligence score
 		fin >> charWis;	 								// Wisdom score
 		fin >> hitPtsMax;									// Character health max
 		fin >> hitPts;									// Character health current
 		fin >> staminaPtsMax;								// Skill/Spell gen max
 		fin >> staminaPts;								// Skill/Spell gen current
 		fin >> charGold;
 		fin >> charLevel;
 		fin >> charExp;
 		fin >> statBonus;
 		fin >> charAttk;
 		fin >> skillPts;
 		fin >> charSkill1;
		fin >> charSkill2;
		fin >> charSkill3;
		fin >> charSkill4;
		fin >> charSkill5;
		fin >> charDef;
		fin >> charWeapon;
            restored = true;
	}
	else
		cerr << "Failed to open file: " << fromFile << endl;

      return restored;
}

void menuMain (string errorMsg)
{
//local variables
   
   int choice; // I like that whole choice variable -- used for getting menu options
   
   // Clear the screen
    cout << " ";
    clrscr();
   
   // Welcome screen.
   cout << "Welcome to Dungeons of the Necromancers Domain 2.0!" << "\n"
        << "Writen by Fellon D 'Armer -- Based on previous works" << "\n"
        << "of the unknown Author of Dungeons of the Necromancers" << "\n"
        << "Domain." << "\n"
        << "\n"
        << "To play:" << "\n"
        << "Either create a new character or load a character." << "\n"
        << "Please select an option: " << "\n"
        << "[1] Load your character." << "\n"
        << "[2] Create a new Character." << "\n"
        << "[1, 2] ? " << "\n" << "\n"
        << errorMsg << "\n";
   
   // clear the errorMsg
   errorMsg = "";
   // Get players input     
   cin >> choice;
   
   // process the choice using a switch
   switch (choice)
   {
   	case 1:
   	 // call the character loader
   	 characterPreload();
   	 menuTown(errorMsg);
   	 break;
   	case 2:
   	 // call the characterGenerator
   	 characterGen();
   	 break;
   	default:
   	 // call back the menu and report a error
   	 errorMsg = "Please choose a correct option! 1 or 2";
   	 menuMain(errorMsg);
   	 break;
   }
}

void menuShop ()
{
}

void menuTrain (string errorMsg)
{
//local variables
   
   int choice; // I like that whole choice variable -- used for getting menu options
   
   // Clear the screen
    cout << " ";
    clrscr();
   choice = 0;
   // Welcome screen.
   cout << "You enter the great Squires Bastion Training hall." << "\n"
        << "The smell of oiled equipment, sweat, and blood assult your nose." << "\n"
        << "A large man walks up to you and glaring down asks" << "\n"
        << "You here to train?" << "\n"
        << "\n"
        << "Your reply:" << "\n"
        << "[1] I am here to Train my level" << endl
        << "[2] I would like to learn some skills" << endl
        << "[3] I want to increase a stat" << endl
        << "[4] I would like to evaluate my skills" << endl
        << "[5] Return to the fountain plaza" << endl
        << "[1, 2, 3, 4, 5]" << "\n" << "\n"
        << errorMsg << "\n";
   
   // clear the errorMsg
   errorMsg = "";
   // Get players input     
   cin >> choice;
   
   // process the choice menu
   switch (choice)
   {
   case 1:
   // Leveler processor
   do_train();
   break;
   case 2:
   // invoke skill learning system
   do_addSkill();
   break;
   case 3:
   // invoke stat increaser
   do_addStat();
   break;
   case 4:
   // stat display processor
   do_stats();
   break;
   case 5:
   // goes back to town
   errorMsg = "You return to the fountain square";
   menuTown(errorMsg);
   default:
   errorMsg = "Please type a correct value";
   menuTrain(errorMsg);
   }
}

void do_addSkill() // The setup of this function can cause all sorts of trouble.
{
// Local variables 
int choice;
// Use a switch to decide what skills to add..  So to speak.
if (skillPts <= 0)
{
errorMsg = "You do not have any Skill Points to learn new skills";
menuTrain(errorMsg);
}

switch (charClass)
{
 case 0: // Warrior Skills
 cout << "Please choose a skill to add points to." << endl
      << "[1] Punch" << endl
      << "[2] Kick" << endl
      << "[3] Bash" << endl
      << "[4] Trip" << endl
      << "[5] Delusions of Granduer" << endl
      << "Choose a skill to add to your list" << endl
      << "[1, 2, 3, 4, 5]" << endl;
      
      cin >> choice;
      
      // move to bottom and process the selection
 break;
 
 case 1: // Priest Spells
 cout << "Please choose a skill to add points to." << endl
      << "[1] Healing Touch" << endl
      << "[2] Soul Drain" << endl
      << "[3] Devine Armor" << endl
      << "[4] Devine Grace" << endl
      << "[5] Holy Smite" << endl
	  << "Choose a spell to add to your list" << endl
      << "[1, 2, 3, 4, 5]" << endl;
      
      cin >> choice;
      
      // move to bottom and process the selection

 break;
 
 case 2: // Sorcerer Spells
 cout << "Please choose a skill to add points to." << endl
      << "[1] Zap" << endl
      << "[2] Ice Knife" << endl
      << "[3] Lightning Bolt" << endl
      << "[4] Fireball" << endl
      << "[5] Black Doom" << endl
      << "Choose a spell to add to your list" << endl
      << "[1, 2, 3, 4, 5]" << endl;
      
      cin >> choice;
      
      // move to bottom and process the selection

 break;
 
 case 3: // Scout Skills
 cout << "Please choose a skill to add points to." << endl
      << "[1] Hide" << endl
      << "[2] Pick Pocket" << endl
      << "[3] Backstab" << endl
      << "[4] Double Throw" << endl
      << "[5] Deathblow" << endl
      << "Choose a skill to add to your list" << endl
      << "[1, 2, 3, 4, 5]" << endl;
      
      cin >> choice;
      
      // move to bottom and process the selection

 break;
 default:
 errorMsg = "You have chosen a incorrect value";
 menuTrain(errorMsg);
 break;
 }
 // Process the list by adding it to the correct skill value in the pfile.
 switch (choice)
 {
 case 1: // Add one to the first skill slot
 charSkill1 = charSkill1 + 1;
 break;
 case 2: // Add one to the second skill slot
 charSkill2 = charSkill2 + 1;
 break;
 case 3: // Add one to the third skill slot
 charSkill3 = charSkill3 + 1;
 break;
 case 4: // Add one to the fourth skill slot
 charSkill4 = charSkill4 + 1;
 break;
 case 5: // Add one to the fifth skill slot
 charSkill5 = charSkill5 + 1;
 break;
 }
 // Success
 errorMsg = "You have increased a skill";
 menuTrain(errorMsg);
}


void do_addStat() // Increase a stat in your attributes
{
// Local variables
int choice;

 cout << "Please choose a Stat to increase." << endl
      << "[1] Strength" << endl
      << "[2] Dexterity" << endl
      << "[3] Intelligence" << endl
      << "[4] Wisdom" << endl
      << "[1, 2, 3, 4]" << endl;
      
      cin >> choice;
      
      // move to bottom and process the selection
 
 // Process the list by adding it to the correct Stat value in the pfile.
 switch (choice)
 {
 case 1: // Add one to the Str stat
 charStr = charStr + 1;
 break;
 case 2: // Add one to the Dex stat
 charDex = charDex + 1;
 break;
 case 3: // Add one to the Int stat
 charInt = charInt + 1;
 break;
 case 4: // Add one to the Wis stat
 charWis = charWis + 1;
 break;
 default:
 errorMsg = "You chose a improper value";
 menuTrain(errorMsg);
 break;
 }
 // Success
 errorMsg = "You have increased a Stat";
 menuTrain(errorMsg);

}

void do_train()
{
int expNext;
// create level iterator
// Level should be 100 - charExp if value <= 0 then do the level
expNext = ((100 * charLevel) - charExp);
// Start the random number bitch machine
srand(time(NULL));
string toFile("");
toFile = charName;

if (expNext > 0)
{
errorMsg = "You do not have enough Experience to train here.";
menuTrain(errorMsg);
}

if (charGold >= 1000)
{
 //Do the training
 charGold = charGold - 1000;
 charLevel = charLevel + 1;
 
 if (charClass == 0) // Warrior level up
 {
 charAttk = (charAttk + 1);
 hitPtsMax = hitPtsMax + rand()%11;
 hitPts = hitPtsMax;
 staminaPtsMax = staminaPtsMax + rand()%5;
 staminaPts = staminaPtsMax;
 statBonus = statBonus + 1;
 skillPts = skillPts + 3;
 }
 
 if (charClass == 1) // Priest 
 {
 charAttk = (charAttk + 1);
 hitPtsMax = hitPtsMax + rand()%9;
 hitPts = hitPtsMax;
 staminaPtsMax = staminaPtsMax + rand()%6;
 staminaPts = staminaPtsMax;
 statBonus = statBonus + 1;
 skillPts = skillPts + 4;
 }
 
 if (charClass == 2) // Sorcerer
 {
 charAttk = (charAttk + 1);
 hitPtsMax = hitPtsMax + rand()%5;
 hitPts = hitPtsMax;
 staminaPtsMax = staminaPtsMax + rand()%9;
 staminaPts = staminaPtsMax;
 statBonus = statBonus + 1;
 skillPts = skillPts + 5;
 }
 
 if (charClass == 3)  // Scout
 {
 charAttk = (charAttk + 1);
 hitPtsMax = hitPtsMax + rand()%7;
 hitPts = hitPtsMax;
 staminaPtsMax = staminaPtsMax + rand()%7;
 staminaPts = staminaPtsMax;
 statBonus = statBonus + 1;
 skillPts = skillPts + 6;
 }
// save file
saveGame(toFile, charName, hitPtsMax, charGold);
errorMsg = "You have trained well";
menuTrain(errorMsg);
}
else
{
errorMsg = " You do not have enough gold to train here";
menuTrain(errorMsg);
}

}

void do_stats()
{
// local variables
int choice;
int expNext;
int charSkill;
expNext = ((100 * charLevel) - charExp);
// Convert everything to strings so humans can read it.
string strRace;
strRace = calcRace(charRace);
string strClass;
strClass = calcClass(charClass);
string strGender;
strGender = calcGender(charGender);
charSkill = 1;
string strSkill1;
strSkill1 = calcSkill(charSkill);
charSkill = 2;
string strSkill2;
strSkill2 = calcSkill(charSkill);
charSkill = 3;
string strSkill3;
strSkill3 = calcSkill(charSkill);
charSkill = 4;
string strSkill4;
strSkill4 = calcSkill(charSkill);
charSkill = 5;
string strSkill5;
strSkill5 = calcSkill(charSkill);


// Show character statistics
// clear screan first
  cout << "" << endl;
  clrscr();

cout << "DnD2 Character Statistics" << endl
     << "Name: " << charName << "  Race: " << strRace << " Gender: " << strGender << endl
     << "Class: " << strClass << "  Level: " << charLevel << endl
     << "Str: " << charStr << " Dex: " << charDex << " Int: " << charInt << " Wis: " << charWis << endl
     << "Attack Bonus: " << charAttk << endl
     << "Max HP: " << hitPtsMax << " Crnt HP: " << hitPts << endl
     << "Max Stamina: " << staminaPtsMax << " Current Stamina: " << staminaPts << endl
     << "Skill points left: " << skillPts << " Stat Bonuses left: " << statBonus << endl
     << "Weapon: " << charWeapon << " Armor: " << charDef << endl
     << "Skills/Spells " << endl
     << "Slot 1: " << strSkill1 << " (" << charSkill1 << ")" << endl
     << "Slot 2: " << strSkill2 << " (" << charSkill2 << ")" << endl
     << "Slot 3: " << strSkill3 << " (" << charSkill3 << ")" << endl
     << "Slot 4: " << strSkill4 << " (" << charSkill4 << ")" << endl
     << "Slot 5: " << strSkill5 << " (" << charSkill5 << ")" << endl                    
     << "" << endl
     << "Gold: " << charGold << endl
     << "Experience Points: " << charExp << endl
     << "Experience to next level: " << expNext << endl
     << "" << endl 
     << "Have you seen enough?" << endl
     << "[1] Yes, thank you." << endl
     << "[2] I would like to revel in the greatness that is me one more time." << endl
     << "Choose a option: " << endl
     << "[1, 2]" << endl;
     
     cin >> choice;
     
     switch (choice)
     {
     case 1:
     errorMsg = "Nice statistics!";
     menuTrain(errorMsg);
     break;
     case 2:
     do_stats();
     break;
     default:
     errorMsg = "You answer strangley";
     menuTrain(errorMsg);  
     break;
     }
}

void menuHealer(string errorMsg)
{
int choice;

// Clear screen
cout << "";
clrscr();

if (hitPts <= 0)
  {
  hitPts = hitPtsMax;
  cout << "I have healed you" << endl;
  }  
  //Now do the menu
  cout << "You have entered the Temple of Gothma" << "\n"
        << "Black leather and chains seem to be rather dominant here." << "\n"
        << "A young woman approaches you." << "\n"
        << "How may I serve you?" << "\n"
        << "\n"
        << "Your choices:" << "\n"
        << "[1] I require healing" << "\n"
        << "[2] Leave" << "\n"              
        << "[1, 2]" << "\n" << "\n"
        << errorMsg << "\n";
   
   // clear the errorMsg
   errorMsg = "";
   // Get players input     
   cin >> choice;
   
   switch (choice)
   {
   case 1:
   // Get healed 1 for 1gold
   break;
   case 2:
   // Leave
   errorMsg = "You leave the temple";
   menuTown(errorMsg);
   break;
   default:
   errorMsg = "Please choose something from the menu";
   menuHealer(errorMsg);
   break;
   }
 menuHealer(errorMsg);
}

void menuArena (string errorMsg)
{
//local variables
   
   int choice; // I like that whole choice variable -- used for getting menu options
   
   // Clear the screen
    cout << " ";
    clrscr();
   
   // Welcome screen.
   cout << "You have entered the arena of Suldin" << "\n"
        << "Blood and trash litter the sandy floor" << "\n"
        << "People are sitting in the stands watching the events" << "\n"
        << "A scarred man walks over to you." << "\n"
        << "Wanna fight?" << "\n"
        << "We's got a lot of monsters" << "\n"
        << "\n"
        << "Your choices:" << "\n"
        << "[1] I'll fight" << "\n"
        << "[2] Leave" << "\n"              
        << "[1, 2]" << "\n" << "\n"
        << errorMsg << "\n";
   
   // clear the errorMsg
   errorMsg = "";
   // Get players input     
   cin >> choice;
   
   switch (choice)
   {
   case 1:
   // Make a monster and then load the fight stuff
   monsterMaker();
   do_fight();
   break;
   case 2:
   // Leave
   errorMsg = "You leave the arena";
   menuTown(errorMsg);
   break;
   default:
   errorMsg = "Please choose something from the menu";
   menuArena(errorMsg);
   break;
   }

}


void menuTavern (string errorMsg) // The tavern
{
//local variables
   
   int choice; // I like that whole choice variable -- used for getting menu options
   
   // Clear the screen
    cout << " ";
    clrscr();
   
   // Welcome screen.
   cout << "You are standing in the Vagabond Rose Inn" << "\n"
        << "This is a wonderful and delightful tavern with with" << "\n"
        << "a few rooms for rent as well. You see some people sleeping" << "\n"
        << "in the common room. A large bar stands against the far wall" << "\n"
        << "with all of the many comforts for adventures." << "\n"
        << "The barkeep approaches you. How may I help you?" << "\n"
        << "\n"
        << "Your choices:" << "\n"
        << "[1] Get a room for the night" << "\n"
        << "[2] Sleep it off in the common room" << "\n"
        << "[3] Get it on with a drink" << "\n"
        << "[4] Head back to the street" << "\n"              
        << "[1, 2, 3, 4]" << "\n" << "\n"
        << errorMsg << "\n";
   
   // clear the errorMsg
   errorMsg = "";
   // Get players input     
   cin >> choice;
   
   switch (choice)
   {
   case 1:
   // Take 10 gold and save the game and quit
   do_room();
   break;
   case 2:
   // Take no gold, give a disgusted look and quit
   do_common();
   break;
   case 3:
   // Take 1 gold and drink up
   do_drink();
   break;
   case 4:
   // Go back to the main city
   errorMsg = "You have left the tavern";
   menuTown(errorMsg);
   break;
   default:
   errorMsg = "Please choose something from the menu";
   menuTavern(errorMsg);
   break;
   }

}

void do_drink() // Buys a drink
{
if (charGold >= 1)
{
charGold = charGold - 1;
errorMsg = "That was a wonderful watermelon twist";
menuTavern(errorMsg);
}
else
{
errorMsg = "The bartender says 'I'm sorry, but you do not have enough gold'";
menuTavern(errorMsg);
}

}

void do_room() // Gets a room at the inn
{
string toFile("");
toFile = charName;

if (charGold >= 10)
{
charGold = charGold - 10;
cout << "Have a good rest";
saveGame(toFile, charName, hitPtsMax, charGold);

exit(0);
}
else
{
errorMsg = "You do not have enough gold";
menuTavern(errorMsg);
}
}

void do_common() // Save and quit for free
{
string toFile("");
toFile = charName;

cout << "You crash out on a nice section of floor near the hearth and promplty fall asleep." << endl
     << "The barkeeper comes over to you and covers you up with a wool blanket." << endl
     << "Muttering under his breath.. You people, such a mess.";
     
saveGame(toFile, charName, hitPtsMax, charGold);
exit(0);
}

void menuTown (string errorMsg)  // In town
{
//local variables
   
   int choice; // I like that whole choice variable -- used for getting menu options
   
   // Clear the screen
    cout << " ";
    clrscr();
   
   // Welcome screen.
   cout << "You are standing in the fountain plaza in Suldin." << "\n"
        << "The plaza is surronded by the temple and bazzar." << "\n"
        << "A beautiful Inn is just the other side of the fountain." << "\n"
        << "Some people mill around the fountain plaza." << "\n"
        << "A young bard sits on the side of the fountain singing songs." << "\n"
        << "\n"
        << "Your choices:" << "\n"
        << "[1] Enter the Arena" << "\n"
        << "[2] Enter the Dragon Imports Adventurers Shop" << "\n"
        << "[3] Enter the House of Healing Temple" << "\n"
        << "[4] Enter the Squires Bastion Training Grounds" << "\n"
        << "[5] Speak to the Bard" << "\n"
        << "[6] Flick a coin into the fountain" << "\n"
        << "[7] Enter the Vagabond Rose Inn & Tavern" << "\n"              
        << "[1, 2, 3, 4, 5, 6, 7]" << "\n" << "\n"
        << errorMsg << "\n";
   
   // clear the errorMsg
   errorMsg = "";
   // Get players input     
   cin >> choice;
   
   // process the choice using a switch
   switch (choice)
   {
   	case 1:
   	 // call the arena menu
   	 errorMsg = "You have entered the arena";
   	 menuArena(errorMsg);
   	 break;
   	case 2:
   	 // call the shopMenu
   	 errorMsg = "shop menu -- Not done\n";
   	 menuTown(errorMsg);
   	 break;
   	case 3:
   	 // call the healerMenu
   	 errorMsg = "You enter the High temple of Gothma";
   	 menuHealer(errorMsg);
   	 break;
   	case 4:
   	 // call the trainMenu
   	 errorMsg = "You have entered the Training grounds";
   	 menuTrain(errorMsg);
   	 break;
   	case 5:
   	 // call the bardmenu
   	 errorMsg = "The bard is not talking yet\n";
   	 menuTown(errorMsg);
   	 break;
   	case 6:
   	 // call the fountain processor
   	 errorMsg = "The fountain is dry\n";
   	 menuTown(errorMsg);
   	 break;
   	case 7:
   	 // call the tavern menu
   	 errorMsg = "You enter the Vagabond Rose Inn & Tavern";
   	 menuTavern(errorMsg);
   	 break;
   	default:
   	 // call back the menu and report a error
   	 errorMsg = "Please choose a correct option!";
   	 menuTown(errorMsg);
   	 break;
   }

}

void actionFight ()
{
}

void actionFlee ()
{
}

void actionSpell ()
{
}

void actionSkill ()
{
}

void characterGen ()
{
// Local variables
int choice;
string toFile("null"); // Save file
string strRace;
strRace = calcRace(charRace);
string strClass;
strClass = calcClass(charClass);
string strGender;
strGender = calcGender(charGender);


 // clear the screen
 cout << " ";
 clrscr();
 
 // Make a menu to show current character creation status.
 cout << "Character creation menu" << endl
      << "Please choose a option" << endl
      << "[1] Set your race: currently -> " << strRace << endl
      << "[2] Set your class: currently -> " << strClass << endl
      << "[3] Set your stats: currently -> " << "Str: " << charStr << " Dex: " << charDex << " Int: " << charInt << " Wis: " << charWis << endl
      << "[4] Set your Gender: currently -> " << strGender << endl
      << "[5] Set your character name currently -> " << charName << endl
      << "[6] Exit character generator" << endl
      << "[1, 2, 3, 4, 5, 6]" << endl;
 // Get choice     
 cin >> choice;
 
 // Process choice
 switch (choice)
 {
 case 1:
 // call the player race setting process
 setRace(charRace);
 break;
 case 2:
 // call the class setting process
 setClass();
 break;
 case 3:
 // call the stat setting process
 setStats();
 break;
 case 4:
 // call the gender processor
 setGender();
 break;
 case 5:
 setName();
 break;
 case 6:
 // End the character processor
 // If all the stats are set, then let them go and save the character
 // If they are not all set, boot them back into the generator.
 if (raceSet == true || classSet == true || statSet == true || genderSet == true)
 // send them to town.
 {
 // Create max hp and assign them full hp.
 if (charClass == 0)  // Warrior 
 {
 hitPtsMax = 10;
 hitPts = 10;
 staminaPtsMax = 4;
 staminaPts = 4;
 }
 
 if (charClass == 1) // Priest 
 {
 hitPtsMax = 8;
 hitPts = 8;
 staminaPtsMax = 6;
 staminaPts = 6;
 }
 
 if (charClass == 2) // Sorcerer
 {
 hitPtsMax = 4;
 hitPts = 4;
 staminaPtsMax = 8;
 staminaPts = 8;
 }
 
 if (charClass == 3)  // Scout
 {
 hitPtsMax = 6;
 hitPts = 6;
 staminaPtsMax = 6;
 staminaPts = 6;
 }
 
 charLevel = 1;
 charExp = 0;
 charGold = 100;
 statBonus = 5;
 charAttk = 1;
 charWeapon = 0;
 charDef = 10;
 charSkill1 = 1;
 
 toFile = charName;
 saveGame(toFile, charName, hitPtsMax, charGold);
 errorMsg = "Welcome to the game dude";
 menuTown(errorMsg);
 }
 else
 {
 // Reload the character gen keeping set values
 characterGen();
 }
 default:
 // Reload the menu and spit out a error message
 errorMsg = "You do not have all the values set. Please try again.";
 characterGen();
 break;
 }
      
}
 
string calcSkill(int charSkill) // converts class to string value
{
string holder("");
switch (charClass)
{
case 0: // Warrior
if (charSkill == 1)
 {
 holder = "Punch";
 }
 if  (charSkill == 2)
 {
 holder = "Kick";
 }
 if (charSkill == 3)
 {
 holder = "Bash";
 }
 if (charSkill == 4)
 {
 holder = "Trip";
 }
 if (charSkill == 5)
 {
 holder = "Delusions of Granduer";
 }
 break;
 case 1: //Priest
 if (charSkill == 1)
 {
 holder = "Healing Touch";
 }
 if  (charSkill == 2)
 {
 holder = "Soul Drain";
 }
 if (charSkill == 3)
 {
 holder = "Devine Armor";
 }
 if (charSkill == 4)
 {
 holder = "Devine Grace";
 }
 if (charSkill == 5)
 {
 holder = "Holy Smite";
 }
 break;
 case 2: // Sorcerer
 if (charSkill == 1)
 {
 holder = "Zap";
 }
 if  (charSkill == 2)
 {
 holder = "Ice Knife";
 }
 if (charSkill == 3)
 {
 holder = "Lightning Bolt";
 }
 if (charSkill == 4)
 {
 holder = "Fireball";
 }
 if (charSkill == 5)
 {
 holder = "Black Doom";
 }
 break;
 case 4: // Scout class
 if (charSkill == 1)
 {
 holder = "Hide";
 }
 if  (charSkill == 2)
 {
 holder = "Pick Pocket";
 }
 if (charSkill == 3)
 {
 holder = "Backstab";
 }
 if (charSkill == 4)
 {
 holder = "Double Throw";
 }
 if (charSkill == 5)
 {
 holder = "Deathblow";
 }
 break;
 }
return holder;

}

string calcRace(int charRace) // converts race to string value
{
string holder("");
if (charRace == 0)
 {
 holder = "Human";
 }
 if  (charRace == 1)
 {
 holder = "Dwarf";
 }
 if (charRace == 2)
 {
 holder = "Skank Elf";
 }
 if (charRace == 3)
 {
 holder = "Gnomish Stripper";
 }
 return holder;
}

string calcClass(int charClass) // converts class to string value
{
string holder("");
if (charClass == 0)
 {
 holder = "Warrior";
 }
 if  (charClass == 1)
 {
 holder = "Priest";
 }
 if (charClass == 2)
 {
 holder = "Sorcerer";
 }
 if (charClass == 3)
 {
 holder = "Scout";
 }
 return holder;

}

string calcGender(int charGender) // converts gender to string value
{
string holder("");
if (charGender == 0)
 {
 holder = "Male";
 }
 if  (charGender == 1)
 {
 holder = "Female";
 }

 return holder;

}

void setRace(int& charRace) // Race setting processor
{
// local variables
int choice;
// Let the player choose a race
 /* 0 = human, 1 = Dwarf, 2 = Elf, 3 = Gnome */
 
 // reset the choice variable
 choice = 0;
 cout << "Choose a race:" << endl
      << "[1] Human" << endl
      << "[2] Dwarf" << endl
      << "[3] Elf" << endl
      << "[4] Gnome" << endl;
 
 // Aquire the race selection
 cin >> choice;
 
 switch (choice)
 {
  case 1:
  //make player an human
  charRace = 0;
  raceSet = true;
  break;
  case 2:
  // Make player a dwarf
  charRace = 1;
  raceSet = true;
  break;
  case 3:
  // Make player a pansy ass elf
  charRace = 2;
  raceSet = true;
  break;
  case 4:
  //Make player a gnomish striper
  charRace = 3;
  raceSet = true;
  break;
  default:
  // Print an error message and present screen again
  setRace(charRace);
  cout << "Enter a legal race #.";   
 }
 characterGen();
 
}

void setStats()
{
// Local variables
int choice;

// Create the characters stats.
 // and print them out
 // Seed the random number generator
 srand(time(NULL));
 
 charStr = 5 + rand()%6;   						// Roll Str 5 - 10
 cout << charStr;
 charDex = 5 + rand()%6;						// Roll Dex 5 - 10
 cout << charDex;
 charInt = 5 + rand()%6;						// Roll Int 5 - 10
 cout << charInt;
 charWis = 5 + rand()%6;						// Roll Wis 5 - 10
 cout << charWis;
 
 // Print out the data
 
 cout << "Strength: " << charStr << " Dexterity: " << charDex << " Inteligence: " 
      << charInt << " Wisdom: " << charWis << endl
      << "Reroll [1], Accept [2], Cancel [3]:" << endl
      << "[1, 2, 3]" << endl;
 
 // Get players choice
 cin >> choice;

 switch (choice)
 {
 case 1:
 // Reroll stats
 setStats();
 break;
 case 2:
 // Accept and set the stats
 statSet = true;
 characterGen();
 break;
 case 3:
 // Cancel this process
 charStr = 0;
 charDex = 0;
 charInt = 0;
 charWis = 0;
 characterGen();
 break;
 default:
 cout << "Incorrect input, try again";
 }
 characterGen();
}

void setClass()
{
// local variables
int choice;

// Let the player choose a class
 /* 0 = Warrior, 1 = Priest, 2 = Sorcerer, 3 = Scout */
 
 // reset the choice variable
 choice = 0;
 cout << "Choose a class:" << endl
      << "[1] Warrior" << endl
      << "[2] Priest" << endl
      << "[3] Sorcerer" << endl
      << "[4] Scout" << endl;
 
 // Aquire the race selection
 cin >> choice;
 
 switch (choice)
 {
  case 1:
  //make player an Warrior
  classSet = true;
  charClass = 0;
  break;
  case 2:
  // Make player a Priest
  charClass = 1;
  classSet = true;
  break;
  case 3:
  // Make player a Sorcerer
  charClass = 2;
  classSet = true;
  break;
  case 4:
  //Make player a Scout
  charClass = 3;
  classSet = true;
  break;
  default:
  // Print an error message and present screen again
  setClass();
  cout << "Enter a legal Class #.";   
 }
 
 characterGen();
}


void setGender()	
{
// local variables
int choice;

choice = 0;
 cout << "Choose a Gender:" << endl
      << "[1] Male" << endl
      << "[2] Female" << endl;
 
 // Aquire the race selection
 cin >> choice;
 
 switch (choice)
 {
  case 1:
  //make player a male
  genderSet = true;
  charGender = 0;
  break;
  case 2:
  // Make player a female
  genderSet = true;
  charGender = 1;
  break;
  default:
  // Print an error message and present screen again
  
  cout << "Enter a legal Gender #."; 
 }
 characterGen();
}

void characterPreload() // Used to buffer the menu down a bit.
{
 // local variables
 string tempcharName("");
 string fromFile("");
 
 
 // clear the screen first
 cout << "";
 clrscr();
 
 // Prompt for character name
 cout << "Please enter your character name: " << "\n";
 cin >> tempcharName;
 fromFile = tempcharName; // pass it to the filename
 retrieveGame(fromFile, charName, hitPtsMax, charGold);
 errorMsg = "Welcome to Suldin";
}

void setName() // Sets the players name
{
cout << "Please enter your name: " << endl;
cin >> charName;
}
     
void do_fight()
{
// Local variables
int choice;
string MSG("");
string MSG2("");
bool flee(false);
int charStat;
int strMod;
int attkRoll;
int attkTotal;
int mobTotal;
int dexMod;
int defTotal;
int charDmg;
int mobDmg;
int mobRoll;
srand(time(NULL));
/* Mob variables
string mobStatus("");
string mobName("");
int mobHP(0);
int mobHPMax(0);
int mobAttk(0);
int mobDef(0);
*/
//do a nice little loop here so we can do everthing with in the function

while ((hitPts > 0) && (mobHP > 0) && (flee == false))
{
cout << "You are in combat!!" << endl
     << "A " << mobName << " is before you!" << endl
	 << "It appears to be in " << mobStatus << " condition." << endl
	 << "Your options are: " << endl
	 << "Your Hp are: " << hitPts << "/" << hitPtsMax << endl
	 << "Monsters stats " << mobHP << "/" << mobHPMax << endl
	 << "[1] Attack" << endl
	 << "[2] Flee" << endl
	 << "[3] Skill/Spell" << endl
	 << "[1, 2, 3]" << endl
	 << MSG << endl
	 << MSG2 << endl;
	 cin.ignore(256,'\n');
	 cin >> choice;
	
switch (choice)
 {
 case 1:
 // Hit the monster and allow it to strike back
 // Need a way of getting stats now.
 //Lets beat some stuff up.
 // Math attack = charAttk + strmod + die roll
 charStat = charStr;
 strMod = calcStats(charStat);
 attkRoll = rand()%21;
 attkTotal = charAttk + attkRoll + strMod;
 mobRoll = rand()%21;
 mobTotal = mobRoll + mobAttk;
 // Now we have both of thier attack rolls. Lets get thier defense score.
 charStat = charDex;
 dexMod = calcStats(charStat);
 defTotal = dexMod + charDef;
 // We now have the defense total. Lets check to see who hit. Simplify by letting player hit first
 if (attkTotal >= mobDef)
 {
 // Roll Dmg
 switch (charWeapon)
 {
 case 0:
 // Bare handed
 charDmg = strMod + rand()%4;
 break;
 case 1:
 // Level 1 weapon
 charDmg = strMod + rand()%5;
 break;
 case 2:
 // Level 2 weapon
 charDmg = strMod + rand()%7;
 case 3:
 //Level 3 weapon
 charDmg = strMod + rand()%9;
 break;
 }
 //Process damage
 mobHP = mobHP - charDmg;
 MSG = "You whak the monster for some damage";
 }
 else
 {
 MSG = "You missed the monster";
 }
 // End player damge
 //Now do monster check Check to see if it is dead. Always good.
 if ((mobTotal >= defTotal) || (mobHP > 0))
 {
 mobDmg = mobMod + rand()%9; // Apply damage if check goes through then clear damage
 hitPts = hitPts - mobDmg;
 MSG2 = "The monster Whaks you!";
 }
 else
 {
 MSG2 = "The monster Missed you";
 }
 break;
 case 2:
 // RUN AWAY!!!  Giant rabbits scarry
 // Sucess passes the error Arg back to the arena menu
 errorMsg = "You attempt to flee! You suceed!";
 flee = true;
 break;
 case 3:
 // Invoke skill sub menu
 break;
 default:
 // Call it a bad choice
 MSG = "You can not do that in combat";
 
 break;
 }
 }
if (hitPts <= 0)
{
errorMsg = "You got thumped pretty good";
flee = false;
menuHealer(errorMsg);
}
else
{
errorMsg = "You thumped the monster and gained some gold and experiance";
charExp = charExp + (charLevel * 10);
charGold = charGold + (charLevel * 5);
flee = false;
menuArena(errorMsg);
 }
}

int calcStats(int charStat)
{
int holder(0);
if ((charStat > 11) || (charStat < 14))
 {
 holder = 1;
 }
if ((charStat > 13) || (charStat < 16))
 {
 holder = 2;
 }
if ((charStat > 15) || (charStat < 18))
 {
 holder = 3;
 }
if ((charStat > 17) || (charStat < 20))
 {
 holder = 4;
 }
if ((charStat > 19) || (charStat < 22))
 {
 holder = 5;
 }
if (charStat > 21) // We will just max it here. If not I would be here all day
 {
 holder = 6;
 }

 return holder;
}