#include <iostream>
#include <unordered_set>

using namespace std;

class nestedObject
{
private:
    string value;
    unordered_set<string> keys;
public:
    void helper(string &str)
    {
        int i = 0;

        //Iterate string until we find closing bracket
        while(i < str.size() && str[i] != '}')
        {
            //If we come across open bracket, then that beginning of key. Extract the key
            if(str[i] == '{')
            {
                i++;
                string curr = "";

                //Key is until we find :
                while(i < str.size() && str[i] != ':' && str[i] != '}')
                    curr += str[i++];

                //Store the key in the set
                keys.insert(curr);
            }
            else if(str[i] == ':')
            {
                //If next character is open bracket, move onto next character, since its nested key
                if(str[i+1] == '{')
                    i++;
                //Else we have a value. extract it
                else
                {
                    i++;
                    string curr = "";
                    while(i < str.size() && str[i] != '}')
                        curr += str[i++];
                    
                    value = curr;
                }
            }
        }
    }

    nestedObject(string str)
    {
        helper(str);
    }

    string getValue(string key)
    {
        return (keys.find(key) != keys.end()) ? value : "";
    }
};

int main()
{
    //Case 1: nested object with d as its value
    nestedObject *input1 = new nestedObject("{a:{b:{c:d}}}");
    //Case 2: Similar to case 1
    nestedObject *input2 = new nestedObject("{Google:{Facebook:{Microsoft:{Intel:Companies}}}}");
    //Case3: Empty object
    nestedObject *input3 = new nestedObject("");
    //Case4: Empty info inside the object
    nestedObject *input4 = new nestedObject("{}");
    //Case5: Empty value.
    nestedObject *input5 = new nestedObject("{a:{b:{c:{d:}}}}");

    cout << "key: c" << ", output1: " << input1->getValue("c") << endl;
    cout << "key: z" << ", output1: " << input1->getValue("z") << endl << endl;

    cout << "key: Google" << ", output2: " << input2->getValue("Google") << endl;
    cout << "key: a" << ", output2: " << input2->getValue("a") << endl << endl;

    cout << "key: a" << ", output3: " << input3->getValue("a") << endl << endl;

    cout << "key: b" << ", output4: " << input4->getValue("b") << endl << endl;

    cout << "key: a" << ", output5: " << input5->getValue("a") << endl << endl;

    delete(input1); delete(input2);
    delete(input3); delete(input4);
    delete(input5);

    return 0;
}



/*
Reading the description, it looks like we have a key value pair. The key is a string and value can be a string or another nested object.
I am considering entire object as a string for simplicity.

Assumption:
We have an input that is consistent with below format:
* The object always starts with '{'
* key always follows '{' and ends before ':'
* value or nested object follows after ':'

Any inputs that are not consistent with above format may give unexpected results.

Solution:
1) We start iterating the string and whenever we come across '{', we treat it as a new object and extract the key.
2) When we come across ':', the string following it is the value.
3) If they key that we look for does not exist in the object, we return empty string as our default value.

Time complexity: 
Initialization of the object: O(N), where N is length of the string. This is because we are iterating the entire string once.
getValue(): O(1). This is because searching in unordered_set is amortized constant.

Space complexity: O(N), where N is the length of the string. This is because we are storing key and value.
*/