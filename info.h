//variant 15
//Balashov Oleksandr
#pragma once
#include <string>
#include <set>
#include <exception>
#include <stdexcept>
#include <math.h>
#include <algorithm>
#include"exceptions.h"
class Info
{
public:
    class Student
    {
    public:
        explicit Student(const std::string &name, const std::string &patronym, const std::string &surname);
        int getAverageScore() const;
        int getBestScore() const;
        unsigned getAttemptNumber() const;
        std::string getName() const;
        std::string getSurname() const;
        std::string getPatronym() const;
        bool operator == (const Student&) const;
        bool operator < (const Student&) const;
        bool operator > (const Student&) const;
        bool operator <= (const Student&) const;
        bool operator >= (const Student&) const;
        bool operator != (const Student&) const;
        void load(int year,int score, std::string text);
        void stat(std::string&);
    private:
        std::string name_ ;
        std::string patronym_ ;
        std::string surname_ ;
        double averageScore = 0;
        int bestScore = 0;
        void isValidName(const std::string&);
        void isValidSurname(const std::string&);
        void isValidPatronym(const std::string&);
    public:
        struct Task
        {
            explicit Task(int &year, int &score, std::string &text);
            bool operator == (const Task&) const;
            bool operator < (const Task&) const;
            bool operator > (const Task&) const;
            bool operator <= (const Task&) const;
            bool operator >= (const Task&) const;
            bool operator != (const Task&) const;
            void isValidTaskText(const std::string&);
            void isValidScore(const int&v);
            void isValidYear(const int&v);
            int year_;
            int score_;
            std::string text_;
        };
    private:
        std::multiset<Task> tasks;
    };
    void load(const std::string &name, const std::string &patronym, const std::string &surname);
    void load(const std::string &name, const std::string &patronym,int year,int score, const std::string &surname,std::string text);
private:
    std::set<Student> students;
    int threshold = 90;
public:
    void stat(std::string&);
};
