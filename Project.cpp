/*A scheduling program to implements a Queue with two levels:
Level 1 : Fixed priority preemptive Scheduling
Level 2 : Round Robin Scheduling
*/
#include <bits/stdc++.h> //header file that includes every standard library. This header file is used reduce the time of execution of the program
using namespace std;

struct Process_Data // Declaring a stucture to 
{
	int Number;
	int Process_id;    //Process Id
	int Arrival_time; //Process Arrival Time
	int Burst_time; //Process Brust Time
	int Priority; //Process' Priority
	int Finish_time; // Finish Time of process
	int Remaining_time; //Process Remaining  Time During Execution
	int Waiting_time; //Waiting Time
	int Start_time; //Process start Time
	int Res_time;

};

struct Process_Data current;
typedef struct Process_Data P_d ;
bool idsort(const P_d& x , const P_d& y)
{
	return x.Pid < y.Pid;
}
bool arrivalsort( const P_d& x ,const P_d& y)
{
	if(x.A_time < y.A_time)
		return true;
	else if(x.A_time > y.A_time)
		return false;
	if(x.Priority < y.Priority)
		return true;
	else if(x.Priority > y.Priority)
		return false;
	if(x.Pid < y.Pid)
		return true;

	return false;
}

bool Numsort( const P_d& x ,const P_d& y)
{
	return x.Num < y.Num;
}
/*Sorting on the base of Priority if that same then on the base of PID*/
struct comPare
{
	bool operator()(const P_d& x ,const P_d& y)
	{
		if( x.Priority > y.Priority )
			return true;
		else if( x.Priority < y.Priority )
			return false;
		if( x.Pid > y.Pid )
			return true;

		return false;
		
	}
	
};
/**To check the Input **/
void my_check(vector<P_d> mv)
{
	for(unsigned int i= 0; i < mv.size() ;i++)
	{
		cout<<" Pid :"<<mv[i].Pid<<" _time : "<<mv[i].A_time<<" B_time : "<<mv[i].B_time<<" Priority : "<<mv[i].Priority<<endl;
	}

}


int main()
{
	int i;
	vector< P_d > input;
	vector<P_d> input_copy;
	P_d temp;
	int pq_process = 0; // for PQ process
	int rq_process = 0; // for RQ process
	int A_time;
	int B_time;
	int Pid;
	int Priority;
	int n;
	int clock;
	int total_exection_time = 0;
	cin>>n;
	for( i= 0; i< n; i++ )
	{
		cin>>Pid>>A_time>>B_time>>Priority;
		temp.Num = i+1;
		temp.A_time = A_time;
		temp.B_time = B_time;
		temp.R_time = B_time;
		temp.Pid = Pid;
		temp.Priority = Priority;
		input.push_back(temp);
	}
	input_copy = input;
	sort( input.begin(), input.end(), arrivalsort );
    //cout<<"arrivalsort : "<<endl;
    //my_check( input ); // To check the sort unomment it
    total_exection_time = total_exection_time + input[0].A_time;
    for( i= 0 ;i< n; i++ )
    {
    	if( total_exection_time >= input[i].A_time )
    	{
    		total_exection_time = total_exection_time +input[i].B_time;
    	}
    	else
    	{
    		int diff = (input[i].A_time - total_exection_time);
    		total_exection_time = total_exection_time + diff + B_time;

    	}
    }

    
	



