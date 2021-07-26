//College Name:                                  "Coimbatore Institute Of Technology"                      DATE:05/10/2020
//Department Name:                                       "Computer Science"
//Subject Name:                                           "Data Structures"
//Project Name:                                          "RAT AND THE MAZE"
//Professor Name:                                         "PRABHAKAR SIR"
//Student Name:                                      "R.Aravind" "R.Kavinraja"
//Roll No:                                             1905005      1905023
#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#define BUT 0
#define qaz 3
#include<graphics.h>
#include<gdiplus.h>
#include <windows.h>
#include<windowsx.h> //os interaction
void setmaze();  // function that sets all elements in maze to 0 other than edges
void draw();    //function to draw the maze graphics
int start();    //function to implement stack
int xPos;
RECT r;         //structure to store rectangle sizess (grapical drawing )
int endck,startck,wall,startbut;   //to ensure only one start stop is clicked
int yPos ;
HDC hdc;     //handle to the paint window
int sx=0,sy=0,pos;
RECT rec,rect;
HWND edit;
HWND hwnd;
int a=10,b=10;  //total no of rows and colomn
int DX=9,DY=9,mx,my;
void setstart(int ax,int ay)
   {//start of function-->setstart
    mx=ax;
    my=ay;
   }//end of function-->setstart
PAINTSTRUCT ps;
int maze[30][30];
int mark[30][30];
LRESULT CALLBACK WindowProc(HWND hwnd,UINT msg, WPARAM wParam, LPARAM lParam)//this is the must for windows procedure
   {//start of function--> Windowproc
    switch(msg)
       {   //wparam is the keyyy pressed
        case WM_RBUTTONDOWN:
           { //start of WM_RBUTTONDOWN(right side of mouse clicked)
            xPos = GET_X_LPARAM(lParam);  // x coordinate of mouse when clicked
            yPos = GET_Y_LPARAM(lParam);  // y coordinate of mouse when clicked
            HBRUSH h181= CreateSolidBrush(RGB(255,255,0));
            SelectObject(hdc,h181);
            mx=(xPos-200)/(800/a),my=(yPos-100)/(500/b);  //mx and my are the index value of the maze where the mouse is clicked
            if((xPos>200)&&(xPos<1000)&&(yPos>100)&&(yPos<600))
               {  //starting of if statement 11
                if(wParam == MK_RBUTTON)
                   {  //set start position (when only the right button of mouse is clicked)
                    if(startck==0)   //endck is to avoid setting of start position twice before reset
                       {
                        startck=1;
                        sx=my;
                        sy=mx;
                        mark[my][mx]=1;
                        maze[my][mx]=1;
                        FloodFill(hdc,xPos,yPos,RGB(0,0,255));
                       } //end of if statement of startck
                   }//end of if statement of MK_RBUTTON
                else
                   {    //set end position  (when ctrl + right button of the mouse is clicked)
                    if(endck==0)  ////endck is to avoid setting of end position twice before reset
                       {
                        endck=1;
                        DX=my;
                        DY=mx;
                        mark[my][mx]=1;
                        maze[my][mx]=1;
                        FloodFill(hdc,xPos,yPos,RGB(0,0,255));
                       }//end of if statement of endck
                   }//end of else statement of MK_RBUTTON
               }//end of if statement 11
            break;
           }//end of WM_RBUTTONDOWN of switch(msg)
        case WM_LBUTTONDOWN:
           {      //left mouse clicked(setting up walls)
            xPos = GET_X_LPARAM(lParam);  // x coordinate of mouse when clicked
            yPos = GET_Y_LPARAM(lParam);  // y coordinate of mouse when clicked
            HBRUSH h121= CreateSolidBrush(RGB(255,0,0));
            mx=(xPos-200)/(800/a),my=(yPos-100)/(500/b);
            if((xPos>200)&&(xPos<1000)&&(yPos>100)&&(yPos<600)&&(wall==0))
               { //start of if statement 22
                SelectObject(hdc,h121);
                mark[my][mx]=1;   //walls marked as 1 in mark
                maze[my][mx]=1;   //walls marked as 1 in maze
                FloodFill(hdc,xPos,yPos,RGB(0,0,255));
               } //end of if statement 22
            break;
           } //end of case WM_LBUTTONDOWN of switch(msg)
        case WM_COMMAND:
           {   //button(resetmaze or start) is pressed
            switch(wParam)
               { //start of switch(wParam)
                case 3:           //when reset maze button pressed
                   {
                    sx=1,sy=1;
                    DX=8,DY=8;
                    startbut=0;
                    endck=0;
                    wall=0;
                    startck=0;
                    setmaze();
                    HBRUSH h123= CreateSolidBrush(RGB(0, 0, 0));
                    SelectObject(hdc,h123);
                    FloodFill(hdc,300,200,RGB(0,0,0));
                    DeleteObject(h123);
                    draw();
                    break;
                   } //end of case 3 in switch wParam
                case 0:
                   {  //when start button is pressed
                    if(startbut==0)   //checks if only once the start button is pressed
                       {//start of if statement 33
                        wall=1;startbut=1;
                        if(start()==-1) //if no possible way start function returns -1
                           {//start of if statement 44
                            MessageBox(hwnd,"NO POSSIBLE WAY","MAZE",MB_OK);
                           }//end of if statement of 44
                        else
                           {//start of else statement of 44
                            MessageBeep(MB_OK);
                            MessageBox(hwnd,"SUCCESS","MAZE",MB_OK);
                           }//end of else statement of 44
                        setmaze();
                       }//end of if statement of 33
                    else
                       {//start of else statement of 33
                        MessageBeep(MB_OK);
                        MessageBox(hwnd,"reset the maze","MAZE",MB_OK);
                       }//end of else statement of 33
                    break;
                   }//end of case 0 in switch wParam
               }//end of switch(wParam)
            break;
           }// end of case WM_COMMAND of switch(msg)
        case WM_CLOSE:
           {
            PostQuitMessage(69);//to close the program
            break;
           }// end of case WM_CLOSE of switch(msg)
        default:
           {
            return DefWindowProc(hwnd,msg,wParam,lParam);
            break;
           }// end of defualt case of switch(msg)
       }//end of switch(msg)
   }//end of function--> Windowproc

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
   {//start of WINAPI WinMain
    setmaze();
    const auto uuu="trt";
    WNDCLASSEX ch={0};
    ch.cbSize=(sizeof(ch));   //size to size of the above created structure class
    ch.style=CS_OWNDC; //always to be set like thiss
    ch.lpfnWndProc=WindowProc;  //(defulat choice)       //holds the pointer to funtion windows procedure
    ch.hInstance=hInstance;
    ch.lpszClassName=uuu ;  //class name to be passed to window funtion
    ch.hbrBackground=HBRUSH(WM_ERASEBKGND);
    ch.cbClsExtra=0;
    ch.cbWndExtra=0;
    ch.hCursor=LoadCursor (NULL, IDC_ARROW);;
    RegisterClassEx(&ch);    //pass structure memory address
    hwnd=CreateWindowEx(0,uuu,"study",WS_OVERLAPPEDWINDOW,200,200,600,200,HWND_DESKTOP,NULL,hInstance,NULL);
    SetWindowLong(hwnd, GWL_STYLE,GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
    SetWindowLong(hwnd, GWL_STYLE,GetWindowLong(hwnd, GWL_STYLE) & ~WS_MINIMIZEBOX);
    hdc=BeginPaint(hwnd,&ps);
    CreateWindowEx(0,
        "BUTTON",  // Predefined class; Unicode assumed
        "START",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON|WS_OVERLAPPED,  // Styles
        50,         // x position
        300 ,        // y position
        100,        // Button width
        100,        // Button height
        hwnd,// Parent window
        HMENU(BUT),       // No menu.
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);
    CreateWindowEx(0,
        "BUTTON",  // Predefined class; Unicode assumed
        "RESET MAZE",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON|WS_OVERLAPPED,  // Styles
        50,         // x position
        500,        // y position
        100,        // Button width
        100,        // Button height
        hwnd,// Parent window
        HMENU(qaz),       // No menu.
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);
        ShowWindow(hwnd,SW_MAXIMIZE); //USED TO DISPLAY WINDOW
        draw();
        MSG msg;
        bool reus;
    while((reus=GetMessage(&msg,NULL,0,0))>0) //used to get all messages handle=null beacuse need to get message for all windows
       { //start of while statement 222
        TranslateMessage(&msg);// used to transulate message to understandable form
        DispatchMessage(&msg);//used to send messages to windows proc
       }//end of while statement 222
    if(reus==-1)
       {  //start of if statement 55 we capture the result of get message and check for error
        return -1;
       }//end of if statement 55
    else
       {//start of else statement 55
        return msg.wParam;
       } //end of else statement 55
   }//end of main function :: WINAPI WinMain
void draw()   //draw function declaration used to draw the grapics
   {
    rect.left=150;
    rect.top=0;
    rect.bottom=90;
    rect.right=1050;
    r.left=1040;
    r.top=230;
    r.bottom=600;
    r.right=1340;
    HPEN hBluePen = CreatePen(PS_SOLID,2,RGB(0, 0, 255));
    SelectObject(hdc, hBluePen);
    SetBkColor(hdc,RGB(0,0,0));
    HBRUSH h129= CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc,h129);
    Rectangle(hdc,1030,200,1335,500);
    DeleteObject(h129);
    MoveToEx(hdc,1030,270,NULL);
    LineTo(hdc,1335,270);
    MoveToEx(hdc,1200,200,NULL);
    LineTo(hdc,1200,500);
    SetTextColor(hdc,RGB(0,255,0));
    HFONT hFont=CreateFont (30, 0,0,0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
    SelectObject(hdc, hFont);
    SetBkMode(hdc,TRANSPARENT);
    DrawText(hdc, TEXT(" CONTROL"),-1,&r,DT_LEFT);
    r.top=205;
    DrawText(hdc, TEXT("                     SET\n                      POSITION"),-1,&r,NULLREGION);
    r.top=290;
    DrawText(hdc, TEXT("RIGHT CLICK"),-1,&r,DT_LEFT);
    DrawText(hdc, TEXT("                        START"),-1,&r,NULLREGION);
    r.top=350;
    DrawText(hdc, TEXT("    CTRL+\nRIGHT CLICK"),-1,&r,DT_LEFT);
    r.top=360;
    DrawText(hdc, TEXT("                        END"),-1,&r,NULLREGION);
    r.top=440;
    DrawText(hdc, TEXT("LEFT CLICK"),-1,&r,DT_LEFT);
    DrawText(hdc, TEXT("                        WALL"),-1,&r,NULLREGION);
    DeleteObject(hFont);
    SetTextColor(hdc,RGB(0,255,0));
    HFONT pFont=CreateFont (100, 0,0,100, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
    SelectObject(hdc, pFont);
    SetBkMode(hdc,TRANSPARENT);
    DrawText(hdc, TEXT("RAT AND THE MAZE "),-1,&rect,DT_CENTER);
    DeleteObject(pFont);
    SetBkColor(hdc,RGB(0,0,0));
    HBRUSH h123= CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc,h123);
    Rectangle(hdc,200,100,1000,600);
    for(int j=100;j<580;j=j+(500/b))
       {//start of for function 11111
        MoveToEx(hdc,200,j,NULL);
        LineTo(hdc,1000,j);
       }//end of for function 11111
    for(int i=200;i<995;i=i+(800/a))
	   {//start of for function 22222
	    MoveToEx(hdc,i,100,NULL);
        LineTo(hdc,i,600);
       }//end of for function 22222
    HBRUSH hQ= CreateSolidBrush(RGB(255, 0, 0));
    SelectObject(hdc,hQ);
    int it=-1,jt=0;
    for(int j=100;j<595;j=j+(500/b))
       {//start of for function 33333
        it=it+1;
        jt=0;
        for(int i=200;i<980;i=i+(800/a))
	       {//start of for function 55555
	        if(maze[it][jt]==1)
               {//start of if function 2121
	            FloodFill(hdc,i+3,j+3,RGB(0,0,255));
               }//end of if function 2121
	        jt=jt+1;
           }//end of for function 55555
       }//end of for function 33333
   }//end of function-->draw()
int start() //start function declaration
   {
    //*****************************************************************************************************************************************
                           //    +++++++++++++++++++++++++ main stack implementation +++++++++++++++++++++++++
    int stack[100][3]={sx,sy,-1},top=1,i=0,j=0;
    int w,g=0,h=0;
    HBRUSH h2= CreateSolidBrush(RGB(0, 255, 0));
    HBRUSH h3= CreateSolidBrush(RGB(0, 255, 255));
    SelectObject(hdc,h2);
    int move[2][8]={{1,1,0,-1,-1,-1,0,1},{0,1,1,1,0,-1,-1,-1}};
    //MOVE TABLE
    //0 ---- DOWN
    //1------RIGHT DOWN
    //2----- RIGHT
    //3-----RIGHT TOP
    //4-----TOP
    //5-----LEFT TOP
    //6------LEFT
    //7------LEFT DOWN

    setfillstyle(USER_FILL,GREEN);
    while(top!=0)
       { //start of while statement 1313
        top=top-1; //this is to retrace the path back( move the top of the stack back by 1)
        i=stack[top][0]; //to set the (i  = the row location is reseted to stack of top th row )
        j=stack[top][1]; //to set the (j  = the colomn location is reseted to stack of top th colomn )
        w=stack[top][2]+1; //to set the (w  = the direction is reseted to stack of top th direction(which is the direction to contuine checking form) )
        while((w<=7)&&(w>=0))        //while to check all 8 directions
           { //start of while statement 2323
            g=i+move[0][w];
            h=j+move[1][w];
            if((g<0)||(h<0))     //to check if move goes out of maze
               { //start of if statement 3535
                return -1;
               } //end of if statement 3535
        if((g==DX)&&(h==DY))      //this is to check if the destination is reached
           { //start of if statement 7676
            top++;             //increment top to add the final moved locations data
            stack[top][0]=g;   //the final moved locations data row in the maze
            stack[top][1]=h;   //the final moved locations data columns in the maze
            stack[top][2]=w;   //the final locations data direction(0 to 7)
            //for(int p=1;p<top;p++){ }to pop
            goto z;  // to terminate as the final destination is reached
           }//end of if statement 7676
        if((mark[g][h]==0)&&(maze[g][h]==0))  //check if there is space in maze to move(in code ==0 go in)
           {//start of if statement 8989
            mark[g][h]=1;       //setting the new moved position as 1
            top=top+1;             //increment top to add the new moved locations data
            stack[top][0]=g;   //the new moved locations data row in the maze
            stack[top][1]=h;   //the new moved locations data columns in the maze
            stack[top-1][2]=w;   //the new locations data direction(0 to 7)
                              //(w+1 to check from the next direction)(other words to avoid rechecking the next location)
            Sleep(1000);
            SelectObject(hdc,h2);
            FloodFill(hdc,210+(stack[top][1]*(800/a)),(110+(stack[top][0]*(500/b))),RGB(0,0,255));
            i=g,j=h;
            w=-1;//to reset the direction to start checking from 0 again for the new moved location
           }//end of if statement 8989
            w=w+1; // to move to the next direction
           }//end of while statement 2323
        Sleep(1000);
        SelectObject(hdc,h3);
        FloodFill(hdc,210+(stack[top][1]*(800/a)),(110+(stack[top][0]*(500/b))),RGB(0,0,255));
       }//end of while statement 1313
    z:
    if(top==0)// if all elements in the stack are poped or(if it retraces back to starting position of stack)
       {   //return -1 if no way out
        return -1;
       }
   }//end of declaration of function-->start()
//************************************************************************************************************************************************
void setmaze()
   {//to set all elements in the maze to 0 and the walls as 1
    for(int i = 0; i <b; i++)
       {//starting of for statement 5676
        for(int j = 0; j < a; j++)
           {//starting of for statement 4944
            if((i==0)||(j==0)||(i==(b-1))||(j==(a-1))) //to check if wall
               {
                maze[i][j]=1; //setting walls as 1
                mark[i][j]=1;
                continue;
               }
    maze[i][j]=0;
    mark[i][j]=0; //setting other locations as 0
           }//ending of for statement 4944
       }//ending of for statement 5676
   }//end of function-->setmaze()



//               ++++++++++++++++@@@@@@@@@@@@@@@@@@@@@@%%   PROJECT SUCCESSFULLY COMPLETED   %%@@@@@@@@@@@@@@@@@@@@@@++++++++++++++++
