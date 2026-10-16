#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char name[50];
    int age;
    struct Person *father;
    struct Person *mother;
} Person;

Person *create_person(const char *name, int age)
{
    Person *person = malloc(sizeof(Person));

    if (person == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    snprintf(person->name, sizeof(person->name), "%s", name);
    person->age = age;
    person->father = NULL;
    person->mother = NULL;

    return person;
}
void link_parents(Person *child, Person *father, Person *mother)
{
	child->father = father;
	child->mother = mother;
}
void read_person_info(const char *role, char *name_out, int *age_out)
{
	char age_input[20];
	printf("Enter name of %s:", role);
	fgets(name_out, 50, stdin);
	name_out[strcspn(name_out,"\n")] = '\0';

	printf("Enter age of %s:", role);
	fgets(age_input, sizeof(age_input), stdin);
	*age_out = atoi(age_input);
}


void print_family_relationships(const Person *me)
{
	printf("\n=== FAMILY TREE RELATIONSHIPS ===\n\n");
	
	printf("1. YOURSELF:\n");
	printf(" - Name: %s | Age: %d\n\n", me->name, me->age);

	printf("2. PARENTS:\n");
	printf("  - Father: %s | Age: %d\n", me->father->name, me->father->age);
	printf("  - Mother: %s | Age: %d\n\n", me->mother->name, me->mother->age);

	printf("3. PATERNAL GRANDPARENTS (via Father's Pointers):\n");
	printf("  - Grandfather : %s | Age: %d\n", me->father->father->name, me->father->father->age);
	printf("  - Grandmother: %s | Age: %d\n\n", me->father->mother->name, me->father->mother->age);

	printf("4. MATERNAL GRANDPARENTS (via Mother's Pointers):\n");
	printf("  - Grandfather : %s | Age: %d\n", me->mother->father->name, me->mother->father->age);
	printf("  - Grandmother : %s | Age: %d\n", me->mother->mother->name, me->mother->mother->age);
}

void free_family_tree(Person *people[], int count)
{
        for(int i=0; i <count; i++) {
        free(people[i]);
}
}

int main(void)
{
	char name[50];
	int age;
 
	printf("Family Tree Project\n");
	
	read_person_info("Paternal Grandfather", name, &age);
	Person *paternal_grandfather = create_person(name, age);

	read_person_info("Paternal Grandmother", name, &age);
        Person *paternal_grandmother = create_person(name, age);

	read_person_info("Maternal Grandfather", name, &age);
        Person *maternal_grandfather = create_person(name, age);

	read_person_info("Maternal Grandmother", name, &age);
        Person *maternal_grandmother = create_person(name, age);

	read_person_info("Father", name, &age);
        Person *father = create_person(name, age);

	read_person_info("Mother", name, &age);
        Person *mother = create_person(name, age);	
	
	read_person_info("Yourself", name, &age);
        Person *me = create_person(name, age);
	
	link_parents(father, paternal_grandfather, paternal_grandmother);
	link_parents(mother, maternal_grandfather, maternal_grandmother);
	link_parents(me, father, mother);
	
	print_family_relationships(me);

	Person *people[] = {
		paternal_grandfather,
		paternal_grandmother,
		maternal_grandfather,
		maternal_grandmother,
		father,
		mother,
		me,
};

     free_family_tree(people, 7);

	return 0;
}
