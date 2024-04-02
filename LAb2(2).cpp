#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// Function to find the word of maximum length
string find_max_word(const string& str) {
    stringstream ss(str);
    string word, max_word;
    int max_length = 0;

    while (ss >> word) {
        int length = word.length();
        if (length > max_length) {
            max_length = length;
            max_word = word;
        }
    }

    return max_word;
}

// Function to extract words in the format "word,word" from the string
void extract_specific_format_words(const string& str, string words[][2], int& count) {
    stringstream ss(str);
    string word;

    count = 0; // Reset the counter

    while (ss >> word) { // Split the string into words
        // Check if the word contains a comma
        size_t pos = word.find(',');
        if (pos != string::npos) {
            // Check if there is a space after the comma
            size_t space_pos = word.find(' ', pos + 1);
            if (space_pos == string::npos) { // If there is no space after the comma
                // Get the first and second word
                string first_word = word.substr(0, pos);
                string second_word = word.substr(pos + 1);

                // Add the words to the array
                words[count][0] = first_word;
                words[count][1] = second_word;
                ++count; // Increment the counter
            }
        }
    }
}

// Function to remove invalid formats
void remove_invalid_formats(string words[][2], int& count) {
    for (int i = 0; i < count; ++i) {
        // Check if the first word is empty
        if (words[i][0].empty() || words[i][1].empty()) {
            // If the first word is empty, shift all subsequent words one position to the left
            for (int j = i; j < count - 1; ++j) {
                words[j][0] = words[j + 1][0];
                words[j][1] = words[j + 1][1];
            }
            --count; // Decrement the counter
            --i; // Decrement the loop variable to recheck the current position
        }
    }
}

int main() {
    char choice;
    string input;
    string words[100][2]; // Array to store words
    do {
        // Menu display
        cout << "\nMenu:\n";
        cout << "1 - Enter a string of characters\n";
        cout << "2 - Find the word of maximum length\n";
        cout << "3 - Process the string\n";
        cout << "4 - Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        system("cls");

        switch (choice) {
        case '1':
            // Enter a string of characters
            cin.ignore(); // Clear input buffer
            cout << "Enter a string of text: ";
            getline(cin, input);
            break;
        case '2':
            // Find the word of maximum length
            cout << "Word of maximum length: " << find_max_word(input) << endl;
            break;
        case '3':
            // Process the string

            int count; // Word counter
            extract_specific_format_words(input, words, count);
            remove_invalid_formats(words, count);
            // Print the extracted words
            cout << "Words separated by commas: ";
            for (int i = 0; i < count; ++i) {
                cout << words[i][0] << "," << words[i][1] << " ";
            }
            cout << endl;
            break;
        case '4':
            // Exit the program
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != '4');

    return 0;
}
