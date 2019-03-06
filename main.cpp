#include<iostream>
#include<vector>
#include<string>
using namespace std;
// Global Values -------------------------------------------------------------------------------------------------------
vector <string> variables;
vector <int> varValues;

// Enums ---------------------------------------------------------------------------------------------------------------
enum Operation {
    PLUS = 0,
    MINUS = 1
};

// Functions -----------------------------------------------------------------------------------------------------------
int is_known_variable(string key) {
    for (int i = 0;i < variables.size();i++) {
        if (variables[i] == key) {
            return true;
        }
    }
    return false;
}

int return_number(string s) {
    for (int i = 0;i < variables.size();i++) {
        if (variables[i] == s) {
            return varValues[i];
        }
    }
    return 0;
}

int findEqualSign (vector <string> s) {
    for (int i = 0;i < s.size();i++) {
        if (s[i] == "=" || s[i] == ":") {
            return i;
        }
    }
    return -1;
}

int evaluateString (string input) {
    input.push_back(' ');

    vector<string> elements;

    string temp;
    for(string::iterator it = input.begin(); it != input.end(); ++it) {
        if (not isspace(*it)) {
            temp.push_back(*it);
        }else {
            if (temp != "") {
                elements.push_back(temp);
                temp = "";
            }
        }
    }
    for (vector <string>::iterator it = elements.begin();it != elements.end();++it){
        cout << *it << ' ';
    }
    cout << endl;
//    variables.push_back("x");
//    varValues.push_back(56);
    int result = 0;
    Operation operation = PLUS;
    bool wait_for_number = true, error = false;
    int evalStartIndex = findEqualSign(elements);
    if (evalStartIndex > 0) {
        variables.push_back(elements[0]);
    }
    for ( vector <string>::iterator it = elements.begin() + 1 + evalStartIndex; it != elements.end(); ++it ) {
        bool is_number = true;
        for ( string::iterator cit = it->begin(); cit != it->end(); ++cit)
            if (not isdigit(*cit))
                is_number = false;
        if ((*it).length() >= 2)
            is_number = true;

        if (is_number) {
            if (wait_for_number) {
                if (operation == PLUS) {
                    result += atoi(it->c_str());
                    wait_for_number = false;
                } else if (operation == MINUS){
                    result -= atoi(it->c_str());
                    wait_for_number = false;
                }
            } else {
                cout << "ERROR" << endl;
                return -1;
            }
        } else if (is_known_variable(*it)) {
            if (operation == PLUS) {
                result += return_number(*it);
                wait_for_number = false;
            } else if (operation == MINUS){
                result -= return_number(*it);
                wait_for_number = false;
            }
        }
        else {
            if (wait_for_number) {
                cout << "ERROR" << endl;
                return -1;
            } else {
                if ((*it) == "+"){
                    operation = PLUS;
                    wait_for_number = true;
                } else if ((*it) == "-"){
                    operation = MINUS;
                    wait_for_number = true;
                } else {
                    cout << "ERROR" << endl;
                    return -1;
                }
            }
        }
    }
    if (evalStartIndex > 0) {
        varValues.push_back(result);
    }
    return result;
}
// Main Program --------------------------------------------------------------------------------------------------------
int main(){
	string input;
	int n;
	cout << "how many lines would you like ?";
	cin >> n;
	getline(cin, input);
	for (int i = 0;i < n;i++) {
	    cout << i+1 << ": ";
	    getline(cin, input);
	    cout << evaluateString(input) <<endl;
	}
//	getline(cin, input);
//	cout << evaluateString(input);
}
