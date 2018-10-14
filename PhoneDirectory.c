#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

struct directory {
   char f_name[100];
   char l_name[50];
   char ph_no[50];
};

struct directory dir[100];
struct directory search_cont;
int cnt = 0;

void create(char * filename) {                //Function to create directory
  FILE * f = fopen(filename, "r");

  if (f != NULL) {
    while (1) {
      int t = fscanf(f, "%s %s %s", dir[cnt].f_name, dir[cnt].l_name, dir[cnt].ph_no);
      dir[cnt].l_name[strlen(dir[cnt].l_name) - 1] = '\0';
      if (t == EOF)
        break;
      cnt++;
    }

  }
  fclose(f);

}

void display() {                             //Function to display directory                           
  for (int i = 0; i < cnt; i++) {
    printf("%s %s %s\n", dir[i].f_name, dir[i].l_name, dir[i].ph_no);
  }
}

void insert(char * name, char * phone_no) {  //Function to insert a new entry into dictionary
  char * arr[10];
  int c = 0;
  int flag = 0;
  arr[c] = strtok(name, " ");
  while (arr[c] != NULL) {
    arr[++c] = strtok(NULL, " ");
  }
  for (int i = 0; i < cnt; ++i) {
    if (strcmp(dir[i].f_name, arr[0]) == 0) {
      if (strcmp(dir[i].l_name, arr[1]) == 0) {
        if (strcmp(dir[i].ph_no, phone_no) == 0) {
          printf("\nentry already exist in the directory\n");
          flag = 1;
        }
      }
    }
  }
  if (flag != 1) {
    strcpy(dir[cnt].f_name, arr[0]);
    strcpy(dir[cnt].l_name, arr[1]);
    strcpy(dir[cnt].ph_no, phone_no);
    cnt++;
  }
}

void deleteEntry(char * name1) {            //Function to delete an entry from dictionary
  char * array1[10];
  int i = 0;
int temp1=0;
 
  array1[i] = strtok(name1, " ");
  while (array1[i] != NULL) {
    array1[++i] = strtok(NULL, " ");
  }
  int flag = 0;
  for (int i = 0; i < cnt; ++i) {
    if (strcmp(dir[i].f_name, array1[0]) == 0) {
      if (strcmp(dir[i].l_name, array1[1]) == 0) {
                temp1=i;
           }
    }
  }
        for (int j = temp1 + 1; j < cnt; ++j) {
          memcpy( & dir[j - 1], & dir[j], sizeof(struct directory));
          flag = 1;
        }
        cnt = cnt - 1;
      
  if (flag == 0) {
    printf("Unabale to delete as entry not found");
  }
}

void search(struct directory search_cont, int low, int high) {    
  if (low > high) {
    printf("Name Not Found");
  } else {
    int mid = (low + high) / 2;
    if (strcmp(search_cont.f_name, dir[mid].f_name) == 0) {
      if (strcmp(search_cont.l_name, dir[mid].l_name) == 0) {
        for (int i = 0; i < cnt; ++i) {
          if (strcmp(dir[i].f_name, dir[mid].f_name) == 0)
            if (strcmp(dir[i].l_name, dir[mid].l_name) == 0) {
              printf("%d %s %s %s\n",i+1, dir[i].f_name, dir[i].l_name, dir[i].ph_no);
            }

        }

      } else if (strcmp(search_cont.l_name, dir[mid].l_name) < 0) {
        search(search_cont, 0, mid - 1);
      } else {
        search(search_cont, mid + 1, high);
      }
    } else if (strcmp(search_cont.f_name, dir[mid].f_name) < 0) {
      search(search_cont, 0, mid - 1);
    } else {
      search(search_cont, mid + 1, high);
    }
  }
}

void searchDirectory(char * name) {            //Function to search a contact from dictionary
  char * arr1[10];
  int i = 0;
  arr1[i] = strtok(name, " ");
  while (arr1[i] != NULL) {
    arr1[++i] = strtok(NULL, " ");
  }
  strcpy(search_cont.f_name, arr1[0]);
  strcpy(search_cont.l_name, arr1[1]);
  search(search_cont, 0, cnt - 1);
}

int compare(struct directory s1, struct directory s2) {
  if (strcmp(s1.f_name, s2.f_name) < 0) {
    return -1;
  } else if (strcmp(s1.f_name, s2.f_name) > 0) {
    return 1;
  } else {
    if (strcmp(s1.l_name, s2.l_name) < 0) {
      return -1;
    } else if (strcmp(s1.l_name, s2.l_name) > 0) {
      return 1;
    } else {
      if (strcmp(s1.ph_no, s2.ph_no) < 0) {
        return -1;
      } else {
        return 1;
      }
    }
  }
}

void swap(struct directory * p, struct directory * q) {
  struct directory temp;
  memcpy( & temp, p, sizeof(struct directory));
  memcpy(p, q, sizeof(struct directory));
  memcpy(q, & temp, sizeof(struct directory));
}

int divide(struct directory * qsort, int a, int b) {
  int pIndex = a + rand() % (b - a + 1);
  struct directory pivot;
  int i = a - 1;
  memcpy( & pivot, & qsort[pIndex], sizeof(struct directory));
  swap( & qsort[pIndex], & qsort[b]);
  for (int j = a; j < b; j++) {
    if (compare(qsort[j], pivot) < 0) {
      i++;
      swap( & qsort[i], & qsort[j]);
    }

  }
  swap( & qsort[i + 1], & qsort[b]);
  return i + 1;
}

void quick(struct directory * qsort, int f, int l) {
  int i;
  if (f < l) {
    i = divide(qsort, f, l);
    quick(qsort, f, i - 1);
    quick(qsort, i + 1, l);
  }
}

void sortDirectory() {
  quick(dir, 0, cnt - 1);
}

void main(int argc, char * argv[]) {
  int choice = 0;
  int i;

  char p_no[20];
  char del[50];
  char fname[10];
  char lname[10];

  int val = 0;
  create(argv[1]);
  while (1) {
    printf("\n1. Sort contacts\n");
    printf("2. Insert a new contact\n");
    printf("3. Search a contact\n");
    printf("4. Delete a existing contact\n");
    printf("5. Display the directory\n");
    printf("6. Exit\n");
    printf("Enter your choice : ");
    scanf("%d", & choice);
    switch (choice) {
    case 1:
     
      sortDirectory();
      for (i = 0; i < cnt; ++i)
        printf("%s %s, %s\n", dir[i].f_name, dir[i].l_name, dir[i].ph_no);
      break;

    case 2:

      printf("\n Enter The first and last name : ");
      scanf("%s %s", fname, lname);
      char * fullname = (char * ) malloc(1 + strlen(fname) + strlen(lname));
      strcpy(fullname, fname);
      strcat(strcat(fullname, " "), lname);
      char name[50];
      strcpy(name, fullname);
      printf("\n Enter phone number : ");
      scanf("%s", p_no);
      insert(name, p_no);
      break;

    case 3:
      printf("\n Enter The first and last name : ");
      scanf("%s %s", fname, lname);

      char * fullname2 = (char * ) malloc(1 + strlen(fname) + strlen(lname));
      strcpy(fullname2, fname);
      strcat(strcat(fullname2, " "), lname);
      char name2[50];
      strcpy(name2, fullname2);
      searchDirectory(name2);

      break;
    case 4:
      
      printf("\n Enter The first and last name : ");
      scanf("%s %s", fname, lname);
      char * fullname1 = (char * ) malloc(1 + strlen(fname) + strlen(lname));
      strcpy(fullname1, fname);
      strcat(strcat(fullname1, " "), lname);
      char name1[50];
      strcpy(name1, fullname1);
      deleteEntry(name1);
      break;

    case 5:
      display();
      break;

    case 6:
      exit(0);

      break;

    default:
      break;
    }
  }
}

