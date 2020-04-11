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

bool idsort(const P_d& a , const P_d& b)
{
	return a.Process_id < b.Process_id;
}
/* Sorting is on the base of arrival time if that match then on Priority order of Priority, also  match than on the base of Process Id*/
bool arrivalsort( const P_d& a ,const P_d& b) // Function to sort the the process at arrival
{
	if(a.Arrival_time < b.Arrival_time)
		return true;
	else if(a.Arrival_time > b.Arrival_time)
		return false;
	if(a.Priority < b.Priority)
		return true;
	else if(a.Priority > b.Priority)
		return false;
	if(a.Process_id < b.Process_id)
		return true;

	return false;
}


bool Numsort( const P_d& a ,const P_d& b)
{
	return a.Number < b.Number;
}
/*Sorting on the base of Priority if that same then on the base of PID*/
struct comPare
{
	bool operator()(const P_d& a ,const P_d& b)
	{
		if( a.Priority > b.Priority )
			return true;
		else if( a.Priority < b.Priority )
			return false;
		if( a.Process_id > b.Process_id )
			return true;

		return false;
		
	}
	
};

/*To check the Input */
void my_check(vector<P_d> mv)
{
	for(unsigned int i= 0; i < mv.size() ;i++)
	{
		cout<<" Process ID:"<<mv[i].Process_id<<" Arrival time : "<<mv[i].Arrival_time<<" Burst time: "<<mv[i].Burst_time<<" Priority: "<<mv[i].Priority<<endl;
	}

}

int main()
{
	int i;
	vector< P_d > input;
	vector<P_d> input_copy;
	P_d temp;
	int pq_process = 0; // for Fixed Priority Preempetive Schedulling  process
	int rq_process = 0; // for Round Robin process
	int Arrival_time;
	int Burst_time;
	int Process_id;
	int Priority;
	int n; // number of processes(or the test cases)
	int Clock;
	int total_execution_time = 0;
	cout<<"Enter the number of cases which you wish to execute using this algorithm:";
	cin>>n;
	for( i= 0; i< n; i++ )
	{
		cin>>Process_id>>Arrival_time>>Burst_time>>Priority;
		temp.Number = i+1;
		temp.Arrival_time = Arrival_time;
		temp.Burst_time = Burst_time;
		temp.Remaining_time = Burst_time;
		temp.Process_id = Process_id;
		temp.Priority = Priority;
		input.push_back(temp);
	}
	input_copy = input;
	sort( input.begin(), input.end(), arrivalsort );
    //cout<<"arrivalsort : "<<endl;
    //my_check( input ); // To check the sort unomment it
    total_execution_time = total_execution_time + input[0].Arrival_time;
    for( i= 0 ;i< n; i++ )
    {
    	if( total_execution_time >= input[i].Arrival_time )
    	{
    		total_execution_time = total_execution_time +input[i].Burst_time;
    	}
    	else
    	{
    		int diff = (input[i].Arrival_time - total_execution_time);
    		total_execution_time = total_execution_time + diff + Burst_time;
    	}
    }

	int Ghant[total_execution_time]={0}; //Ghant Chart
	for( i= 0; i< total_execution_time; i++ )
	{
		Ghant[i]=-1;
	}
	//cout<<"total_exection_time : "<<total_exection_time<<endl;

	priority_queue < P_d ,vector<Process_Data> ,comPare> pq; //Priority Queue PQ

	
	queue< P_d > rq; //Round Robin Queue RQ
	int cpu_state = 0; //idle if 0 then Idle if 1 the Busy
	int quantum = 4 ; //Time Quantum
	current.Process_id = -2;
	current.Priority = 999999;

	for ( Clock = 0; Clock< total_execution_time; Clock++ )
	{
		/**Insert the process with same Arrival time in Priority Queue**/
		for( int j = 0; j< n ; j++ )
		{
			if(Clock == input[j].Arrival_time)
			{
				pq.push(input[j]);
			}
		}
		

		if(cpu_state == 0) //If CPU idle
		{
			if(!pq.empty())
			{
				current = pq.top();
				cpu_state = 1;
				pq_process = 1;
				pq.pop();
				quantum = 4; 
			}
			else if(!rq.empty())
			{
				current = rq.front();
				cpu_state = 1;
				rq_process = 1;
				rq.pop();
				quantum = 4;
			}
		}
		else if(cpu_state == 1) //If cpu has any procss
		{
			if(pq_process == 1 && (!pq.empty()))
			{
				if(pq.top().Priority < current.Priority ) //If new process has high priority
				{
					rq.push(current); //push current in RQ
					current = pq.top();
					pq.pop();
					quantum = 4; 
				}
			}
			else if(rq_process == 1 && (!pq.empty())) //If process is from RQ and new process come  in PQ
			{
				rq.push(current);
				current = pq.top();
				pq.pop();
				rq_process = 0;
				pq_process = 1;
				quantum = 4 ;
			}
			

		}


		if(current.Process_id != -2) // Process Execution
		{
			current.Remaining_time--;
			quantum--;
			Ghant[Clock] = current.Process_id;
			if(current.Remaining_time == 0) //If process Finish
			{
				cpu_state = 0 ;
				quantum = 4 ;
				current.Process_id = -2;
				current.Priority = 999999;
				rq_process = 0;
				pq_process = 0;
			}
			else if(quantum == 0 ) //If time Qunatum of a current running process Finish
			{
				rq.push(current);
				current.Process_id = -2;
				current.Priority = 999999;
				rq_process = 0;
				pq_process = 0;
				cpu_state=0;

			}

		}
		
	}


	sort( input.begin(), input.end(), idsort );
	
	for(int i=0;i<n;i++)
	{
		for(int k=total_execution_time;k>=0;k--)
		{
			if(Ghant[k]==i+1)
			{
				input[i].Finish_time=k+1;
				break;

			}
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int k=0;k<total_execution_time;k++)
		{

			if(Ghant[k]==i+1)
			{
				input[i].Start_time=k;
				break;
			}
		}
	}
	
	sort( input.begin(), input.end(), Numsort );

	for(int i=0;i<n;i++)
	{
		input[i].Res_time=input[i].Start_time-input[i].Arrival_time;
		input[i].Waiting_time=(input[i].Finish_time-input[i].Arrival_time)-input[i].Burst_time;

	}
	
	for(int i=0;i<n;i++)
	{
		cout<<input[i].Process_id<<" "<<input[i].Res_time<<" "<<input[i].Finish_time<<" "<<input[i].Waiting_time<<endl;
		
	}	
	return 0;
}


