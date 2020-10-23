#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>

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

void generate_file_with_n_random_pairs_lq_r(string filepath, int n, int r)
{
    ofstream iFile;

    iFile.open(filepath);
    if(!iFile)
    {
        cout << "Something went wrong, aborting!\n";
        exit(1);
    } else
    {
        for (int i = 0; i < n; i++)
        {
            int rd1(rand()%r), rd2(rd1 + rand()%r);
            iFile << rd1 << " " << rd2 << endl;
        }
    }
    iFile.close();
}

void read_jobs_from_file_to_vector(string filepath, vector<Job> &j)
{
    fstream iFile;
    
    iFile.open(filepath);

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

    iFile.close();
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    vector<Job> j;
    int n;

    cout << "Enter number of jobs: ";
    cin >> n;

    generate_file_with_n_random_pairs_lq_r("temp.txt", n , n);
    read_jobs_from_file_to_vector("temp.txt", j);
    
    sort(j.begin(), j.end(), finish_time_comparator);

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

    float a = static_cast<float>(j.size()) - 1;
    float b = static_cast<float>(selected_jobs.size());


    cout << "From a total of " << a << " requests, "
         << b << " were accepted.\n" 
         << "That's around " << ((b/a)*100)
         << "% of the requests.\n";

    remove("temp.txt");

    return 0;
}
