#include <iostream>
#include<vector>
#define number_of_process 9
#include<stdlib.h>
#include<iomanip>
#define lower 2
#define upper 7
using namespace std;
double total_wait_time,total_turnaround_time,total_completion_time;
vector<int>temp_burst(9);
struct process
{
    int pid;
    int arrival;
    int burst;
    int priority;
    int completion_time;
    int turn_around_time;
    int waiting_time;
};
void initialize_process(struct process p[], long long rollno)
{
    int count=0;
    long long temp=rollno;
    while(temp)
    {

        p[count].pid=count+1;
        p[count].priority=temp%10;
        p[8-count].arrival=temp%10;
        p[count].burst=(rand()%(upper-lower+1))+lower;
        temp_burst[count]=p[count].burst;
        temp=temp/10;
        count++;
    }
}

void sort_process(struct process p[])
{
    int k=0;
    for(int i=0;i<=9;i++)
    {
        for(int j=0;j<number_of_process;j++)
        {
            if(p[j].arrival==i)
            {
                struct process temp=p[j];
                p[j]=p[k];
                p[k]=temp;
                k++;
            }
        }
    }
}
void print(struct process p[])
{
    cout<<"PID"<<setw(4)<<"AT"<<setw(5)<<"Prio"<<setw(5)<<"BT"<<setw(5)<<"CT"<<setw(5)<<"TAT"<<setw(5)<<"WT"<<endl;
    for(int i=1;i<=9;i++)
    {
        for(int j=0;j<number_of_process;j++)
            if(p[j].pid==i)
                cout<<p[j].pid<<setw(5)<<p[j].arrival<<setw(5)<<p[j].priority<<setw(5)<<temp_burst[j]<<setw(5)<<p[j].completion_time<<setw(5)<<p[j].turn_around_time<<setw(5)<<p[j].waiting_time<<endl;
    }
}
void schedule(struct process p[],vector<pair<int,int> >&gant_chart)
{
    int counter=0,complete=0,mx=-1,idx=-1;
    vector<int>complition_time(9,0);
    vector<int>turn_around_time(9,0);
    vector<int>waiting_time(9,0);
    while(complete!=9)
    {
        mx=-1;

        for(int i=0;i<number_of_process;i++)
        {
            if(p[i].arrival<=counter and p[i].priority>mx and p[i].burst>0)
            {
                mx=p[i].priority;
                idx=i;
            }
        }
        p[idx].burst--;
        gant_chart.push_back(make_pair(counter,p[idx].pid));
        if(p[idx].burst==0)
        {complete++;p[idx].completion_time=counter+1; p[idx].turn_around_time=p[idx].completion_time-p[idx].arrival;
            p[idx].waiting_time=p[idx].turn_around_time-temp_burst[idx];

            total_completion_time+=p[idx].completion_time;
            total_turnaround_time+=p[idx].turn_around_time;
            total_wait_time+=p[idx].waiting_time;
        }
        counter++;

    }


}
void print_gant(vector<pair<int,int> >gant_chart)
{
    cout<<endl;
    for(int i=0;i<gant_chart.size();i++)
    {
        cout<<"----";
    }
    cout<<endl;
    cout<<"| ";
    for(int i=0;i<gant_chart.size();i++)
    {
        cout<<gant_chart[i].second<<" | ";
    }
    cout<<endl;
    for(int i=0;i<gant_chart.size();i++)
    {
        cout<<"----";
    }
    cout<<endl;
    for(int i=0;i<gant_chart.size();i++)
    {
        if(gant_chart[i].first<9)
        cout<<gant_chart[i].first<<"   ";
        else
            cout<<gant_chart[i].first<<"  ";
    }
    cout<<gant_chart[gant_chart.size()-1].first+1;
}
void header()
{
    cout<<"CS558 : COMPUTER SYSTEM LAB ASSIGNMENT - 04\n";
    cout<<"Instructor : Dr. Manas Khatua and Dr. Moumita Patra\n";
    cout<<"TA's : Alakesh Kalita, Arunav Saikia, Meenu Rani Dey, Priya Undriwade, Vinay Kumar Gupta\n";
    cout<<"Sumbittted By : Himanshu Patel(204101029), Ketan Karnakota(204101030)\n";
}
int main() {
    header();

    cout<<"Premptive Priority Scheduling\n";
    cout<<"**Note : highest numbers are treated as high priority. for example : priority(7) > priority(2)\n";
    cout<<"----------------------------------------------------------------------------------------------\n";
    cout<<"Enter Roll No :";
    long long rollno;
    cin>>rollno;
    struct process p[number_of_process];
    vector<pair<int,int> >gant_chart;
    vector<int>temp_burst(9);
    initialize_process(p,rollno);

    //print(p);
    cout<<endl<<endl;
    //sort_process(p);
    //print(p);

    schedule(p,gant_chart);
    cout<<endl<<endl;
    print(p);

    cout<<"\n\nGant Chart : ";
    print_gant(gant_chart);
    cout<<endl<<endl;
    cout<<"Average  Waiting   Time : "<<total_wait_time/9<<endl;
    cout<<"Average TurnAround Time : "<<total_turnaround_time/9<<endl;
    cout<<"Average Completion Time : "<<total_completion_time/9<<endl;
    return 0;
}