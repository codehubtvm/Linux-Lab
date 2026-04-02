#include<stdio.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MSGKEY 1234
struct msg
{
	long type;
	char text[100];
};
void reverse(char*s)
{
	int l=0,r=strlen(s)-1;
	while(l<r)
	{
		char temp=s[l];
		s[l]=s[r];
		s[r]=temp;
		l++;
		r--;
	}
}
int main()
{
	struct msg m1,m2;
	int qid;
	qid=msgget(MSGKEY,IPC_CREAT|0666);
	msgrcv(qid,&m1,sizeof(m1.text),1,0);
	reverse(m1.text);
	m2.type=2;
	strcpy(m2.text,m1.text);
	msgsnd(qid,&m2,sizeof(m2.text),0);
	return 0;
}










Output 
--------
Open two terminals:

Terminal 1 – Run Receiver
gcc receiver.c -o receiver
./receiver
Terminal 2 – Run Sender
gcc sender.c -o sender
./sender

 SAMPLE OUTPUT
--------------------
Sender Terminal
Enter a string: madam
Reversed string received: madam
Palindrome

Receiver Terminal
(Shows no direct output; works in background)

Sender Terminal 
Enter a string: hello
Reversed string received: olleh
Not a palindrome

Receiver Terminal
(Shows no direct output; works in background)


