#include "stdio.h"
#include "stdlib.h"
#include "sys.h"

#include "CommandTree.h"
#include "ExecuteCommand.h"
#include "globe.h"
#include "PreExecute.h"
#include "string.h"


char line[1000];
char* args[50];
int argsCnt;
char* m = "root";
char* n = "root";
char* name;
char* password;
char* name1 = "yy";
char* password1 = "yy";
int t1,t2;
int t3,t4;
int ttyin0,ttyin1;
int main1()
{
	char lineInput[512];
	getPath( curPath );	
	int root;

	if(!fork())
		{
			close(STDIN);
			close(STDOUT);
			open("/dev/tty2",1);
			open("/dev/tty2",2);
		}
	else
		{
			close(STDIN);
			close(STDOUT);
			open("/dev/tty1",1);
			open("/dev/tty1",2);
		}

	printf("Login: ");
	printf("\n");
M:	printf("UserId: ");
	gets(name);
	t1 = strcmp(name, m);
	t2 = strcmp(name,name1);
	if(t1==0 || t2== 0)
	{	printf("password: ");
		fgets(password);
		printf("\n");
		t3 = strcmp(password, n);
		t4 = strcmp(password, password1);
	}
	else { 	printf("name Error!");
			printf("\n");
			printf("please try again!");
			printf("\n");
			goto M;
		}
	if((t1 == 0 && t3 == 0) || (t2 == 0 && t4 == 0))
		{	if(t1 == 0 && t3 == 0)
			{	setuid(0);
				setgid(0);
				goto L;
			}
		else
		{
				setuid(510);
				setgid(510);
				goto L;
		}
		}
	else {	printf("pass Error!");
			printf("\n");
			printf("please input any key to exit!");
			printf("\n");
			gets(line);
			return 0;
	}

L:	while( 1 )
	{
		root = -1;
		argsCnt = 0;
		InitCommandTree();
		printf("[%s]#", curPath);
		gets( lineInput );
		if ( strcmp( "shutdown", lineInput ) == 0 )
		{
		syncFileSystem();
		printf("You can safely turn down the computer now!\n");
			break;
		}
		argsCnt = SpiltCommand(lineInput);
		root = AnalizeCommand(0, argsCnt - 1, 0);
		if ( root >= 0 )
		{
		ExecuteCommand( &commandNodes[root], 0, 0 );
		}
	}
	return 0;
}
