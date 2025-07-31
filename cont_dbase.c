#include <stdio.h>
#include <string.h>


//  Максимальная длина введенных пользователем данных
#define CHAR_LIM 50
//  Максимальное количество контактов в книге
#define CONTACT_LIM 100 


//  Структура описывает имя, фамилию, телефон и email
typedef struct {
	char firstname[CHAR_LIM];
	char lastname[CHAR_LIM];
	char phone[CHAR_LIM];
	char email[CHAR_LIM];
} Contact;


//  Запуск программы книги контактов
void contact_book(Contact *data, int len);


//  Стартовая фраза
void introductory_phrase();
//  Фраза перед завершением программы
void last_phrase();


//  Вывод опций
void selection_menu(Contact *data, int len);
//  Ввод пользователем номера опции
void enter_menu(char *answer, int len);
//  Переход к нужной опции
int select_item(Contact *data, int len);


//  Добавление контакта в книгу
void add_contact(Contact *data, int len);
//  Ввод контакта пользователем
void input_new_contact(Contact *data, int len);


//  Вывод всех хранящихся контактов
void display_all_contacts(Contact *data, int len);
//  Вывод одного переданного контакта
void print_contact(Contact person);


//  Поиск индекса контакта по заданным имени и фамилии
int find_contact_index(Contact *data, int len, char *name1, char *name2);
//  Очистка буфера ввода
void clear_buffer();
//  Ввод пользователем имени и фамилии контакта
void enter_full_name(char *name1, char *name2);
//  Удаление контакта по переданному индексу
void clear_contact(Contact *data, int index);


//  Поиск и вывод полной информации о контакте по его местоположению
void find_contact(Contact *data, int len);
//  Поиск контакта и удаление информации о нем
void delete_contact(Contact *data, int len);


//  Меняет местами элементы в массиве с контактами
void swap_contacts(Contact *a, Contact *b);
//  Сравнивает имя и фамилию пользователей для функции сортировки
int name_comparison(Contact el, Contact key);
//  Сортирует контакты по имени и фамилии с помощью вставок
void insertion_sort_for_contacts(Contact *data, int len);


int main()
{
	Contact data[CONTACT_LIM] = {0};
	
	contact_book(data, CONTACT_LIM);
	
	return 0;
}


void contact_book(Contact *data, int len)
{
	introductory_phrase();
	
	selection_menu(data, len);
	
	last_phrase();
}


void introductory_phrase()
{
	printf("Hello! In this program you can interact\n");
	printf("with the contact book. Let's go started.\n");
}


void last_phrase()
{
	printf("\nSee you later. Bye!\n");
}


void selection_menu(Contact *data, int len)
{
	do {
	printf("\n1 - Add contact\n");
	printf("2 - Show all contacts\n");
	printf("3 - Find contact\n");
	printf("4 - Delete contact\n");
	printf("5 - Exit\n\n");
	} while (select_item(data, len) == 0);
}


void enter_menu(char *answer, int len)
{
	fgets(answer, len, stdin);
	
	while (strlen(answer) != 2 || 
		!('1' <= answer[0] && answer[0] <= '5')) {
			
		printf("Wrong answer, try again\n");
		
		fgets(answer, len, stdin);
	}
}


int select_item(Contact *data, int len)
{
	char answer[CHAR_LIM] = {0};
	
	enter_menu(answer, sizeof(answer));
	
	switch (answer[0]) {
		case '1': add_contact(data, len); break;
		case '2': display_all_contacts(data, len); break;
		case '3': find_contact(data, len); break;
		case '4': delete_contact(data, len); break;
		case '5': return 1;
	}
	
	return 0;
}


void add_contact(Contact *data, int len)
{
	printf("Format: Firstname Lastname Phone Email\n\n");
	
	input_new_contact(data, len);
	
	insertion_sort_for_contacts(data, len);
}


void input_new_contact(Contact *data, int len)
{
	int k = 0;
	
	for (int i = 0; data[i].firstname[0] != '\0'; i++)
		k = i + 1;
		
	if (k >= len) {
    printf("The contact book is full!\n");
    return;
	}
		
	scanf("%s %s %s %s", data[k].firstname, data[k].lastname, data[k].phone, data[k].email);
	
	clear_buffer();
}


void display_all_contacts(Contact *data, int len)
{
	printf("\nFirstname  Lastname  Phone  Email");
	printf("\n---------------------------------\n");
	
	for (int i = 0; i < len; i++) {
		if (data[i].firstname[0] != '\0') {
			print_contact(data[i]);
		}
	}
		
	printf("---------------------------------\n");
}


void print_contact(Contact person)
{
	printf("%s %s %s %s\n", person.firstname, person.lastname, person.phone, person.email);
}


int find_contact_index(Contact *data, int len, char *name1, char *name2)
{
	int index = -1;
	
	for (int i = 0; i < len; i++) {
		if (strcmp(data[i].firstname, name1) == 0 && strcmp(data[i].lastname, name2) == 0) {
			index = i;
		}
	}
	
	return index;
}


void clear_buffer()
{
	for (int c = getchar(); c != '\n' && c != EOF; c = getchar())
		;
}


void enter_full_name(char *name1, char *name2)
{
	scanf("%s %s", name1, name2);
	
	clear_buffer();
}


void clear_contact(Contact *data, int index)
{
	data[index].firstname[0] = '\0';
	data[index].lastname[0] = '\0';
	data[index].phone[0] = '\0';
	data[index].email[0] = '\0';
}


void find_contact(Contact *data, int len)
{
	char name1[CHAR_LIM] = {0};
	char name2[CHAR_LIM] = {0};
	int index;
	
	printf("Format: Firstname Lastname\n\n");
	
	enter_full_name(name1, name2);
	
	index = find_contact_index(data, len, name1, name2);
	
	if (index != -1) {
		printf("\nThis contact found:\n");
		print_contact(data[index]);
	} else {
		printf("\nThis contact not found\n");
	}
}


void delete_contact(Contact *data, int len)
{
	char name1[CHAR_LIM] = {0};
	char name2[CHAR_LIM] = {0};
	int index;
	
	printf("Format: Firstname Lastname\n\n");
	
	enter_full_name(name1, name2);
	
	index = find_contact_index(data, len, name1, name2);
	
	if (index != -1) {
		clear_contact(data, index);
		printf("\nDelete successful\n");
	} else {
		printf("\nDelete not successful. This Contact not found\n");
	}
}


void swap_contacts(Contact *a, Contact *b)
{
	Contact temp = *a;
	*a = *b;
	*b = temp;
}


int name_comparison(Contact el, Contact key)
{
	if (el.firstname[0] == '\0')
		return 1;
		
	int result = 0;
	int comparison_result = strcmp(el.firstname, key.firstname);
	
	if (comparison_result > 0) {
		result = 1;
	} else if (comparison_result == 0 && strcmp(el.lastname, key.lastname) > 0) {
		result = 1;
	}
	
	return result;
}


void insertion_sort_for_contacts(Contact *data, int len)
{
	for (int i = 1; i < len; i++) {
		Contact key = data[i];
		int k = i - 1;
		
		if (key.firstname[0] == '\0')
			continue;
			
		while (k >= 0 && name_comparison(data[k], key)) {
			data[k + 1] = data[k];
			k--;
		}
		
		data[k + 1] = key;
	}
}
