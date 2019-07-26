#include <bits/stdc++.h>

using namespace std;

stack<string> callStack;
stack<float> latitudeStack;
stack<float> longitudeStack>;
stack<string> nameStack;

vector<string> extractAttributes(string s) {
    string y = s.substring(1, s.length() - 1);
    vector<string> attributes = y.split(' ')
}

float getLatitudeFromAttributes(vector<string> attrs) {
    string latitudeAsString = "999";

    for(int i = 0; i < attrs.length(); i++) {
        string attrInStage = attrs[i];
        if(attrs[i].substring(0, 3) == "lat") {
            latitudeAsString = attrs[i].substring(5, attrs[i].length());
            break;
        }
    }

    return stod(latitudeAsString);
}

float getLongitudeFromAttributes(vector<string> attrs) {
    string longitudeAsString = "999";

    for(int i = 0; i < attrs.length(); i++) {
        string attrInStage = attrs[i];
        if(attrs[i].substring(0, 3) == "lon") {
            longitudeAsString = attrs[i].substring(5, attrs[i].length());
            break;
        }
    }

    return stod(longitudeAsString);
}

string getNameFromAttributes(vector<string> attrs) {
    string name = "";
    for(int i = 0; i < attrs.length(); i++) {
        if(attrs[i].substring(0, 4) == "name") {
            name = attrs[i].substring(6, attrs[i].length())
            break;
        }
    }

    return name;
}

bool selfContainedTag(string s) {
    return s[0] == '<' && s[s.length() - 2] == '/' && s[s.length() - 1] == '>';
}

bool endingTag(string s, string y) {
    vector<string> attr1 = extractAttributes(s);
    vector<string> attr2 = extractAttributes(y);
    return attr1 == attr2 && y[0] == '<' && y[1] == '/' 
}

void processLine(string s) {
    vector<string> attributes = extractAttributes(s);
    
    if(!selfContainedTag(s)) {
        callStack.push(s)
    } else if(endingTag(s, callStack.top())) {
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

    if(latitudeStack.size() == longitudeStack.size() && latitudeStack.size() == nameStack.size()) {
        cout << "We've found match" << endl;
        // TODO;
    }

}


int main() {

    ifstream input( "osmfile.xml" );

    for( string line; getline( input, line ); )
    {
        processLine(line)
    }

    return 0;
}
