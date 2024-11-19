#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Student {
protected:
    std::string first_name;
    std::string last_name;
    float gpa;
    int grad_year;
    std::string grad_semester;
    int enroll_year;
    std::string enroll_semester;
    bool is_graduate;

public:
    Student() : first_name(""), last_name(""), gpa(0.0), grad_year(0),
                grad_semester(""), enroll_year(0), enroll_semester(""),
                is_graduate(false) {}

    virtual ~Student() {}

    void setName(const std::string &first, const std::string &last) {
        first_name = first;
        last_name = last;
    }
    std::string getName() const { return first_name + " " + last_name; }

    void setGPA(float g) { gpa = g; }
    float getGPA() const { return gpa; }

    void setGradYear(int year, const std::string &semester) {
        grad_year = year;
        grad_semester = semester;
    }

    void setEnrollYear(int year, const std::string &semester) {
        enroll_year = year;
        enroll_semester = semester;
    }

    void setGraduateStatus(bool status) { is_graduate = status; }

    virtual std::string getInfo() const = 0;
};

class Art_Student : public Student {
private:
    std::string art_emphasis;

public:
    Art_Student() : art_emphasis("Art Studio") {}

    void setArtEmphasis(const std::string &emphasis) { art_emphasis = emphasis; }
    std::string getArtEmphasis() const { return art_emphasis; }

    std::string getInfo() const override {
        return "Art Emphasis: " + art_emphasis;
    }
};

class Physics_Student : public Student {
private:
    std::string concentration;

public:
    Physics_Student() : concentration("Biophysics") {}

    void setConcentration(const std::string &conc) { concentration = conc; }
    std::string getConcentration() const { return concentration; }

    std::string getInfo() const override {
        return "Concentration: " + concentration;
    }
};

int main() {
    std::vector<Art_Student *> art_students;
    std::vector<Physics_Student *> physics_students;

    for (int i = 0; i < 5; ++i) {
        Art_Student *art = new Art_Student;
        art->setName("ArtFirst" + std::to_string(i), "ArtLast" + std::to_string(i));
        art->setGPA(3.5 + i * 0.1);
        art->setGradYear(2025, "Spring");
        art->setEnrollYear(2021, "Fall");
        art->setGraduateStatus(false);
        art->setArtEmphasis(i % 2 == 0 ? "Art Studio" : "Art History");
        art_students.push_back(art);
    }

    for (int i = 0; i < 5; ++i) {
        Physics_Student *physics = new Physics_Student;
        physics->setName("PhysicsFirst" + std::to_string(i), "PhysicsLast" + std::to_string(i));
        physics->setGPA(3.2 + i * 0.2);
        physics->setGradYear(2024, "Fall");
        physics->setEnrollYear(2020, "Spring");
        physics->setGraduateStatus(true);
        physics->setConcentration(i % 2 == 0 ? "Biophysics" : "Earth and Planetary Sciences");
        physics_students.push_back(physics);
    }

    std::ofstream outfile("student_info.dat");
    if (outfile.is_open()) {
        for (const auto &art : art_students) {
            outfile << "Art Student: " << art->getName() << ", GPA: " << art->getGPA()
                    << ", " << art->getInfo() << "\n";
        }
        for (const auto &physics : physics_students) {
            outfile << "Physics Student: " << physics->getName() << ", GPA: " << physics->getGPA()
                    << ", " << physics->getInfo() << "\n";
        }
        outfile.close();
    }

    for (auto &art : art_students) delete art;
    for (auto &physics : physics_students) delete physics;

    return 0;
}
