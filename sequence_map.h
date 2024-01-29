// Jacob Martin
// SequenceMap.h of Homework 2.

#ifndef _SEQUENCE_MAP_H
#define _SEQUENCE_MAP_H
#include <iostream>
#include <string>
#include <vector>

class SequenceMap
{
public:
	//Big-Five:
	//Zero-parameter constructor.
    SequenceMap() = default;
    //Copy-constructor.
    SequenceMap(const SequenceMap &rhs) = default; //: recognition_sequence_{rhs.recognition_sequence_}, enzyme_acronyms_{rhs.enzyme_acronyms_} {};
    //Copy-assignment.
    SequenceMap& operator=(const SequenceMap &rhs) = default;
	// {
	// 	if (this != &rhs) 
	// 	{
    //   		this->recognition_sequence_ = rhs.recognition_sequence_;
    //   		this->enzyme_acronyms_ = rhs.enzyme_acronyms_;
    // 	}
    // 	return *this;
	// }
    //Move-constructor.
    SequenceMap(SequenceMap &&rhs) = default; //: recognition_sequence_{std::move(rhs.recognition_sequence_)}, enzyme_acronyms_{std::move(rhs.enzyme_acronyms_)} {};
    //Move-assignment.
    SequenceMap& operator=(SequenceMap &&rhs) = default;
	// {
	// 	if (this != &rhs) 
	// 	{
	// 		this->recognition_sequence_ = std::move(rhs.recognition_sequence_);
    //   		this->enzyme_acronyms_ = std::move(rhs.enzyme_acronyms_);
    // 	}
    // 	return *this;
	// }
    //Destructor.
    ~SequenceMap() = default;

	SequenceMap(const std::string &a_rec_seq, const std::string &an_enz_acro) //parameterized constructor
	{
		this->recognition_sequence_ = a_rec_seq; //setting recognition to parameter passed
		this->enzyme_acronyms_.push_back(an_enz_acro); //putting the parameter passed into the enzyme vector
	}
	
	bool operator<(const SequenceMap& rhs) const //comparing two sequence maps
	{
        return recognition_sequence_ < rhs.recognition_sequence_; //seeing which recognition sequence is greater
    }
	
	//Overload the operator<< for SequenceMap 
    friend std::ostream& operator<<(std::ostream& out, const SequenceMap& sequence) 
	{
        //out << sequence.recognition_sequence_ << "\n";
        for (const auto& acronym : sequence.enzyme_acronyms_) { //putting the object's enzyme vector into the ostream in the given format
            out << acronym << " ";
        }
		out << "\n";
        return out; 
    }
	
	void Merge(const SequenceMap &other_sequence) //merging two sequence map objects
	{
		for (const auto& enzyme : other_sequence.enzyme_acronyms_)  //pushing the object passed's enzyme vector into this object's vector
			enzyme_acronyms_.push_back(enzyme);
	}


	std::vector<std::string> getArcos() const //get function that returns the enzyme vector
	{
		return enzyme_acronyms_;
	}

private:
	std::string recognition_sequence_ ;
	std::vector<std::string> enzyme_acronyms_;
};

#endif