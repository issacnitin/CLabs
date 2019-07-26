#include <bits/stdc++.h>

using namespace std;

stack<string> callStack;
stack<float> latitudeStack;
stack<float> longitudeStack;
stack<string> nameStack;

vector<string> split(string s, char delimiter) {
    vector<string> result;
    string tempString = "";

    bool insideOpenQuotes = false;
    for(int i = 0; i < s.length(); i++) {
        if(s[i] == '"') insideOpenQuotes = !insideOpenQuotes;
        if(!insideOpenQuotes && s[i] == delimiter) {
            if(tempString.length() > 0) {
                result.push_back(tempString);
            }
            tempString = "";
        } else {
            tempString += s[i];
        }   
    }

    if(tempString.length() > 0) {
        result.push_back(tempString);
    }

    return result;
}

vector<string> extractAttributes(string s) {
    string y = s.substr(1, s.length() - 2);
    vector<string> attributes = split(y, ' ');
    return attributes;
}

string getValue(string s) {
    string result = "";
    bool openQuotes = false;
    
    for(int i = 0; i < s.length(); i++) {
        if(
            s[i] == '"' && 
            !(i > 0 && s[i] == '\\') // Escaped quotes
        ) 
            openQuotes = !openQuotes;
        if(openQuotes && (i > 0 && s[i-1] != '\\' && s[i] != '"')) result += s[i];
    }

    return result;
}

float getLatitudeFromAttributes(vector<string> attrs) {
    string latitudeAsString = "999";

    for(int i = 0; i < attrs.size(); i++) {
        string attrInStage = attrs[i];
        if(strcmp(attrs[i].substr(0, 3).c_str(), "lat") == 0) {
            latitudeAsString =  getValue(attrs[i]);
            break;
        }
    }

    cout<<"Latitude as string " << latitudeAsString << endl;

    return stod(latitudeAsString);
}

float getLongitudeFromAttributes(vector<string> attrs) {
    string longitudeAsString = "999";

    for(int i = 0; i < attrs.size(); i++) {
        string attrInStage = attrs[i];
        if(strcmp(attrs[i].substr(0, 3).c_str(), "lon") == 0) {
            longitudeAsString = getValue(attrs[i]);
            break;
        }
    }

    cout<<"Longitude as string " << longitudeAsString <<endl;

    return stod(longitudeAsString);
}

string getNameFromAttributes(vector<string> attrs) {
    string name = "";
    bool isKeyName = false;
    for(int i = 0; i < attrs.size(); i++) {
        if(attrs[i][0] == 'v') {
            name = getValue(attrs[i]);
        }
        else if(attrs[i][0] == 'k') {
            isKeyName = (strcmp(getValue(attrs[i]).c_str(), "name") == 0); 
        }
    }

    cout<<"Name found "<<name<<endl;
    if(isKeyName) return name;
    return "";
}

bool selfContainedTag(string s) {
    return s[0] == '<' && s[s.length() - 2] == '/' && s[s.length() - 1] == '>';
}

bool endingTag(string s, string y) {
    vector<string> attr1 = extractAttributes(s);
    vector<string> attr2 = extractAttributes(y);
    return attr1 == attr2 && y[0] == '<' && y[1] == '/';
}

void processLine(string s) {
    vector<string> attributes = extractAttributes(s);
    
    if(!selfContainedTag(s)) {
        callStack.push(s);
    } else if(!callStack.empty() && endingTag(s, callStack.top())) {
        callStack.pop();
    }

    float lat = getLatitudeFromAttributes(attributes);
    float lon = getLongitudeFromAttributes(attributes);
    string name = getNameFromAttributes(attributes);

    if(lat != 999 && lon != 999) {
        latitudeStack.push(lat);
        longitudeStack.push(lon);
    }

    if(name != "") {
        nameStack.push(name);
    }

    if(latitudeStack.size() != 0 && latitudeStack.size() == longitudeStack.size() && latitudeStack.size() == nameStack.size()) {
        cout << "We've found match for " << nameStack.top() << endl;
        latitudeStack.pop(); longitudeStack.pop(); nameStack.pop();
        // TODO;
    }

}


int main() {

    ifstream input( "osmfile.xml" );

    for( string line; getline( input, line ); )
    {
        cout<<line<<endl;
        processLine(line);
    }

    return 0;
}
