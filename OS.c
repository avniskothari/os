#include<stdio.h>
int arrival_time1[30],arrival_time2[30],priority2[30],process2[30],arrival_time3[30];
int burst_time1[30],burst_time2[30],burst_time3[30];

int Total=0,t1=0,t2=0,t3=0;

int n,i,at[30],bt[30],pr[30],j=0,k=0,l=0;

int total,x,temp[30],counter=0;
float avg_waiting_time1=0.0,avg_turnaround_time1=0.0;

int p,waiting_time3[30],turnaround_time3[30];
float avg_waiting_time3=0.0,avg_turnaround_time3=0.0;

int position,q,temp1,sum=0,waiting_time2[30],turnaround_time2[30];
float avg_waiting_time2,avg_turnaround_time2;

void round_robin_all();
void round_robin();
void priority();
void fcfs();


int main()
{
	printf("Enter Total Number of Process : ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("\n\n+------  Process[%d]  ---->\n",i+1);
		printf("|\tArrival Time :\t");
		scanf("%d",&at[i]);
		printf("|\tBurst Time :\t");
		scanf("%d",&bt[i]);
		printf("|\tPriority [1 - 30] :\t");
		scanf("%d",&pr[i]);
		Total=Total+bt[i];
		printf("|\n");
	}
	printf("+--------------------------->\n\n");

	for(i=0;i<n;i++)
	{
		if(pr[i]>=1&&pr[i]<=10)
		{
			printf("Process[%d] belongs to Queue 1\n",i+1);
			arrival_time1[j]=at[i];
			burst_time1[j]=bt[i];
			j++;
			t1=t1+bt[i];
		}

		else if(pr[i]>=11&&pr[i]<=20)
		{
			printf("Process[%d] belongs to Queue 2\n",i+1);
			arrival_time2[k]=at[i];
			burst_time2[k]=bt[i];
			priority2[k]=pr[i];
			process2[k]=k+1;
			k++;
			t2=t2+bt[i];
		}

		else if(pr[i]>=21&&pr[i]<=30)
		{
			printf("Process[%d] belongs to Queue 3\n",i+1);
			arrival_time3[l]=at[i];
			burst_time3[l]=bt[i];
			l++;
			t3=t3+bt[i];
		}
	}
    printf("\n\n");
	round_robin_all();
	round_robin();
	priority();
	fcfs();

	return 0;
}

//Round robin for all d queue for quantum time 10

void round_robin_all()
{


    printf("+---------------------------------------------\n");
    printf("|\t\tROUND ROBIN FOR ALL\n");
    printf("+---------------------------------------------\n|\n");
	printf("|\tTime Quantum between the 3 queues is 10\n");
	for(i=1;i<Total;i=i+10)
	{
		if(t1>10)
		{
			printf("|\tQueue1 is running for 10 units\n");
			t1=t1-10;
		}
		else if(t1<=10&&t1!=0)
		{
			printf("|\tQueue1 is running for %d units\n",t1);
			t1=0;
		}
		if(t2>10)
		{
			printf("|\tQueue2 is running for 10 units\n");
			t2=t2-10;
		}
		else if(t2<=10&&t2!=0)
		{
			printf("|\tQueue2 is running for %d units\n",t2);
			t2=0;
		}
		if(t3>10)
		{
			printf("|\tQueue3 is running for 10 units\n");
			t3=t3-10;
		}
		else if(t3<=10&&t3!=0)
		{
			printf("|\tQueue3 is running for %d units\n",t3);
			t3=0;
		}
	}
    printf("+---------------------------------------------\n\n\n");

}

// Round Robin for queue 1 for having highest priority

void round_robin()
{
    if(j==0){
        return;
    }
	printf("\n\nTime Quantum for Queue1 is 4\n");
	for(i=0;i<j;i++)
	{
		temp[i]=burst_time1[i];
	}

    printf("+---------------------------------------------\n");
    printf("|\t\tROUND ROBIN FOR QUEUE 1\n");
    printf("+---------------------------------------------\n|\n");
	printf("|\n\tProcess ID\tBurst Time\t Turnaround Time\t Waiting Time\n");
	x=j;

	arrival_time1[0]=0;

    for(i=0,total=0;x>0;)
    {
    	if(temp[i]<=4&&temp[i]>0)
        {
            total=total+temp[i];
            temp[i]=0;
            counter=1;
        }
        else if(temp[i]>0)
        {
            temp[i]=temp[i]-4;
            total=total+4;
        }
        if(temp[i]==0&&counter==1)
        {
            x--;
            int wt_time = total-arrival_time1[i]-burst_time1[i];
            if(wt_time<0){
            	wt_time=0;
			}
            printf("\n|\tProcess[%d]\t\t%d\t\t%d\t\t%d",i+1,burst_time1[i],total-arrival_time1[i],wt_time);
            avg_waiting_time1=avg_waiting_time1+total-arrival_time1[i]-burst_time1[i];
            avg_turnaround_time1=avg_turnaround_time1+total-arrival_time1[i];
            counter = 0;
        }
        if(i==j-1)
        {
            i=0;
        }
        else if(arrival_time1[i+1]<=total)
        {
            i++;
        }
        else
        {
            i=0;
        }

    }

    avg_waiting_time1=avg_waiting_time1/j;
    avg_turnaround_time1=avg_turnaround_time1/j;
    printf("\n\n|\tAverage Waiting Time:%f",avg_waiting_time1);
    printf("\n|\tAverage Turnaround Time:%f\n\n",avg_turnaround_time1);
    printf("+---------------------------------------------\n\n\n");
}

// Priority for queue 2 for having average priority

void priority()
{
	if(k==0){
		return;
	}
	for(i=0;i<k;i++)
    {
        position=i;
        for(q=i+1;q<k;q++)
        {
            if(priority2[q]<priority2[position])
            {
                position=q;
            }
        }
        temp1=priority2[i];
        priority2[i]=priority2[position];
        priority2[position]=temp1;

        temp1=burst_time2[i];
        burst_time2[i]=burst_time2[position];
        burst_time2[position]=temp1;

        temp1=process2[i];
        process2[i]=process2[position];
        process2[position]=temp1;
    }
    waiting_time2[0]=0;
    for(i=1;i<k;i++)
    {
        for(q=0;q<i;q++)
        {
            waiting_time2[i]=waiting_time2[i]+burst_time2[j];
        }
    }
    avg_waiting_time2=sum/k;
    sum=0;
    float wt_sum=0;
    printf("+---------------------------------------------\n");
    printf("|\t\tPRIORITY FOR QUEUE 2\n");
    printf("+---------------------------------------------\n|\n");
	printf("|\n\tProcess ID\tBurst Time\t Turnaround Time\t Waiting Time\n");
    for(i=0;i<k;i++)
    {
        if(i!=0){
            waiting_time2[i]+=1;
        }
    	turnaround_time2[i]=burst_time2[i]+waiting_time2[i];
        sum=sum+turnaround_time2[i];
        wt_sum += waiting_time2[i];
        printf("\n|\tProcess[%d]\t\t%d\t\t %d\t\t %d\n",process2[i],burst_time2[i],waiting_time2[i],turnaround_time2[i]);
    }
    avg_turnaround_time2=(1.0*sum)/k;
    printf("\n|\tAverage Waiting Time:\t %f",wt_sum/k);
    printf("\n|\tAverage Turnaround Time:\t %f\n",avg_turnaround_time2);
    printf("+---------------------------------------------\n|\n|");

    for(i=0;i<k;i++)
    {
    	while(burst_time2[i]!=0)
    	{
    		if(burst_time2[i]>10)
    		{
				printf("\n|\tProcess[%d] of Queue2 is running for 10 units\n|",i+1);
				burst_time2[i]=burst_time2[i]-10;
			}
			else if(burst_time2[i]<=10)
			{
				printf("\n|\tProcess[%d] of Queue2 is running for %d units\n|",i+1,burst_time2[i]);
				burst_time2[i]=0;
			}
		}
	}
    printf("\n+---------------------------------------------\n\n\n");

}

// First Come First Serve for queue 3 for having lowest priority

void fcfs()
{
	if(l==0){
		return;
	}
	waiting_time3[0] = 0;
    for(i=1;i<l;i++)
    {
        waiting_time3[i] = 0;
        for(p=0;p<l;p++)
        {
            waiting_time3[i]=waiting_time3[i]+burst_time3[p];
        }
    }
    printf("\n\n+---------------------------------------------");
    printf("\n|\tFCFS FOR QUEUE 3");
    printf("\n+---------------------------------------------");
    printf("\n\tProcess\t\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("\n+---------------------------------------------");
    for(i=0;i<l;i++)
    {
        turnaround_time3[i]=burst_time3[i]+waiting_time3[i];
        avg_waiting_time3=avg_waiting_time3+waiting_time3[i];
        avg_turnaround_time3=avg_turnaround_time3+turnaround_time3[i];
        printf("\n|\tProcess[%d]\t\t%d\t\t%d\t\t%d\n",i+1,burst_time3[i],waiting_time3[i],turnaround_time3[i]);
    }
    avg_waiting_time3=avg_waiting_time3/l;
    avg_turnaround_time3=avg_turnaround_time3/l;
    printf("\n+---------------------------------------------");
    printf("\n|\tAverage Waiting Time=%f",avg_waiting_time3);
    printf("\n|\tAverage Turnaround Time=%f",avg_turnaround_time3);
    printf("\n+---------------------------------------------\n|");
    for(i=0;i<l;i++)
    {
    	while(burst_time3[i]!=0)
    	{
    		if(burst_time3[i]>10)
    		{
				printf("\n|\tProcess[%d] of Queue3 is running for 10 units",i+1);
				burst_time3[i]=burst_time3[i]-10;
			}
			else if(burst_time3[i]<=10)
			{
				printf("\n|\tProcess[%d] of Queue3 is running for %d units",i+1,burst_time3[i]);
				burst_time3[i]=0;
			}
		}
	}
    printf("\n+---------------------------------------------\n\n\n");
}

