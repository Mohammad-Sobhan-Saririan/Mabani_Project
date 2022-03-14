#include <iostream>
#include <math.h>
#include "SBDL.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "clui.h"

int** Page;
int** View;
int Mo_y, Mo_x, player_number = 0,ramz;
char* karbar_Name=new char[100];
using namespace std;

int length(char* str)
{
	int box = 0, i = 0;
	while (str[i++] != '\0')
	{
		box++;
	}
	return box;
}


struct save
{
	char paye[20][20];
	char safhe[20][20];
	int Toolsafhe ;
	int Time;
};


struct Player
{
	char* Name=new char[100];
	int score;

};

void swap(Player & s, Player& t)
{
	Player temp = s;
	s = t;
	t = temp;
}
void sort(Player Araye[])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9 - i; j++)
		{
			if (Araye[j + 1].score > Araye[j].score)
			{
				swap(Araye[j + 1], Araye[j]);
			}
		}
	}
}

void asl_Game(int Tool_Safhe, int Min_Number)
{
	Page = new int* [Tool_Safhe];
	View = new int* [Tool_Safhe];

	for (int j = 0; j < Tool_Safhe; j++)
	{
		Page[j] = new int[Tool_Safhe];
		View[j] = new int[Tool_Safhe];
	}
	int point = 0, i = 0, j = 0, k = 0;
	for (int a = 0; a < 200; a++)
	{
		point = 0;
		j = rand() % (Tool_Safhe);
		k = rand() % (Tool_Safhe);
		Page[j][k] = 'B';

		for (i = 0, j = 0; i < Tool_Safhe; i++)
		{
			for (j = 0; j < Tool_Safhe; j++)
			{
				View[i][j] = '\0';
				if (Page[i][j] == 'B') { point++; }
				else { Page[i][j] = '\0'; }
			}
		}
		if (Min_Number <= point) { break; }

	}
	for (i = 0, j = 0; i < Tool_Safhe; i++)
	{
		for (j = 0; j < Tool_Safhe; j++)
		{
			if (Page[i][j] == 'B') continue;
			if (i > 0) { if (Page[i - 1][j] == 'B') Page[i][j] += 1; }
			if ((i > 0) && (j > 0)) { if (Page[i - 1][j - 1] == 'B') Page[i][j] += 1; }
			if (j > 0) { if (Page[i][j - 1] == 'B') Page[i][j] += 1; }
			if ((i < Tool_Safhe - 1) && (j > 0)) { if (Page[i + 1][j - 1] == 'B') Page[i][j] += 1; }
			if (i < Tool_Safhe - 1) { if (Page[i + 1][j] == 'B') Page[i][j] += 1; }
			if ((i < Tool_Safhe - 1) && (j < Tool_Safhe - 1)) { if (Page[i + 1][j + 1] == 'B') Page[i][j] += 1; }
			if (j < Tool_Safhe - 1) { if (Page[i][j + 1] == 'B') Page[i][j] += 1; }
			if ((i > 0) && (j < Tool_Safhe - 1)) { if (Page[i - 1][j + 1] == 'B') Page[i][j] += 1; }
		}

	}
}

int main(int argc, char* argv[])
{
	
	const int window_width = 1000;
	const int window_height = 700;
	SBDL::InitEngine("MINE_SWEEPER", window_width, window_height);

	srand(time(NULL));

	Texture New_Game, Change_Name, Load_Game, Leaderboard, Quite,font_texture,Enter_Name, Enter_Name_go,finialscore,playnam,leaderplay,leaderscor;
	Texture Sath_Begi, Sath_inter, Sath_prof,Sath_Rand,scornum;
	int x = 20, y = 20,k,i=0,j=0,m=0,n=0,flagcont=0,wincont=0,emptycont=0,winlose=0,time_score=1,emtiaz=0,nomre=0,q=10,sabt=0;
	save* list=new save[4]; Player Araye[10];
	int Tool =10,Arz=7,count=0,Mouse_Butt=0,sakht_zamin=0,aasm=5;
	int result = 0, Esm =5,Sathicon=0,Tool_Safhe,point,Min_Number,karbar_score=0;
	char* ne = new char[1] ;
	ne[0] = '\0';

	for (int i = 0; i < 10; i++)
	{
		Araye[i].score = 0;
		int god = length(ne);
		for (int j = 0; j < 100; j++)
		{
			Araye[i].Name[j] = ne[0];
		}
	}

	Sound* sound1 = SBDL::loadSound("assets/win.wav");
	Sound* sound = SBDL::loadSound("assets/lose.wav");
	Music* music = SBDL::loadMusic("assets/morn.wav");
	Font* font = SBDL::loadFont("assets/times.ttf", 250);
	Font* font1 = SBDL::loadFont("assets/times.ttf", 30);



	SBDL::playMusic(music, -1);

	Texture Background5 = SBDL::loadTexture("assets/stone.jpg");
	Texture Background4 = SBDL::loadTexture("assets/wood.jpg");
	Texture Background3 = SBDL::loadTexture("assets/sky.jpg");
	Texture Background2 = SBDL::loadTexture("assets/divar.jpg");
	Texture Background1 = SBDL::loadTexture("assets/tabiat.jpg");
	Texture Background = SBDL::loadTexture("assets/backg.jpg");
	Texture blue = SBDL::loadTexture("assets/white.png");
	Texture leader = SBDL::loadTexture("assets/leaderbord.png");
	Texture play_button = SBDL::loadTexture("assets/Play.png");
	Texture Back_button = SBDL::loadTexture("assets/BACK1.png");
	Texture Menu_button = SBDL::loadTexture("assets/MENU1.png");
	Texture Menu_bar = SBDL::loadTexture("assets/MENU2.png");
	Texture Winpic = SBDL::loadTexture("assets/you win.jpg");
	Texture emgrey = SBDL::loadTexture("assets/new2.png");
	Texture losepic = SBDL::loadTexture("assets/game over.jpg");
	Texture spacgrey = SBDL::loadTexture("assets/spacgrey.png");
	Texture bomb = SBDL::loadTexture("assets/bombicon.png");
	Texture flag = SBDL::loadTexture("assets/flag.png");
	Texture Time = SBDL::loadTexture("assets/time.png");
	Texture scor = SBDL::loadTexture("assets/scorebord.png");
	Texture slot1 = SBDL::loadTexture("assets/saveslot1.png");
	Texture slot2 = SBDL::loadTexture("assets/saveslot2.png");
	Texture slot3 = SBDL::loadTexture("assets/saveslot3.png");
	Texture slot4 = SBDL::loadTexture("assets/saveslot4.png");
	Texture Save_bar = SBDL::loadTexture("assets/SAVE2.png");
	Texture Resume_bar = SBDL::loadTexture("assets/RESUME2.png");
	Texture playnamback = SBDL::loadTexture("assets/backname.png");

	

	SDL_Rect BackgR = { 0,0,1000,700 };
	SDL_Rect slot1R = { 350,210,300,70 };
	SDL_Rect slot2R = { 350,281,300,70 };
	SDL_Rect slot3R = { 350,352,300,70 };
	SDL_Rect slot4R = { 350,423,300,70 };
	SDL_Rect scornumR = { 140,65,35,30 };
	SDL_Rect scoreR = { 50,50,130,60 };
	SDL_Rect play_namR = { 820,50,130,60 };
	SDL_Rect play_nam_backR = { 810,40,150,80 };
	SDL_Rect leaderR = { 200,100,600,100 };
	SDL_Rect leaderscoreR = { 620,120,100,40 };
	SDL_Rect leadernameR = { 250,118,150,40 };
	SDL_Rect winpicR = { 250,200,500,300 };
	SDL_Rect scor_bordR = { 350,558,300,100 };
	SDL_Rect finalscorR = { 550,588,60,35 };
	SDL_Rect menbariconR = { 350,200,300,100 };
	SDL_Rect SaveiconR = { 350,304,300,100 };
	SDL_Rect ResumeiconR = { 350,404,300,100 };
	SDL_Rect MenuiconR = { 870,620,100,50 };
	SDL_Rect BackiconR = { 30,620,100,50 };
	SDL_Rect sathBegiR = { 200,210,600,70 };
	SDL_Rect sathinterR = { 200,280,600,70 };
	SDL_Rect sathprofR = { 200,350,600,70 };
	SDL_Rect sathRandR = { 200,420,300,70 };
	SDL_Rect EnterNamegoR = { 250,200,500,100 };
	SDL_Rect Start_icon = { 450,400,100,100 };
	SDL_Rect EnterNameR = { 250,200,500,100 };
	SDL_Rect NewGameR = { 375,150,250,80 };
	SDL_Rect ChangeNameR = { 375,231,250,80 };
	SDL_Rect LoadGameR = { 375,312,250,80 };
	SDL_Rect LeaderboardR = { 375,393,250,80 };
	SDL_Rect QuiteR = { 375,474,180,80 };
	SDL_Rect rect={x,y,30,30}, rext={ x,y,20,20 };

	Sath_Rand = SBDL::createFontTexture(font,"  Random           ", 95, 9, 181);
	Sath_Begi = SBDL::createFontTexture(font, "  Beginner      Land 5 by 5  &  4 Min           ", 181, 9, 167);
	Sath_inter = SBDL::createFontTexture(font, "  intermediate      Land 12 by 12  &  28 Min    ", 38, 9, 181);
	Sath_prof = SBDL::createFontTexture(font, "  professional      Land 20 by 20  &  96 Min    ", 14, 117, 36);
	Enter_Name_go = SBDL::createFontTexture(font, "  Clicked On Start To Enter the Game :  ", 19, 168, 162);
	Enter_Name = SBDL::createFontTexture(font, " Clicked Here to Enter Your Name :  ", 19, 126, 168);
	New_Game = SBDL::createFontTexture(font, " New Game ", 95, 9, 181);
	Change_Name = SBDL::createFontTexture(font, " Change Name ", 181, 9, 167);
	Load_Game = SBDL::createFontTexture(font, " Load Game ", 38, 9, 181);
	Leaderboard = SBDL::createFontTexture(font, " Leaderboard ", 14, 117, 36);
	Quite = SBDL::createFontTexture(font, " Quite ", 117, 16, 14);

		clear_screen();
	while (SBDL::isRunning()) {
		int startTime = SBDL::getTime();

		SBDL::updateEvents();
		SBDL::clearRenderScreen();

		if (Esm>0)
		{
			SBDL::showTexture(Background, BackgR);
			if (Esm == 5) { SBDL::showTexture(Enter_Name, EnterNameR); }
			if (Esm == 4) 
				{
					SBDL::showTexture(play_button, Start_icon);
					SBDL::showTexture(Enter_Name_go, EnterNamegoR);
				}
			if (SBDL::mouseInRect(EnterNameR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_PRESSED))
				{
					Esm = 4; cin.getline(karbar_Name, 100); 
				}

			if (SBDL::mouseInRect(Start_icon) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT,1, SDL_PRESSED)) 
				{ 
					Esm = 0; 
					int god = length(karbar_Name);
					for (int j = 0; j < god; j++)
					{
						Araye[0].Name[j] = karbar_Name[j];
					}
				}
		}

		else 
		{

			if (result == 0)
			{
				SBDL::showTexture(Background1, BackgR);
				SBDL::showTexture(New_Game, NewGameR);
				SBDL::showTexture(Change_Name, ChangeNameR);
				SBDL::showTexture(Load_Game, LoadGameR);
				SBDL::showTexture(Leaderboard, LeaderboardR);
				SBDL::showTexture(Quite, QuiteR);
				
				if (SBDL::mouseInRect(NewGameR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_PRESSED)) { result = 1; }
				if (SBDL::mouseInRect(ChangeNameR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_PRESSED)) { aasm = 5; result = 2; Esm = 0; nomre = 0; }
				if (SBDL::mouseInRect(LoadGameR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_PRESSED)) { result = 3; }
				if (SBDL::mouseInRect(LeaderboardR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_PRESSED)) { result = 4; }
				if (SBDL::mouseInRect(QuiteR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_PRESSED)) { result = 5; }

			}

			if (result == 1)
			{
				if (Sathicon == 0)
				{
					SBDL::showTexture(Background1, BackgR);
					SBDL::showTexture(Back_button, BackiconR);
					if (SBDL::mouseInRect(BackiconR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_PRESSED))
					{
						sakht_zamin = 0;
						Sathicon = 0;
						result = 0;
					}
					SBDL::showTexture(Sath_Begi, sathBegiR);
					SBDL::showTexture(Sath_inter, sathinterR);
					SBDL::showTexture(Sath_prof, sathprofR);
					SBDL::showTexture(Sath_Rand, sathRandR);
					if (SBDL::mouseInRect(sathBegiR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_PRESSED)) { Sathicon = 1; Tool_Safhe = 5, Min_Number = 4; }
					if (SBDL::mouseInRect(sathinterR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_PRESSED)) { Sathicon = 1; Tool_Safhe = 12, Min_Number = 28; }
					if (SBDL::mouseInRect(sathprofR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_PRESSED)) { Sathicon = 1; Tool_Safhe = 20, Min_Number = 96; }
					if (SBDL::mouseInRect(sathRandR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_PRESSED)) { Sathicon = 1; cin >> Tool_Safhe >> Min_Number; }
				}
				else if(Sathicon == 1)
				{

					if (sakht_zamin==0)
						{
							emptycont = 0, winlose = 0, flagcont = 0, emtiaz = 0, time_score = 1,sabt=0;
							sakht_zamin = 1;
							asl_Game(Tool_Safhe, Min_Number);
						}

					else if (sakht_zamin == 1)
						{
						SBDL::showTexture(Background2, BackgR);
							for (j = 0; j < 10; j++)
							{
								if (length(Araye[j].Name) != 0) { if (strcmp(karbar_Name, Araye[j].Name) == 0) { player_number = j; } }
							}

							playnam = SBDL::createFontTexture(font, karbar_Name, 16, 50, 92);
							SBDL::showTexture(playnamback, play_nam_backR);
							SBDL::showTexture(playnam, play_namR);
							SBDL::freeTexture(playnam);

							if (time_score >= 0)
							{ 
								time_score++;
								if (time_score == 20) { emtiaz++; time_score = 0; }
								SBDL::showTexture(Time, scoreR);
								scornum = SBDL::createFontTexture(font, to_string(emtiaz), 255, 192, 0);
								SBDL::showTexture(scornum, scornumR);
								SBDL::freeTexture(scornum);
							}



							Mo_x = Mo_y = 0;
							count++;
							if (sabt == 0)
							{
								if ((SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_PRESSED)) && (count >= 5) && (Mo_x = SBDL::Mouse.x) && (Mo_y = SBDL::Mouse.y))
								{
									count = 0;
								}
								if ((SBDL::Mouse.clicked(SDL_BUTTON_RIGHT, 1, SDL_PRESSED)) && (count >= 5) && (Mo_x = SBDL::Mouse.x) && (Mo_y = SBDL::Mouse.y))
								{
									count = 0;
									Mouse_Butt = 1;
								}
							}

							y = 350-(Tool_Safhe/2)*30;
							for (int i = 0; i < Tool_Safhe; i++)
							{
								rect.y = y;
								rext.y = y + 5;
								x = 500 - (Tool_Safhe / 2) * 30;
								for (int j = 0; j < Tool_Safhe; j++)
								{
									if (((Mo_y <= y + 30) && (y <= Mo_y)) && ((Mo_x <= x + 30) && (x <= Mo_x)))
									{
										if (View[i][j] == '\0')
										{
											if (Mouse_Butt == 0)
											{
												if (Page[i][j] == 'B')
												{
													for (n = 0, m = 0; n < Tool_Safhe; n++)
													{
														for (m = 0; m < Tool_Safhe; m++)
														{
															if ((Page[n][m] == 'B')&&(View[n][m] != 'F')) { View[n][m] = Page[n][m]; }
															winlose = 1;
														}
													}
												}
												else if (Page[i][j] != '\0') { View[i][j] = Page[i][j]; }
												else { View[i][j] = ' '; } 
											}
											else if (Mouse_Butt == 1) 
											{
													flagcont = 0;
													for (n = 0, m = 0; n < Tool_Safhe; n++)
													{
														for (m = 0; m < Tool_Safhe; m++)
														{
															if (View[n][m] == 'F') { flagcont++; }
														}
													}
													if (flagcont < Min_Number) { View[i][j] = 'F'; Mouse_Butt = 0; }
											}
										}
										else if ((View[i][j] == 'F') && (Mouse_Butt == 1)) { View[i][j] = '\0'; Mouse_Butt = 0;}
									}

									rect.x = x;
									rext.x = x + 5;
									SBDL::showTexture(blue, rect);
									if (View[i][j] == 'B')
									{ 
										SBDL::showTexture(bomb, rect);
									}
									else if (View[i][j] == 'F')
									{
										SBDL::showTexture(flag, rect);
									}
									else if ((View[i][j] != '\0' )&& (View[i][j] != ' '))
									{
										if (View[i][j] == 1) { font_texture = SBDL::createFontTexture(font1, to_string(View[i][j]), 255, 0, 0); }
										else if (View[i][j] == 2) { font_texture = SBDL::createFontTexture(font1, to_string(View[i][j]), 34, 91, 181); }
										else if (View[i][j] == 3) { font_texture = SBDL::createFontTexture(font1, to_string(View[i][j]), 50, 105, 41); }
										else if (View[i][j] == 4) { font_texture = SBDL::createFontTexture(font1, to_string(View[i][j]), 71, 255, 224); }
										else if (View[i][j] == 5) { font_texture = SBDL::createFontTexture(font1, to_string(View[i][j]), 71, 200, 255); }
										else if (View[i][j] == 6) { font_texture = SBDL::createFontTexture(font1, to_string(View[i][j]), 174, 92, 250); }
										else if (View[i][j] == 7) { font_texture = SBDL::createFontTexture(font1, to_string(View[i][j]), 209, 104, 232); }
										else if (View[i][j] == 8) { font_texture = SBDL::createFontTexture(font1, to_string(View[i][j]), 247, 96, 174); }

										SBDL::showTexture(font_texture, rext);
										SBDL::freeTexture(font_texture);
									}
									else if (View[i][j] == '\0') 
									{
										SBDL::showTexture(emgrey, rect); 
									}
									else if  (View[i][j] == ' ')
									{
										SBDL::showTexture(spacgrey, rect);
									}

									x += 30;
								}
								y += 30;

							}
							wincont = 0; flagcont = 0;
							for (n = 0, m = 0; n < Tool_Safhe; n++)
							{
								for (m = 0; m < Tool_Safhe; m++)
								{
									if (View[n][m] == 'F') { flagcont++; wincont++; }
									else if (View[n][m] != '\0') { wincont++; }
								}
							}
							if (wincont == Tool_Safhe * Tool_Safhe)
							{
								if (sabt == 0) { karbar_score = flagcont * ((Min_Number * 30) - emtiaz) + 100; }
								if (Tool_Safhe < 16) { winpicR.y = 50, winpicR.h = 200;}

								else { winpicR.y = 200, winpicR.h = 300;}

								finialscore = SBDL::createFontTexture(font, to_string(karbar_score), 10, 144, 13);
								SBDL::showTexture(Winpic, winpicR);
								SBDL::showTexture(scor, scor_bordR);
								SBDL::showTexture(finialscore , finalscorR);
								SBDL::freeTexture(finialscore);

								time_score = -3;
								if (sabt == 0) { Araye[player_number].score += karbar_score; sabt = 1; 
								SBDL::playSound(sound1, 1);}
							}
							if (winlose == 1)
							{
								karbar_score = (flagcont+1) * ((Min_Number * 30) - emtiaz) -200 ;
								if (Tool_Safhe < 16) { winpicR.y = 50, winpicR.h = 200; }
								else { winpicR.y = 200, winpicR.h = 300; }
								finialscore = SBDL::createFontTexture(font, to_string(karbar_score), 10, 144, 13);
								SBDL::showTexture(losepic, winpicR);
								SBDL::showTexture(scor, scor_bordR);
								SBDL::showTexture(finialscore, finalscorR);
								SBDL::freeTexture(finialscore);

								time_score = -3;
							
								if (sabt == 0) { Araye[player_number].score += karbar_score; sabt = 1; 
								SBDL::playSound(sound, 1);}
							}

							SBDL::showTexture(Menu_button, MenuiconR);
							SBDL::showTexture(Back_button, BackiconR);


							if (SBDL::mouseInRect(MenuiconR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_PRESSED))
							{
								Sathicon = 2;
							}
							if (SBDL::mouseInRect(BackiconR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_PRESSED))
							{
								sakht_zamin = 0;
								Sathicon = 0;

								for (int d = 0; d < Tool_Safhe; d++)
								{
									delete[] View[d];
									delete[] Page[d];
								}
								delete[] View;
								delete[] Page;
							}


						}
				}
				if (Sathicon == 2)
				{
					SBDL::showTexture(Background3, BackgR);

					SBDL::showTexture(Menu_bar, menbariconR);
					SBDL::showTexture(Save_bar, SaveiconR);
					SBDL::showTexture(Resume_bar, ResumeiconR);

					if (SBDL::mouseInRect(menbariconR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_PRESSED))
					{
						sakht_zamin = 0;
						Sathicon = 0;
						result = 0;
						for (int d = 0; d < Tool_Safhe; d++)
						{
							delete[] View[d];
							delete[] Page[d];
						}
						delete[] View;
						delete[] Page;
					}
					if (SBDL::mouseInRect(ResumeiconR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_PRESSED))
					{
						sakht_zamin = 1;
						Sathicon = 1;
						result = 1;
					}
					if (SBDL::mouseInRect(SaveiconR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_PRESSED))
					{
						Sathicon = 3;
						count = 0;
					}
				}

				if (Sathicon == 3)
				{
					count++;
					SBDL::showTexture(Background4, BackgR);					
					SBDL::showTexture(slot1, slot1R);
					SBDL::showTexture(slot2, slot2R);
					SBDL::showTexture(slot3, slot3R);
					SBDL::showTexture(slot4, slot4R);

					if(count>10)
					{ 
						q = 10;

						if (SBDL::mouseInRect(slot1R) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_RELEASED)) { q = 0; }
							if (SBDL::mouseInRect(slot2R) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_RELEASED)) { q = 1; }
								if (SBDL::mouseInRect(slot3R) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_RELEASED)) { q = 2; }
									if (SBDL::mouseInRect(slot4R) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_RELEASED)) { q = 3; }
						if(q<4)
						{ 
							list[q].Toolsafhe = Tool_Safhe;
							list[q].Time = emtiaz;

							for (n = 0, m = 0; n < Tool_Safhe; n++)
								{
									for (m = 0; m < Tool_Safhe; m++)
											{
													list[q].paye[n][m] = Page[n][m];
													list[q].safhe[n][m] = View[n][m];
											}
								}

							sakht_zamin = 1;
							Sathicon = 1;
							result = 1;
						}
					}
				}


			}

			if (result == 3)
			{
				SBDL::showTexture(Background4, BackgR);
				SBDL::showTexture(Back_button, BackiconR);
				if (SBDL::mouseInRect(BackiconR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_PRESSED))
				{
					sakht_zamin = 0;
					Sathicon = 0;
					result = 0;
				}
				q = 10;
				SBDL::showTexture(slot1, slot1R);
				SBDL::showTexture(slot2, slot2R);
				SBDL::showTexture(slot3, slot3R);
				SBDL::showTexture(slot4, slot4R);

				if (SBDL::mouseInRect(slot1R) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_RELEASED)) { q = 0; }
				if (SBDL::mouseInRect(slot2R) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_RELEASED)) { q = 1; }
				if (SBDL::mouseInRect(slot3R) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_RELEASED)) { q = 2; }
				if (SBDL::mouseInRect(slot4R) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_RELEASED)) { q = 3; }
				if (q < 4)
				{
					if ((list[q].Toolsafhe > 0) && (list[q].Toolsafhe < 21))
					{
						Tool_Safhe = list[q].Toolsafhe;
						emtiaz = list[q].Time;

						Page = new int* [Tool_Safhe];
						View = new int* [Tool_Safhe];

						for (int j = 0; j < Tool_Safhe; j++)
						{
							Page[j] = new int[Tool_Safhe];
							View[j] = new int[Tool_Safhe];
						}



						for (n = 0, m = 0; n < Tool_Safhe; n++)
						{
							for (m = 0; m < Tool_Safhe; m++)
							{
								Page[n][m] = list[q].paye[n][m];
								View[n][m] = list[q].safhe[n][m];
							}
						}


						sakht_zamin = 1;
						Sathicon = 1;
						result = 1;
					}
				}
			}

			if (result == 2)
			{
				SBDL::showTexture(Background, BackgR);
				if (aasm > 0)
				{

					if (aasm == 5) { SBDL::showTexture(Enter_Name, EnterNameR); }
					if (aasm == 4)
							{
								SBDL::showTexture(play_button, Start_icon);
								SBDL::showTexture(Enter_Name_go, EnterNamegoR);
							}
					if (SBDL::mouseInRect(EnterNameR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED))
							{
								aasm = 4; cin.getline(karbar_Name, 100); 
							}
					if (SBDL::mouseInRect(Start_icon) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_PRESSED)) { aasm = 0; }
				}

				else
				{
					if (nomre == 0)
					{
						for (j = 0; j < 10; j++)
						{
							if (length(Araye[j].Name) != 0) 
							{ 
								if (strcmp(karbar_Name, Araye[j].Name) == 0) 
								{ 
									player_number = j; 
									result = 0;
									karbar_score = Araye[j].score;
									nomre = 0;
									break;
								} 
								else { nomre = 2; }
							}
						}
					}
					if (nomre == 2)
					{ 
						for (i = 0; i < 10; i++)
							{
								if (length(Araye[i].Name) == 0)
								{
									for (int j = 0; j < length(karbar_Name); j++)
									{
										Araye[i].Name[j] = karbar_Name[j];
									}
									nomre = 10;
									result = 0;
									player_number = i;
									break;
								}
								else { nomre = 1; }
							}
					}
					if (nomre == 1) {result = 2;}
				}
			}
			if (result == 4)
			{
				SBDL::showTexture(Background5, BackgR);

				sort(Araye);

				SBDL::showTexture(Back_button, BackiconR);
				if (SBDL::mouseInRect(BackiconR) && SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 2, SDL_PRESSED))
				{
					sakht_zamin = 0;
					Sathicon = 0;
					result = 0;
				}
				
				leaderR.y = 100; leadernameR.y = 125; leaderscoreR.y = 130;
				for (int i = 0; i < 5; i++)
				{	
					int num = Araye[i].score;
					SBDL::showTexture(leader, leaderR);

					if (length(Araye[i].Name) != 0)
					{
						
						leaderplay = SBDL::createFontTexture(font, Araye[i].Name, 0, 255, 55);
						leaderscor = SBDL::createFontTexture(font, to_string(num), 15, 23, 255);
						SBDL::showTexture(leaderplay, leadernameR);
						SBDL::showTexture(leaderscor, leaderscoreR);
						SBDL::freeTexture(leaderplay);
						SBDL::freeTexture(leaderscor);

					}
					leaderR.y += 102;
					leaderscoreR.y += 102;
					leadernameR.y += 102;
				}

			}
			if (result == 5)
			{
				break;
                delete karbar_Name ;
			}
			
		}
		SBDL::updateRenderScreen();

			SBDL::delay(50);

	}
}