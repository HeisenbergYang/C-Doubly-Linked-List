// Tomer Elmalem
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Here we are going to write some functions to support a linked list that stores Students (first name, last name, grade, gtid)  */
/* Here is the data the user in this case us will be storing into our linked list */
/* YOU ARE REQUIRED TO COMPLETE THIS PART */
typedef struct Student
{
	char* first_name; /* This will be malloc'd!*/
	char* last_name; /* This will also be malloc'd */
	int grade;
	unsigned int gtid;
} Student;

Student* create_student(const char* first_name, const char* last_name, int grade, unsigned int gtid)
{
  Student *s = malloc(sizeof(Student));

  // allocate the first and last name
  char *f = malloc((strlen(first_name)+1)*sizeof(char));
  char *l = malloc((strlen(last_name)+1)*sizeof(char));

  // copy the provided first and last name into pointers
  strncpy(f, first_name, strlen(first_name)+1);
  strncpy(l, last_name, strlen(last_name)+1);

  // store the pointers and other data in the struct
  s->first_name = f;
  s->last_name = l;
  s->grade = grade;
  s->gtid = gtid;

  return s;
}

/* For these functions below you should never be passed in NULL */
/* You will always get valid data here */
void print_student(void* data)
{
  Student *s = data;
  printf("Student: %s %s\n", s->first_name, s->last_name);
  printf("Grade: %d\n", s->grade);
  printf("GtID: %d\n", s->gtid);
}

void free_student(void* data)
{
  Student *s = data;

  // Free the names first
  free(s->first_name);
  free(s->last_name);
  
  // Then the student
  free(s);
}

int student_eq(const void* a, const void* b)
{
  const Student *s1 = a;
  const Student *s2 = b;

  // If everything between the two students is the same return 1
  if (!strncmp(s1->first_name, s2->first_name, strlen(s1->first_name)) &&
      !strncmp(s2->last_name,  s2->last_name,  strlen(s1->last_name)) &&
      s1->grade == s2->grade &&
      s1->gtid == s2->gtid) {
    return 1;
  } else {
    return 0;
  }
}

/* Predicate function: is the student failing?
 * Takes in a pointer to a student
 * return 1 if grade is lower than 60 (failing)
 * or 0 otherwise.
 */
int student_failing(const void* a) {
  const Student *s = a;
  if (s->grade < 60) return 1;
  return 0;
}

/* This main function does a little testing
   Like all good CS Majors you are required to test
   your code here. There is no substitute for testing
   and you should be sure to test for all edge cases
   e.g., calling remove_front on an empty list.
*/
int main(void) 
{
	/* Now to make use of all of this stuff */
	list* llist = create_list();
  
  	/* What does an empty list contain?  Lets use our handy traversal function */
  	printf("TEST CASE 1\nAn Empty list should print nothing here:\n");
  	traverse(llist, print_student);
	printf("\n");

 	/* Lets add a student and then print */
 	push_front(llist, create_student("Nick", "Polive", 56, 239402128));
 	printf("TEST CASE 2\nA List with one student should print that student:\n");
 	traverse(llist, print_student);
 	printf("\n");
 	
 	/* Lets remove that student and then print */
 	remove_front(llist, free_student);
 	printf("TEST CASE 3\nAnother Empty list should print nothing here:\n");
 	traverse(llist, print_student);
 	printf("\n");

 	/* Lets add two elements and then print */
 	push_front(llist, create_student("Baron", "von Baris", 92, 123456789));
 	push_front(llist, create_student("George", "Burdell", 65, 902313373));
 	printf("TEST CASE 4\nA List with two students should print those two students:\n");
 	traverse(llist, print_student);
 	printf("\n"); 	

 	/* Test find occurence when the node is not found */
	// Notice the commented line below is BAD because the return value from create_student was malloc'd and you never free it!
	// find_occurence(llist, create_student("Nurse", "Joy", 3, 131313137), student_eq));
	Student* p = create_student("Nurse", "Joy", 3, 131313137);
	printf("TEST CASE 5\nFinding occurence when a node is not in the list should fail: \n");
	printf("%d\n", find_occurrence(llist, p, student_eq));
	/* Remember to FREE everything you malloc I malloc'd space for p and now I am done with it so I free it */
	free_student(p);

  	/* Lets kill the list */
  	empty_list(llist, free_student);
 	printf("TEST CASE 6\nAfter freeing all nodes the list should be empty:\n");
 	traverse(llist, print_student);
 	printf("\n"); 	
 	
 	/* YOU ARE REQUIRED TO MAKE MORE TEST CASES THAN THE ONES PROVIDED HERE */
 	/* You will get points off if you do not you should at least test each function here */

        /* Testing the push_back function. Push three people to the front and one to the back.
           Order should be Brandon, Noo, Baron, and then Tinky. */
        // Note that Teletubbies do not make good 2110 students
        push_front(llist, create_student("Baron", "von Baris", 92, 123456789));
        push_front(llist, create_student("Noo", "Noo", 13, 666));
        push_front(llist, create_student("Brandon", "the Destroyer", 200, 54545454));
        push_back(llist, create_student("Tinky", "Winky", 0, 222222222));
        printf("TEST CASE 7\nPush to back. Order should be Brandon, Noo, Baron, Tinky:\n");
        traverse(llist, print_student);
        printf("\n");

        /* Now lets test remove front! Brandon should no longer be in the list */
        remove_front(llist, free_student);
        printf("TEST CASE 8\nRemove front. Brandon should no longer be in the list:\n");
        traverse(llist, print_student);
        printf("\n");

        /* Lets get rid of Tinky. I never liked that guy anyway. */
        remove_back(llist, free_student);
        printf("TEST CASE 9\nRemove back. Tinky should no longer by in the list:\n");
        traverse(llist, print_student);
        printf("\n");

        /* Lets test the index removal before the list gets too small */
        remove_index(llist, 1, free_student);
        printf("TEST CASE 10\nRemove by index. Remove the student at index 1, Baron should no longer be in the list:\n");
        traverse(llist, print_student);
        printf("\n");

        /* K, time for a new list. */
  	empty_list(llist, free_student);
        push_front(llist, create_student("Baron", "von Baris", 92, 123456789));
        push_front(llist, create_student("Noo", "Noo", 13, 666));
        push_front(llist, create_student("Brandon", "the Destroyer", 200, 54545454));
        push_back(llist, create_student("Tinky", "Winky", 0, 222222222));
        push_back(llist, create_student("Tinky", "Winky", 0, 222222222));

        /* Oh no! We've accidentally added Tinky to the list twice but I don't want him there at all!
           Time to test the remove_data function and rid us of Tinky. */
        p = create_student("Tinky", "Winky", 0, 222222222);
        int removed = remove_data(llist, p, student_eq, free_student);
        printf("TEST CASE 11\nRemove data. A new list was created and Twinky was accidentally added twice. I don't want him there at all so lets test the remove data function. Tinky should not be in the list:\n");
        traverse(llist, print_student);
        printf("Occurences removed: %d\n", removed);
        printf("\n");
        free_student(p);

        /* If we try to remove Tinky again, nothing should happen */
        p = create_student("Tinky", "Winky", 0, 222222222);
        removed = remove_data(llist, p, student_eq, free_student);
        printf("TEST CASE 12\nRemove data. If we try to remove Tinky again nothing should happen:\n");
        traverse(llist, print_student);
        printf("Occurences removed: %d\n", removed);
        printf("\n");
        free_student(p);

        /* Time to test the retrieval functions */
        printf("TEST CASE 13\nFront. Lets get the front of the list. Should be Brandon:\n");
        print_student(front(llist));
        printf("\n");

        /* Testing the get_index function */
        printf("TEST CASE 14\nGet index. Lets get the student at index 1. Should be Noo:\n");
        print_student(get_index(llist, 1));
        printf("\n");

        /* Test the back function */
        printf("TEST CASE 15\nBack. Let's get the student at the back of the list. Should be Baron:\n");
        print_student(back(llist));
        printf("\n");

        /* Test if the list is empty */
        printf("TEST CASE 16\nIs empty. Is the list empty? (should be no)\n");
        printf(is_empty(llist) ? "Yes\n" : "No\n");
        printf("\n");

        /* Test the size */
        printf("TEST CASE 17\nSize. What is the size of the list? (should be 3)\n");
        printf("%d\n", size(llist));
        printf("\n");

        /* Test if exists */
        p = create_student("Baron", "von Baris", 92, 123456789);
        printf("TEST CASE 18\nFind occurence. Does the student Baron von Baris exist in the list? (should be yes)\n");
        printf(find_occurrence(llist, p, student_eq) ? "Yes\n" : "No\n");
        printf("\n");
        free_student(p);

        /* Lets test some of the functions on a list size of 0 */
        empty_list(llist, free_student);

        /* Push to front is obviously working at this point */

        /* Test push back */
        push_back(llist, create_student("Baron", "von Baris", 92, 123456789));
        printf("TEST CASE 19\nPush back on empty list:\n");
        traverse(llist, print_student);
        printf("\n");
        empty_list(llist, free_student);

        /* Test remove front on empty list */
        printf("TEST CASE 20\nRemove fromt on empty list: (should fail and return -1)\n");
        printf("%d\n", remove_front(llist, free_student));
        printf("\n");

        /* Test remove index on empty list */
        printf("TEST CASE 21\nRemove index on empty list: (should fail and return -1)\n");
        printf("%d\n", remove_index(llist, 0, free_student));
        printf("\n");

        /* Test remove back on empty list */
        printf("TEST CASE 22\nRemove back on empty list: (should fail and return -1)\n");
        printf("%d\n", remove_back(llist, free_student));
        printf("\n");

        /* Test remove data on empty list */
        p = create_student("Baron", "von Baris", 92, 123456789);
        printf("TEST CASE 23\nRemove data on empty list: (nothing should happen, should return 0)\n");
        printf("%d\n", remove_data(llist, p, student_eq, free_student));
        printf("\n");
        free_student(p);

        /* Test front on an empty list */
        printf("TEST CASE 24\nFront on empty list:\n");
        printf("%d\n", (int)front(llist));
        printf("\n");

        /* Test back on an empty list */
        printf("TEST CASE 25\nBack on empty list:\n");
        printf("%d\n", (int)back(llist));
        printf("\n");

        /* Test get index on empty list */
        printf("TEST CASE 26\nGet index on empty list:\n");
        printf("%d\n", (int)get_index(llist, 0));
        printf("\n");

        /* Test is empty on empty list */
        printf("TEST CASE 27\nIs empty on empty list:\n");
        printf("%d\n", is_empty(llist));
        printf("\n");

        /* Test find occurrence on empty list */
        p = create_student("Baron", "von Baris", 92, 123456789);
        printf("TEST CASE 28\nFind occurrence on empty list:\n");
        printf("%d\n", find_occurrence(llist, p, student_eq));
        printf("\n");
        free_student(p);

        /* Now what happens if you empty an empty list? */
        empty_list(llist, free_student);

        /* Lets test a list of size 1 */
        push_front(llist, create_student("Baron", "von Baris", 92, 123456789));
        
        /* Test push back on list of size 1 */
        push_back(llist, create_student("Noo", "Noo", 13, 666));
        printf("TEST CASE 29\nPush back on list of size 1. Should be Baron then Noo:\n");
        traverse(llist, print_student);
        printf("\n");
        empty_list(llist, free_student);

        /* Lets test remove back on list of size 1 */
        push_front(llist, create_student("Baron", "von Baris", 92, 123456789));
        printf("TEST CASE 30\nRemove back on list of size 1. Should be empty:\n");
        remove_back(llist, free_student);
        printf("\n");

        /* Lets remove index on list of size 1 */
        push_front(llist, create_student("Baron", "von Baris", 92, 123456789));
        printf("TEST CASE 31\nRemove index on list of size 1. Should be empty:\n");
        remove_index(llist, 0, free_student);
        traverse(llist, print_student);
        printf("\n");

        /* Test remove data on list of size 1 */
        push_front(llist, create_student("Baron", "von Baris", 92, 123456789));
        p = create_student("Baron", "von Baris", 92, 123456789);
        printf("TEST CASE 32\nRemove data on list of size 1: (should return 1)\n");
        printf("%d\n", remove_data(llist, p, student_eq, free_student));
        printf("\n");
        free_student(p);

        /* Test front of a list of size 1 */
        push_front(llist, create_student("Baron", "von Baris", 92, 123456789));
        printf("TEST CASE 33\nFront of a list of size 1: (should be Baron)\n");
        print_student(front(llist));
        printf("\n");

        /* Test back of a list of size 1 */
        printf("TEST CASE 34\nBack of a list of size 1: (should be Baron)\n");
        print_student(back(llist));
        printf("\n");

        /* Test get index of a list of size 1 */
        printf("TEST CASE 35\nGet index of a list of size 1: (should be Baron)\n");
        print_student(get_index(llist, 0));
        printf("\n");
        
        empty_list(llist, free_student);
        /* Test remove if */
        push_front(llist, create_student("Baron", "von Baris", 92, 123456789));
        push_front(llist, create_student("Noo", "Noo", 13, 666));
        push_front(llist, create_student("Brandon", "the Destroyer", 200, 54545454));
        push_back(llist, create_student("Tinky", "Winky", 0, 222222222));
        push_back(llist, create_student("Tinky", "Winky", 0, 222222222));
        push_front(llist, create_student("Baron", "von Baris", 2, 123456789));
        printf("TEST CASE 36\nRemove if (should only display students with grades higher then 60):\n");
        remove_if(llist, student_failing, free_student);
        traverse(llist, print_student);
        printf("\n");

        /* Empty the list now that we're done with it */
        empty_list(llist, free_student);

 	/* Testing over clean up*/
 	free(llist);
 	
  	return 0;
}
