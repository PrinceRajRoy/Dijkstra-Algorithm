# include<iostream>
# include<fstream>
# include<stdlib.h>
# define INFINITY 10000000

using namespace std;

void swap(int *i,int *j){                                          //Function To Swap Values

     int  y=*i;
         *i=*j;
         *j=y;

     return;
}

class DIJKS{

             int **graph,*sdist,*heap,*pvalue,*cvalue,n,source;

         public:

             DIJKS();
             void read();
             int  emin();
             void heapifyu(int);
             void heapifyd(int);
             void change();
             void result();

           };


DIJKS :: DIJKS(){                                           //Constructor To Allocate Memory And Initialize With Values

int i,j;
cout<<"Enter The Number Of Vertices : ";
cin>>n;
cout<<"Enter The Source Vertex : ";
cin>>source;

graph = new int*[n];

for(i=0;i<n;i++)
    graph[i] = new int[n];

pvalue =  new int[n];
cvalue =  new int[n];
heap   =  new int[n+1];
heap[0] = n;
sdist  =  new int[n];

for(i=0;i<n;i++){

  for(j=0;j<n;j++)
    graph[i][j]= INFINITY;
    pvalue[i]  = NULL;
    sdist[i]   = INFINITY;
    heap[i+1]    = INFINITY;
    cvalue[i]  = i+1;

}

heap[source]=0;
sdist[source-1]=0;

read();
change();
result();
return;
}


void DIJKS :: read(){                                           //Function To Read Graph From File

ifstream fp("dijkstra.txt");

int num,i,j;
char ch;

for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      graph[i][j]=INFINITY;

while(!fp.eof()){

    fp>>i;

    do{
    fp>>j>>num;
    if(i>n||j>n){
        cout<<"!!!Wrong Vertex Provided In The File!!!";
        exit(1);
    }
    graph[i-1][j-1]=num;
    graph[j-1][i-1]=num;
    fp.get(ch);
    }while(ch!='\n'&&!fp.eof());

}

/*for(i=1;i<n+1;i++){
    for(j=1;j<n+1;j++)
        cout<<graph[i][j]<<" ";
        cout<<"\n";
}*/

fp.close();
return;
}


int DIJKS :: emin()                                               //Function To Extract The Minimum Value From Heap
{
	int m=cvalue[0];
	cvalue[0]=cvalue[heap[0]-1];
	heap[1]=heap[heap[0]];
	heap[0]--;
	heapifyd(1);
	return m;
}


void DIJKS :: heapifyu(int n)                                     //Function To Perform Heapify-Up Operation After Insertion
{                                                                 //Of Element To The Heap
	int j=n/2;

	if(j>=1 && heap[n]<heap[j])
	{
		    swap(&cvalue[n-1],&cvalue[j-1]);
	        swap(&heap[n],&heap[j]);
	        heapifyu(j);

	}
	return;
}


void DIJKS :: heapifyd(int i)                                     //Function To Perform Heapify-Down Operation After Extract
{                                                                 //Minimum Value From Heap Is Performed
	int lc=(2*i),rc=(2*i+1),x;

	if(lc<heap[0])
	{
	        if(rc<heap[0] && heap[rc]<heap[lc])
                        x=rc;
	        else
                        x=lc;

		if(heap[x]<heap[i])
		{
			swap(&cvalue[i-1],&cvalue[x-1]);
			swap(&heap[i],&heap[x]);
			heapifyd(x);
		}
	}
	return;
}


void DIJKS :: change(){                                          //Function To Implement Dijkstra's Algorithm

int k,l,m;
heapifyu(source);
while(heap[0]>0){
m=emin()-1;
for(l=0;l<n;l++)
{
    if(sdist[l]>(sdist[m]+graph[m][l]) && graph[m][l]!=INFINITY)
    {
    sdist[l]=sdist[m]+graph[m][l];
    pvalue[l]=m+1;

    for(int i=0;i<heap[0];i++)
    {
    if(cvalue[i]==l)
    {
    heap[i+1]=sdist[l];
    heapifyu(i+1);
    break;
    }
    }
    }
}
}
return;
}


void DIJKS :: result(){                                            //Function To Print The Resultant Values

	for(int i=0;i<n;i++)
	{
		if(pvalue[i]==NULL)
            cout<<"For Vertex "<<i+1<<"   "<<source<<" --- "<<i+1<<" = "<<sdist[i]<<" Parent = "<<i+1<<endl;
        else
            cout<<"For Vertex "<<i+1<<"   "<<source<<" --- "<<i+1<<" = "<<sdist[i]<<" Parent = "<<pvalue[i]<<endl;
	}
	return;
}

int main(){

DIJKS ob;

}

