#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <cwchar>


// https://cplusplus.com/forum/windows/204878/

typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT  FontFamily;
    UINT  FontWeight;
    WCHAR FaceName[LF_FACESIZE];
}CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;
//the function declaration begins
#ifdef __cplusplus
extern "C" {
#endif
BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX
lpConsoleCurrentFontEx);
#ifdef __cplusplus
}
#endif

void SetFontSize(int type){
	if(type==1){
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 2;                   // Width of each character in the font
		cfi.dwFontSize.Y = 5;                  // Height
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	}else if(type==0){
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 8;                   // Width of each character in the font
		cfi.dwFontSize.Y = 18;                  // Height
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	}
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void gotoxy (int given_x, int given_y){
    COORD c;
    c.X = given_x;
    c.Y = given_y;
    SetConsoleCursorPosition (
        GetStdHandle ( STD_OUTPUT_HANDLE ), c);
}

void set_gameBoundaries(){
	int i=3;

	for(i;i<=106;i++){
		gotoxy(i,0);
		printf("%c",219);
	}

	i=3;

	for(i;i<=106;i++){
		gotoxy(i,26);
		printf("%c",219);
	}


	i=0;
	for(i;i<=26;i++){
		gotoxy(3,i);
		printf("%c",219);	
	}
	
	i=0;
	for(i;i<=26;i++){
		gotoxy(106,i);
		printf("%c",219);	
	}

}



class Player
{
	

    private:
        int actual_x=0;
        int actual_y=0;
		int speed=1;

    public:

	//Starts the spawnpoint of the player
	Player(int x_Spawnpoint, int y_Spawnpoint){
		actual_x = x_Spawnpoint;
		actual_y = y_Spawnpoint;

		UnDraw();
		gotoxy(actual_x,actual_y);
		Draw();
	}

	void Draw(){
		gotoxy(actual_x,actual_y);
		printf("%c",79);
		gotoxy(actual_x,actual_y-1);
		printf("%c",179);
	}

	void UnDraw(){
		gotoxy(actual_x,actual_y);
		printf(" ");
		gotoxy(actual_x,actual_y-1);
		printf(" ");
	}

	void Move(){
		gotoxy(actual_x,actual_y);
	}







    // setters
	void plus_X(int x){
		actual_x = actual_x+x;
	}
	void plus_Y(int y){
		actual_y = actual_y+y;
	}

	void minus_X(int x){
		actual_x = actual_x-x;
	}
	void minus_Y(int y){
		actual_y = actual_y-y;
	}


	// getters
	int retrieveActual_X(){
		return this->actual_x;
	}

	int retrieveActual_Y(){
		return this->actual_y;
	}

	int retrieveSpeed(){
		return this->speed;
	}

	int retrieveCharacter(){
		return 159;
	}
};







int main(){
	bool active=true;
	// SetFontSize(1);
	system("mode 110,27"); //sets cmd size to 100 columns and 25 rows
	
	system("cls");
	ShowConsoleCursor(false);
   	set_gameBoundaries();


	Player player(40,10); //spawn point


	//Main thread? Here user controls the player
	while(active){

		//Player1 movement
		if(kbhit()){
			switch(getch()){
				//To make the movement, we first erase the actual piece from where we are, and then make another one on the direction we get
				case 119: //w
					if( player.retrieveActual_Y() - player.retrieveSpeed() >0){

						player.UnDraw();
						player.minus_Y( player.retrieveSpeed() );
						player.Move();
						player.Draw();
						
						
					}
					break;

				case 97: //a
					if(player.retrieveActual_X() - player.retrieveSpeed() >4){
						
						player.UnDraw();
						player.minus_X( player.retrieveSpeed() );
						player.Move();
						player.Draw();
						
						
					}
					break;

				case 115: //s
					if(player.retrieveActual_Y() + player.retrieveSpeed() <26){

						player.UnDraw();
						player.plus_Y( player.retrieveSpeed() );
						player.Move();
						player.Draw();
						
						
					}
					break;

				case 100: //d
					if(player.retrieveActual_X() + player.retrieveSpeed() <106){
						
						player.UnDraw();
						player.plus_X( player.retrieveSpeed() );
						player.Move();
						player.Draw();
						
												
					}
					
					break;



				case 27:
					active=false;
					
					break;
				default:
					break;
			}
		}


	};









	// SetFontSize(0);

	printf("Fin");
    return 0;
}