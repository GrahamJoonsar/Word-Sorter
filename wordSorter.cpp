#include <iostream>
#include <string>
#include <fstream>

bool isWritingToFile = false;
bool isReversed = false;
std::ofstream writeToFile;

struct word{
    struct word * left; // Left child
    struct word * right; // Right child
    std::string text; // the actual text of the word

    word(std::string _text){
        text = _text;
        left = NULL;
        right = NULL;
    }
};

void addWord(struct word * currentWord, std::string wordToBeAdded){ // Adding a word to the binary tree
    if (wordToBeAdded < currentWord->text){
        //std::cout << "left\n";
        if (currentWord->left == NULL){
            currentWord->left = new word(wordToBeAdded);
        } else {
            addWord(currentWord->left, wordToBeAdded);
        }
    } else if (wordToBeAdded > currentWord->text){
        //std::cout << "right\n";
        if (currentWord->right == NULL){
            currentWord->right = new word(wordToBeAdded);
        } else {
            addWord(currentWord->right, wordToBeAdded);
        }
    }
}

void addWordReversed(struct word * currentWord, std::string wordToBeAdded){ // Adding a word to the binary tree in reverse
    if (wordToBeAdded > currentWord->text){
        //std::cout << "left\n";
        if (currentWord->left == NULL){
            currentWord->left = new word(wordToBeAdded);
        } else {
            addWordReversed(currentWord->left, wordToBeAdded);
        }
    } else if (wordToBeAdded < currentWord->text){
        //std::cout << "right\n";
        if (currentWord->right == NULL){
            currentWord->right = new word(wordToBeAdded);
        } else {
            addWordReversed(currentWord->right, wordToBeAdded);
        }
    }
}

void printTree(struct word * currentWord){ // Printing the tree in order
    if (currentWord == NULL){
        return;
    }
    printTree(currentWord->left);
    if (isWritingToFile){
        writeToFile << currentWord->text << '\n';
    }
    std::cout << currentWord->text << '\n';
    printTree(currentWord->right);
}

int main(){
    char usingFile;
    char reversed;
    std::cout << "Are you writing to a file? (Y/N)\n";
    std::cin >> usingFile;

    if (toupper(usingFile) == 'Y'){
        isWritingToFile = true;
        std::string fileName;
        std::cout << "Enter name of file (including extension)\n";
        std::cin >> fileName;
        writeToFile.open(fileName);
    }

    std::cout << "Do you want it to be reversed? (Y/N)\n";
    std::cin >> reversed;

    if (toupper(reversed) == 'Y'){
        isReversed = true;
    }
    
    std::cout << "Enter q to stop\n";

    std::string userAddedWord = "";
    
    std::cout << "Enter a word\n"; // Getting the root
    std::cin >> userAddedWord;

    struct word * root = new word(userAddedWord);

    while (1){ // Getting user input
        std::cout << "Enter a word\n";
        std::cin >> userAddedWord;
        if (userAddedWord != "q"){
            isReversed ? addWordReversed(root, userAddedWord) : addWord(root, userAddedWord);
        } else {
            break;
        }
    }
    
    system("CLS");
    printTree(root);
    std::cin >> userAddedWord;

    writeToFile.close();
}