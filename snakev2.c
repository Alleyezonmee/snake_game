//Please run this on linux.....
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#define length 50 // length of board
#define breadth 100 // breadth of board
#define speed 100000 // snake speed.
int rando(int max) {
 time_t t;
 srand((unsigned) time(&t));
 int ans = rand()%max;
 return ans;
} // random generator.
struct snake{
 int x;
 int y;
 struct snake *next;
 char value;
}; // structure for snake
struct food{
 int x;
 int y;
 char value;
}; // structure for food and mine
int gameEnd(struct snake *head,int diff,char board[length][breadth]) {
  struct snake* ptr,*h1;
  h1=head;
  ptr=head;
    ptr=ptr->next;
    while(ptr!=NULL) {
      if(ptr->x==h1->x && ptr->y==h1->y) {
        return 0;
      }
      ptr=ptr->next;
    }
 return 1;
}  // function for ending game.
void init_board(char board[length][breadth]) {
 for(int i=0;i<length;i++) {
   for(int j=0;j<breadth;j++)  {
     board[i][j]=' ';
   }
 }
 for(int i=0;i<length;i++) {
   board[i][0]='X';
 }
 for(int i=0;i<length;i++) {
   board[i][breadth-1]='X';
 }
 for(int i=0;i<breadth;i++) {
   board[0][i]='X';
 }
 for(int i=0;i<breadth;i++) {
   board[length-1][i]='X';
 }
} // function for initialising board
struct snake * init_snake(struct snake *head) {
 head=(struct snake *)calloc(1,sizeof(struct snake));
 head->x=9;
 head->y=20;
 head->value='v';
 struct snake *tail,*n,*n1;
 n=(struct snake *)calloc(1,sizeof(struct snake));
 n->x=10;
 n->y=20;
 n->value='0';
 n1=(struct snake *)calloc(1,sizeof(struct snake));
 n1->x=11;
 n1->y=20;
 n1->value='0';
 tail=(struct snake *)calloc(1,sizeof(struct snake));
 tail->x=12;
 tail->y=20;
 tail->value='0';
 head->next=n;
 n->next=n1;
 n1->next=tail;
 tail->next=NULL;
 return head;
}
void food_gen(char board[length][breadth]) {
 struct food f;
 int flag=0;
 while(flag!=1)
 {
   f.x=rando(length-1);
   f.y=rando(breadth-1);
   if(board[f.x][f.y]==' ')
   {
     flag=1;
   }
 }
 board[f.x][f.y]='*';
}
void mine_gen(char board[length][breadth]) {
  struct food m;
  int flag=0;
  while(flag!=1) {
    m.x=rando(length-1);
    m.y=rando(breadth-1);
    if(board[m.x][m.y]==' ') {
      flag=1;
    }
  }
  board[m.x][m.y]='@';
}
void print_board(char board[length][breadth], int score, int dif) {
 for(int i=0;i<length;i++) {
   for(int j=0;j<breadth;j++) {
     printf("%c",board[i][j]);
   }
   printf("\n");
 }
 printf("Level:\t%d\nScore:\t%d\n",dif,score);
}
int check(struct snake *head,char val) {
  if((head->value=='^' && val=='w') ||(head->value=='>' && val=='d') || (head->value=='<' && val=='a') || (head->value=='v' && val=='s')) {
    return 1;
  } else {
    return 0;
  }
}
int kbhit(void) {
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}
void level2(char board[length][breadth]) {
  mine_gen(board);
}
void level3(char board[length][breadth]) {
  init_board(board);
  int n=rando(10);
  for(int i=0;i<=n;i++) {
    mine_gen(board);
  }
}
void level4(char board[length][breadth]) {
  init_board(board);
  level3(board);
  for(int i=0;i<length;i++) {
    board[i][0]='#';
  }
  for(int i=0;i<length;i++) {
    board[i][breadth-1]='#';
  }
  for(int i=0;i<breadth;i++) {
    board[0][i]='#';
  }
  for(int i=0;i<breadth;i++) {
    board[length-1][i]='#';
  }
}
void level5(char board[length][breadth]) {
  int i;
  for(i=0;i<length;i++) {
    if(i==16 || i==17 || i==18) {

    } else {
      if(board[i][15]!='*') {
        board[i][15]='#';
      }
    }
  }
  for(i=0;i<length;i++) {
    if(i==23 || i==22 || i==21) {

    } else {
      if(board[i][35]!='*') {
        board[i][35]='#';
      }
    }
  }
}
void playGame(char board[length][breadth],struct snake *start) {
  char posi='w',prev='w';
  struct snake *ptr,*temp,*n;
	int score=0,flag=0,diff=1,flag2=0,flag3=0,flag4=0;
  ptr=start;
  while(gameEnd(start,diff,board)!=0)
  {
    while(!kbhit())
     {
      if(check(start,posi)!=1)
      {
       usleep(speed);
       n=(struct snake*)calloc(1,sizeof(struct snake));
       n->x=ptr->x;
       n->y=ptr->y;
       n->value=ptr->value;
       if(diff<4)
       {
       if(posi=='w') {
        n->x-=1;
        n->value='v';
        if(n->x==0)
         {
          n->x=length-2;
        }
		   }
       else if(posi=='a')
        {
        n->y-=1;
        n->value='>';
			  if(n->y==0) {
          n->y=breadth-2;
        }
       }
       else if(posi=='s') {
        n->x+=1;
        n->value='^';
			  if(n->x==length-1) {
          n->x=1;
        }
       }
       else if(posi=='d') {
        n->y+=1;
        n->value='<';
			  if(n->y==breadth-1) {
          n->y=1;
        }
       }
     }
      else {
       if(posi=='w') {
        n->x-=1;
        n->value='v';
        if(n->x==0) {flag=1; break;}
		   }
       else if(posi=='a') {
        n->y-=1;
        n->value='>';
			  if(n->y==0) {flag=1; break;}
       }
       else if(posi=='s') {
        n->x+=1;
        n->value='^';
			  if(n->x==length-1) {flag=1; break;}
       }
       else if(posi=='d') {
        n->y+=1;
        n->value='<';
			  if(n->y==breadth-1) {flag=1; break;}
       }
     }
       start=n;
       if(board[n->x][n->y]=='@')
       {
         flag=1;
         break;
       }
       if(board[n->x][n->y]=='#') {flag=1;break;}
		   if(board[n->x][n->y]=='*')
       {
			  score++;
        if(score>20 && score<=40)
        {
          if(diff<2)
          {
            diff++;
            level2(board);
          }
        }
        else if(score>40 && score<=60)
         {
          if(diff<3)
          {
            diff++;
            level3(board);
          }
        }
        else if(score>60 && score<=80)
         {
          if(diff<4)
          {
            diff++;
            level4(board);
          }
        }
        else if(score>80 && score<=100) {
          if(diff<5) {
            diff++;
            level5(board);
          }
        }
        if(score>100)
        {
          flag=1;
        }
			  board[n->x][n->y]=n->value;
			  ptr->value='0';
			  board[ptr->x][ptr->y]=ptr->value;
			  n->next=ptr;
			  food_gen(board);
		   }
		   else {
			  n->next=ptr;
			  board[n->x][n->y]=n->value;
	      temp=ptr;
	      ptr=ptr->next;
	      while(ptr->next!=NULL)
        {
	        temp->value=ptr->value;
	        board[temp->x][temp->y]=temp->value;
	        ptr=ptr->next;
	        temp=temp->next;
	      }
	      temp->next=NULL;
	      temp->value=ptr->value;
	      board[temp->x][temp->y]=temp->value;
	      temp=ptr;
	      board[ptr->x][ptr->y]=' ';
	      free(temp);
		   }
      ptr=start;
      system("clear");
      system("stty -echo");
      print_board(board,score,diff);
    }
    else
    {
      posi=prev;
    }
    if(gameEnd(start,diff,board)==0)
    {
      flag=1;
      break;
    }
  }
  if(flag==1) {break;}
  char ch=getchar();
  if(ch=='w' || ch=='a' || ch=='s' || ch=='d') {prev=posi;posi=ch;}
  }
  system("clear");
  printf("\n\t\tGAME OVER\n");
	printf("\n\t\tSCORE - %d\n\n",score);
}
int main() {
 char board[length][breadth];
 init_board(board);
   struct snake *head;
   head=NULL;
   head=init_snake(head);
   struct snake *ptr;
   ptr=head;
   while(ptr!=NULL) {
    board[ptr->x][ptr->y]=ptr->value;
    ptr=ptr->next;
   }
 food_gen(board);
 playGame(board,head);
 system ("/bin/stty cooked");
 system("stty echo");
}
