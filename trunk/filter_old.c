#include <stdio.h>
#include <stdlib.h>

#define NODESIZE 256

typedef struct node{
struct node *nexts[NODESIZE];
}node;


node *createTree(int slen,char *kws[]){
	node *head,*p,*tmp;
	p = (node *)malloc(sizeof(node));
	memset(p,0,sizeof(node));
	head = p;
	int i,j,c;
	for(i=0;i<slen;i++){
		printf("parse %s\n",kws[i]);
		p=head;
		for(j=0;j<strlen(kws[i]);j++){
			c=kws[i][j];
			if(p->nexts[c]==0){
				tmp = (node *)malloc(sizeof(node));
				memset(tmp,0,NODESIZE);
				p->nexts[c] = tmp;
				p = tmp;
				continue;
			}
			p = p->nexts[c];

		}

	}
	return head;
}

void filter(node *head,char *target){
	int i,j;
	node *p;
	int *start,*end;
	int pstart,pend,kwnum;

	start = (int *)malloc(sizeof(int)*10);
	end = (int *)malloc(sizeof(int)*10);
	memset(start,0,sizeof(int)*10);
	memset(end,0,sizeof(int)*10);

	pstart = 0;
	pend = 0;
	kwnum = 0;

	for(i=0;i<strlen(target);i++){
		p = head;
		pstart = i;
		pend = i;
		j=i;
		while(1){
			if(p->nexts[target[j]]==0){
				if(p==head){
					break;	
				}
				start[kwnum] = pstart;
				end[kwnum] = pend;
				kwnum++;
				break;
			}
			pend++;
			p=p->nexts[target[j]];
			j++;
		}
	}
	for(i=0;i<9;i++)
	{
		printf("begin[%d]=%d\t\t",i,start[i]);
		printf("end[%d]=%d\n",i,end[i]);
	}
}
int main(int argc,char *argv[]){
	char *kws[argc-2];
	int i;
	node *head;
	for(i=2;i<argc;i++){
		kws[i-2] = argv[i];
	}

	head = createTree(argc-2,kws);
	filter(head,argv[1]);
	sleep(50);
	return 0;
}
