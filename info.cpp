//variant 15
//Balashov Oleksandr
#include"info.h"

using namespace std;

void Info::load(const string &name, const string &patronym, const string &surname)
{
    students.insert(Student(name, patronym, surname));
}

void Info::load(const string &name, const string &patronym, int year, int score, const string &surname, string text)
{
    auto it = students.insert(Student(name, patronym, surname)).first;
    (const_cast<Student&>(*it)).load(year, score, text);
}

Info::Student::Student(const string &name, const string &patronym, const string &surname) : name_(name),
patronym_(patronym), surname_(surname)
{
    isValidName(name_);
    isValidSurname(surname_);
    isValidPatronym(patronym_);
}

void Info::Student::isValidName(const string&s)
{
  if (s.size()>25)
	  throw MyException("The name [" + s+"] is invalid for student", 303);
}

void Info::Student::isValidSurname(const string&s)
{
  if (s.size()>26)
    throw MyException("The surname [" + s+"] is invalid for student", 303);
}

void Info::Student::isValidPatronym(const string&s)
{
  if (s.size()>20)
    throw MyException("The patronym [" + s+"] is invalid for student", 303);
}

string Info::Student::getName() const
{
    return name_;
}

string Info::Student::getSurname() const
{
    return surname_;
}

string Info::Student::getPatronym() const
{
    return patronym_;
}

unsigned Info::Student::getAttemptNumber() const
{
    return tasks.size();
}

int Info::Student::getAverageScore() const
{
    return round(averageScore);
}

int Info::Student::getBestScore() const
{
    return bestScore;
}

bool Info::Student::operator == (const Info::Student &other) const
{
    return name_ == other.name_ && surname_ == other.surname_ && patronym_ == other.patronym_;
}

bool Info::Student::operator < (const Info::Student &other) const
{
     if((*this).getAverageScore() != other.getAverageScore()) 
		 return ((*this).getAverageScore() < other.getAverageScore());
     else
	 {
			if((*this).getAttemptNumber() != other.getAttemptNumber())
				return (*this).getAttemptNumber() < other.getAttemptNumber();
            else
            {
                if(surname_ != other.surname_) 
					return surname_ < other.surname_;
                else
                {
                    if(name_ != other.name_)
						return name_ < other.name_;
                    else
						return patronym_ < other.patronym_;
                }
            }
     }
}

bool Info::Student::operator <= (const Info::Student &other) const
{
    return (*this) < other || (*this) == other;
}

bool Info::Student::operator > (const Info::Student &other) const
{
    return !((*this) < other || (*this) == other);
}

bool Info::Student::operator != (const Info::Student &other) const
{
    return !((*this) == other);
}

bool Info::Student::operator >= (const Info::Student &other) const
{
    return !((*this) < other);
}

void Info::Student::load(int year, int score, string text)
{
    tasks.insert(Task(year, score, text));
    bestScore = max(score, bestScore);
    averageScore = (double) averageScore / score * (tasks.size() - 1);
}

Info::Student::Task::Task(int &year, int &score, string &text) : year_(year),
score_(score), text_(text)
{
  isValidTaskText(text_);
  isValidYear(year_);
  isValidScore(score_);
}

void Info::Student::Task::isValidTaskText(const string&s)
{
  if (s.size()>55)
    throw MyException("The text [" + s+"] is invalid for Task", 303);
}

void Info::Student::Task::isValidScore(const int&v)
{
  if (v < 0 && v > 100)
    throw MyException("The score ["+to_string(v)+"] is invalid for Task", 303);
}

void Info::Student::Task::isValidYear(const int&v)
{
  if (v <= 2000 && v > 9999)
    throw MyException("The year ["+to_string(v)+"] is invalid for Task", 303);
}

bool Info::Student::Task::operator == (const Task &other) const
{
    return text_ == other.text_;
}

bool Info::Student::Task::operator < (const Task &other) const
{
	if (text_ != other.text_)
		return text_ < other.text_;
	else
	{
		if (score_ != other.score_)
			return score_ < other.score_;
		else 
			return year_ < other.year_;
	}
}

bool Info::Student::Task::operator <= (const Task &other) const
{
    return (*this) < other || (*this) == other;
}

bool Info::Student::Task::operator > (const Task &other) const
{
    return !((*this) < other || (*this) == other);
}

bool Info::Student::Task::operator != (const Task &other) const
{
    return !((*this) == other);
}

bool Info::Student::Task::operator >= (const Task &other) const
{
    return !((*this) < other);
}


void Info::stat(string &s)
{
    for(auto it = students.begin(); it != students.end(); it++)
    {
        auto obj = (const_cast<Student&>(*it));
        if(obj.getBestScore() < threshold)
        {
            s += obj.getName(); s += ",";
            s += obj.getPatronym(); s += ",";
            s += obj.getSurname(); s += ",";
            s += to_string(obj.getAverageScore()); s += ",";
            s += to_string(obj.getAttemptNumber()); s += "\n";
            obj.stat(s);
        }
    }
}

void Info::Student::stat(string &s)
{
    for(auto it = tasks.begin(); it != tasks.end(); it++)
    {
        auto obj = (const_cast<Task&>(*it));
        s += "/t";
        s += obj.text_; s += ",";
        s += to_string(obj.score_); s += ",";
        s += to_string(obj.year_); s += ",";
        s += "/n";
    }
}
