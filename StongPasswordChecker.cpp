#include <iostream>
using namespace std;

#define MINLENGTH 6
#define MAXLENGTH 20

/// I consider that the 'insertion' operation inserts a specific character (can be digit, lowercase letter, uppercase letter) and not a random character
/// WHAT IF PASSWORD CONTAINS SPECIAL CHARACTERS? -> need to delete them -> needs to be implemented (I have not implemented this function due to shortness of time availability)
bool containsUppercase(string s)
{
    for(char c : s)
        if(isupper(c))
            return 1;
    return 0;
}

bool containsLowercase(string s)
{
    for(char c : s)
        if(islower(c))
            return 1;
    return 0;
}

bool containsDigit(string s)
{
    for(char c : s)
        if(isdigit(c))
            return 1;
    return 0;
}

int maxim(int a, int b)
{
    if(a > b)
        return a;
    return b;
}

int maxim(int a, int b, int c)
{
    int maximum = c;
    if (a > maximum)
        maximum = a;
    if (b > maximum)
        maximum = b;

    return maximum;
}

int maxim(int a, int b, int c, int d)
{
    return maxim(maxim(a, b), maxim(c, d));
}

int minim(int a, int b)
{
    if(a < b)
        return a;
    return b;
}

int consecutiveCharacters(string s)
{
    // this function checks how many characters need to be changed due to consecutive characters
    // I took into consideration
    int changes = 0; //represents the total number of changes and is returned by function
    int consecutive = 1; // represents how many consecutive characters are there of one type (aaa)
    char currentChar = s[0];
    for(int i = 1; i < s.length(); i++)
    {
        if(s[i] == currentChar)
            consecutive++;
        else
        {
            if(consecutive >= 3)
                changes = changes + consecutive/3;
            // I noticed that the total number of changes needed to be made depends on the number of consecutive characters of one type
            // the formula is total_number_of_consecutive_chars / 3
            // I considered as different types of consecutive characters ex. bbb, aaaa, cccccc, 1111, AAAAAAAAA, ......
            consecutive = 1;
            currentChar = s[i];
        }
    }
    return changes;
}

int strongPasswordChecker(string s)
{
    int characterChange = 0; // in this variable we store the changes needed to have all 3 types of characters(digit, uppercase, lowercase)
    int lengthShortChange = 0;  // in this variable we store the changes needed if the string is too short
    int lengthLongChange = 0;  // in this variable we store the changes needed if the string is too long
    int consecutiveChange = consecutiveCharacters(s); // in this variable we store the changes needed if we have consecutive characters
    int finalChange = 0; // in this variable we store the final changes needed to meet all conditions

    if(!containsDigit(s))
        characterChange++;
    if(!containsLowercase(s))
        characterChange++;
    if(!containsUppercase(s))
        characterChange++;
    if(s.length() < MINLENGTH)
            lengthShortChange = MINLENGTH - s.length();
    if(s.length() > MAXLENGTH)
        lengthLongChange = s.length() - MAXLENGTH;
    finalChange = maxim(characterChange, lengthShortChange, lengthLongChange, consecutiveChange);
    return finalChange;
}

int main()
{

    /// TESTING THE APPLICATION
    /*
    string passwords[50] = {"a",  "A", "1", "Aa", "A1", "1a", "Aa1", "AaAa11", "AAaa11", "abcabcA1", "abcabc", "ABCABC", "ABCabc",
                            "111ABCA", "abcabcabcabcabcabcabc", "ABCabcabcabcabcabcabc", "111abcabcabcabcabcabc", "caaat1",
                            "caaatt", "caa2aat", "caaat", "caata", "aaaabbbbbbaaaC1", "aaabbbccccdddeeaaabbbbbccc",
                            "ABCaaaaaaaABC1ABC23bbbbbbbbb",  "aaabbaaaabbbaaabbbabaabbbbbbbaaaaaabb1", "bbbbbbPPPPPPP34ccc"};
    int answers[50] = {5,5,5,4,4,4,3,0,0,0,2,2,1,1,3,2,2,1,2,1,2,2,4,6};
    for(int i = 0; i < 27; i++)
    {
        //if(strongPasswordChecker(passwords[i]) != answers[i]) //if this row uncommented -> displays only the wrong answers returned by function
            cout << passwords[i] << " -> " << strongPasswordChecker(passwords[i]) << endl;
    }
    */

    /// Main menu of application for input
    string s = "";
    cout << "Type the password: "; cin >> s;

    int nr = strongPasswordChecker(s);
    if (nr == 0)
        cout << "The entered password is already strong!";
    else
        cout << "The minimum number of changes required to make s a strong password is: " << nr;

    return 0;
}
