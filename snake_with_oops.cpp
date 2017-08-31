#include<iostream>
#include<ncurses.h>
#include<stdlib.h>
using namespace std;
int score=0;
class Screen;
class Snake;
class Food{
public:
int food_col;
int food_row;
int game_over(char a[20][20],int new_col,int new_row,int remove_col,int remove_row){
if(new_col==remove_col&&new_row==remove_row){
return 1;
}
else{
if(a[new_col][new_row]=='#'){
return 0;
}
else
return 1;
}
}
void food(char a[20][20],int x,int y){
for(int i=0;i!=1;i){
x=rand()%19;
y=rand()%19;
this->food_col=x;
this->food_row=y;
if(a[x][y]==' '&& x!=0&&y!=0){
i=1;
score++;
}
}
}
};
class Node{
public:
int i,j;
char a;
Node *next;
Node(int i,int j){
this->i=i;
this->j=j;
this->a='#';
}
void set_next(Node *n){
this->next=n;
}
Node* get_next(){
return this->next;
}
static Node* create_newnode(int i,int j){
Node *newnode;
newnode=new Node(i,j);
return newnode;
}
};

class Screen{
public:
char a[20][20];
Screen(){
for(int i=0;i<20;i++){
for(int j=0;j<20;j++){
a[i][j]=' ';
}
}
} 
void print_screen(Snake s1,Food f1);
};
class Snake{
public:
int remove_col;
int remove_row;
Node *head;
void start_snake(){
Node *start=NULL;
Node *ptr=NULL;
int x=9,y=10;
for(int k=0;k<5;k++,y--){
Node* n=Node::create_newnode(0,0);
//n->a='#';
n->next=NULL;
n->i=x;
n->j=y;
if(start==NULL){
start=n;
ptr=n;
}
else{
ptr->next=n;
ptr=ptr->next;
}
}
this->head=start;
}
void add_snake(Node* head,int remove_col,int remove_row){
Node *n=Node::create_newnode(0,0);
Node *ptr=this->head;
while(ptr->next!=NULL){
ptr=ptr->next;
}
n->i=this->remove_col;
n->j=this->remove_row;
n->a='#';
ptr->next=n;
n->next=NULL;
}
void path(Screen s1,char move,char &last_move,Food f1){
int new_col,new_row,flag=1;
if(move!='d'&&move!='s'&&move!='a'&&move!='w'){
move=last_move;
}
char move_save=move;
for(int p=0;flag==1;p++){
flag=0;
if(move=='w'){
if(last_move=='s'){
flag=1;
move='s';
}
else {
flag=0;
if(this->head->i-1<0){
new_col=this->head->i-1+20;
new_row=this->head->j;
}
else{
new_col=this->head->i-1;
new_row=this->head->j;
}
}
}
else{
if(move=='a'){
if(last_move=='d'){
flag=1;
move='d';
}
else{
flag=0;
if(this->head->j<=0){
new_col=this->head->i;
new_row=this->head->j-1+20;
}
else{
new_col=this->head->i;
new_row=this->head->j-1;
}
}
}
else{
if(move=='s'){
if(last_move=='w'){
flag=1;
move='w';
}
else{
flag=0;
if(this->head->i>=20){
new_col=this->head->i+1-20;
new_row=this->head->j;
}
else{
new_col=this->head->i+1;
new_row=this->head->j;
}
}
}
else{
if(move=='d'){
if(last_move=='a'){
flag=1;
move='a';
}
else{
flag=0;
if(this->head->j>=20){
new_col=this->head->i;
new_row=this->head->j+1-20;
}
else{
new_col=this->head->i;
new_row=this->head->j+1;
}
}
}
}
}
}
}
if(move_save=='a'&&last_move=='d'){
last_move=last_move;
}
else{
if(move_save=='d'&&last_move=='a'){
last_move=last_move;
}
else{
if(move_save=='w'&&last_move=='s'){
last_move=last_move;
}
else{
if(move_save=='s'&&last_move=='w'){
last_move=last_move;
}
else{
if(move!='d'&&move!='s'&&move!='a'&&move!='w'){
move=last_move;
}
else{
last_move=move_save;
}
}
}
}
}
int x,y;
char symbol,swap_symbol;
Node *ptr1=this->head;
while(ptr1->next!=NULL){
ptr1=ptr1->next;
}
if(f1.game_over(s1.a,new_col,new_row,ptr1->i,ptr1->j)){
if(f1.food_col==new_col&&f1.food_row==new_row){
symbol='*';
}
else{
symbol='#';
}
Node *ptr=this->head;
while(ptr->next!=NULL){
x=ptr->i;
y=ptr->j;
swap_symbol=ptr->a;
ptr->i=new_col;
ptr->a=symbol;
ptr->j=new_row;
new_col=x;
symbol=swap_symbol;
new_row=y;
ptr=ptr->next;
}
this->remove_col=ptr->i;
this->remove_row=ptr->j;
ptr->i=new_col;
ptr->j=new_row;
}
}
void rev(Node *head,char &last_move){
Node *ptr=this->head;
Node *ptr1=this->head->next;
ptr->next=NULL;
Node *ptr2=this->head;
while(ptr2!=NULL){
ptr2=ptr1->next; 
ptr1->next=ptr;
if(ptr2!=NULL){
ptr=ptr1;
ptr1=ptr2;
}
}
if(last_move=='w'){
last_move='s';
}
else{
if(last_move=='a'){
last_move='d';
}
else{
if(last_move=='s'){
last_move='w';
}
else{
if(last_move=='d'){
last_move='a';
}
}
}
}
this->head=ptr1;
}
};
void Screen::print_screen(Snake s1,Food f1){
Node *ptr=s1.head;
if(f1.food_col==ptr->i&&f1.food_row==ptr->j){
f1.food(this->a,f1.food_col,f1.food_row);
s1.add_snake(s1.head,s1.remove_col,s1.remove_row);
}
else{
a[s1.remove_col][s1.remove_row]=' ';
}
while(ptr!=NULL){
a[ptr->i][ptr->j]=ptr->a;
ptr=ptr->next;
}
a[f1.food_col][f1.food_row]='*';
ptr=s1.head;
while(ptr!=NULL){
move(ptr->i,ptr->j);
addch(ptr->a);
ptr=ptr->next;
}
move(f1.food_col,f1.food_row);
addch('*');
move(s1.remove_col,s1.remove_row);
addch(' ');
move(0,80);
printw("current score:=%d",score);
move(0,0);
}
int main(){
initscr();
noecho();
napms(90);
raw();
nodelay(stdscr, TRUE);
Node *start=NULL;
Node *start1=NULL;
Screen s1;
Snake s2;
Food f1;
int food_col,food_row,remove_col,remove_row,ncurses_move,flag=0;
char move_start,last_move='p',move1='d';
s2.start_snake();
f1.food(s1.a,f1.food_col,f1.food_row);//start from here
s1.print_screen(s2,f1);
while((move_start=getch())!=1){
napms(90);
if(move_start=='1'){
break;
}
else{
if(move_start=='r'){
s2.rev(s2.head,last_move);
if(move_start=='r'&&move1=='d'){
move_start='a';
}
else{
if(move_start=='r'&&move1=='w'){
move_start='s';
}
else{
if(move_start=='r'&&move1=='s'){
move_start='w';
}
else{
if(move_start=='r'&&move1=='a'){
move_start='d';
}
}
}
}
}
else{
if(move_start=='w'||move_start=='a'||move_start=='s'||move_start=='d'){
move1=move_start;
}
s2.path(s1,move_start,last_move,f1);
if(!f1.game_over(s1.a,s2.head->i,s2.head->j,s2.remove_col,s2.remove_row)&&flag==1){
break;
flag=2;
}
if(move_start=='d'){
flag=1;
}
s1.print_screen(s2,f1);

}
}
refresh();
}
move(10,10);
printw("GAME OVER");
move(12,10);
printw("SCORE:=%d",score);
refresh();
napms(1000);
getch();
endwin();
return 0;
}
