/**********************************************************
 * Name: Savishwa Gaur
 * Date: 02-11-2020
 * NetID: sxg180113
 *********************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

int parse(string);
void displayInvalid(map<string, string>);
void displayValid(map<string, string>);

int main () {

    // Initialize URL variable
    string URL = "";

    // Prompt user to enter URL and save in URL variable
    cout << "Enter a URL" << endl;
    cin >> URL;

    // Print parsed URL to console
    return parse(URL);
}

int parse (string URL) {

    // Initialize variables for URL components
    string protocol, domain, port, filePath, parameters;
    map<string, string> invaldItems;
    map<string, string> validItems;

    // Parse protocol
    protocol = URL.substr(0, URL.find(':'));
    // Validate
    if ((protocol.compare("http") == 0) || (protocol.compare("https") == 0) || (protocol.compare("ftp") == 0) || (protocol.compare("stps") == 0)) {
        validItems["Protocol"] = protocol;
    }
    else {
        invaldItems["Protocol"] = protocol;
    }
    
    // Remove URL contents before protocol to make parsing easier
    URL = URL.substr(protocol.size() + 3, URL.size());

    if (URL.size() < 1) {
        return -1;
    }

    // Parse domain
    if (URL.find(':') != -1) {
        domain = URL.substr(0, URL.find(':'));
    }
    else {
        domain = URL.substr(0, URL.find('/'));
    }
    // Validate
    if (count(domain.begin(), domain.end(), '.') != 2) {
        invaldItems["Domain"] = domain;
    }
    else {
        validItems["Domain"] = domain;
    }

    // Remove URL contents before domain to make parsing easier
    URL = URL.substr(domain.size(), URL.size());

    if (URL.size() < 1) {
        return -1;
    }

    // Parse port if it exists
    if (URL.find(':') != -1) {
        port = URL.substr(1, URL.find('/') - 1);
        // Validate
        if (stoi(port, nullptr, 10) > 1 && stoi(port, nullptr, 10) < 65535) {
            validItems["Port"] = port;
        }
        else {
            invaldItems["Port"] = port;
        }

        // Remove URL contents before port to make parsing easier
        URL = URL.substr(port.size(), URL.size());

        if (URL.size() < 1) {
            return -1;
        }
    }

    // Parse filePath
    filePath = URL.substr(1, URL.find('?') - 1);
    // Validate
    if (filePath.find("html") != -1 || filePath.find("htm") != -1) {
        validItems["File Path"] = filePath;
    }
    else {
        invaldItems["File Path"] = filePath;
    }

    // Remove URL contents before domain to make parsing easier
    URL = URL.substr(filePath.size(), URL.size());
    if (URL.size() < 1) {
        return -1;
    }

    // Parse parameters
    if (URL.find('?') != -1) {
        parameters = URL.substr(2, URL.size());
        validItems["Parameters"] = parameters; 
    }
    
    // Display invalid items if any exist
    if (invaldItems.empty()) {
        displayValid(validItems);
    }
    else { 
        displayInvalid(invaldItems);
    }

    return 0;
}

/* 
*    displayInvalid(map<string, string>): Displays the components which are invalid from the input URL 
*/
void displayInvalid (map<string, string> invalidItems) {
    cout << "Invalid URL with following erroneous components:" << endl; 
    
    if (invalidItems["Protocol"].compare("") != 0) {
        cout << "Protocol: " + invalidItems["Protocol"] + " is not a valid protocol." << endl;
    }

    if (invalidItems["Domain"].compare("") != 0) {
        cout << "Domain: " + invalidItems["Domain"] + " is not a valid domain." << endl;
    }
    
    if (invalidItems["Port"].compare("") != 0) {
        cout << "Port: port number must be between 1 and 65535." << endl;
    }
    
    if (invalidItems["File Path"].compare("") != 0) {
        cout << "File Path: " + invalidItems["File Path"] + " is not a valid file path (needs to be .html or .htm)." << endl;
    }
}

/* 
*    displayValid(map<string, string>): Displays the components which are valid from the input URL if there are no invlaid items
*/
void displayValid (map<string, string> validItems) {
    cout << "Protocol: " + validItems["Protocol"] << endl;
    cout << "Domain: " + validItems["Domain"] << endl;
    cout << "Port: " + validItems["Port"] << endl;
    cout << "File Path: " + validItems["File Path"] << endl;
    cout << "Parameters: " + validItems["Parameters"] << endl;
}