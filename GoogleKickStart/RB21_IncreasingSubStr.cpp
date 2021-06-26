
#include <iostream>
#include <string>
using namespace std;

const int maxN = 10e5;


int rec_sub( int start_index, string str);
void printArray(int arr[], int n);

int main() {
/*
int test_cases;
cin >> test_cases;

for (int i = 0; i < test_cases; i++)
{
   int str_len;
   cin >> str_len;
   //function that re
}
*/
  int test_cases, str_len;
  string test_string;
  int sub_counts [maxN];
  //string test_string = "ABACDA";
  //int str_len = test_string.length();

  cin >> test_cases;

  for( int t=1; t <=test_cases; t++)
  {
    cin >> str_len;
    cin >> test_string;
    for (int i = 0; i < str_len; i++)
    {
      int count = 0;
      count = rec_sub(i, test_string);
      sub_counts[i]= count;
      //use vector to append
    }
    cout << "Case #" << t << ": ";
    printArray(sub_counts, str_len);
  }
  return 0;
}

int rec_sub( int start_index, string str) //faster way with less looping?
{
    if (start_index == 0)
    {
      return 1;
    }
    else if (str[start_index -1] < str[start_index])
    {

      return rec_sub(start_index-1, str)+1;
    }
    else {
        return 1;
    }
}

void printArray(int arr[], int n)

/* n is size here*/

{
    for (int i = 0; i < n; i++)

        cout << arr[i] << " ";
    }
