/*
Project Name: CPlan

Language: C

Author: Alec "Mtnfx" Larsen

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
	struct Goal *body = task->GoalHead;
	while(body->next != NULL){
		body = body->next;
	}
	body->next = goal;
	return;
}

//------------------------------------------------------------------------------

void PrintSummary (Course *head){
	struct Course *body = head;
	int completed;
	int total;
	while (body != NULL){
		total = TotalTaskWeight(body->head);
		completed = TotalTaskCompleted(body->head);
		printf("%s: (%d/%d)",body->name,completed,total);
		struct Task *tbody = body->head;
		while (tbody != NULL){
			total = TotalGoalWeight(tbody->GoalHead);
			completed = TotalGoalCompleted(tbody->GoalHead);
			printf("  %s: (%d/%d)",tbody->TaskName,completed,total);
			struct Goal *gbody = tbody->GoalHead;
			while (gbody != NULL){
				printf("    %s: (%d/%d)",gbody->GoalName, gbody->goal_weight, gbody->weight_completed);
				gbody = gbody->next;
			}
			tbody = tbody->next;
		}
		body = body->next;
	}
	return;
}

//------------------------------------------------------------------------------

Goal *form_goal(char str[max_name_length]){
	//Split str into 3 variables and form goal object.
	char name[max_name_length];
	char tmp[5];
	int weight;
	int complete;
	struct Goal *body = NULL; 
	int i;
	body=(Goal*)calloc(1,sizeof(Goal));
	for(i = 0; strcmp(&str[i+1], ",") != 0; i++){
	}
	strncpy(name, str, i);
	i += 2;
	while (str[i] != ','){
		strcat(tmp, &str[i]);
		i++;
	}
	weight = atoi(tmp);
	strcpy(tmp, "\0\0\0\0\0");
	while (str[i] != '\0'){
		strcat(tmp, &str[i]);
		i++;
	}
	complete = atoi(tmp);
	strcpy(body->GoalName, name);
	body->goal_weight = weight;
	body->weight_completed = complete;
	return body;
}

//------------------------------------------------------------------------------

Course *parseData(){
	//Take previous run data from last session and input into program. Return
	//pointer to first course in plan as the start of a linked list.
	FILE *path;
	char str[max_name_length];
    char filename[10] = "plan.txt";
	int len = 0;
	int g = 0;
	int t = 0;
	struct Node *prev = NULL;
	struct Node *current = NULL;
	struct Node *nhead = NULL;
	struct Course *head = NULL;
	struct Task *tHead = NULL;
	struct Goal *gHead = NULL;	
	struct Course *cprev = NULL;
	struct Task *tprev = NULL;
	struct Goal *gprev = NULL;
	struct Course *course = NULL;
	struct Task *task = NULL;
	struct Goal *goal = NULL;
	
    path = fopen(filename, "r");
    if (path == NULL){
        printf("Plan file not found. Put plan.txt in working directory");
    }
	
    while (fgets(str, max_name_length, path) != NULL){
        strcpy(current->str, str);
		prev->next = current;
		prev = current;
		if (len == 1){
			nhead = prev;
		}
		len++;
	}
	
	current = nhead;
	len = 0;
	
	while (current != NULL){
		strcpy(course->name, current->str);
		while (current->str[0] == 'T'){
			strcpy(task->TaskName,current->str);
			while(current->str[0] == 'G'){
				goal = form_goal(current->str);
				gprev->next = goal;
				if(g == 1){
					gHead = gprev;
				}
				gprev = goal;
				current = current->next;
				g++;				
			}
			task->GoalHead = gHead;
			tprev->next = task;
			if (t == 1){
				tHead = tprev;
			}
			tprev = task;
			t++;
			current = current->next;
		}
		course->head = tHead;
		cprev->next = course;
		if (len == 1){
			head = course;
		}
		cprev = course;
		len++;
		current = current->next;
	}

    fclose(path);
	return head;
}

//------------------------------------------------------------------------------

int main(){
	printf("Bruh.");
	struct Course *head = parseData();
	printf("%s",head->name);
	PrintSummary(head);
	return 0;
}
// All functions in this code run without compiler error.
