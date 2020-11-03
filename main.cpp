#include <iostream>
#include <string>
#include <vector>

using namespace  std;

enum WEEKDAY {
    ПОНЕДЕЛЬНИК,
    ВТОРНИК,
    СРЕДА,
    ЧЕТВЕРГ,
    ПЯТНИЦА,
    СУББОТА,
    ВОСКРЕСЕНЬЕ
};

string getWeekday(WEEKDAY weekday) {
    switch (weekday) {
        case WEEKDAY::ПОНЕДЕЛЬНИК: return "ПОНЕДЕЛЬНИК";
        case WEEKDAY::ВТОРНИК: return "ВТОРНИК";
        case WEEKDAY::СРЕДА: return "СРЕДА";
        case WEEKDAY::ЧЕТВЕРГ: return "ЧЕТВЕРГ";
        case WEEKDAY::ПЯТНИЦА: return "ПЯТНИЦА";
        case WEEKDAY::СУББОТА: return "СУББОТА";
        case WEEKDAY::ВОСКРЕСЕНЬЕ: return "ВОСКРЕСЕНЬЕ";
    }
}

enum CATEGORY {
    A,
    B,
    C,
    D
};

string getCategory(CATEGORY category) {
    switch (category) {
        case  CATEGORY::A: return "A";
        case  CATEGORY::B: return "B";
        case  CATEGORY::C: return "C";
        case  CATEGORY::D: return "D";
    }
}

enum LESSON { //тип занятия
    THEORY,
    PRACTIC,
    EXAMEN
};

string getLesson(LESSON lesson) {
    switch (lesson) {
        case LESSON::THEORY :return "THEORY";
        case LESSON::PRACTIC :return "PRACTIC";
        case LESSON::EXAMEN :return "EXAMEN";

    }
}

class Man {
private:
    string name;
    unsigned  int age;
public:
    Man() {}
    Man (const string name, unsigned int age) {
        this->name = name;
        this->age = age;
    }
    const string getName() {
        return name;
    }
    int getAge() {
        return age;
    }
};

class Pupil : public Man {
private:
    unsigned int practicHours;
    CATEGORY category;
public:
    Pupil(const string name, unsigned int age, CATEGORY cat) : Man(name, age) {
        this->category = cat;
        this->practicHours = 0;
    }
    void setPractHours(unsigned int hrs) {
        this->practicHours = hrs;
    }

    unsigned int getPractHours() {
        return practicHours;
    }

    CATEGORY getCategory() {
        return category;
    }
};

class Group {
private:
    string label;
    vector<Pupil> pupils;
public:
    Group() {};

    Group(string label, vector<Pupil> pupils) : label(label), pupils(pupils) {};
    string getLabel() {
        return label;
    }
    void addPupil(Pupil pupil) {
        this->pupils.push_back(pupil);
    }
    void printPupils() {
        cout << "Список студентов группы: " << label << endl;
        for (int i = 0; i < pupils.size(); ++i) {
            cout << pupils[i].getName()  << " " << pupils[i].getAge() << " " << getCategory(pupils[i].getCategory())<< " " << pupils[i].getPractHours() << endl;
        }
    }
};

class Teacher : public Man {
private:
    CATEGORY category;
    vector<Group> groups;

public:
    Teacher() {};

    Teacher (const string &name, unsigned int age, CATEGORY category, vector<Group> groups) : Man(name, age), category(category), groups(groups) {}

    CATEGORY getCategory() {
        return category;
    }

    void addGroup(Group group) {
        //cout << "Группа добавлена" << endl;
        this->groups.push_back(group);
    }

    void delGroup(Group group) {
        for (int i = 0; i < groups.size(); ++i) {
            if (group.getLabel() == groups[i].getLabel()) {
                groups.erase(groups.begin() + i);
                cout << "Группа удалена" << endl;
                return;
            }
        }
        cout << "У преподавателя нет такой группы" << endl;
    }

    void printGroups() {
        for (int i = 0; i < groups.size(); ++i) {
            cout << groups[i].getLabel() << endl;
        }
    }

    vector<Group> getGroups() {
        return groups;
    }
};

class Lesson {
private:
    unsigned int cabNumb;
    Teacher teacher;
    WEEKDAY weekday;
    Group group;
    LESSON lesson;
public:
    Lesson(Group group, unsigned int cabNumb, const Teacher teacher, LESSON lesson, WEEKDAY weekday)
        :group(group), cabNumb(cabNumb), teacher(teacher), lesson(lesson), weekday(weekday) {};

    Group getGroup(){
        return group;
    };

    WEEKDAY getWeekd() {
        return weekday;
    }

    Teacher getTeacher() {
        return  teacher;
    }

    void printLesson() {
        cout << getWeekday(weekday) << " " << group.getLabel() << " " <<  teacher.getName() << " " << getLesson(lesson) << " " << cabNumb << endl;
    };
};

class Schedule {
private:
    vector<Lesson> lessons;
public:
    Schedule(vector<Lesson> lessons) : lessons(lessons) {}

    void addLesson(Lesson lesson) {
        lessons.push_back(lesson);
    }

    void printSchedule(WEEKDAY day) {
        cout << "Расписание на " << getWeekday(day) << " :" << endl;
        cout << "---------------------------------------" << endl;
        for (unsigned int i = 0; i < lessons.size(); i++) {
            if (lessons[i].getWeekd() == day) {
                lessons[i].printLesson();
            }
        }
        cout << "---------------------------------------" << endl;
        cout << endl;
    }
};

class LessonBuilder {
private:
    unsigned int cabNumb;
    Teacher teacher;
    WEEKDAY weekday;
    Group group;
    LESSON lesson;
public:

    LessonBuilder() {}

    Lesson build() {
        return Lesson {
                group,
                cabNumb,
                teacher,
                lesson,
                weekday,
        };
    }

    void setCabNumb(unsigned int cabNumb) {
        LessonBuilder::cabNumb = cabNumb;
    }

    void setTeacher(const Teacher &teacher) {
        LessonBuilder::teacher = teacher;
    }

    void setWeekday(WEEKDAY weekday) {
        LessonBuilder::weekday = weekday;
    }

    void setGroup(const Group &group) {
        LessonBuilder::group = group;
    }

    void setLesson(LESSON lesson) {
        LessonBuilder::lesson = lesson;
    }

};

class DriveSchool {
private:
    string name;
    vector<Group> groups;
    vector<Teacher> teachers;
    Schedule schedule;
public:
    DriveSchool(const string &name, const vector<Group> &groups, const vector<Teacher> &teachers,
                const Schedule &schedule) : name(name), groups(groups), teachers(teachers), schedule(schedule) {};

    Schedule getSchedule() {
        return schedule;
    }

    void printSchedule(Schedule schedule){
        schedule.printSchedule(ПОНЕДЕЛЬНИК);
        schedule.printSchedule(ВТОРНИК);
        schedule.printSchedule(СРЕДА);
        schedule.printSchedule(ЧЕТВЕРГ);
        schedule.printSchedule(ПЯТНИЦА);
        schedule.printSchedule(СУББОТА);
        schedule.printSchedule(ВОСКРЕСЕНЬЕ);
    };
    void addGroup(Group grp) {
        groups.push_back(grp);
    }

    void addTeacher(Teacher tch) {
        teachers.push_back(tch);
    }

};

int main() {


    Pupil a("Ivan", 20, A); // студенты
    Pupil b("Danila", 22, B);
    Pupil c("Nikita", 30, C);
    Pupil f("Sasha", 25, B);

    vector<Pupil> students; //вектор групп
    vector<Group> groups;
    vector<Teacher> teachers;
    vector<Lesson> rasp;

    Teacher Ivan_Ivanovich("Ivan Ivanovich",45, A, groups);
    Group abc("number 1", students); //группа
    abc.addPupil(a); //добавление студентов в группу
    abc.addPupil(b);
    abc.addPupil(c);

    Group lol("number 2", students);
    lol.addPupil(f);
    Ivan_Ivanovich.addGroup(abc); //группы преподавателя
    //Ivan_Ivanovich.printGroups();

    LessonBuilder builder;
    builder.setLesson(THEORY); //занятие 1
    builder.setCabNumb(11);
    builder.setGroup(abc);
    builder.setTeacher(Ivan_Ivanovich);
    builder.setWeekday(ПОНЕДЕЛЬНИК);
    Lesson TheoryABC = builder.build();

    builder.setLesson(PRACTIC); //занятие 1
    builder.setCabNumb(0);
    builder.setGroup(abc);
    builder.setTeacher(Ivan_Ivanovich);
    builder.setWeekday(СРЕДА);
    Lesson PracticABC = builder.build();

    builder.setLesson(EXAMEN); //занятие 3
    builder.setCabNumb(12);
    builder.setGroup(lol);
    builder.setTeacher(Ivan_Ivanovich);
    builder.setWeekday(СУББОТА);
    Lesson ExamLOL = builder.build();

    builder.setLesson(EXAMEN); //занятие 4
    builder.setCabNumb(15);
    builder.setGroup(lol);
    builder.setTeacher(Ivan_Ivanovich);
    builder.setWeekday(ПОНЕДЕЛЬНИК);
    Lesson examLol = builder.build();

    Schedule schedule(rasp); //расписание
    schedule.addLesson(TheoryABC);
    schedule.addLesson(PracticABC);
    schedule.addLesson(ExamLOL);
    schedule.addLesson(examLol);

    DriveSchool dsf("DOSAAF",groups,teachers,schedule);
    dsf.printSchedule(schedule);
    return 0;
}
