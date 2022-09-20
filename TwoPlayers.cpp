#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <cwchar>
#include <thread>
#include <mutex>


std::mutex Mutex; //gets rid of the threads using printf when they should not

// https://cplusplus.com/forum/windows/204878/

/*Using mingw is neccessary to redefine, using mingw w64 is not*/
// typedef struct _CONSOLE_FONT_INFOEX
// {
//     ULONG cbSize;
//     DWORD nFont;
//     COORD dwFontSize;
//     UINT  FontFamily;
//     UINT  FontWeight;
//     WCHAR FaceName[LF_FACESIZE];
// }CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;
// //the function declaration begins
// #ifdef __cplusplus
// extern "C" {
// #endif
// BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX
// lpConsoleCurrentFontEx);
// #ifdef __cplusplus
// }
// #endif

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
		int speed=2;

		bool movingUp=false;
		bool movingDown=false;
		bool movingLeft=false;
		bool movingRight=false;

    public:

	//Starts the spawnpoint of the player
	Player(int x_Spawnpoint, int y_Spawnpoint){
		actual_x = x_Spawnpoint;
		actual_y = y_Spawnpoint;

		UnDraw();

		Draw();
	}

	void Draw(){
		Mutex.lock();
		gotoxy(actual_x,actual_y);
		printf("%c",79);
		gotoxy(actual_x,actual_y-1);
		printf("%c",179);
		Mutex.unlock();
	}

	void UnDraw(){
		Mutex.lock();
		gotoxy(actual_x,actual_y);
		printf(" ");
		gotoxy(actual_x,actual_y-1);
		printf(" ");
		Mutex.unlock();
	}


	/**
	 * Functions undraws and draws on the new location, taking care of the game borders
	 * 
	 * Not necessary the use of gotocy, draw and undraw already took care of it
	*/
	void Move(){
		if(movingLeft){
			if(actual_x+speed<106){
				UnDraw();
				actual_x=actual_x+speed;
				Draw();
			}


			
		}else if(movingRight){
			if(actual_x-speed>3){
				UnDraw();
				actual_x=actual_x-speed;
				Draw();
			}


		}else if(movingUp){
			if(actual_y-speed>1){
				UnDraw();
				actual_y=actual_y-speed;
				Draw();
			}

		}else if(movingDown){

			if(actual_y+speed<26){
				UnDraw();
				actual_y=actual_y+speed;
				Draw();
			}


		}
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

	//moving left
	void set_ML(bool state){
		this->movingLeft=state;
	}
	//moving right
	void set_MR(bool state){
		this->movingRight=state;
	}
	//moving Up
	void set_MU(bool state){
		this->movingUp=state;
	}
	//moving Down
	void set_MD(bool state){
		this->movingDown=state;
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

	//moving left
	bool ML(){
		return movingLeft;
	}
	//moving right
	bool MR(){
		return movingRight;
	}
	//moving up
	bool MU(){
		return movingUp;
	}
	//moving down
	bool MD(){
		return movingDown;
	}

};






void initPlayer_1(){ //wasd keys player
	Player player(90,10); //spawn point (x,y)

	bool active=true;
	while(active){
		//key codes https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
		
		
		//example taken from https://stackoverflow.com/questions/5523111/keypress-event-in-cs

		// if ((GetAsyncKeyState(VK_LEFT) < 0) != movingLeft) {
		// 	movingLeft = !movingLeft;
		// 	// gameObject->setVelocity(movingLeft ? -10 : 0);
		// }

		//to get rid of always getting the keyevent, we just set up a flag each time the key is pressed
		if((GetAsyncKeyState(0x44) < 0) != player.ML() ){ //D key
			player.set_ML( !player.ML() );
			player.Move();

		//to get rid of always getting the keyevent, we just set up a flag each time the key is pressed
		}else if((GetAsyncKeyState(0x41) < 0) != player.MR() ){ //A key
			player.set_MR( !player.MR() );
			player.Move();

		//to get rid of always getting the keyevent, we just set up a flag each time the key is pressed
		}else if((GetAsyncKeyState(0x57) < 0) != player.MU() ){ //W key
			player.set_MU( !player.MU() );
			player.Move();

		//to get rid of always getting the keyevent, we just set up a flag each time the key is pressed
		}else if((GetAsyncKeyState(0x53) < 0) != player.MD() ){ //S key
			player.set_MD( !player.MD() );
			player.Move();


		}else if(GetKeyState(VK_ESCAPE) & 0x8000){
			active=false;
		}
		
	


	//while bracket
	};
}


void initPlayer_2(){ //arrow keys player
	Player player(40,10); //spawn point (x,y)

	bool active=true;
	while(active){
		//key codes https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
		
		
		//example taken from https://stackoverflow.com/questions/5523111/keypress-event-in-cs

		// if ((GetAsyncKeyState(VK_LEFT) < 0) != movingLeft) {
		// 	movingLeft = !movingLeft;
		// 	// gameObject->setVelocity(movingLeft ? -10 : 0);
		// }

		//to get rid of always getting the keyevent, we just set up a flag each time the key is pressed
		if((GetAsyncKeyState(VK_RIGHT) < 0) != player.ML() ){ //D key
			player.set_ML( !player.ML() );
			player.Move();

		//to get rid of always getting the keyevent, we just set up a flag each time the key is pressed
		}else if((GetAsyncKeyState(VK_LEFT) < 0) != player.MR() ){ //A key
			player.set_MR( !player.MR() );
			player.Move();

		//to get rid of always getting the keyevent, we just set up a flag each time the key is pressed
		}else if((GetAsyncKeyState(VK_UP) < 0) != player.MU() ){ //W key
			player.set_MU( !player.MU() );
			player.Move();

		//to get rid of always getting the keyevent, we just set up a flag each time the key is pressed
		}else if((GetAsyncKeyState(VK_DOWN) < 0) != player.MD() ){ //S key
			player.set_MD( !player.MD() );
			player.Move();


		}else if(GetKeyState(VK_ESCAPE) & 0x8000){
			active=false;
		}
		
	


	//while bracket
	};
}



int main(){
	
	// SetFontSize(1);
	system("mode 110,27"); //sets cmd size to 100 columns and 25 rows
	
	system("cls");
	ShowConsoleCursor(false);
   	set_gameBoundaries();

	//init threads for each player
	std::thread Player1(initPlayer_1);
	std::thread Player2(initPlayer_2);

	bool active=true;
	while(active){
		if(GetKeyState(VK_ESCAPE) & 0x8000){
			active=false;
			printf("MAIN THREAD ENDED");
		}
		
	


	//while bracket
	};






    return 0;
}