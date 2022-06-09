#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <map>

using std::stack;
using std::queue;
using std::map;
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;


bool check_mistake(const string&);

string del_space(const string&);//think about const string&

vector<char> take_all_var(string);

string postfix(string);

string to_binary(int, int);

vector <int> tab_truth(string);

int main()
{
    string line1, line2;
    cout << "First expression: ";
    std::getline(cin, line1);
    line1 = del_space(line1);
    cout << "Second expression: ";
    std::getline(cin, line2);
    line2 = del_space(line2);
    cout << endl;
    if (line1.size() == 0)
    {
        cout << "Null first string" << endl;
        return 0;
    }
    else if (line2.size() == 0)
    {
        cout << "Null second string" << endl;
        return 0;
    }

    if (!check_mistake(line1))
    {
        cout << "There is a mistake in the first expression" << endl;
        return 0;
    }
    else if (!check_mistake(line2))
    {
        cout << "There is a mistake in the second expression" << endl;
        return 0;
    }

    
    vector<int> result_1 = tab_truth(line1);
    vector<int> result_2 = tab_truth(line2);
    if (result_1 == result_2)
        cout << "Equality" << endl;
    else
        cout << "Not equality" << endl;

    return 0;
}

bool check_mistake(const string& line) {
    int count{ 0 };
    for (auto sym : line) {
        if (sym == '(')
            count++;
        else if (sym == ')')
            count--;
    }

    if (count)
        return false;
    
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == '(')
        {
            if (line[i + 1] == ')')
                return false;
            else if ((line[i + 1] == '+')||(line[i + 1] == '*'))
                return false;

        }
        else if (line[i] == ')')
        {
            if (line[i + 1] == '(')
                return false;
        }
        else if ((line[i] == '+') || (line[i] == '*') || (line[i] == '!'))
        {
            if ((i + 1 == line.size()) || (line[i + 1] == ')') ||
                (line[i + 1] == '+') || (line[i + 1] == '*'))
                return false;

            if ((line[i] != '!') && ((i == 0) || (line[i - 1] == '+') || (line[i - 1] == '*')))
                return false;

        }        

    }

    return true;
}

string del_space(const string& line)
{
    string res = "";
    for (auto sym : line)
        if ((sym != ' ')&&(sym != '\t'))
            res += sym;

    return res;
}

vector<char> take_all_var(string line)
{
    vector<char> dictionary;
    for (auto sym : line)
    {
        if ((sym < 'a') || (sym > 'z'))
            continue;

        
        if (std::count(dictionary.cbegin(), dictionary.cend(), sym) == 0)
            dictionary.push_back(sym);
    }

    return dictionary;
}

string postfix(string line) {
    string res = "";
    stack <char> st;
    queue <char> q;
    for (auto sym : line)
        if (sym == '(')
            st.push(sym);
        else if (sym == ')')
        {
            while (st.top() != '(')
            {
                res += st.top();
                st.pop();
            }

            st.pop();
        }
        else if (sym == '!')
        {
            while ((!st.empty()) && (st.top() == '!'))
            {
                res += st.top();
                st.pop();
            }

            st.push(sym);
        }
        else if (sym == '*')
        {
            while ((!st.empty()) && ((st.top() == '*') || (st.top() == '!')))
            {
                res += st.top();
                st.pop();
            }

            st.push(sym);
        }
        else if (sym == '+')
        {
            while ((!st.empty()) && ((st.top() == '+') || (st.top() == '*') || (st.top() == '!')))
            {
                res += st.top();
                st.pop();
            }

            st.push(sym);
        }
        else
            res += sym;
    
    while (!st.empty())
    {
        res += st.top();
        st.pop();
    }

    return res;
}

string to_binary(int count, int d_size)
{
    string res = "";
    while (count)
    {
        if (count % 2)
            res = '1' + res;
        else
            res = '0' + res;

        count /= 2;
    }

    while (res.size() < d_size)
    {
        res = '0' + res;
    }

    return res;
}

vector <int> tab_truth(string line)
{
    vector<char> dictionary;
    dictionary = take_all_var(line);
    line = postfix(line);

    vector<int> table;
    map<char, bool> dic_v2;
    string bin;
    bool var_1, var_2, var_3, res_1, res_2, p_res_1, p_res_2, p_var_1, p_var_2, p_var_3;
    int count = static_cast<int>(dictionary.size());
    for (int i = 0; i < pow(2,count); i++)
    {
        var_1 = false; var_2 = false; var_3 = false; res_1 = false; res_2 = false;
        p_res_1 = false; p_res_2 = false; p_var_1 = false; p_var_2 = false; p_var_3 = false;
        
        bin = to_binary(i, dictionary.size());
        
        for (int pos = 0; pos < dictionary.size(); pos++)
        {
            dic_v2[dictionary[pos]] = static_cast<bool>(bin[pos] - '0');
        }
       
        for (auto sym : line)
        {
            if ((sym != '*') && (sym != '+') && (sym != '!'))
            {
                if (!p_var_1)
                {
                    if ((sym == '0') || (sym == '1'))
                        var_1 = static_cast<bool>(sym - '0');
                    else
                        var_1 = dic_v2[sym];
                    
                    p_var_1 = true;
                }
                else if (!p_var_2)
                {
                    if ((sym == '0') || (sym == '1'))
                        var_2 = static_cast<bool>(sym - '0');
                    else
                        var_2 = dic_v2[sym];

                    p_var_2 = true;
                }
                else if (!p_var_3)
                {
                    var_3 = var_1;
                    if ((sym == '0') || (sym == '1'))
                        var_1 = static_cast<bool>(sym - '0');
                    else
                        var_1 = dic_v2[sym];

                    p_var_3 = true;
                }
            }
            else
            {
                if (sym == '!')
                {
                    if ((p_var_1)&&(!p_var_2))
                        var_1 = !var_1;
                    else if ((!p_res_1) && (!p_res_2))
                        var_2 = !var_2;
                    else if ((p_res_1)&&(!p_res_2))
                        res_1 = !res_1;
                    else
                        res_2 = !res_2;
                }
                else if (sym == '*')
                {
                    if (((!p_res_1) || (!p_var_2)) && (!p_res_2)) {
                        if (!p_var_2)
                        {
                            if (!p_var_3)
                                res_1 = res_1 && var_1;
                            else
                                res_1 = res_1 && var_3;

                        }
                        else
                            res_1 = var_1 && var_2;
                        
                        p_res_1 = true;
                    }
                    else if (!p_res_2) {
                        res_2 = var_1 && var_2;
                        p_res_2 = true;
                    }
                    else
                    {
                        res_1 = res_1 && res_2;
                        p_res_2 = false;
                    }

                    p_var_1 = false; p_var_2 = false;
                }
                else if (sym == '+')
                {
                    if (((!p_res_1) || (!p_var_2))&& (!p_res_2)) {
                        if (!p_var_2)
                        {
                            if (!p_var_3)
                                res_1 = res_1 || var_1;
                            else
                                res_1 = res_1 || var_3;
                        }
                        else
                            res_1 = var_1 || var_2;
                        
                        p_res_1 = true;
                    }
                    else if (!p_res_2) {
                        res_2 = var_1 || var_2;
                        p_res_2 = true;
                    }
                    else
                    {
                        res_1 = res_1 || res_2;
                        p_res_2 = false;
                    }

                    p_var_1 = false; p_var_2 = false;
                }
            }

        }

        dic_v2.clear();


        if (!p_res_1)
            res_1 = var_1;

        if (res_1)
            table.push_back(1);
        else
            table.push_back(0);
    }


    return table;
}