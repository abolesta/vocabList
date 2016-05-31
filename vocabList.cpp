#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<locale>

using namespace std;

void fileInOut(ifstream &inputFile);
void existingWords(vector<string>&wordlist, ifstream &wordsTxt);
void listWords(vector<string>&wordlist, ifstream &fin);
void alphaLoop(vector<string>&wordlist);
bool nonLetter(char ch);
char lowerCase(char ch);
string toAlpha(string str);
void quickSort(vector<string>&a, int lo, int hi);
void sort(vector<string>&a, int n);
void swap(string&a, string&n);
void printWords(vector<string>wordlist, ofstream &output);
void cleanup(ifstream &fin, ofstream &output);
bool repeat();

int main(){
	bool check = true;
	while (check == true){
		ifstream fin, wordsTxt;
		fileInOut(fin);
		wordsTxt.open("words.txt");
		vector<string>wordlist;
		existingWords(wordlist, wordsTxt);
		listWords(wordlist, fin);
		alphaLoop(wordlist);
		sort(wordlist, wordlist.size());
		wordlist.erase(unique(wordlist.begin(), wordlist.end()), wordlist.end());
		ofstream output;
		printWords(wordlist, output);
		cleanup(fin, output);
		check = repeat();
	}

	cin.ignore();
	cin.get();
	return 0;
}

void fileInOut(ifstream &inputFile){
	char filename[50];
	cout << "Enter filename: ";
	cin >> filename;
	inputFile.open(filename);
}

void existingWords(vector<string>&wordlist, ifstream &wordsTxt){
	string line, word;
	int characters;

	while (!wordsTxt.eof()){
		getline(wordsTxt, line);
		characters = line.length();
		int lastSpace = -1;

		for (int i = 0; i<line.length(); i++){
			if (line.substr(0, 17) == "Number of words: "){}

			else if (line[i] == ' '){
				word = line.substr(lastSpace + 1, (i - lastSpace - 1));
				wordlist.push_back(word);
				lastSpace = i;
				characters--;
			}

			else if (i == line.length() - 1){
				word = line.substr(lastSpace + 1, (i - lastSpace));
				wordlist.push_back(word);
			}
		}
	}
	wordsTxt.close();
}

void listWords(vector<string>&wordlist, ifstream &fin){
	string line, word;
	int characters;

	while (!fin.eof()){
		getline(fin, line);
		characters = line.length();
		int lastSpace = -1;

		for (int i = 0; i<line.length(); i++){
			if (line[i] == ' '){
				word = line.substr(lastSpace + 1, (i - lastSpace - 1));
				wordlist.push_back(word);
				lastSpace = i;
				characters--;
			}

			else if (i == line.length() - 1){
				word = line.substr(lastSpace + 1, (i - lastSpace));
				wordlist.push_back(word);
			}
		}
	}
}

void alphaLoop(vector<string>&wordlist){
	for (int j = 0; j < wordlist.size(); ++j){
		wordlist[j] = toAlpha(wordlist[j]);
	}
}

bool nonLetter(char ch){
	return !isalpha(ch, locale());
}

char lowerCase(char ch){
	return tolower(ch, locale());
}

string toAlpha(string str){
	str.erase(remove_if(str.begin(), str.end(), nonLetter), str.end());
	transform(str.begin(), str.end(), str.begin(), lowerCase);

	return str;
}

void quickSort(vector<string>&a, int lo, int hi){
	if (lo >= hi) return;
	string pivot = a[hi];
	int i = lo - 1;
	int j = hi;

	while (i < j){
		while (a[++i] < pivot);
		while (j >= lo && a[--j] > pivot);
		if (i < j) swap(a[i], a[j]);
	}
	swap(a[i], a[hi]);
	quickSort(a, lo, i - 1);
	quickSort(a, i + 1, hi);
}

void sort(vector<string>&a, int n){
	quickSort(a, 0, n - 1);
}

void swap(string&a, string&n){
	string temp = a;
	a = n;
	n = temp;
}


void printWords(vector<string>wordlist, ofstream &output){
	output.open("words.txt");
	for (int j = 0; j<wordlist.size(); j++){
		output << wordlist[j];
		output << "\n";
	}
	output << "\nNumber of words: " << wordlist.size();
}

void cleanup(ifstream &fin, ofstream &output){
	fin.close();
	output.close();
	cout << "\nFinished.\n";
}

bool repeat(){
	string check;
	cout << "\nNew file? ";
	cin >> check;
	cout << "\n";

	if (check == "yes" || check == "y") return true;
	else return false;
}