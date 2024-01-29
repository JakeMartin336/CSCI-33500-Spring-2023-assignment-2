// <Your name>
// Main file for Part2(b) of Homework 2.

#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
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
  return line.substr(0, first_slash); //grabs from the start of the string until the first slash
}

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) 
{
  ifstream infile(db_filename); //reading file passed
  string db_line, a_reco_seq, headers, enzyme_acronym;
  
  if (!infile.is_open()) //error handling
  {
    cout << "Error: Cannot open file " << db_filename << "\n";
    exit(0);
  }

  for (size_t i = 0; i < 10; i++) //skipping the first 10 lines in the rebase210 file
    getline(infile, headers);

  while (getline(infile, db_line)) //reading the file line by line
  {
    if(db_line.length() > 0) //if the file's string length is over 0
    {
      size_t slash_pos = db_line.find('/'); //find the first slash in the string
      enzyme_acronym = GetEnzymeAcronym(db_line, slash_pos); //create the enzyme acro
      while (GetNextRecognitionSequence(db_line, a_reco_seq, slash_pos)) //while there are more reco sequen in the line passed by the file
      {
        if(a_reco_seq != "")
        {
          SequenceMap new_sequence_map(a_reco_seq, enzyme_acronym); //create a sequence map using the enzyme acro and the reco sequence
          a_tree.insert(new_sequence_map); //insert it into the tree
        }
      }
    }
  }
  infile.close();

  //2, calls the getNumOfNodes helper funtion
  cout << "2: " << a_tree.getNumberOfNodes() << endl;
  //3a, calculates the average depth by dividing the totaldepth by the number of nodes
  float average_depth = (a_tree.getTotalDepth()) / (a_tree.getNumberOfNodes());
  cout << "3a: " << average_depth << endl;
  //3b, calculates ratio of the average depth using the formula given
  float ratio_depth = (average_depth) / (log2(a_tree.getNumberOfNodes()));
  cout << "3b: " << ratio_depth << endl;
  //4a + 4b
  ifstream seqfile(seq_filename); //reading the text file passed
  string seq_line;
  int successful_queries = 0, total_query_calls = 0;
  if (!seqfile.is_open()) //error handling, making sure the file can be opened
  {
    cout << "Error: Cannot open file " << seq_filename << "\n";
    exit(0);
  }
  while (getline(seqfile, seq_line)) //reading the text file line by line
  {
    SequenceMap temp(seq_line, ""); //creating a sequence map using the line from the text file
    if(a_tree.contains(temp)) //if the tree contains the same sequence map as the one that was given from the text file
      successful_queries++; //incrimenting queries
    total_query_calls += a_tree.findCount(temp); //finding amount of recursive calls
  }
  seqfile.close();
  cout << "4a: " << successful_queries << endl;
  float average_query_calls = total_query_calls / successful_queries; //finding average num of recursive calls from the formula given
  cout << "4b: " << average_query_calls << endl;
  //5a + 5b
  ifstream rem_file("sequences.txt"); //reading the text file passed
  string rem_line;
  int count = 0, total_calls = 0, successful_removes = 0;
  while (getline(rem_file, rem_line)) //reading text file line by line
  {
    SequenceMap temp(rem_line, ""); //creating a sequence map based on the line from the text file
    count++; //incrimenting
    if (count % 2 == 0) //if an even incriment
      continue;
    int calls = a_tree.remove(temp); //remove the nodes that match from the tree
    if (calls >= 0) 
    {
      successful_removes++; //incriment
      total_calls += calls; //incriment
    }
  }
  rem_file.close();
  cout << "5a: " << successful_removes << endl;
  float recur_calls = total_calls / successful_removes;
  cout << "5b: " << recur_calls << endl;
  //6a + 6b + 6c, redoing the same process that i did for 2 and 3
  cout << "6a: " << a_tree.getNumberOfNodes() << endl;
  float average_depth2 = (a_tree.getTotalDepth()) / (a_tree.getNumberOfNodes());
  cout << "6b: " << average_depth2 << endl;
  float ratio_depth2 = (average_depth2) / (log2(a_tree.getNumberOfNodes()));
  cout << "6c: " << ratio_depth2 << endl;

}
}  // namespace

int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
