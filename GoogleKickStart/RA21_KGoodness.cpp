#include<iostream>
#include<string>
using namespace std;

int main()
{
    int test_cases;
    cin >> test_cases;

    for (int casenumber = 1; casenumber<= test_cases; casenumber++)
    {
        int n, k; //n length, goal k goodness score
        string s;
        cin >> n >> k >> s;
        int N = n-1;
        int score = 0;
        for(int i = 0; i< (N/2); i++)
        {
            cout << s[i] << s[N-i+1] << endl;
            if (s[i] != s[N-i+1])
            {
                score++;
            }
        }
        int operations = k - score;
    cout << score <<endl;
    cout << "Case #" << casenumber << ": " << operations;
    }

    return 0;
}
