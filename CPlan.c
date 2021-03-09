/*
Project Name: CPlan

Language: C

Author: Alec "MountainFox" Larsen

Description:
When complete, program should allow for entry, cleaning, and modification of goals.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define max_name_length 256

//------------------------------------------------------------------------------

typedef struct Node{
	char str[max_name_length];
	struct Node *next;
}Node;

//------------------------------------------------------------------------------

typedef struct Course{
	char name[9];
	struct Task *head;
	struct Course *next;
}Course;

//------------------------------------------------------------------------------

typedef struct Task{
	char TaskName[max_name_length];
	struct Goal *GoalHead;
	struct Task *next;
}Task;

//------------------------------------------------------------------------------

typedef struct Goal{
	char GoalName[max_name_length];
	int goal_weight;
	int weight_completed;
	struct Goal *next;
}Goal;

//------------------------------------------------------------------------------

int TotalGoalWeight (Goal *head){
    /*--------------------------------------------------------------------------
    Calculate the total weight of all goals in the given goal list.
    --------------------------------------------------------------------------*/
	struct Goal *body = head;
	int total = 0;
	while(body != NULL){
		total += body->goal_weight;
		body = body->next;
	}
	return total;
}

//------------------------------------------------------------------------------

int TotalTaskWeight (Task *head){
    /*--------------------------------------------------------------------------
    Calculate the total weight of all tasks in the given task list.
    --------------------------------------------------------------------------*/
	struct Task *body = head;
	int total = 0;
	while(body != NULL){
		total += TotalGoalWeight(body->GoalHead);
		body = body->next;
	}
	return total;
}

//------------------------------------------------------------------------------

int TotalGoalCompleted (Goal *head){
    /*--------------------------------------------------------------------------
    Calculate the total weight completed of all goals in the given goal list.
    --------------------------------------------------------------------------*/
	struct Goal *body = head;
	int total = 0;
	while(body != NULL){
		total += body->weight_completed;
		body = body->next;
	}
	return total;
}

//------------------------------------------------------------------------------

int TotalTaskCompleted (Task *head){
    /*--------------------------------------------------------------------------
    Calculate the total weight completed of all tasks in the given task list.
    --------------------------------------------------------------------------*/
	struct Task *body = head;
	int total = 0;
	while(body != NULL){
		total += TotalGoalCompleted(body->GoalHead);
		body = body->next;
	}
	return total;
}

//------------------------------------------------------------------------------

void AppendGoal (Task *task, Goal *goal){
    /*--------------------------------------------------------------------------
    Append the goal specified to the end of the task list specified by head
    Task.
    --------------------------------------------------------------------------*/
	struct Goal *body = task->GoalHead;
	while(body->next != NULL){
		body = body->next;
	}
	body->next = goal;
	return;
}

//------------------------------------------------------------------------------

void PrintSummary (Course *head){
    /*--------------------------------------------------------------------------
    Print the hierarchal list of all courses, goals, and tasks with accompanying
    % completion for all elements.
    --------------------------------------------------------------------------*/
	struct Course *body = head;
	int completed;
	int total;
	int w;
	int c;
	float pct;
	while (body != NULL){
	    w = TotalTaskWeight(body->head);
	    c = TotalTaskCompleted(body->head);
	    pct = (float)c/(float)w * 100;
        printf("%s\n", body->name);
        printf("%d/%d (%.2f%%)\n", c, w, pct);
        
        struct Task *tbody = body->head;
        while (tbody != NULL){
            w = TotalGoalWeight(tbody->GoalHead);
	        c = TotalGoalCompleted(tbody->GoalHead);
	        pct = (float)c/(float)w * 100;
            printf("  %s\n", tbody->TaskName);
            printf("  %d/%d (%.2f%%)\n", c, w, pct);
            
            struct Goal *gbody = tbody->GoalHead;
            while (gbody != NULL){
                w = gbody->goal_weight;
	            c = gbody->weight_completed;
	            pct = (float)c/(float)w * 100;
                printf("    %s\n", gbody->GoalName);
                printf("    %d/%d (%.2f%%)\n", c, w, pct);
                gbody = gbody->next;
            }
            tbody = tbody->next;
        }
		body = body->next;
	}
	return;
}

//------------------------------------------------------------------------------

Goal *form_goal(char str[max_name_length], Goal *ghead, int *g){
    /*--------------------------------------------------------------------------
    Create a new Goal, append it to the end of the goal list, and return the
    head of the list.
    --------------------------------------------------------------------------*/
        //Split str into 3 variables and form goal object.
	char name[max_name_length];
	char *tmp;
	int weight;
	int complete;
	struct Goal *body = NULL; 
	body=(Goal*)calloc(1,sizeof(Goal));
	tmp = strtok(str, ",");
	strcpy(body->GoalName, tmp);
	
	tmp = strtok(NULL, ",");
	weight = atoi(tmp);
	tmp = strtok(NULL, ",");
	complete = atoi(tmp);
	body->goal_weight = weight;
	body->weight_completed = complete;
	
	if(*g == 0){
	    printf("Goal Head Set to: %s - (Weight = %d, Completed = %d)\n",body->GoalName, body->goal_weight, body->weight_completed);
	    *g = 1;
	    return body;
	}
	while (ghead->next != NULL){
	    ghead = ghead->next;
	}
	ghead->next = body;
	printf("Goal Added: %s\n",body->GoalName);
	return ghead;
}

//------------------------------------------------------------------------------

Node *createNode (char str[max_name_length], Node *nhead){
    /*--------------------------------------------------------------------------
    Create node and append it to the end of the list. Return head of the Node 
    list.
    --------------------------------------------------------------------------*/
    struct Node *n;
    n =(Node*)calloc(1,sizeof(Node));
    strcpy(n->str, str);
    if(strcmp(nhead->str, "NULL") == 0){
        printf("Head set to: %s",n->str);
        return n;
    }
    struct Node *body = nhead;
    while(body->next != NULL){
        body = body->next;
    }
    printf("Node Added: %s",n->str);
    body->next = n;
    return nhead;
}

//------------------------------------------------------------------------------

Task *createTaskNode (char str[max_name_length], Task *thead, Goal *gHead, int *t){
    /*--------------------------------------------------------------------------
    Create a new task node, append it  to the end of the task list, and return
    the head of the list.
    --------------------------------------------------------------------------*/
    struct Task *n;
    n =(Task*)calloc(1,sizeof(Task));
    strncpy(n->TaskName, str, strlen(str) - 1);
    n->GoalHead = gHead;
    if(*t == 0){
        printf("Head of Tasks Set To: %s\n",n->TaskName);
        *t = 1;
        return n;
    }
    struct Task *body = thead;
    while (body->next != NULL){
      body = body->next;
    }
    printf("Task Added: %s\n",n->TaskName);
    body->next = n;
    return thead;
}

//------------------------------------------------------------------------------

Course *createCourseNode (char str[max_name_length], Course *head, Task *tHead){
    /*--------------------------------------------------------------------------
    Create course node, append it to the end of the course list, and return the 
    head of the course list.
    --------------------------------------------------------------------------*/
    struct Course *n;
    n =(Course*)calloc(1,sizeof(Course));
    strncpy(n->name, str, strlen(str) - 1);
    n->head = tHead;
    if(strcmp(head->name,"NULL") == 0){
        printf("Head of Courses Set To: %s\n",n->name);
        return n;
    }
    struct Course *body = head;
    while (body->next != NULL){
        body = body->next;
    }
    printf("Course Added: %s\n",n->name);
    body->next = n;
    return head;
}

//------------------------------------------------------------------------------

Node *ExtractData(){
    /*--------------------------------------------------------------------------
    Pull all data from plan.txt to prepare for hierarchy sorting.
    --------------------------------------------------------------------------*/
    char str[max_name_length];
    struct Node *nhead = NULL;
    FILE *path;
    char filename[10] = "plan.txt";
    
    path = fopen(filename, "r");
    if (path == NULL){
        printf("Plan file not found. Put plan.txt in working directory\n");
    }
	
	nhead =(Node*)calloc(1,sizeof(Node));
	strcpy(nhead->str,"NULL");
	
	// This loop should initialize all lines of the file plan.txt into a linked list.
    while (fgets(str, max_name_length, path) != NULL){
        nhead = createNode(str, nhead);
	}
	
	struct Node *current = nhead;
	while (current != NULL){
	    printf("%s",current->str);
	    current = current->next;
	}
	return nhead;
}

//------------------------------------------------------------------------------

int main(){
    /*--------------------------------------------------------------------------
    This entire section brings all data in plan into the program. Note that for
    this program to run without modifying code, plan.txt must exist in your
    working directory.
    --------------------------------------------------------------------------*/
    char last_node;
    int t = 0;
    int g = 0;
	struct Node *nhead = NULL;
	struct Course *head = NULL;
	struct Task *tHead = NULL;
	struct Goal *gHead = NULL;
	char course_name[max_name_length];
    char task_name[max_name_length];
    
    nhead =(Node*)calloc(1,sizeof(Node));
    head =(Course*)calloc(1,sizeof(Course));
    tHead =(Task*)calloc(1,sizeof(Task));
    gHead =(Goal*)calloc(1,sizeof(Goal));

    nhead = ExtractData();
    
    /*--------------------------------------------------------------------------
    The following section sorts all data extracted from plan.txt into the
    hierarchal structure this program uses.
    --------------------------------------------------------------------------*/
    strcpy(head->name,"NULL");
	// This loop hopefully initializes the three tiered linked list correctly.
	while (nhead != NULL){
	    if (nhead->str[0] == 'C'){
	        if (last_node == 'G'){
	           tHead = createTaskNode(task_name, tHead, gHead, &t);
	           g = 0;
	           head = createCourseNode(course_name, head, tHead);
	           t = 0;
	        }
	        last_node = 'C';
	        strcpy(course_name, nhead->str);
	    }
		if (nhead->str[0] == 'T'){
		    if (last_node == 'G'){
		        tHead = createTaskNode(task_name, tHead, gHead, &t);
		        g = 0;
		    }
		    strcpy(task_name, nhead->str);
		}
		if(nhead->str[0] == 'G'){
		    gHead = form_goal(nhead->str, gHead, &g);
			last_node = 'G';
		}
	    nhead = nhead->next;
	}
	tHead = createTaskNode(task_name, tHead, gHead, &t);
	head = createCourseNode(course_name, head, tHead);
	
	/*--------------------------------------------------------------------------
	This section actually does stuff with the data. As it was the last function
	to be implemented, a test to confirm AppendGoal works properly is included.
	--------------------------------------------------------------------------*/
	//Prepare variables to test appending function
	g = 0;
	char r[max_name_length];
	strcpy(r,"G:Edit,1,1\n");
	struct Goal *new_goal = NULL;
	new_goal=(Goal*)calloc(1,sizeof(Goal));
	//Initialize new goal for appending
	new_goal = form_goal(r, NULL, &g);
	//Append goal
	AppendGoal(head->head, new_goal);
	//Check goal was appended properly
	PrintSummary(head);
	
	return 0;
}
// All functions in this code run without compiler error.
// List should Init Correctly
// List should print all % completions alongside course/task/goal names.
