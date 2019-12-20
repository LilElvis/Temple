#include "Proto.h"
#include <string>
#include <iostream>
#include <fmod.hpp>

	//Structure containing the players inventory
	struct Inventory
	{
		int bullets = 6;
		bool hasKnife = false;
		bool hasKey = false;
		int numberOfInventories = 0;
	};
	Inventory inInventory;

	GameState theMoves();

	//Structure containing coordinate array variables
	const int HEIGHT = 8;
	const int WIDTH = 7;
	struct Position
	{
		int x = 0;
		int y = 0;
		std::string command;
		Room coordinates[WIDTH][HEIGHT];
	};
	Position pos;

//Function that dictates "custom escape characters" used in strings.
void printStringColoured(std::string a_stringToColour)
{
	std::string str = a_stringToColour;
	std::size_t found = str.find_first_of("@");

	while (found != std::string::npos)
	{
		switch (str[found+1])
		{
		case 'r':
			std::cout << str.substr(0, found);
			str = str.substr(found + 2);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
			break;
		case 'g':
			std::cout << str.substr(0, found);
			str = str.substr(found + 2);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey);
			break;
		case 'd':
			std::cout << str.substr(0, found);
			str = str.substr(found + 2);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DarkGrey);
			break;
		}
		found = str.find_first_of("@");
	}

	std::cout << str;
}

//Sets default window size
void WindowSize()
{
	system("MODE CON COLS=71 LINES=40");
	SetWindowText(GetConsoleWindow(), L"TEMPLE");
	
/*HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	MoveWindow(console, r.left, r.top, 600, 650, TRUE);*/
}

//Implementation of Sounds
class FModControl
{
public:
	FMOD::System*	m_system;
	FMOD::Sound*	m_sound;
	FMOD::Channel*	m_channel;

	FModControl(){}

	void InitializeFMod()
	{
		FMOD::System_Create(&m_system);

		m_system->init(100, FMOD_INIT_NORMAL, 0);

	}
	void FModLoadSound(std::string a_filePath, bool loopSound)
	{
		m_system->createSound(a_filePath.c_str(), FMOD_2D, 0, &m_sound);
		if (loopSound == true)
		{
			m_sound->setMode(FMOD_LOOP_NORMAL);
		}
		else
		{
			m_sound->setMode(FMOD_LOOP_OFF);
		}
	}

	void FModPlaySound()
	{
		m_system->playSound(m_sound, 0, false, &m_channel);
	}
};

//Function containing the main menu and it's functionality
GameState menu()
{
	system("cls");
	GameState gamestate;
	std::cout << "¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "[x][x][x][x] |][][][]] [][]       [][] |[][]]]  []][]]     |][][][]] \n";
	std::cout << "   [[[]]]  | |]][||]]  [!!!\\     /!!!] |[  ]]]] []][ |     |]][||]]  \n";
	std::cout << "   [[]]]   }  ]]]       [[ ]\\   /[ ]]   |[][]]   [][ |      ]]]      \n";
	std::cout << "  []]]]   {  |][][][]] [=====\\_/=====]  |]]]    [[]] {     |][][][]] \n";
	std::cout << "    [[][     |]][||]]  [====]___[====]  |]]]    []]]] }    |]][||]]  \n";
	std::cout << "   []] |      ]]]      [==|\\[\\_/]/|==]  |]]      [][]       ]]]      \n";
	std::cout << "  []]  |     |][][][]] [==] \\[=]/ [==]  |]]     []||||]    |][][][]] \n";
	std::cout << "    []       |]][||]] [xxxx] [x] [xxxx] |]      []]]]||||] |]][||]]  \n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "?????????????????????????????????????????????????????????????????????\n";

	std::cout << "\n";
	std::cout << "You're a rogue. An adventurer with a reputation for getting results.\n";
	std::cout << "Now your skills will be put to the ultimate test. Hired for a job \n";
	std::cout << "that no one else has even attempted: to raid an ancient temple with \n";
	std::cout << "a treasure beyond your most astonishing fantasies.You have the \n";
	std::cout << "potential to become an unrivaled legend. \n";
	std::cout << "\n";
	std::cout << "Shall we ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "begin";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "? Or do you wish to ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "exit";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "? Perhaps you care to read the\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "instructions";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " first?\n";
	std::getline(std::cin, pos.command);

	if (pos.command == "begin" || pos.command == "start" || pos.command == "commence" || pos.command == "b" || pos.command == "s")
	{
		gamestate = PLAYSTATE;
		return gamestate;
	}
	else if (pos.command == "exit" || pos.command == "quit" || pos.command == "e" || pos.command == "q")
	{
		std::cout << "\nThanks for not playing..? I guess.\n";
		gamestate = ENDSTATE;
		return gamestate;
	}
	else if (pos.command == "instructions" || pos.command == "i" || pos.command == "instruction" || pos.command == "help" || pos.command == "h")
	{
		std::cout << "\nWhile attempting to avoid an untimely death, and ultimately escape\n";
		std::cout << "the treacherous temple, you would be wise to follow these helpful\ntips:\n"; 
		std::cout << "\n1. Look out for the key words, highlighted in ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "red";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << ", for hints as to \n";
		std::cout << "what pos.command you should use in each scenario.\n";
		std::cout << "\n2. When on the move, the direction you should type is stated in\n";
		std::cout << "cardinal, but you can type a plethra of different things. For\nexample,";
		std::cout << " typing 'up', 'u', or 'n', is the same as typing 'north'!\n";
		std::cout << "\n3. NEVER type 'inventory'... Ever...\n";
		std::cout << "\n4. When prompted to ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << ", make sure you spell it correctly!\n";
		std::cout << "Mispelling it will spell your doom. Keep in mind you only have six\n"; 
		std::cout << "bullets, you can't just waltz on through shooting everything in \n";
		std::cout << "sight. Check how many bullets you have at any time you're out of \n";
		std::cout << "combat by typing ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "Gyre";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << ".\n";
		std::cout << "\n5. You can see these tips by calling for ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "help";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " as long as you're\nnot in combat!\n";
		std::cout << "\nSo, with that information in mind, shall we ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "begin";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "? Or do you wish to\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "exit";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "?\n";
		std::getline(std::cin, pos.command);
		if (pos.command == "begin" || pos.command == "start" || pos.command == "commence" || pos.command == "b" || pos.command == "s")
		{
			gamestate = PLAYSTATE;
			return gamestate;
		}
		else if (pos.command == "exit" || pos.command == "quit" || pos.command == "e" || pos.command == "q")
		{
			std::cout << "\nThanks for not playing..? I guess.\n";
			gamestate = ENDSTATE;
			return gamestate;
		}
		else
		{
			std::cout << "\nNot sure what that means... Try again. \n";
			gamestate = MENUSTATE;
			return gamestate;
		}
	}
	else
	{
		std::cout << "\nNot sure what that means... Try again. \n";
		gamestate = MENUSTATE;
		return gamestate;
	}
}

//Function that handles room events
GameState roomEvent()
{
	GameState gamestate;
	
	FModControl audio;
	audio.InitializeFMod();

	system("cls");

	while (pos.coordinates[pos.x][pos.y].inEvent = true)
	{
		audio.m_system->update();
		if (pos.coordinates[pos.x][pos.y].location == 0)
		{
			std::cout << "\nEverything is a blur. A dimly lit menagerie of ancient\n";
			std::cout << "artifacts long lost to the stream of time. There are two \n";
			std::cout << "torches mounted on each of the walls, their flickering light \n";
			std::cout << "casting your pale shadow over the length of the cracking\n";
			std::cout << "limestone floor. You shift your feet forwards, careful to avoid\n";
			std::cout << "anything that might disturb the delicate silence that blankets\n";
			std::cout << "the room.\n";
			std::cout << "\nErected in the middle of the vast chamber was an intricately\n"; 
			std::cout << "carved monolith, smothered in a faded red that gave it an almost\n";
			std::cout << "flesh-like appearance. But it is not the monolith itself that\n";
			std::cout << "catches your attention but what is sunk within it. An iridescent\n";
			std::cout << "sphere, both ominous and irresistible.\n";
			std::cout << "\nFinally, after travelling through the depths of this temple, you\n";
			std::cout << "have found the treasure you were sent to retrieve. It's smooth to \n";
			std::cout << "the touch, you can feel the power surge through your fingertips.\n";
			std::cout << "\nSuddenly, the temple seems to shudder in fear. The floor shakes\n";
			std::cout << "beneath you, the cracks becoming a web beneath your feet. Debris \n";
			std::cout << "snap off from the ceiling, plummeting towards you. Your foot is \n";
			std::cout << "gripped beneath the collapsing stone. You feel the pain snap \n";
			std::cout << "through your skull, then you feel nothing. Everything goes black.\n";
			std::cout << "\nYou awake. The room is pitch-dark, the only light is coming from\n";
			std::cout << "the glowstick pinned to the side of your jacket. The torches must \n";
			std::cout << "have been put out by the falling debris. There's no way out. \n";
			std::cout << "Collapsed pillars had made sure of that. Even the monolith itself \n";
			std::cout << "is nothing more than shattered remnants. This is no time to wait \n";
			std::cout << "around. Maybe you should";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << " look ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "harder...\n";
			std::getline(std::cin, pos.command);
			if (pos.command == "look")
			{
				std::cout << "\nIt's difficult to make out anything besides the strange glyphs\n";
				std::cout << "etched into the walls. There's a gaping ditch, just large enough to\n";
				std::cout << "crawl through, hollowed out in the corner of the wall. It smells\n"; 
				std::cout << "fetid, a waft of decay flooding into your nostrils. Your hand\n";
				std::cout << "briefly grazes over your trusty revolver, ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "Gyre";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << ", counting each of\nthe six shots in the chamber.\n";
				pos.coordinates[pos.x][pos.y].inEvent = false;
				gamestate = PLAYSTATE;
				return gamestate;
			}
		}
		else if(pos.coordinates[pos.x][pos.y].location == 1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DarkGrey); std::cout << "\n............................................................\n..........................:.................................\n......................77.:++7,..............................\n......................7I:I:,I7..............................\n......................7I+:I.I7..............................\n......................7I..II=~..............................\n......................~=+I.~~=..............................\n................?~~~.~~~~~+=~=~~.~~.........................\n.................~:?~:~~~~=?==~~=~~~~.......................\n................~=,???=.~=~,,=~+~~=.........................\n................~,=I?~.~~.?~.~~?~==.....?...................\n................=+?+=~?+?.?=.~.~?~~....?..+.?+..............\n..............~~~~~.~.=~=~~?+?.~~~=...+?.,.~,,?.............\n...............:+:...,=:===~~..,:I?~....:~~:.+?.............\n..............++==...~:,=.~~....?.:~~~::=..,.+?.............\n..............=~~~~.:=:::=I.:~=~.~I.~.,???...+..............\n...............=....~:=:~,:~~~:.,?:::..=~..=................\n................II,:::~+:.~=~.............=.................\n.............,...~.=,~+~=~:~~...............................\n............~......=~:~=~:~~~:..............................\n............?......~~.~=+~:~~~..............................\n...........=+....+~??.......=~:.............................\n................,.~.......++~~,.............................\n.................=~~=......~~~~.............................\n................~+~~~.....~~~=~.............................\n...............~~~~~~.........,.............................\n................~?:,......+.?~~.,...........................\n..............:~=,~=.......~=:I~~=..........................\n...............................,............................\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "\nYou crawl into a hall. You hear footsteps that slam like the beat \n";
			std::cout << "of some sacrificial drum. A shadow extends to the edge of the wall, \n";
			std::cout << "thin like the twisted rope of a noose. You ought to hide before it \n";
			std::cout << "comes near! Searching frantically, you see a pile of";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);  std::cout << " boulders ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "near \nthe edge of the hall, as well as a granite";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << " table ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "you \ncould hide behind! Which one will it be?\n";
			std::getline(std::cin, pos.command);
			if (pos.command == "boulder" || pos.command == "boulders")
			{
				std::cout << "\nA shadow of monstrous proportions is charred into the wall, an \n";
				std::cout << "outline of mountainous flesh. A flaming sword, scorching your skin \n";
				std::cout << "as its blade gets closer to the edge of the stones. Your heart stops \n";
				std::cout << "for what feels like minutes before it finally turns, leaving the\n";
				std::cout << "hall. A knife falls from it's hilt, you'd be wise to ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "take"; 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " it. \n";
				std::getline(std::cin, pos.command);
				if (pos.command == "take")
				{
					std::cout << "\nKnife added to inventory!\n";
					inInventory.hasKnife = true;
					pos.coordinates[pos.x][pos.y].inEvent = false;
					gamestate = PLAYSTATE;
					return gamestate;
				}
				else
				{
					std::cout << "\nOh, just ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "take";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " it. \n";
					std::cout << "\nKnife added to inventory!\n";
					inInventory.hasKnife = true;
					pos.coordinates[pos.x][pos.y].inEvent = false;
					gamestate = PLAYSTATE;
					return gamestate;
				}
			}
			else if (pos.command == "table")
			{
				//audio.FModLoadSound("assets/encounter.wav", false);
				//audio.FModPlaySound();
				std::cout << "\nThe creature comes closer, its boot crashes near your face. You \n";
				std::cout << "hold your breath as it stops. It can see you clearly between the \n";
				std::cout << "legs! A massive fist crashes through the granite table. That was a \n";
				std::cout << "mistake. There's no point in trying to hide now. You reach for Gyre,\n";
				std::cout << "maybe you can";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << " shoot ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "it...\n";
				std::getline(std::cin, pos.command);
				if (pos.command == "shoot" &&  inInventory.bullets > 0)
				{
					//audio.FModLoadSound("assets/gun.wav", false);
					//audio.FModPlaySound();
					std::cout << "\nThe screeching creature rushes at you. Your hand snaps to Gyre, \n";
					std::cout << "slipping it from the worn leather holster. The sword flies past \n";
					std::cout << "your neck, inches from cleaving your head off. You cock the revolver \n"; 
					std::cout << "and fire. It falls back, its scream like nails on chalkboard played \n";
					std::cout << "through a tin can. It thrashes around the floor, crumpling inward \n";
					std::cout << "like a spider. You slow your breath.\n";
					--inInventory.bullets;
					std::cout << "You only have " << inInventory.bullets << " bullets left...\n";
					std::cout << "\nA knife shines on the monsters hilt, you'd be wise to ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "take";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " it. \n";
					std::getline(std::cin, pos.command);
					if (pos.command == "take")
					{
						std::cout << "\nKnife added to inventory!\n";
						inInventory.hasKnife = true;
						pos.coordinates[pos.x][pos.y].inEvent = false;
						gamestate = PLAYSTATE;
						return gamestate;
					}
					else
					{
						std::cout << "\nOh, just ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "take";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " it. \n";
						std::cout << "\nKnife added to inventory!\n";
						inInventory.hasKnife = true;
						pos.coordinates[pos.x][pos.y].inEvent = false;
						gamestate = PLAYSTATE;
						return gamestate;
					}
				}
				else
				{
					std::cout << "\nYour legs feel cemented to the floor as it comes closer. It \n";
					std::cout << "towers over you, the stench of its breath like rotting flesh. \n";
					std::cout << "The sword came down, your blood painting the walls as the smell \n";
					std::cout << "of your charred corpse filled the hall. You'll be buried here \n";
					std::cout << "along with its secrets.\n";
					gamestate = GAMEOVER;
					return gamestate;
				}
			}
		}
		else if (pos.coordinates[pos.x][pos.y].location == 2)
		{
			std::cout << "\nThe room is sprawling, dark and decrepit. A creature's twisted head\n";
			std::cout << "comes into view as you peer over the side of the wall. Then another.\n";
			std::cout << "Now you're sure, there's more than one threat. Whatever you had done\n";
			std::cout << "with the sphere had triggered the release of these creatures. They\n";
			std::cout << "turn their heads toward you, their reddened eyes buried beneath \n";
			std::cout << "folds of their graying skin. There's a";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << " pillar ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "right next to you and\na dark ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "corner ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "near the edge of the ";
			std::cout << "room. Might be a good idea to\nhide.\n";
			std::getline(std::cin, pos.command);
			if (pos.command == "pillar")
			{
				std::cout << "\nYou hide behind the pillar, crawling slowly forward. You hear the\n";
				std::cout << "sound of their rasping breathing as they sniff the air, as if they\n";
				std::cout << "can smell the fear sinking deep into your stomach. And for all you \n";
				std::cout << "knew, they could. One of the creatures lumbers away, leaving only \n";
				std::cout << "one patrolling the room.The creature lurches slowly towards you.\n";
				std::cout << "Remembering the knife in your pocket, your only courses of action\n";
				std::cout << "are to ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "stab ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "or ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << ".\n";
				std::getline(std::cin, pos.command);
				if (pos.command == "stab")
				{

					std::cout << "\nThe creature approaches slowly. You lay in wait as it draws closer,\n";
					std::cout << "and closer. With perfect timing you jump from cover, thrusting the \n";
					std::cout << "knife through its neck, sending blood splurting  across the ground. \n";
					std::cout << "You attempt to remove the knife from its neck, but alas, your\n";
					std::cout << "efforts are futile. The coast seems to be clear, for now...\n";
					inInventory.hasKnife = false;
					pos.coordinates[pos.x][pos.y].inEvent = false;
					gamestate = PLAYSTATE;
					return gamestate;
				}
				else if (pos.command == "shoot"  &&  inInventory.bullets > 0)
				{
					//audio.FModLoadSound("assets/gun.wav", false);
					//audio.FModPlaySound();
					std::cout << "\nThe creature is moving slowly, it has yet to detect your presence.\n";
					std::cout << "Despite your trembling hands it's an easy target, you lean out and \n";
					std::cout << "put a single bullet in it's head. It drops dead, and the coast is \n";
					std::cout << "clear for now.\n";
					--inInventory.bullets;
					std::cout << "You only have " << inInventory.bullets << " bullets left...\n";
					pos.coordinates[pos.x][pos.y].inEvent = false;
					gamestate = PLAYSTATE;
					return gamestate;
				}
			}
				else if (pos.command == "corner")
				{
					//audio.FModLoadSound("assets/encounter.wav", false);
					//audio.FModPlaySound();
					std::cout << "\nYou force yourself into the dark corner. It's smaller than you \n";
					std::cout << "thought it would be. The creatures can see you in the darkness. You\n";
					std::cout << "try to run, but there's nowhere to go. You have no choice but to\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "!\n";
					std::getline(std::cin, pos.command);
					if (pos.command == "shoot"  &&  inInventory.bullets > 0)
					{
						//audio.FModLoadSound("assets/gun.wav", false);
						//audio.FModPlaySound();
						std::cout << "\nYou draw Gyre, blasting one of the creatures, sending it crashing\n";
						std::cout << "to the ground. You reach for the knife as the second creature draws\n";
						std::cout << "nearer. You throw the knife with all your might, piercing the \n";
						std::cout << "creature's face, stopping it dead in it's tracks. Literally.\n";
						--inInventory.bullets;
						std::cout << "You only have " << inInventory.bullets << " bullets left...\n";
						pos.coordinates[pos.x][pos.y].inEvent = false;
						gamestate = PLAYSTATE;
						return gamestate;
					}
					else
					{
						std::cout << "\nYou wince for a moment, fumbling your gun before feeling a sword \n";
						std::cout << "pierce through your stomach. The creatures slam your corpse down onto\n";
						std::cout << "a pike, leaving it as a warning to any future intruders. It's\n";
						std::cout << "alright. Not everyone can be one of the greats.\n";
						gamestate = GAMEOVER;
						return gamestate;
					}
				}
			}
		else if (pos.coordinates[pos.x][pos.y].location == 6)
		{
				std::cout << "\nThe second you walk through the door, the water numbs your legs\n";
				std::cout << "through the thin jumpsuit. The ebony pool stretches out below you,\n";
				std::cout << "opaque and bleak. You see a massive statue to the east, similar to ";
				std::cout << "the creatures but much less vicious. It almost looks regal, a tragic look\n";
				std::cout << "carved into its face. The last remnant of a civilization that should\n";
				std::cout << "be long dead. The approaching light brings you back to a reality where\n";
				std::cout << "these creatures are anything but dead. You see a crevice in the side\n";
				std::cout << "of the ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "statue";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << ", or you could simply hide in the ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "water";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " beneath you.\n";
				std::getline(std::cin, pos.command);
				if (pos.command == "statue")
				{
					std::cout << "\nThe light fades as the monster passes near to your hiding place.\n";
					std::cout << "You wait until there's nothing else but the silence and darkness of \n";
					std::cout << "the chamber to greet you. \n";
					pos.coordinates[pos.x][pos.y].inEvent = false;
					gamestate = PLAYSTATE;
					return gamestate;
				}
				else if (pos.command == "water")
				{
					//audio.FModLoadSound("assets/encounter.wav", false);
					//audio.FModPlaySound();
					std::cout << "\nThe light grows brighter with each step. You start to realize that\n";
					std::cout << "you made a mistake. While the water looked opaque in the dark, with\n";
					std::cout << "its sword, it can see right through. You see the sword flash down \n";
					std::cout << "towards your body. You scramble out of the way as the creature \n";
					std::cout << "releases a savage moan. You look to Gyre, in hopes it will still ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "\nshoot";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " while flooded....\n";
					std::getline(std::cin, pos.command);
					if (pos.command == "shoot"  &&  inInventory.bullets > 0)
					{
						//audio.FModLoadSound("assets/gun.wav", false);
						//audio.FModPlaySound();
						std::cout << "\nYou lift your revolver from your water-drenched belt. The flash\n";
						std::cout << "from the shot illuminates the water for a moment. You're lucky this \n";
						std::cout << "time. It plunges dead into the water, the sword emitting a cloud of \n";
						std::cout << "steam as it sinks to the bottom. Blood seeps out from its corpse.\n";
						--inInventory.bullets;
						std::cout << "You only have " << inInventory.bullets << " bullets left...\n";
						pos.coordinates[pos.x][pos.y].inEvent = false;
						gamestate = PLAYSTATE;
						return gamestate;
					}
					else
					{
						std::cout << "\nThe creature stands over you, impaling you with one swift motion. \n";
						std::cout << "It slides the sword through your guts. You feel everything until it \n";
						std::cout << "slides up through your skull, sending you to oblivion. You're just \n";
						std::cout << "another failure waiting to be forgotten by history.\n";
						gamestate = GAMEOVER;
						return gamestate;
					}
				}
			}
		else if (pos.coordinates[pos.x][pos.y].location == 7)
		{
			std::cout << "\nAfter the massive chamber, the hallway feels claustrophobic, like it\n"; 
			std::cout << "is trying to crush you before you can get any farther. But at least\n";
			std::cout << "there are no creatures. You look at the glyphs carved into the wall.\n";
			std::cout << "You see elaborate depictions of battles between creatures.One group \n";
			std::cout << "looks like those creatures but the others was different. More refined\n";
			std::cout << "and less bulky. They both held a shining sphere similar to the one \n";
			std::cout << "you found. You force your eyes away from the glyphs. There's a \n";
			std::cout << "skeleton with its hands clamped shut. It looks less... human with \n";
			std::cout << "each step, its misshapen bones twisted around something shining.\n";
			std::cout << "A gilded key which feels cold in your palm as you slip it into\n"; 
			std::cout << "your pouch.\n";
			std::cout << "\nKey added to inventory!\n";
			pos.coordinates[pos.x][pos.y].inEvent = false;
			inInventory.hasKey = true;
			pos.coordinates[2][3].description = "\n@d  .   7.   .7   .7  .7               7.  7, .I   7.   .   \n  .   7.   .7   .   .7               7.  7, .I   7.   .   \n  .   7.7  .7   .   .7               7.  7, .I   7.  7.   \n  .   7.7  .7   .7  .7    7.....7    7.  7, .I   7.  7.   \n  .   7.7  .7   .   .7   7.......    7.  7, .I   7.   .   \n  .   7.   .7   .7  .7    .......    7.  7, .I   7.   .   \n  .   7.   .7   .7  .7    .......    7.  7, .I   7.  7.   \n  .   7.   .7   .7  .7    .......    7.  7, .I   7.  7.   \n  .   7.   .7   .7  .7    .......    7.  7, .I   7.   .   \n  .   7.   .7   .   ++++++++++++++++++ + 7, .I   7.   .   \n  .   7.   .7   .7  ++++++++++++++++++ + 7, .I   7.  7.   \n  .   7.   .7   ++++++++++++++++++++++++++.I   7.   .   \n  .   7.7  .7   ++++++++++++++++++++++++++7.I   7.  7.   \n  .   7.7  .7   ++++++++++++++++++++++++++7.I   7.  7.   \n  .   7.7  ....................................7   7.  7.   \n  .   7.   ++++++++++++++++++++++++++++++++++++    7.   .   \n  .   7.   ++++++++++++++++++++++++++++++++++++    7.   .   \n  .   7.   ++++++++++++++++++++++++++++++++++++    7.  7.   \n  . + ............................................., .   \n  .    ++++++++++++++++++++++++++++++++++++++++++++ + .   \n  .    ++++++++++++++++++++++++++++++++++++++++++++ + .   \n  .    ++++++++++++++++++++++++++++++++++++++++++++ + .   \n  .......................................................   \n++++++++++++++++++++++++++++++++++++++++++++++++++++++ + \n++++++++++++++++++++++++++++++++++++++++++++++++++++++ + \n++++++++++++++++++++++++++++++++++++++++++++++++++++++ + \n++++++++++++++++++++++++++++++++++++++++++++++++++++++ + \n@gYou are in the stairwell, the doors are to the @rnorth@g and the @rsouth@g.\n";
			pos.coordinates[2][3].southDoor = true;
			pos.coordinates[2][3].inEvent = true;
			gamestate = PLAYSTATE;
			return gamestate;
		}
		else if (pos.coordinates[pos.x][pos.y].location == 8)
		{
			std::cout << "\nYou hear a crackling near the back of the chamber. The whole room is\n";
			std::cout << "under a cloak of pitch darkness. Then everything flares crimson \n";
			std::cout << "orange. A roaring mound of flesh shifts forward, bursts of flames\n";
			std::cout << "ripping from each hole in its rotting flesh. It is yet another \n";
			std::cout << "creature, unlike anything you had ever seen. You need to find a place\n";
			std::cout << "to hide. You see a small ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "crawlspace";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " in the wall, a crumbled ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "rock\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "covered in vines, a cracked ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "pillar";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " near the edge of the room and a\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "vine";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " extending from the ceiling.\n";
			std::getline(std::cin, pos.command);
			if (pos.command == "crawlspace")
			{
				//audio.FModLoadSound("assets/encounter.wav", false);
				//audio.FModPlaySound();
				std::cout << "\nThe creature slides by you, one of the holes moves right in front of\n";
				std::cout << "your face. Fire shoots out at you, scorching your face.That wasn't a \n";
				std::cout << "very bright move. You scramble out of the crawlspace. You should \n";
				std::cout << "probably ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " it before it comes back to roast you again.\n";
				std::getline(std::cin, pos.command);
				if (pos.command == "shoot"  &&  inInventory.bullets > 0)
				{
					//audio.FModLoadSound("assets/gun.wav", false);
					//audio.FModPlaySound();
					std::cout << "\nYou pull out Gyre, firing a shot straight through the upper flesh \n";
					std::cout << "which you assume is the creature's head. The flesh shifts and\n";
					std::cout << "wriggles like jello as the creature writhes and dies. That was a\n";
					std::cout << "little too close.\n";
					--inInventory.bullets;
					std::cout << "You only have " << inInventory.bullets << " bullets left...\n";
					pos.coordinates[pos.x][pos.y].inEvent = false;
					gamestate = PLAYSTATE;
					return gamestate;
				}
				else
				{
					std::cout << "\nYou failed! You feel the creature's flames engulf you, charring your\n";
					std::cout << "skin to a blackened crisp. You try to run but you trip on a fallen \n";
					std::cout << "rock, smashing your skull across the floor. The creature slides over\n";
					std::cout << "your lifeless corpse, burning whatever remains. Hope you wanted to be\n";
					std::cout << "cremated.";
					gamestate = GAMEOVER;
					return gamestate;
				}
			}
			else if (pos.command == "rock")
			{
				//audio.FModLoadSound("assets/encounter.wav", false);
				//audio.FModPlaySound();
				std::cout << "\nThe creature slides straight over the crumbling rock, its fetid \n";
				std::cout << "flesh inches from your face. You stumble, tripping over the rock \n";
				std::cout << "right before the fire erupts from its body. Probably should have \n";
				std::cout << "used your brain before hiding there. You might be able to ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey);std::cout << " it.\n";
				std::getline(std::cin, pos.command);
				if (pos.command == "shoot"  &&  inInventory.bullets > 0)
				{
					//audio.FModLoadSound("assets/gun.wav", false);
					//audio.FModPlaySound();
					std::cout << "\nYou pull out Gyre, firing a shot straight through the upper flesh \n";
					std::cout << "which you assume is the creature's head. The flesh shifts and\n";
					std::cout << "wriggles like jello as the creature writhes and dies. That was a\n";
					std::cout << "little too close.\n";
					--inInventory.bullets;
					std::cout << "You only have " << inInventory.bullets << " bullets left...\n";
					pos.coordinates[pos.x][pos.y].inEvent = false;
					gamestate = PLAYSTATE;
					return gamestate;
				}
				else
				{
					std::cout << "\nYou failed! You feel the creature's flames engulf you, charring your\n";
					std::cout << "skin to a blackened crisp. You try to run but you trip on a fallen \n";
					std::cout << "rock, smashing your skull across the floor. The creature slides over\n";
					std::cout << "your lifeless corpse, burning whatever remains. Hope you wanted to be\n";
					std::cout << "cremated.";
					gamestate = GAMEOVER;
					return gamestate;
				}
			}
			else if (pos.command == "pillar")
			{
				//audio.FModLoadSound("assets/encounter.wav", false);
				//audio.FModPlaySound();
				std::cout << "\nThe creature lumbers towards you. It swings it's raw flesh at you. \n";
				std::cout << "The sheer mass of its body rips through the pillar, sending the \n";
				std::cout << "debris flying at you. Hiding behind a cracked pillar wasn't such a\n";
				std::cout << "smart move. You should ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " it before it crushes you too. \n";
				std::getline(std::cin, pos.command);
				if (pos.command == "shoot"  &&  inInventory.bullets > 0)
				{
					//audio.FModLoadSound("assets/gun.wav", false);
					//audio.FModPlaySound();
					std::cout << "\nYou pull out Gyre, firing a shot straight through the upper flesh \n";
					std::cout << "which you assume is the creature's head. The flesh shifts and\n";
					std::cout << "wriggles like jello as the creature writhes and dies. That was a\n";
					std::cout << "little too close.\n";
					--inInventory.bullets;
					std::cout << "You only have " << inInventory.bullets << " bullets left...\n";
					pos.coordinates[pos.x][pos.y].inEvent = false;
					gamestate = PLAYSTATE;
					return gamestate;
				}
				else
				{
					std::cout << "\nYou failed! You feel the creature's flames engulf you, charring your\n";
					std::cout << "skin to a blackened crisp. You try to run but you trip on a fallen \n";
					std::cout << "rock, smashing your skull across the floor. The creature slides over\n";
					std::cout << "your lifeless corpse, burning whatever remains. Hope you wanted to be\n";
					std::cout << "cremated.";
					gamestate = GAMEOVER;
					return gamestate;
				}
			}
			else if (pos.command == "vine")
			{
				std::cout << "\nYou grab the vine, careful to maintain a tight grip. The creature\n";
				std::cout << "moves closer underneath you. For some reason, it doesn't see you.\n";
				std::cout << "Maybe it can't look up. You hold in a sigh of relief as it slides\n";
				std::cout << "forward. You push your momentum forward, swinging yourself to the\n";
				std::cout << "other side of the room.\n";
				pos.coordinates[pos.x][pos.y].inEvent = false;
				gamestate = PLAYSTATE;
				return gamestate;
			}
		}
		else if (pos.coordinates[pos.x][pos.y].location == 10 && inInventory.hasKey == false)
		{
			std::cout << "\nYou found the stairwell, a sharp contrast of thick shadows and\n"; 
			std::cout << "flickering torchlight. You walk up the stairs, careful not to catch\n";
			std::cout << "your foot on any of the crumbling, limestone steps. You see a door \n";
			std::cout << "at the top, a gilded lock fixed in the center. It doesn't budge, no\n";
			std::cout << "matter how hard you try to push it. There must be something needed\n";
			std::cout << "to open the door, maybe its somewhere else.\n";
			pos.coordinates[pos.x][pos.y].inEvent = false;
			pos.coordinates[2][3].description = "\n@gYou are in the stairwell, going up and to the south. At the top, \nthere is a sealed door. The only open door, is to the @rnorth@g.\n";
			pos.coordinates[2][3].southDoor = false;
			gamestate = PLAYSTATE;
			return gamestate;
		}
		else if (pos.coordinates[pos.x][pos.y].location == 10 && inInventory.hasKey == true)
		{
			std::cout << "\nYou walk up the stairwell, the shadows draped across the edge of\n";
			std::cout << "the dimming light. You reach the door at the top of the stairs. You\n";
			std::cout << "pull out the gilded key from your pouch, slipping it in the lock.\n";
			std::cout << "You hear the sound of the door dragging steadily upwards as it opens.\n\n";
			pos.coordinates[pos.x][pos.y].inEvent = false;
			gamestate = PLAYSTATE;
			return gamestate;
		}
		else if (pos.coordinates[pos.x][pos.y].location == 11)
		{
			std::cout << "\nYou hear the sound of chinking coming from above you. You look up\n";
			std::cout << "slowly and you see it. It's sprawled across the ceiling, its spindle-\n";
			std::cout << "like arms contorted like a spider's. Its eyes are inky black, the\n"; 
			std::cout << "pupils rolling into the back of its head. You need to find a place\n";
			std::cout << "to hide, where it can't see you. There are cracked ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "boulders"; 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " near the\n";
			std::cout << "edge of the room and a granite ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "table"; 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " to your right.\n";
			std::getline(std::cin, pos.command);
			if (pos.command == "boulders" || pos.command == "boulder")
			{
				//audio.FModLoadSound("assets/encounter.wav", false);
				//audio.FModPlaySound();
				std::cout << "\nThe creature hisses, stretching its arm like worn-out gum, its claws \n"; 
				std::cout << "slash past your face. It could clearly see you from above. At this \n";
				std::cout << "juncture, your best course of action is to ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " it.\n";
				std::getline(std::cin, pos.command);
				if (pos.command == "shoot"  &&  inInventory.bullets > 0)
				{
					//audio.FModLoadSound("assets/gun.wav", false);
					//audio.FModPlaySound();
					std::cout << "\nYou fire one shot, the bullet piercing through its ribs, causing\n";
					std::cout << "blood to pour onto your face. It crashes to the floor, its skull\n"; 
					std::cout << "shattering like china.\n";
					--inInventory.bullets;
					std::cout << "You only have " << inInventory.bullets << " bullets left...\n";
					pos.coordinates[pos.x][pos.y].inEvent = false;
					gamestate = PLAYSTATE;
					return gamestate;
				}
				else
				{
					std::cout << "\nYou hear the sounds of padded feet pounding above you. Its arm\n"; 
					std::cout << "stretches down slashes your throat. You choke to death on your own \n";
					std::cout << "blood. You sputter as it eats you alive. Not a very fitting end for a\n";
					std::cout << "legend.\n";
					gamestate = GAMEOVER;
					return gamestate;
				}
			}
			else if (pos.command == "table")
			{
				std::cout << "\nIt seems that you're safe underneath the table. The creature can't\n";
				std::cout << "see you. It stays for a moment before crawling through a cracked hole\n";
				std::cout << "in the wall. You're alone now.\n";
				pos.coordinates[pos.x][pos.y].inEvent = false;
				gamestate = PLAYSTATE;
				return gamestate;
			}
		}
		else if (pos.coordinates[pos.x][pos.y].location == 14)
		{
			std::cout << "\nYou enter the room and hear nothing. The silence smothers you as\n";
			std::cout << "your eyes scan the room with the little light that torches can \n";
			std::cout << "provide. You see holes on the ceiling. There is a closed door to the \n";
			std::cout << "east and on the floor in front of it you see three objects; a ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "sun";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "\nshaped stone and two ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "moon";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " shaped stones, arranged in a line with the\n";
			std::cout << "sun in the middle. They each rest on raised plates. They appear to\n";
			std::cout << "be light enough to pick up.\n";
			std::getline(std::cin, pos.command);
			if (pos.command == "sun")
			{
				std::cout << "\nThe door slowly creaks open. Seems like you made the right choice.\n";
				pos.coordinates[pos.x][pos.y].inEvent = false;
				gamestate = PLAYSTATE;
				return gamestate;
			}
			else if (pos.command == "moon")
			{
				std::cout << "\nNothing happened. You might want to pick up something else. There is\n";
				std::cout << "still one ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "moon";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << ", and a ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "sun";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << ".\n";
				std::getline(std::cin, pos.command);
				if (pos.command == "moon")
				{
					std::cout << "\nThe door slowly creaks open. Seems like you made the right choice.\n";
					pos.coordinates[pos.x][pos.y].inEvent = false;
					gamestate = PLAYSTATE;
					return gamestate;
				}
				else if (pos.command == "sun")
				{
					std::cout << "\nYou know something's wrong immediately. Spikes creak out of the\n";
					std::cout << "holes, then it crashes down, killing you in an instant. You should\n";
					std::cout << "have payed more attention.\n";
					gamestate = GAMEOVER;
					return gamestate;
				}
			}
		}
		else if (pos.coordinates[pos.x][pos.y].location == 16)
		{
			std::cout << "\nYou walk into a chamber, its floor cracking open into emptiness. You\n";
			std::cout << "don't know how far it goes down but you're not ready to find out. You\n";
			std::cout << "hear scraping on the ceiling. It's another one of those bastards. It's\n";
			std::cout << "hard to see but you can almost make out a something shifting between\n";
			std::cout << "the shadows. You need to find a place to hide. You see a ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "statue";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " near\n";
			std::cout << "the corner of the room and a ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "pillar";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " you can hide behind.\n";
			std::getline(std::cin, pos.command);
			if (pos.command == "statue")
			{
				std::cout << "\nYou hide between the statue's legs, crouching underneath. The creature\n";
				std::cout << "moves past you, it's hissing growing steadily softer. This is your\n";
				std::cout << "chance to get out.\n";
				pos.coordinates[3][6].inEvent = false;
				gamestate = PLAYSTATE;
				return gamestate;
			}
			else if (pos.command == "pillar")
			{
				//audio.FModLoadSound("assets/encounter.wav", false);
				//audio.FModPlaySound();
				std::cout << "\nThe creature wraps around the pillar, spotting you behind its girth.\n";
				std::cout << "It lashes out, smacking you across the floor. That was a poorly chosen\n";
				std::cout << "hiding spot. You'll have to ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " it.\n";
				std::getline(std::cin, pos.command);
				if (pos.command == "shoot")
				{
					//audio.FModLoadSound("assets/gun.wav", false);
					//audio.FModPlaySound();
					std::cout << "\nYou fire a shot out at the ceiling. It seems almost by pure luck but\n";
					std::cout << "the sound of its screams confirm that you made it...somehow. It\n";
					std::cout << "crashes down into one of the holes littering the floor. Another\n";
					std::cout << "bullet gone.\n";
					pos.coordinates[3][6].inEvent = false;
					gamestate = PLAYSTATE;
					return gamestate;
				}
				else
				{
					std::cout << "\nIt crushes your skull like a walnut, squeezing your brain through its\n";
					std::cout << "spindly fingers. That was a pathetic death, maybe you don't deserve to\n";
					std::cout << "be remembered.\n";
					gamestate = GAMEOVER;
					return gamestate;
				}
			}
		}
		else if (pos.coordinates[pos.x][pos.y].location == 17)
		{
			std::cout << "\nYou see one of the creatures near the back of the room, its\n";
			std::cout << "flame - smothered sword almost blinding you after all the dark\n";
			std::cout << "corridors. You have to find a place to hide. You see a sacrificial\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "table";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " and a cracked ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "hole";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " in the floor.\n";
			std::getline(std::cin, pos.command);
			if (pos.command == "table")
			{
				//audio.FModLoadSound("assets/encounter.wav", false);
				//audio.FModPlaySound();
				std::cout << "\nYou hide underneath the table, the stench of blood almost overwhelming.\n";
				std::cout << "The light comes closer with each step until it is right next to you.\n";
				std::cout << "It drags you from underneath the table, throwing you to back of the\n";
				std::cout << "wall. You don't learn your lesson do you? Might be the time to ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " it.\n";
				std::getline(std::cin, pos.command);
				if (pos.command == "shoot" && inInventory.bullets > 0)
				{
					//audio.FModLoadSound("assets/gun.wav", false);
					//audio.FModPlaySound();
					std::cout << "\nYou whip out Gyre and fire once, sending shards of the creature's\n";
					std::cout << "skull clattering to the floor. A bullet wasted.\n";
					--inInventory.bullets;
					std::cout << "You only have " << inInventory.bullets << " bullets left...\n";
					pos.coordinates[pos.x][pos.y].inEvent = false;
					gamestate = PLAYSTATE;
					return gamestate;
				}
				else
				{
					std::cout << "\nThe creature cuts your legs off at the knees, sending you crashing to\n";
					std::cout << "the ground. You try to drag yourself to the door as you bleed out. It\n";
					std::cout << "seems to take sadistic pleasure in watching you crawl before it impales\n";
					std::cout << "you, turning your body into a human shish kebab. This was a sad way to\n";
					std::cout << "end your journey.\n";
					gamestate = GAMEOVER;
					return gamestate;
				}
			}
			else if (pos.command == "hole")
			{
				std::cout << "\nThe creature moves past your hole. It clearly doesn't seem to notice\n";
				std::cout << "you as it thunders past. It leaves the room.You can see that the room\n";
				std::cout << "is a dead end. It is a waste of time.\n";
				pos.coordinates[pos.x][pos.y].inEvent = false;
				gamestate = PLAYSTATE;
				return gamestate;
			}
		}
		else if (pos.coordinates[pos.x][pos.y].location == 18)
		{
			std::cout << "\nThe stairwell is small, like it was designed to crush you slowly.\n";
			std::cout << "You walk over the debris scattered across the stairs .You spot a door\n";
			std::cout << "at the top of the stairwell. The door has a small space to fit\n";
			std::cout << "something in.You pull out the gilded key, slipping it into the lock.\n";
			std::cout << "The door starts to slide open but you hear something. A soft\n";
			std::cout << "whistling past your ear. You shift out of the way just in time to see\n";
			std::cout << "a dart imbedded in the wall. The other door is closing behind you. The\n";
			std::cout << "room is booby-trapped! You need to find a place to hide until the\n";
			std::cout << "door opens. You see a wide ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "vase";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " and a small ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "statue";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " at the base of the\n";
			std::cout << "stairwell.\n";
			std::getline(std::cin, pos.command);
			if (pos.command == "vase")
			{
				std::cout << "\nYour heart is beating faster and faster with each impact. The\n";
				std::cout << "porcelain cracks more with each dart but the trap halts just before\n";
				std::cout << "it shatters. Finally, the door at the top of the stairs is open, and\n";
				std::cout << "the door at the bottom has reopened.\n";
				pos.coordinates[pos.x][pos.y].inEvent = false;
				gamestate = PLAYSTATE;
				return gamestate;
			}
			else if (pos.command == "statue")
			{
				std::cout << "\nIt's too late! You realize that you're too big to fit behind this\n";
				std::cout << "statue. You feel each dart penetrate your skin. You can do nothing\n";
				std::cout << "but wait as the life fades out of your body. What kind of treasure\n";
				std::cout << "hunter can't survive a trap?\n";
				gamestate = GAMEOVER;
				return gamestate;
			}
		}
		else if (pos.coordinates[pos.x][pos.y].location == 21)
		{
			//audio.FModLoadSound("assets/finalboss.wav", false);
			//audio.FModPlaySound();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DarkGrey); 
			std::cout << "            7,I                                          \n";
			std::cout << "             ,:=7                            ...         \n";
			std::cout << "           7.::77                          ..77~:.       \n";
			std::cout << "           :::                            7,    .:?      \n";
			std::cout << "          =::?                             :.7   :.      \n";
			std::cout << "    77    7::,                             7    ::7      \n";
			std::cout << "77 .::::.777.:?                                7::       \n";
			std::cout << ".  :::=.:::7 7:.77                           77::7    7  \n";
			std::cout << "~.7::I    ::7 7,7                            .::77 .::::I\n";
			std::cout << "~:::.     7.7.77:7                           ::7 .::777..\n";
			std::cout << "          7.::~ :7                          7:, 77.   .:7\n";
			std::cout << "          7.:: =:7           ..             7:~  ~  .:.7 \n";
			std::cout << "           .:~ .:7     I=~    ~:7777        7::77= .:7   \n";
			std::cout << "          7=:77::7   7~~~..+??.,:~:7        .::7I. ::7   \n";
			std::cout << "  7,       ::77::7   7  .:7:?~ ~? 77        ::77:7  :.   \n";
			std::cout << " 7..  ,7   .::7::7  7?:.7??.?=?:7.::?.7   7.:77::    7..7\n";
			std::cout << "77...7:?   7::,7:.  I....++~~:?,?.7:,.    7:77.:,        \n";
			std::cout << "7,7 ,::.    7::.7:7 ,?~77~.=.~.~777:??  7..7+::7         \n";
			std::cout << " +:,.,.= 7   7::~7:=.+..,77~~:.77.~..?:::77::.7          \n";
			std::cout << "   ::~=7       7~===:.I++~:.~~:~+?.?,~...::I             \n";
			std::cout << "   .777===77  I=~:~::=.~~.:~:~=.,~~.~~:+~~7              \n";
			std::cout << "   777=,..77  .:.==+:..~~+.,:=++~:~==~:::.==7            \n";
			std::cout << "   7.=..7..7....:7I===..+7I.===..7:~~====: :.7           \n";
			std::cout << "     ~I,.... :.7   7.....:....?+.7:.. 7  ..:7.. 7~       \n";
			std::cout << "        7 ...,7     .  ?............I     77:.7.:77      \n";
			std::cout << "              7  77 ..:,::7   7777.:7     7..I.=:  I7    \n";
			std::cout << "             7.:,.:...,.7 7 7 =~77 7:~7     777   77.7   \n";
			std::cout << "              .:7  77 7.............~?.:7   777 ==..=,   \n";
			std::cout << "               .7  7,:=   777   7777:  ~7      .77...    \n";
			std::cout << "             .    :.7777  ::: ....~.   :7      777.~.7   \n";
			std::cout << "             .:~,:.,...:,7::7 =.,~...7 7.        7.=~7   \n";
			std::cout << "                7   7777 7::77 777 ,:             .77    \n";
			std::cout << "                     7+,.7::=7..:  ::7            7      \n";
			std::cout << "                      7 .7...  7    +::.7 .7             \n";
			std::cout << "            777I...: . 7.   7.7, 7   ,:::,7              \n";
			std::cout << "             7.77 ?.   77,:.  .  7=77                    \n";
			std::cout << "          ? 77   . 7    :..7 ?  =7.:77 777 7 77 777      \n";
			std::cout << "    +77    ,   77    .7777.7  .    ,    7   7 7= 77.  	  \n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "\nThe moment you step through the door, you feel something squish\n";
			std::cout << "beneath your feet then slither away. You force your eyes upward and\n";
			std::cout << "see it. Its face is a gaping maw of blackened flesh and shattered \n";
			std::cout << "teeth. On its sides are massive tentacles with bone-like spines\n";
			std::cout << "jutting from the ends. It towers over you, its breath heavy with\n";
			std::cout << "decay. Its body looked like a mass of sliding, thrashing intestines\n"; 
			std::cout << "shifting across the floor. One of the tentacles shoots at you, \n"; 
			std::cout << "smashing your body against the wall. You feel your ribs crack under\n";
			std::cout << "the weight for a moment. After a quick scan of the room, you spot\na ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "pillar"; 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " to either ";
			std::cout << "side of you. No matter the creature's size,\nyour best course of action ";
			std::cout << "is the same, you'll have to hide, or ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "...\n";
			std::getline(std::cin, pos.command);
			if (pos.command == "pillar")
			{
				//audio.FModLoadSound("assets/finalboss.wav", false);
				//audio.FModPlaySound();
				std::cout << "\nYou duck behind the pillar but it doesn't last long. A tentacle \n"; 
				std::cout << "slashes through the pillar, sending rubble flying at you. You see another\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "pillar";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " to your left. You could hide behind that one or you could try to\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " it.\n";
				std::getline(std::cin, pos.command);
				if (pos.command == "pillar")
				{
					//audio.FModLoadSound("assets/finalboss.wav", false);
					//audio.FModPlaySound();
					std::cout << "\nThe creature seems even more agitated. Two tentacles penetrate the\n";
					std::cout << "pillar, shattering it in two. This time the tentacle scraps past your\n";
					std::cout << "forehead, causing blood to flow past your eyes. You could hide behind\n";
					std::cout << "another ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "pillar";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " you see on the other side of the room. Or you could\n";
					std::cout << "still try to ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " it.\n";
					std::getline(std::cin, pos.command);
					if (pos.command == "pillar")
					{ 
						//audio.FModLoadSound("assets/finalboss.wav", false);
						//audio.FModPlaySound();
						std::cout << "\nYou stumble forward, just avoiding the tentacles slipping towards\n";
						std::cout << "your ankles. This time three tentacles rip through the pillar,";
						std::cout << "snapping your ankle. You could force yourself to limp towards the \n";
						std::cout << "last ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "pillar";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " or you could ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " it.\n";
						std::getline(std::cin, pos.command);
						if (pos.command == "pillar")
						{
							//audio.FModLoadSound("assets/finalboss.wav", false);
							//audio.FModPlaySound();
							std::cout << "\nYou hobble towards the last pillar, holding onto it for balance. You\n";
							std::cout << "realize that this is probably the end. The pillar shatters, but you\n"; 
							std::cout << "are not dead yet, you hear a rumbling. The ceiling is collapsing. You\n";
							std::cout << "twist forward, getting through the door just as the ceiling collapses,\n";
							std::cout << "burying the creature underneath the limestone. You made it.\n";
							std::cout << "You survived.\n";
							pos.coordinates[pos.x][pos.y].inEvent = false;
							gamestate = WINNINGSTATE;
							return gamestate;
						}
						else if (pos.command == "shoot" && inInventory.bullets > 0)
						{
							//audio.FModLoadSound("assets/gun.wav", false);
							//audio.FModPlaySound();
							std::cout << "\nYou pull out Gyre, firing one shot into the creature. It keeps twisting\n";
							std::cout << "forward, undaunted. Maybe this wasn’t a good idea.\n";
							std::cout << "You need to ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again.\n";
							std::getline(std::cin, pos.command);
							if (pos.command == "shoot" && inInventory.bullets > 0)
							{
								std::cout << "\nIt stops for a moment, blood bursting from its moist skin, but it\n";
								std::cout << "doesn’t stop. It’s still coming. You HAVE to ";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again!\n";
								std::getline(std::cin, pos.command);
								if (pos.command == "shoot" && inInventory.bullets > 0)
								{
									std::cout << "You shoot towards its maw, the bullet snapping off some of its teeth.\n";
									std::cout << "Its thrashing for a moment but it keeps moving. Faster now.\n";
									std::cout << "PLEASE ";
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again!!\n";
									std::getline(std::cin, pos.command);
									if (pos.command == "shoot" && inInventory.bullets > 0)
									{
										std::cout << "\nYou shoot one of the tentacles trying to crush you, blasting it from\n";
										std::cout << "the creature’s body. It seems like it’s actually feeling it.\n";
										std::cout << "Just ";
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again!!!\n";
										std::getline(std::cin, pos.command);
										if (pos.command == "shoot" && inInventory.bullets > 0)
										{
											std::cout << "\nThis shot goes right through its body, its tar-like blood bubbling\n";
											std::cout << "out from the wound slowly. You might be close.\n";
											std::cout << "COME ON, ";
											SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
											SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again!!!!\n";
											std::getline(std::cin, pos.command);
											if (pos.command == "shoot" && inInventory.bullets > 0)
											{
												std::cout << "It’s right there, its remaining tentacles slithering around your feet\n";
												std::cout << "like the snakes they are. For the love of whatever god\n";
												std::cout << "you worship, ";
												SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
												SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "!!!!!!!!1111!!!!!11111!!1!!!!!11!!!\n";
												std::getline(std::cin, pos.command);
												if (pos.command == "shoot" && inInventory.bullets > 0)
												{
													std::cout << "You put Gyre straight into its mouth then fire, blasting its brains\n";
													std::cout << "out across the floor. The tentacles crunch then shrivel together\n";
													std::cout << "before finally dying in a pool of its own blood. You walk out of\n";
													std::cout << "the temple. You survived...";
													pos.coordinates[pos.x][pos.y].inEvent = false;
													gamestate = WINNINGSTATE;
													return gamestate;
												}
												else
												{
													//audio.FModLoadSound("assets/click.wav", false);
													//audio.FModPlaySound();
													std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
													std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
													std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
													std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
													std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
													std::cout << "shoot through your body. You are conscious just long enough to feel\n";
													std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
													std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
													std::cout << "so bad being a failure.";
													gamestate = GAMEOVER;
													return gamestate;
												}
											}
											else
											{
												//audio.FModLoadSound("assets/click.wav", false);
												//audio.FModPlaySound();
												std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
												std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
												std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
												std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
												std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
												std::cout << "shoot through your body. You are conscious just long enough to feel\n";
												std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
												std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
												std::cout << "so bad being a failure.";
												gamestate = GAMEOVER;
												return gamestate;
											}
										}
										else
										{
											//audio.FModLoadSound("assets/click.wav", false);
											//audio.FModPlaySound();
											std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
											std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
											std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
											std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
											std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
											std::cout << "shoot through your body. You are conscious just long enough to feel\n";
											std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
											std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
											std::cout << "so bad being a failure.";
											gamestate = GAMEOVER;
											return gamestate;
										}
									}
									else
									{
										//audio.FModLoadSound("assets/click.wav", false);
										//audio.FModPlaySound();
										std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
										std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
										std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
										std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
										std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
										std::cout << "shoot through your body. You are conscious just long enough to feel\n";
										std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
										std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
										std::cout << "so bad being a failure.";
										gamestate = GAMEOVER;
										return gamestate;
									}
								}
								else
								{
									//audio.FModLoadSound("assets/click.wav", false);
									//audio.FModPlaySound();
									std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
									std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
									std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
									std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
									std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
									std::cout << "shoot through your body. You are conscious just long enough to feel\n";
									std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
									std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
									std::cout << "so bad being a failure.";
									gamestate = GAMEOVER;
									return gamestate;
								}
							}
							else
							{
								//audio.FModLoadSound("assets/click.wav", false);
								//audio.FModPlaySound();
								std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
								std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
								std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
								std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
								std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
								std::cout << "shoot through your body. You are conscious just long enough to feel\n";
								std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
								std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
								std::cout << "so bad being a failure.";
								gamestate = GAMEOVER;
								return gamestate;
							}
						}
						else
						{
							std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
							std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
							std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
							std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
							std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
							std::cout << "shoot through your body. You are conscious just long enough to feel\n";
							std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
							std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
							std::cout << "so bad being a failure.";
							gamestate = GAMEOVER;
						}
					}
					else if (pos.command == "shoot" && inInventory.bullets > 0)
					{
						//audio.FModLoadSound("assets/gun.wav", false);
						//audio.FModPlaySound();
						std::cout << "\nYou pull out Gyre, firing one shot into the creature. It keeps twisting\n";
						std::cout << "forward, undaunted. Maybe this wasn’t a good idea.\n";
						std::cout << "You need to ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again.\n";
						std::getline(std::cin, pos.command);
						if (pos.command == "shoot" && inInventory.bullets > 0)
						{
							std::cout << "\nIt stops for a moment, blood bursting from its moist skin, but it\n";
							std::cout << "doesn’t stop. It’s still coming. You HAVE to ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again!\n";
							std::getline(std::cin, pos.command);
							if (pos.command == "shoot" && inInventory.bullets > 0)
							{
								std::cout << "You shoot towards its maw, the bullet snapping off some of its teeth.\n";
								std::cout << "Its thrashing for a moment but it keeps moving. Faster now.\n";
								std::cout << "PLEASE ";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again!!\n";
								std::getline(std::cin, pos.command);
								if (pos.command == "shoot" && inInventory.bullets > 0)
								{
									std::cout << "\nYou shoot one of the tentacles trying to crush you, blasting it from\n";
									std::cout << "the creature’s body. It seems like it’s actually feeling it.\n";
									std::cout << "Just ";
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again!!!\n";
									std::getline(std::cin, pos.command);
									if (pos.command == "shoot" && inInventory.bullets > 0)
									{
										std::cout << "\nThis shot goes right through its body, its tar-like blood bubbling\n";
										std::cout << "out from the wound slowly. You might be close.\n";
										std::cout << "COME ON, ";
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again!!!!\n";
										std::getline(std::cin, pos.command);
										if (pos.command == "shoot" && inInventory.bullets > 0)
										{
											std::cout << "It’s right there, its remaining tentacles slithering around your feet\n";
											std::cout << "like the snakes they are. For the love of whatever god\n";
											std::cout << "you worship, ";
											SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
											SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "!!!!!!!!1111!!!!!11111!!1!!!!!11!!!\n";
											std::getline(std::cin, pos.command);
											if (pos.command == "shoot" && inInventory.bullets > 0)
											{
												std::cout << "You put Gyre straight into its mouth then fire, blasting its brains\n";
												std::cout << "out across the floor. The tentacles crunch then shrivel together\n";
												std::cout << "before finally dying in a pool of its own blood. You walk out of\n";
												std::cout << "the temple. You survived...";
												pos.coordinates[pos.x][pos.y].inEvent = false;
												gamestate = WINNINGSTATE;
												return gamestate;
											}
											else
											{
												//audio.FModLoadSound("assets/click.wav", false);
												//audio.FModPlaySound();
												std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
												std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
												std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
												std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
												std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
												std::cout << "shoot through your body. You are conscious just long enough to feel\n";
												std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
												std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
												std::cout << "so bad being a failure.";
												gamestate = GAMEOVER;
												return gamestate;
											}
										}
										else
										{
											//audio.FModLoadSound("assets/click.wav", false);
											//audio.FModPlaySound();
											std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
											std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
											std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
											std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
											std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
											std::cout << "shoot through your body. You are conscious just long enough to feel\n";
											std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
											std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
											std::cout << "so bad being a failure.";
											gamestate = GAMEOVER;
											return gamestate;
										}
									}
									else
									{
										//audio.FModLoadSound("assets/click.wav", false);
										//audio.FModPlaySound();
										std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
										std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
										std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
										std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
										std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
										std::cout << "shoot through your body. You are conscious just long enough to feel\n";
										std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
										std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
										std::cout << "so bad being a failure.";
										gamestate = GAMEOVER;
										return gamestate;
									}
								}
								else
								{
									//audio.FModLoadSound("assets/click.wav", false);
									//audio.FModPlaySound();
									std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
									std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
									std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
									std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
									std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
									std::cout << "shoot through your body. You are conscious just long enough to feel\n";
									std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
									std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
									std::cout << "so bad being a failure.";
									gamestate = GAMEOVER;
									return gamestate;
								}
							}
							else
							{
								//audio.FModLoadSound("assets/click.wav", false);
								//audio.FModPlaySound();
								std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
								std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
								std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
								std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
								std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
								std::cout << "shoot through your body. You are conscious just long enough to feel\n";
								std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
								std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
								std::cout << "so bad being a failure.";
								gamestate = GAMEOVER;
								return gamestate;
							}
						}
						else
						{
							//audio.FModLoadSound("assets/click.wav", false);
							//audio.FModPlaySound();
							std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
							std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
							std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
							std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
							std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
							std::cout << "shoot through your body. You are conscious just long enough to feel\n";
							std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
							std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
							std::cout << "so bad being a failure.";
							gamestate = GAMEOVER;
							return gamestate;
						}
					}
					else
					{
						std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
						std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
						std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
						std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
						std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
						std::cout << "shoot through your body. You are conscious just long enough to feel\n";
						std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
						std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
						std::cout << "so bad being a failure.";
						gamestate = GAMEOVER;
					}
				}
				else if (pos.command == "shoot" && inInventory.bullets > 0)
				{
					//audio.FModLoadSound("assets/gun.wav", false);
					//audio.FModPlaySound();
					std::cout << "\nYou pull out Gyre, firing one shot into the creature. It keeps twisting\n";
					std::cout << "forward, undaunted. Maybe this wasn’t a good idea.\n";
					std::cout << "You need to ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again.\n";
					std::getline(std::cin, pos.command);
					if (pos.command == "shoot" && inInventory.bullets > 0)
					{
						std::cout << "\nIt stops for a moment, blood bursting from its moist skin, but it\n";
						std::cout << "doesn’t stop. It’s still coming. You HAVE to ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again!\n";
						std::getline(std::cin, pos.command);
						if (pos.command == "shoot" && inInventory.bullets > 0)
						{
							std::cout << "You shoot towards its maw, the bullet snapping off some of its teeth.\n";
							std::cout << "Its thrashing for a moment but it keeps moving. Faster now.\n";
							std::cout << "PLEASE ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again!!\n";
							std::getline(std::cin, pos.command);
							if (pos.command == "shoot" && inInventory.bullets > 0)
							{
								std::cout << "\nYou shoot one of the tentacles trying to crush you, blasting it from\n";
								std::cout << "the creature’s body. It seems like it’s actually feeling it.\n";
								std::cout << "Just ";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again!!!\n";
								std::getline(std::cin, pos.command);
								if (pos.command == "shoot" && inInventory.bullets > 0)
								{
									std::cout << "\nThis shot goes right through its body, its tar-like blood bubbling\n";
									std::cout << "out from the wound slowly. You might be close.\n";
									std::cout << "COME ON, ";
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again!!!!\n";
									std::getline(std::cin, pos.command);
									if (pos.command == "shoot" && inInventory.bullets > 0)
									{
										std::cout << "It’s right there, its remaining tentacles slithering around your feet\n";
										std::cout << "like the snakes they are. For the love of whatever god\n";
										std::cout << "you worship, ";
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "!!!!!!!!1111!!!!!11111!!1!!!!!11!!!\n";
										std::getline(std::cin, pos.command);
										if (pos.command == "shoot" && inInventory.bullets > 0)
										{
											std::cout << "You put Gyre straight into its mouth then fire, blasting its brains\n";
											std::cout << "out across the floor. The tentacles crunch then shrivel together\n";
											std::cout << "before finally dying in a pool of its own blood. You walk out of\n";
											std::cout << "the temple. You survived...";
											pos.coordinates[pos.x][pos.y].inEvent = false;
											gamestate = WINNINGSTATE;
											return gamestate;
										}
										else
										{
											//audio.FModLoadSound("assets/click.wav", false);
											//audio.FModPlaySound();
											std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
											std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
											std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
											std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
											std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
											std::cout << "shoot through your body. You are conscious just long enough to feel\n";
											std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
											std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
											std::cout << "so bad being a failure.";
											gamestate = GAMEOVER;
											return gamestate;
										}
									}
									else
									{
										//audio.FModLoadSound("assets/click.wav", false);
										//audio.FModPlaySound();
										std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
										std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
										std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
										std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
										std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
										std::cout << "shoot through your body. You are conscious just long enough to feel\n";
										std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
										std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
										std::cout << "so bad being a failure.";
										gamestate = GAMEOVER;
										return gamestate;
									}
								}
								else
								{
									//audio.FModLoadSound("assets/click.wav", false);
									//audio.FModPlaySound();
									std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
									std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
									std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
									std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
									std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
									std::cout << "shoot through your body. You are conscious just long enough to feel\n";
									std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
									std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
									std::cout << "so bad being a failure.";
									gamestate = GAMEOVER;
									return gamestate;
								}
							}
							else
							{
								//audio.FModLoadSound("assets/click.wav", false);
								//audio.FModPlaySound();
								std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
								std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
								std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
								std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
								std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
								std::cout << "shoot through your body. You are conscious just long enough to feel\n";
								std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
								std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
								std::cout << "so bad being a failure.";
								gamestate = GAMEOVER;
								return gamestate;
							}
						}
						else
						{
							//audio.FModLoadSound("assets/click.wav", false);
							//audio.FModPlaySound();
							std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
							std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
							std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
							std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
							std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
							std::cout << "shoot through your body. You are conscious just long enough to feel\n";
							std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
							std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
							std::cout << "so bad being a failure.";
							gamestate = GAMEOVER;
							return gamestate;
						}
					}
					else
					{
						//audio.FModLoadSound("assets/click.wav", false);
						//audio.FModPlaySound();
						std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
						std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
						std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
						std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
						std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
						std::cout << "shoot through your body. You are conscious just long enough to feel\n";
						std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
						std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
						std::cout << "so bad being a failure.";
						gamestate = GAMEOVER;
						return gamestate;
					}
				}
				else
				{
					std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
					std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
					std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
					std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
					std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
					std::cout << "shoot through your body. You are conscious just long enough to feel\n";
					std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
					std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
					std::cout << "so bad being a failure.";
					gamestate = GAMEOVER;
				}
			}
			else if (pos.command == "shoot" && inInventory.bullets > 0)
			{
				//audio.FModLoadSound("assets/gun.wav", false);
				//audio.FModPlaySound();
				std::cout << "\nYou pull out Gyre, firing one shot into the creature. It keeps twisting\n";
				std::cout << "forward, undaunted. Maybe this wasn’t a good idea.\n";
				std::cout << "You need to ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again.\n";
				std::getline(std::cin, pos.command);
				if (pos.command == "shoot" && inInventory.bullets > 0)
				{
					std::cout << "\nIt stops for a moment, blood bursting from its moist skin, but it\n";
					std::cout << "doesn’t stop. It’s still coming. You HAVE to ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again!\n";
					std::getline(std::cin, pos.command);
					if (pos.command == "shoot" && inInventory.bullets > 0)
					{
						std::cout << "You shoot towards its maw, the bullet snapping off some of its teeth.\n";
						std::cout << "Its thrashing for a moment but it keeps moving. Faster now.\n";
						std::cout << "PLEASE ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again!!\n";
						std::getline(std::cin, pos.command);
						if (pos.command == "shoot" && inInventory.bullets > 0)
						{
							std::cout << "\nYou shoot one of the tentacles trying to crush you, blasting it from\n";
							std::cout << "the creature’s body. It seems like it’s actually feeling it.\n";
							std::cout << "Just ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again!!!\n";
							std::getline(std::cin, pos.command);
							if (pos.command == "shoot" && inInventory.bullets > 0)
							{
								std::cout << "\nThis shot goes right through its body, its tar-like blood bubbling\n";
								std::cout << "out from the wound slowly. You might be close.\n";
								std::cout << "COME ON, ";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " again!!!!\n";
								std::getline(std::cin, pos.command);
								if (pos.command == "shoot" && inInventory.bullets > 0)
								{
									std::cout << "It’s right there, its remaining tentacles slithering around your feet\n";
									std::cout << "like the snakes they are. For the love of whatever god\n";
									std::cout << "you worship, ";
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "!!!!!!!!1111!!!!!11111!!1!!!!!11!!!\n";
									std::getline(std::cin, pos.command);
									if (pos.command == "shoot" && inInventory.bullets > 0)
									{
										std::cout << "You put Gyre straight into its mouth then fire, blasting its brains\n";
										std::cout << "out across the floor. The tentacles crunch then shrivel together\n";
										std::cout << "before finally dying in a pool of its own blood. You walk out of\n";
										std::cout << "the temple. You survived...";
										pos.coordinates[pos.x][pos.y].inEvent = false;
										gamestate = WINNINGSTATE;
										return gamestate;
									}
									else
									{
										//audio.FModLoadSound("assets/click.wav", false);
										//audio.FModPlaySound();
										std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
										std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
										std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
										std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
										std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
										std::cout << "shoot through your body. You are conscious just long enough to feel\n";
										std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
										std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
										std::cout << "so bad being a failure.";
										gamestate = GAMEOVER;
										return gamestate;
									}
								}
								else
								{
									//audio.FModLoadSound("assets/click.wav", false);
									//audio.FModPlaySound();
									std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
									std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
									std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
									std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
									std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
									std::cout << "shoot through your body. You are conscious just long enough to feel\n";
									std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
									std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
									std::cout << "so bad being a failure.";
									gamestate = GAMEOVER;
									return gamestate;
								}
							}
							else
							{
								//audio.FModLoadSound("assets/click.wav", false);
								//audio.FModPlaySound();
								std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
								std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
								std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
								std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
								std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
								std::cout << "shoot through your body. You are conscious just long enough to feel\n";
								std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
								std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
								std::cout << "so bad being a failure.";
								gamestate = GAMEOVER;
								return gamestate;
							}
						}
						else
						{
							//audio.FModLoadSound("assets/click.wav", false);
							//audio.FModPlaySound();
							std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
							std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
							std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
							std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
							std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
							std::cout << "shoot through your body. You are conscious just long enough to feel\n";
							std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
							std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
							std::cout << "so bad being a failure.";
							gamestate = GAMEOVER;
							return gamestate;
						}
					}
					else
					{
						//audio.FModLoadSound("assets/click.wav", false);
						//audio.FModPlaySound();
						std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
						std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
						std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
						std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
						std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
						std::cout << "shoot through your body. You are conscious just long enough to feel\n";
						std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
						std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
						std::cout << "so bad being a failure.";
						gamestate = GAMEOVER;
						return gamestate;
					}
				}
				else
				{
					//audio.FModLoadSound("assets/click.wav", false);
					//audio.FModPlaySound();
					std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
					std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
					std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
					std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
					std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
					std::cout << "shoot through your body. You are conscious just long enough to feel\n";
					std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
					std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
					std::cout << "so bad being a failure.";
					gamestate = GAMEOVER;
					return gamestate;
				}
			}
			else
			{
				std::cout << "\nOh no… You stumble. A tentacle shoots through your stomach, sending\n";
				std::cout << "guts splattering across the wall like some sick piece of modern art.\n";
				std::cout << "tentacle rips off your right arm before you can even reach Gyre. Your\n";
				std::cout << "left arm moves to try to struggle. Do something.Then it’s torn off\n";
				std::cout << "too. Your legs are snapped off like a wishbone. Three more tentacles\n";
				std::cout << "shoot through your body. You are conscious just long enough to feel\n";
				std::cout << "your body torn apart from the inside, your blood giving the room a new\n";
				std::cout << "paint job. You failed right before the finish line. I guess it’s not\n";
				std::cout << "so bad being a failure.";
				gamestate = GAMEOVER;
				return gamestate;
			}
		}
		}
	}

//Function that handles two dimensional movement
GameState theMoves()
{
	GameState gamestate;
	//Room One
	pos.coordinates[0][0].description = "\n@gYou are in the treasure room, there seems to be a small passage\nto the @rsouth@g.\n";
	pos.coordinates[0][0].northDoor = false;
	pos.coordinates[0][0].southDoor = true;
	pos.coordinates[0][0].eastDoor = false;
	pos.coordinates[0][0].westDoor = false;
	//pos.coordinates[0][0].inEvent = true;
	pos.coordinates[0][0].location = 0;

	//Room Two
	pos.coordinates[0][1].description = "\n@gYou are in the hallway, the small passage is to the @rnorth @gand\nthere is a door to the @rsouth@g.\n";
	pos.coordinates[0][1].northDoor = true;
	pos.coordinates[0][1].southDoor = true;
	pos.coordinates[0][1].eastDoor = false;
	pos.coordinates[0][1].westDoor = false;
	//pos.coordinates[0][1].inEvent = true;
	pos.coordinates[0][1].location = 1;

	//Room Three
	pos.coordinates[0][2].description = "\n@gYou are in another room. There's a door to the @rnorth@g and @reast@g.\n";
	pos.coordinates[0][2].northDoor = true;
	pos.coordinates[0][2].southDoor = false;
	pos.coordinates[0][2].eastDoor = true;
	pos.coordinates[0][2].westDoor = false;
	//pos.coordinates[0][2].inEvent = true;
	pos.coordinates[0][2].location = 2;

	//Room Four
	pos.coordinates[1][2].description = "\n@gYou enter a room covered in a blanket of dust, there are doors to\nthe @reast@g and the @rwest@g.\n";
	pos.coordinates[1][2].northDoor = false;
	pos.coordinates[1][2].southDoor = false;
	pos.coordinates[1][2].eastDoor = true;
	pos.coordinates[1][2].westDoor = true;
	pos.coordinates[1][2].inEvent = false;
	pos.coordinates[1][2].location = 3;

	//Room Five (The Intersection) <== Things get confusing after this point...
	pos.coordinates[2][2].description = "\n@d~~~~~~~~~~~,,~,,,.~~~~~~~~~~~~~~~~~~~~~=,,,,,,=~~~~~~~~~~~~~\n~~~~~~~~~~~,,,,,,.~~~~~~~~~~~~~~~~~~~~~=,,,,,,.~~~~~~~~~~~~~\n~~~~~~~~~~~,,,:,,.~~~~~~~~~~~~~~~~~~~~~,,,,,,,.~~~~~~~~~~~~~\n~~~~~~~~~~~~,,,,,=~~~~~~~~~~~~~~~~~~~~~.,,:,,,.~~~~~~~~~~~~~\n~~~~~~~~~~~:,,:,,:~~~~~~~~~~~~~~~~~~~~~.,,,,,,.~~~~~~~~~~~~~\n~~~~~~~~~~~.,,,,,,~~~~~~~~~~~~~~~~~~~~~.,,,,,,:~~~~~~~~~~~~~\n~~~~~~~~~~~.,~,,,,~~~~~~~~~~~~~~~~~~~~~.,,,,,,=~~~~~~~~~~~~~\n~~~~~~~~~~~.,:~,,,~~~~~~~~~~~~~~~~~~~~~.,,,,,,~~~~~~~~~~~~~~\n~~~~~~~~~~~=,~,,,,~~~~~~~~~~~~~~~~~~~~~.,:,,,,~~~~~~~~~~~~~~\n~~~~~~~~~~~~,,,,,,~~~~~~~~~~~~~~~~~~~~~:,,:,,,~~~~~~~~~~~~~~\n~~~~~~~~~~~~,,,:,,=~~~~~~~~.....~~~~~~~=,,,,,,~~~~~~~~~~~~~~\n~~~~~~~~~~~~,,,:,,~~~~~~~~~.~:.~~~~~~~~~,,,,,=~~~~~~~~~~~~~~\n~~~~~~~~~~~~,,,,,,.~~~~~~~~.,..~~~~~~~~,,,::,.~~~~~~~~~~~~~~\n~~~~~~~~~~~~~,:,,,.~~~~~~:77  77.~~~~~~,,,:,,.~~~~~~~~~~~~~~\n~~~~~~~+~~~~:,,,,,.~~~~~7        .~~~~~,,,,,,.~~~~~~~~~~~~~~\n~~~~~~77~~~~.,,:,,.~~~~7         7~~~~~,,,,,,.~~~..~~~~~~~~~\n~~~=    ~~~~.,,:,,.~~~~7          ~~~~~,,:,,,,~~~.  7.=~~~~~\n~~7     =~~~.,,:,,=~~~~          7~~~~~,,::,,+~~~.      I:~~\n:       .~~~~,:,,,~~~~~7         7~~~~~,,::,,~~~~.        77\n        .~~~~,:,,,,~~~~7          ~~~~~,,::,,~~~~.          \n        7~~~~,,,,,=,,::::~~:,..........,,:,,,~~~~+          \n         ~~~~,=.............................+~~~~7          \n         =~~:..............~.~................~~~           \n      77 .......................................=  7 7      \n     ...:.....................~.......................77 777\n.......:...........................................:........\n..~........................,.:.......................:......\n.......................................................:....\n............................................................\n............................................................\n@gYou walk into an echoing chamber with four doors; one to the @rnorth@g,\nthe @reast@g, the @rsouth@g, and the @rwest@g.\n";
	pos.coordinates[2][2].northDoor = true;
	pos.coordinates[2][2].southDoor = true;
	pos.coordinates[2][2].eastDoor = true;
	pos.coordinates[2][2].westDoor = true;
	pos.coordinates[2][2].inEvent = false;
	pos.coordinates[2][2].location = 4;

	//Room Six (North Fork)----------------------------------------------------------------------------
	pos.coordinates[2][1].description = "\n@gYou walk into a room wrapped in thick vines twisting along the\nfloor. There is a door to the @rnorth@g and the @rsouth@g.\n";
	pos.coordinates[2][1].northDoor = true;
	pos.coordinates[2][1].southDoor = true;
	pos.coordinates[2][1].eastDoor = false;
	pos.coordinates[2][1].westDoor = false;
	pos.coordinates[2][1].inEvent = false;
	pos.coordinates[2][1].location = 5;

	//Room Seven (North Fork)
	pos.coordinates[2][0].description = "\n@d.+++++.+,:.IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n.+++++..:.IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n.==..::.IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n........7IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n.==..~.....IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n..=...=...:IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n........:::.IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n::.,:::,::.7IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n::::.:..:.7IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n::::::.,IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n===.====.IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n===.====.IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n===:====.IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n::::::::::IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n:,::::::::III=:IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n.:::::.:::III::IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n:,.,:::.::II+::IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n:::::.:.::II::::IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n::,.:::.::II:::::IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n:::::::.::II:::::IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n          7777  777777777777777777777777.7777777777777777777\n                                                            \n                                       77 7                 \n     ................................................       \n .......................................................77  \n 7    :.....................................................\n 7  77+.................................................    \n7.....................................................      \n@gYou walk into a room with an ebony pool. There are doors to the\n@reast@g and the @rsouth@g.\n";
	pos.coordinates[2][0].northDoor = false;
	pos.coordinates[2][0].southDoor = true;
	pos.coordinates[2][0].eastDoor = true;
	pos.coordinates[2][0].westDoor = false;
	//pos.coordinates[2][0].inEvent = true;
	pos.coordinates[2][0].location = 6;

	//Room Eight (North Fork KEY ROOM)
	pos.coordinates[3][0].description = "\n@gThe room in which you found the gilded key. The only door is to\nthe @rwest@g.\n";
	pos.coordinates[3][0].northDoor = false;
	pos.coordinates[3][0].southDoor = false;
	pos.coordinates[3][0].eastDoor = false;
	pos.coordinates[3][0].westDoor = true;
	//pos.coordinates[3][0].inEvent = true;
	pos.coordinates[3][0].location = 7;

	//Room Nine (Eastern Fork)-------------------------------------------------------------------------
	pos.coordinates[3][2].description = "\n@gThat overly complicated room. There's doors to the @reast@g and @rwest@g.\n";
	pos.coordinates[3][2].northDoor = false;
	pos.coordinates[3][2].southDoor = false;
	pos.coordinates[3][2].eastDoor = true;
	pos.coordinates[3][2].westDoor = true;
	//pos.coordinates[3][2].inEvent = true;
	pos.coordinates[3][2].location = 8;

	//Room Ten (PAN ROOM)
	pos.coordinates[4][2].description = "@d\n77:77                                                       \n ??==+=7                                                    \n  7I.=++==7                                                 \n     7+?++++77                                              \n       7??=+++=                                             \n         77+,==++I                                          \n             I+~+++=7                                       \n               7?,=~++7        77??7I+II?777                \n                  I+~~,~77?..................,:?77          \n                    I,:?.........................,::7       \n                    7.............................,.,:7     \n                  7+...........,:=+=++=~,.............,=    \n                  =.........::,,,:::::,,,,,,::=::,,....,=   \n                 7..........,,::::::::,::,.,.,,,:~,.....,?  \n                 7.........,,,,,,,::,:,,,,,,,,,,,,,,....,+  \n                 7+.....,,,,,,,,,:,,,,,,,,,,,,,,,,.,..,,.+  \n                  I?....,,,,,,,,::::,:,:::,,,,,,:,,,,,,,+I  \n                   I7..,,,,,,,::,:::::::::::,,,,::,:,,~?+   \n                    I=7::,,,,,,:,::::::::::,,,,::,,,+==+    \n                     7~~~7,,,,,,:::::::::::::::::,I=+=?     \n                      7?~~~~~+?=.::::::::::.77~~~~~=+7      \n                        7?~~~~~~~~~~~~~~~~~~~~~~~=?7        \n                           7?=:~~~~~~~~~~~~~:==+I           \n                             7  7II???????II77              \n\n@gWhat's this? There's a frying pan here...\nThis must be left over from an earlier build. The only door is to\nthe @rwest@g.\n";
	pos.coordinates[4][2].northDoor = false;
	pos.coordinates[4][2].southDoor = false;
	pos.coordinates[4][2].eastDoor = false;
	pos.coordinates[4][2].westDoor = true;
	pos.coordinates[4][2].inEvent = false;
	pos.coordinates[4][2].location = 9;

	//Room Eleven (Main Fork)--------------------------------------------------------------------------
	//pos.coordinates[2][3].description = "\nYou are in the stairwell, going up and to the south. At the top, \nthere is a sealed door. The only open door, is to the north.\n";
	pos.coordinates[2][3].northDoor = true;
	//pos.coordinates[2][3].southDoor = false;
	pos.coordinates[2][3].eastDoor = false;
	pos.coordinates[2][3].westDoor = false;
	//pos.coordinates[2][3].inEvent = true;
	pos.coordinates[2][3].location = 10;

	//Room Twelve
	pos.coordinates[2][4].description = "\n@gYou are in an inky black room. There is a door to the @rnorth@g and \n@rsouth@g.\n";
	pos.coordinates[2][4].northDoor = true;
	pos.coordinates[2][4].southDoor = true;
	pos.coordinates[2][4].eastDoor = false;
	pos.coordinates[2][4].westDoor = false;
	//pos.coordinates[2][4].inEvent = true;
	pos.coordinates[2][4].location = 11;

	//Room Thirteen
	pos.coordinates[2][5].description = "\n@gThere are four tall standing pillars wrapped in moss and vines in each\ncorner of the room. There is a door to the \n@rwest@g and @rnorth@g.\n";
	pos.coordinates[2][5].northDoor = true;
	pos.coordinates[2][5].southDoor = false;
	pos.coordinates[2][5].eastDoor = false;
	pos.coordinates[2][5].westDoor = true;
	pos.coordinates[2][5].inEvent = false;
	pos.coordinates[2][5].location = 12;

	//Room Fourteen
	pos.coordinates[1][5].description = "\n@gYou enter a hexagonal room, a strange breeze comes from the cracking\nwalls. There is a door to the @reast@g and @rsouth@g.\n";
	pos.coordinates[1][5].northDoor = false;
	pos.coordinates[1][5].southDoor = true;
	pos.coordinates[1][5].eastDoor = true;
	pos.coordinates[1][5].westDoor = false;
	pos.coordinates[1][5].inEvent = false;
	pos.coordinates[1][5].location = 13;

	//Room Fifteen
	pos.coordinates[1][6].description = "\n@gYou enter the room with holes on the ceiling. There are doors to the\n@rnorth@g and the @reast@g.\n";
	pos.coordinates[1][6].northDoor = true;
	pos.coordinates[1][6].southDoor = false;
	pos.coordinates[1][6].eastDoor = true;
	pos.coordinates[1][6].westDoor = false;
	//pos.coordinates[1][6].inEvent = true;
	pos.coordinates[1][6].location = 14;


	//Room Sixteen
	pos.coordinates[2][6].description = "\n@gYou notice more carvings and glyphs etched along the walls. There\nappear to be bones scattered along the walls of the room.\nThere are doors to the @reast@g and the @rwest@g.\n";
	pos.coordinates[2][6].northDoor = false;
	pos.coordinates[2][6].southDoor = false;
	pos.coordinates[2][6].eastDoor = true;
	pos.coordinates[2][6].westDoor = true;
	pos.coordinates[2][6].inEvent = false;
	pos.coordinates[2][6].location = 15;
	
	//Room Seventeen
	pos.coordinates[3][6].description = "\n@gYou walk into a chamber with a floor covered in holes. There is a door\nto the @rnorth@g, the @reast@g and the @rwest@g.\n";
	pos.coordinates[3][6].northDoor = true;
	pos.coordinates[3][6].southDoor = false;
	pos.coordinates[3][6].eastDoor = true;
	pos.coordinates[3][6].westDoor = true;
	//pos.coordinates[3][6].inEvent = true;
	pos.coordinates[3][6].location = 16;

	//Room Eighteen (Branches from Seventeen)
	pos.coordinates[3][5].description = "\n@gYou walk into a room with a sacrificial table and a cracked hole in\nthe floor. The only door is to the @rsouth@g.\n";
	pos.coordinates[3][5].northDoor = false;
	pos.coordinates[3][5].southDoor = true;
	pos.coordinates[3][5].eastDoor = false;
	pos.coordinates[3][5].westDoor = false;
	//pos.coordinates[3][5].inEvent = true;
	pos.coordinates[3][5].location = 17;

	//Room Nineteen
	pos.coordinates[4][6].description = "@d\n  .   7.   .7   .7  .7               7.  7, .I   7.   .   \n  .   7.   .7   .   .7               7.  7, .I   7.   .   \n  .   7.7  .7   .   .7               7.  7, .I   7.  7.   \n  .   7.7  .7   .7  .7    7.....7    7.  7, .I   7.  7.   \n  .   7.7  .7   .   .7   7.......    7.  7, .I   7.   .   \n  .   7.   .7   .7  .7    .......    7.  7, .I   7.   .   \n  .   7.   .7   .7  .7    .......    7.  7, .I   7.  7.   \n  .   7.   .7   .7  .7    .......    7.  7, .I   7.  7.   \n  .   7.   .7   .7  .7    .......    7.  7, .I   7.   .   \n  .   7.   .7   .   ++++++++++++++++++ + 7, .I   7.   .   \n  .   7.   .7   .7  ++++++++++++++++++ + 7, .I   7.  7.   \n  .   7.   .7   ++++++++++++++++++++++++++.I   7.   .   \n  .   7.7  .7   ++++++++++++++++++++++++++7.I   7.  7.   \n  .   7.7  .7   ++++++++++++++++++++++++++7.I   7.  7.   \n  .   7.7  ....................................7   7.  7.   \n  .   7.   ++++++++++++++++++++++++++++++++++++    7.   .   \n  .   7.   ++++++++++++++++++++++++++++++++++++    7.   .   \n  .   7.   ++++++++++++++++++++++++++++++++++++    7.  7.   \n  . + ............................................., .   \n  .    ++++++++++++++++++++++++++++++++++++++++++++ + .   \n  .    ++++++++++++++++++++++++++++++++++++++++++++ + .   \n  .    ++++++++++++++++++++++++++++++++++++++++++++ + .   \n  .......................................................   \n++++++++++++++++++++++++++++++++++++++++++++++++++++++ + \n++++++++++++++++++++++++++++++++++++++++++++++++++++++ + \n++++++++++++++++++++++++++++++++++++++++++++++++++++++ + \n++++++++++++++++++++++++++++++++++++++++++++++++++++++ + \n@gYou are in a dark stairwell. There are doors to the @reast@g and the @rwest@g.\n";
	pos.coordinates[4][6].northDoor = false;
	pos.coordinates[4][6].southDoor = false;
	pos.coordinates[4][6].eastDoor = true;
	pos.coordinates[4][6].westDoor = true;
	//pos.coordinates[4][6].inEvent = true;
	pos.coordinates[4][6].location = 18;

	//Room Twenty
	pos.coordinates[5][6].description = "\n@gYou enter the room and everything feels smaller. The walls are closer\nand the ceiling is lower. The light illuminates this room much\nbetter than the others. There are doors to the @rsouth@g and the @rwest@g.\n";
	pos.coordinates[5][6].northDoor = false;
	pos.coordinates[5][6].southDoor = true;
	pos.coordinates[5][6].eastDoor = false;
	pos.coordinates[5][6].westDoor = true;
	pos.coordinates[5][6].inEvent = false;
	pos.coordinates[5][6].location = 19;

	//Room Twenty-one
	pos.coordinates[5][7].description = "\n@gThe room is just as bright as before and you've become accustomed to\nthe size. The room seems almost welcoming, enticing you forwards.\nThere are doors to the @rnorth@g and the @rwest@g.\n";
	pos.coordinates[5][7].northDoor = true;
	pos.coordinates[5][7].southDoor = false;
	pos.coordinates[5][7].eastDoor = false;
	pos.coordinates[5][7].westDoor = true;
	pos.coordinates[5][7].inEvent = false;
	pos.coordinates[5][7].location = 20;

	//Room Twenty-two
	pos.coordinates[4][7].description = "\n@gYOU SHOULDN'T BE SEEING THIS.\n";
	pos.coordinates[4][7].northDoor = false;
	pos.coordinates[4][7].southDoor = false;
	pos.coordinates[4][7].eastDoor = true;
	pos.coordinates[4][7].westDoor = false;
	//pos.coordinates[4][7].inEvent = true;
	pos.coordinates[4][7].location = 21;
	
	//Movement
	while (!pos.coordinates[pos.x][pos.y].inEvent)
	{		
		//std::cout << pos.coordinates[pos.x][pos.y].description;
		printStringColoured(pos.coordinates[pos.x][pos.y].description);
		std::cout << "\nWhat direction will you go?\n";
		std::getline(std::cin, pos.command);

		if (pos.command == "north" && pos.coordinates[pos.x][pos.y].northDoor == true || pos.command == "n" && pos.coordinates[pos.x][pos.y].northDoor == true || pos.command == "up" && pos.coordinates[pos.x][pos.y].northDoor == true || pos.command == "u" && pos.coordinates[pos.x][pos.y].northDoor == true || pos.command == "go north" && pos.coordinates[pos.x][pos.y].northDoor == true)
		{
			pos.y = pos.y--;
		}
		else if (pos.command == "south" && pos.coordinates[pos.x][pos.y].southDoor == true || pos.command == "s" && pos.coordinates[pos.x][pos.y].southDoor == true || pos.command == "down" && pos.coordinates[pos.x][pos.y].southDoor == true || pos.command == "d" && pos.coordinates[pos.x][pos.y].southDoor == true || pos.command == "go south" && pos.coordinates[pos.x][pos.y].southDoor == true)
		{
			pos.y = pos.y++;
		}
		else if (pos.command == "east" && pos.coordinates[pos.x][pos.y].eastDoor == true || pos.command == "e" && pos.coordinates[pos.x][pos.y].eastDoor == true || pos.command == "right" && pos.coordinates[pos.x][pos.y].eastDoor == true || pos.command == "r" && pos.coordinates[pos.x][pos.y].eastDoor == true || pos.command == "go east" && pos.coordinates[pos.x][pos.y].eastDoor == true)
		{
			pos.x = pos.x++;
		}
		else if (pos.command == "west" && pos.coordinates[pos.x][pos.y].westDoor == true || pos.command == "w" && pos.coordinates[pos.x][pos.y].westDoor == true || pos.command == "left" && pos.coordinates[pos.x][pos.y].westDoor == true || pos.command == "l" && pos.coordinates[pos.x][pos.y].westDoor == true || pos.command == "go west" && pos.coordinates[pos.x][pos.y].westDoor == true)
		{
			pos.x =pos. x--;
		}
		else if (pos.command == "north" && pos.coordinates[pos.x][pos.y].northDoor == false || pos.command == "n" && pos.coordinates[pos.x][pos.y].northDoor == false || pos.command == "up" && pos.coordinates[pos.x][pos.y].northDoor == false || pos.command == "u" && pos.coordinates[pos.x][pos.y].northDoor == false || pos.command == "go north" && pos.coordinates[pos.x][pos.y].northDoor == false)
		{
			std::cout << "\nYou stumble backwards, you've walked straight into a wall.\nTry again.\n";
		}
		else if (pos.command == "south" && pos.coordinates[pos.x][pos.y].southDoor == false || pos.command == "s" && pos.coordinates[pos.x][pos.y].southDoor == false || pos.command == "down" && pos.coordinates[pos.x][pos.y].southDoor == false || pos.command == "d" && pos.coordinates[pos.x][pos.y].southDoor == false || pos.command == "go south" && pos.coordinates[pos.x][pos.y].southDoor == false)
		{
			std::cout << "\nYou stumble backwards, you've walked straight into a wall.\nTry again.\n";
		}
		else if (pos.command == "east" && pos.coordinates[pos.x][pos.y].eastDoor == false || pos.command == "e" && pos.coordinates[pos.x][pos.y].eastDoor == false || pos.command == "right" && pos.coordinates[pos.x][pos.y].eastDoor == false || pos.command == "r" && pos.coordinates[pos.x][pos.y].eastDoor == false || pos.command == "go east" && pos.coordinates[pos.x][pos.y].eastDoor == false)
		{
			std::cout << "\nYou stumble backwards, you've walked straight into a wall.\nTry again.\n";
		}
		else if (pos.command == "west" && pos.coordinates[pos.x][pos.y].westDoor == false || pos.command == "w" && pos.coordinates[pos.x][pos.y].westDoor == false || pos.command == "left" && pos.coordinates[pos.x][pos.y].westDoor == false || pos.command == "l" && pos.coordinates[pos.x][pos.y].westDoor == false || pos.command == "go west" && pos.coordinates[pos.x][pos.y].westDoor == false)
		{
			std::cout << "\nYou stumble backwards, you've walked straight into a wall.\nTry again.\n";
		}
		//Inventory Easter Egg Begins...
		else if (pos.command == "inventory" && inInventory.numberOfInventories == 0|| pos.command == "open inventory" && inInventory.numberOfInventories == 0)
		{
			std::cout << "\nNever do that again. Ever.\n";
			inInventory.numberOfInventories++;
		}
		else if (pos.command == "inventory" && inInventory.numberOfInventories == 1 || pos.command == "open inventory" && inInventory.numberOfInventories == 1)
		{
			std::cout << "\nPls.\n";
			inInventory.numberOfInventories++;
		}
		else if (pos.command == "inventory" && inInventory.numberOfInventories == 2 || pos.command == "open inventory" && inInventory.numberOfInventories == 2)
		{
			std::cout << "\nSTAHP!\n";
			inInventory.numberOfInventories++;
		}
		else if (pos.command == "inventory" && inInventory.numberOfInventories == 3 || pos.command == "open inventory" && inInventory.numberOfInventories == 3)
		{
			std::cout << "\nNOW YOU'VE DONE IT!\n";
			gamestate = GAMEOVER;
			return gamestate;
		}//...Inventory Easter Egg ends.
		else if (pos.command == "instructions" || pos.command == "i" || pos.command == "instruction" || pos.command == "help" || pos.command == "h")
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DarkGrey); std::cout << "\nWhile attempting to avoid an untimely death, and ultimately escape\n";
			std::cout << "the treacherous temple, you would be wise to follow these helpful\ntips:\n";
			std::cout << "\n1. Look out for the key words, highlighted in ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "red";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DarkGrey); std::cout << ", for hints as to \n";
			std::cout << "what pos.command you should use in each scenario.\n";
			std::cout << "\n2. When on the move, the direction you should type is stated in\n";
			std::cout << "cardinal, but you can type a plethra of different things. For\nexample,";
			std::cout << " typing 'up', 'u', or 'n', is the same as typing 'north'!\n";
			std::cout << "\n3. NEVER type 'inventory'... Ever...\n";
			std::cout << "\n4. When prompted to ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "shoot";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << ", make sure you spell it correctly!\n";
			std::cout << "Mispelling it will spell your doom. Keep in mind you only have six\n";
			std::cout << "bullets, you can't just waltz on through shooting everything in \n";
			std::cout << "sight. Check how many bullets you have at any time you're out of \n";
			std::cout << "combat by typing ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "Gyre";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << ".\n";
			std::cout << "\n5. You can see these tips by calling for ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "help";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << " as long as you're\nnot in combat!\n";
			std::cout << "\nNow, go fourth, ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "continue";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DarkGrey); std::cout << " your adventure!\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey);
			std::getline(std::cin, pos.command);
			if (pos.command == "continue" || pos.command == "c")
			{}
		}
		else if ((pos.command == "Gyre" && inInventory.bullets == 6) || (pos.command == "gyre" && inInventory.bullets == 6))
		{
			std::cout << "\nYou draw Gyre, upon opening the chamber you count the shots.\nAll "<< inInventory.bullets <<" are accounted for.\n";
		}
		else if ((pos.command == "Gyre" && inInventory.bullets < 6 && inInventory.bullets > 1) || (pos.command == "gyre" && inInventory.bullets < 6 && inInventory.bullets > 1))
		{
			std::cout << "\nYou draw Gyre, upon opening the chamber you count the shots.\nOnly " << inInventory.bullets << " bullets remain.\n";
		}
		else if ((pos.command == "Gyre" && inInventory.bullets == 1) || (pos.command == "gyre" && inInventory.bullets == 1))
		{
			std::cout << "\nYou draw Gyre, upon opening the chamber you count the shots.\nYou only have " << inInventory.bullets << " bullet left.\n";
		}
		else if ((pos.command == "Gyre" && inInventory.bullets == 0) || (pos.command == "gyre" && inInventory.bullets == 0))
		{
			std::cout << "\nYou draw Gyre, and dread opening the chamber...\nYou have no bullets left.\n";
		}
		else if (pos.command == "weast" || pos.command == "go weast")//Spongebob Easter Egg
		{
			std::cout << "\nThat's not a real direction, Patrick.\n";
		}
		else if (pos.command == "")
		{
			std::cout << "\nTry typing something, and then hit enter.\n";
		}
		else 
		{ 
			std::cout << "\nNot sure what that means... Try again.\n"; 
		}
	}
	if (pos.coordinates[pos.x][pos.y].inEvent == true)
	{
		gamestate = EVENTSTATE;
		return gamestate;
	}
}

//Function that re-initializes variables upon restarting the game
void restart()
{
		inInventory.bullets = 6;
		inInventory.hasKnife = false;
		inInventory.hasKey = false;
		inInventory.numberOfInventories = 0;
		pos.x = 0;
		pos.y = 0;
		pos.coordinates[0][0].inEvent = true;
		pos.coordinates[0][1].inEvent = true;
		pos.coordinates[0][2].inEvent = true;
		pos.coordinates[2][0].inEvent = true;
		pos.coordinates[3][0].inEvent = true;
		pos.coordinates[2][3].inEvent = true;
		pos.coordinates[2][4].inEvent = true;
		pos.coordinates[1][6].inEvent = true;
		pos.coordinates[3][6].inEvent = true;
		pos.coordinates[3][5].inEvent = true;
		pos.coordinates[4][6].inEvent = true;
		pos.coordinates[4][7].inEvent = true;
}

GameState gameOver()
{
	GameState gamestate;
	restart();
	std::cout << "\n¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "     [][    |][][][]][x][x][x][x]    [][       $$$      $$$   |[]]   \n";
	std::cout << "  [][][     |]][||]]    [[[]]]  |  [][][      $$-$$    $$-$$  |[[]]  \n";
	std::cout << " [][        ]]]         [[]]]   } [][        $$---$$  $$---$$ |[ ]]] \n";
	std::cout << "[][    ]]][ |][][][]]  []]]]   { [][    ]]][ $------$$------$ |[  ]]]\n";
	std::cout << " [][    [][ |]][||]]     [[][     [][    [][ $------$$------$ |[  ]]]\n";
	std::cout << "  [][][][]  ]]]         []] |      [][][][]  $$---$$  $$---$$ |[ ]]] \n";
	std::cout << "   [[][]]   |][][][]]  []]  |       [[][]]    $$-$$    $$-$$  |[[]]  \n";
	std::cout << "     []]    |]][||]]     []           []]      $$$      $$$   |[]]   \n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "?????????????????????????????????????????????????????????????????????\n";
	std::cout << "\nGAME OVER!\n";
	std::cout << "\nWould you like to ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "restart"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "? Or would you like to ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "quit"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "? \n";
	std::getline(std::cin, pos.command);
	if (pos.command == "restart")
	{
		gamestate = MENUSTATE;
		return gamestate;
	}
	else if (pos.command == "quit")
	{
		gamestate = ENDSTATE;
		return gamestate;
	}
}

GameState winning()
{
	GameState gamestate;
	std::cout << "You smell the fresh air flowing into your nostrils. You never thought\n";
	std::cout << "you'd be this happy to see daylight.Your eyes squint as you look up at\n";
	std::cout << "the sky for a moment. You move forwards, feeling the breeze moving\n";
	std::cout << "over your dirt-stained face. You move into your ship, the door sliding\n";
	std::cout << "shut behind. Your ship starts to blast off as you slide into the\n";
	std::cout << "pilot's seat. When you get back to Earth, you should charge them\n";
	std::cout << "double. All that's left for you now is the ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "credits";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << ".\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DarkGrey); std::cout << "                         7I7                                \n";
	std::cout << "                        :...77                              \n";
	std::cout << "                       +...~..                              \n";
	std::cout << "                      7.....7.:                             \n";
	std::cout << "                     ~.......7..                            \n";
	std::cout << "                     .........,.?                           \n";
	std::cout << "                    ..........7..                           \n";
	std::cout << "                   ...........=?.,7                         \n";
	std::cout << "                   ............7..7                         \n";
	std::cout << "                  =............ ...7                        \n";
	std::cout << "                  ,...........~7...7                        \n";
	std::cout << "                  ............: ...7                        \n";
	std::cout << "                  ............77...7                        \n";
	std::cout << "                 7:...........7....7                        \n";
	std::cout << "                 7:=.........7+...~=7                       \n";
	std::cout << "                7~~:.........7....::~7                      \n";
	std::cout << "                     .::.........7                          \n";
	std::cout << "                     .++.........7                          \n";
	std::cout << "                     .=+.......:.I      ...                 \n";
	std::cout << "       ,.:          ,.............7     ...=7               \n";
	std::cout << "     7:..:        7............,...,    ...77               \n";
	std::cout << "     77..:       7..~.:+,............:  ...                 \n";
	std::cout << "       ..:      ...  .:++........, ....:...                 \n";
	std::cout << "       ..:    7..,7  ..+.........:  7...,..7                \n";
	std::cout << "       ..:   7..I    ............,    77,..7                \n";
	std::cout << "       ..:  ,..      :............      :..7                \n";
	std::cout << "       ..:7..~       :............      ~..7                \n";
	std::cout << "       ,.:..         .............      =..7                \n";
	std::cout << "       :.:.7         .............7     +..                 \n";
	std::cout << "       :.:            ............7     I..                 \n";
	std::cout << "       :.:            ...........~      I..7                \n";
	std::cout << "    7.?:.: ..7     7 .~..........~7     I..777  7           \n";
	std::cout << "    .7.:,,,.7 ..7 7 77.~........,~.7   .,..77   ,I          \n";
	std::cout << " 7...7,,,,,,,,:.,,,.7  .........~~~7?7.7.,,~,:.   7         \n";
	std::cout << ".7  77:,,,,,,,,,,,,,.7  .......~~.77.~.,,,,~,,,.77?+..=7    \n";
	std::cout << "7  :.,,,,:,,,,,,,,,,,.   ~..:::~. .:,,,,,,,,,,,. 77    7.7  \n";
	std::cout << "  .,,,,,,,,,,,,,,,,:,.  +~~~~~~. 7,,,,,,,,,.,,,,,,,,~.7  7.7\n";
	std::cout << "  .,,,,,,:,,,,,,,,,:.7  .,,,..., 7.,=,,,,,,.,,,,,,,,,,.   7.\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey);
	std::getline(std::cin, pos.command);
	if (pos.command == "credits")
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "Project Manager\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "Darius Hackney\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "Programmers\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "Raymond Dee\n";
		std::cout << "Simon Pichl\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "Level Designers\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "Cameron van Velzen\n";
		std::cout << "Darius Hackney\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "Audio\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "Darius Hackney\n";
		std::cout << "Raymond Dee\n";
		std::cout << "Simon Pichl\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "Writers\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "Cameron van Velzen\n";
		std::cout << "Darius Hackney\n";
		std::cout << "Raymond Dee\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red); std::cout << "Artist\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Grey); std::cout << "Kenneth Ho\n\n";
		gamestate = ENDSTATE;
		return gamestate;
	}
}