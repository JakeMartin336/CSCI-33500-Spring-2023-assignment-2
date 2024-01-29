// Jacob Martin
// Main file for Part2(a) of Homework 2.

#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

namespace 
{

bool GetNextRecognitionSequence(const string &db_line, string &a_reco_seq, size_t &first_slash) 
{
  size_t next_slash_position = db_line.find("/", first_slash+1); //using the position of the first slash to find the position of the next slash

  // check if "//" has been reached
  if (next_slash_position == string::npos)
    return false;
  else {
    // extract the sequence between the two slashes
    a_reco_seq = db_line.substr(first_slash+1, next_slash_position-first_slash-1);
    first_slash = next_slash_position;
    return true;
  }
}

std::string GetEnzymeAcronym(const string& line, const size_t &first_slash) 
{
  return line.substr(0, first_slash); //getting from the start of the string til the first slash
}

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) 
{
  ifstream infile(db_filename); //reading file
  string db_line, a_reco_seq, headers, enzyme_acronym;
  
  if (!infile.is_open()) //making sure the file can be opened
  {
    cout << "Error: Cannot open file " << db_filename << "\n";
    exit(0);
  }

  for (size_t i = 0; i < 10; i++) //skipping the first 10 lines in the rebase210 file that dont have any recognition sequences or enzymes
    getline(infile, headers);

  while (getline(infile, db_line))  //reading the file line by line
  {
    size_t slash_pos = db_line.find('/'); //finding the first slash in the line that indicates the end of the enzyme acronym
    enzyme_acronym = GetEnzymeAcronym(db_line, slash_pos); //storing the enzyme acronym in a string
    while (GetNextRecognitionSequence(db_line, a_reco_seq, slash_pos)) //while there are more recognition sequences in the line
    {
      SequenceMap new_sequence_map(a_reco_seq, enzyme_acronym); //create a sequence map with the enzyme acro and the reco sequence
      a_tree.insert(new_sequence_map); //insert the new sequence map into the tree
    }
  }

  string s1, s2, s3;
  cin >> s1 >> s2 >> s3; //reading the strings from user input

  SequenceMap temp1(s1, ""); //creating sequence map from the user input
  SequenceMap temp2(s2, "");
  SequenceMap temp3(s3, "");
  
  cout << a_tree.getEnzymeAcronym(temp1) << endl; //if the sequence map's recognition sequence matches any in the tree, then it will print the node's enzyme acro
  cout << a_tree.getEnzymeAcronym(temp2) << endl;
  cout << a_tree.getEnzymeAcronym(temp3) << endl;

  infile.close();
}

}  // namespace


int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
