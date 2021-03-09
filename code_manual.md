# Code Manual

### Structures

##### Node
Nodes link together into linked list to hold all data froom plan.txt before it is transferred into hierarchy.

str (char[]): stores one line of data from data.txt file.

next (*Node): Points to next Node in linked list

##### Goal
Goals are the lowest level of the hierarchal structure. They represent individual mini-tasks you must do to finish larger tasks (ie. a single question of an assignment)

GoalName (char[]): Name of goal. Cannot contain ',' as these are already used for delimiting strings.

goal_weight (int): Total "size" of goal. Generally, longer goals should get more weight for more accurate % completion figures.

weight_completed (int): Amount of goal completed. Should not be higher than goal_weight.

next (*Goal): Points to next goal in linked list

##### Task
Tasks are the middle level  of the hierarchal structure, between goals and courses. They represent entire tasks such as a whole assignment.

TaskName (char[]): Name of task.

GoalHead (*Goal): Points to the head of the linked list of goals associated with the task.

next (*Task): Points to the next task in the linked list of tasks (If next = NULL, this is the last task).

##### Course
Courses are the broadest level  of the hierarchal structure. They represent entire courses.

name (char[9]): This is the course code of your course. Note that your course codes must be 6 characters as 3 of the 9 characters are used for the course tag (C:) and the terminnating character.

TaskHead (*Task): Points to the head of the linked list of tasks for this course

next (*Course): Points to the next course in the linked list of courses (If next = NULL, this is the last course).

### Runtime Functions

TotalGoalWeight: Calculate the combined weight of all goals in a task.

TotalTaskWeight: Calculates the combined weight of all tasks in a course.

TotalGoalCompleted: Calculates the total weight completed across all goals in a task.

TotalTaskCompleted: Calculates the total weight completed across all tasks in a course.

AppendGoal: Appends a user defined goal to the end of the specified task.

PrintSummary: Prints list of all courses, tasks, and goals as well as associated % completion for all.

### Initialization Functions

form_goal: creates Goal.

createNode: creates Node.

createTaskNode: creates Task.

createCourseNode: creates Course.

ExtractData: Pulls data from plan.txt to prepare for sorting into hierarchal structure.
