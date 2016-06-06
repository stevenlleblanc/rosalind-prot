// Solution to rosalind.info problem, "Translating RNA into Protein"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

pair<string, string> * table_reader(string file) {
	// Reads data from file containing codon - amino acid pairings,
	// separated by whitespaces, and outputs *pair<codon, string>
	ifstream input(file);

	pair<string, string> * output;
	output = new pair<string, string>[64];
	string code, amino;

	if (input.is_open()) {
		for (unsigned int i = 0; i < 64; i++) {
			input >> code >> amino;
			output[i].first = code;
			output[i].second = amino;
		}
	}
	input.close();
	return output;
}

string codon_translation(string codon, pair<string, string> * table) {
	// Given codon, searches through the table for its respective amino acid
	// and returns it

	for (unsigned int i = 0; i < 64; i++) {
		if (table[i].first == codon) {
			return table[i].second;
		}
	}
	return "";
}

string seq_translation(string rna, pair<string, string> * table) {
	string temp;
	string output;
	string codon;

	for (unsigned int i = 0; i < rna.size(); i++) {
		// Reads through entirety of provided RNA string
		if (codon.size() == 3) {
			// Translates codon, terminates if stop codon is reached
			temp = codon_translation(codon, table);
			if (temp == "Stop") {
				return output;
			}
			else {
				output += temp;
				codon.clear();
			}
		}
		// Builds up codon to size 3
		codon += rna[i];
	}
	return output;
}

int main() {

	pair<string, string> * table;

	table = table_reader("codon_table.txt");

	ifstream input("dataset.txt");

	string rna_seq;
	if (input.is_open()) {
		getline(input, rna_seq);

		ofstream output("answer.txt");
		output << seq_translation(rna_seq, table) << endl;
		output.close();
	}

	return 0;
}