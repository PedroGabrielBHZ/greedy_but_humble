#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Job
{
    int start, finish;
};

bool finish_time_comparator(Job j1, Job j2)
{
    return (j1.finish < j2.finish);
}

void display_vector(vector<Job> j)
{
    for (int i = 0; i < j.size(); i++)
    {
        cout << "(" << j[i].start << ", " << j[i].finish << ")\n";
    }
    cout << endl;    
}

int main(int argc, char const *argv[])
{
    vector<Job> j;

    fstream iFile;
    iFile.open(argv[1]);
    if(!iFile)
    {
        cout << "Something went wrong, aborting!\n";
        exit(1);
    } else
    {
        while(!iFile.eof())
        {
            Job in_j;
            iFile >> in_j.start >> in_j.finish;
            j.push_back(in_j);
        }
    }
    
    display_vector(j);
    sort(j.begin(), j.end(), finish_time_comparator);
    display_vector(j);

    vector<Job> selected_jobs;
    selected_jobs.push_back(j[0]);
    int last_finishing_time = j[0].finish;

    for (int i = 0; i < j.size(); i++)
    {
        if(j[i].start > last_finishing_time)
        {
            selected_jobs.push_back(j[i]);
            last_finishing_time = j[i].finish;
        }
    }

    display_vector(selected_jobs);

    return 0;
}
