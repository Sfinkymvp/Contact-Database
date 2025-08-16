#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//  Максимальное количество контактов в базе данных
const int CONTACT_LIM 100 
//  Максимальная длина введенных пользователем данных
const int CHAR_LIM 50

//  Структура описывает имя, фамилию, телефон и email
typedef struct {
	char firstname[CHAR_LIM];
	char lastname[CHAR_LIM];
	char phone[CHAR_LIM];
	char email[CHAR_LIM];
} Contact;

//  Запуск программы базы данных контактов
void get_contact_database(Contact *data, int len);

//  Печать стартовой фразы
void print_greeting();
//  Печать последней фразы
void print_farewell();

//  Вывод опций
void select_menu(Contact *data, int len);
//  Ввод пользователем номера опции
int enter_menu_option();
//  Переход к нужной опции
int select_option(Contact *data, int len);

//  Добавление контакта в базу данных
void add_contact(Contact *data, int len);
//  Ввод контакта пользователем
void enter_contact(Contact *data, int len);

//  Вывод всех хранящихся контактов
void display_all_contacts(Contact *data, int len);
//  Вывод одного переданного контакта
void print_contact(Contact person);

//  Проверяет, содержит ли что-нибудь кроме пробельных символов буфер ввода
int is_input_buffer_clean();
//  Очистка буфера ввода
void clear_input_buffer();
//  Очистка терминала
void clear_screen();

//  Поиск индекса контакта по заданным имени и фамилии
int find_contact_index(Contact *data, int len, char *name1, char *name2);
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

//  Экспорт контактов
void save_contacts(Contact *data, int len);
//  Переносит контакты в файл
void transfer_contacts(Contact *data, int len, char *file);
//  Ввод пользователем файла, в который будет произведено сохранение
void enter_file(char *file, int max_name_len);

//  Импорт контактов
void load_contacts(Contact *data, int len);
//  Переносит контакты из файла
void loading_contacts(Contact *data, int len, char *file);
//  Проверяет, существует ли файл или нет
int file_exists(char *file);

int main()
{
	Contact data[CONTACT_LIM] = {0};
	
	get_contact_database(data, CONTACT_LIM);
	
	return 0;
}


void get_contact_database(Contact *data, int len)
{	
	print_greeting();
	
	select_menu(data, len);
	
	print_farewell();
}


void print_greeting()
{
	printf("Hello! In this program you can interact\n"
           "with the contact book. Let's go started.\n");
}


void print_farewell()
{
	printf("See you later. Bye!\n");
}


void select_menu(Contact *data, int len)
{
	do {    
	    printf("1 - Add contact\n"
               "2 - Show all contacts\n"
               "3 - Find contact\n"
               "4 - Delete contact\n"
               "5 - Exit\n"
               "6 - Save contacts to file\n"
               "7 - Load contacts from file\n\n");
	} while (select_option(data, len) == 0);
}


int enter_menu_option()
{
    while (1) {
        int answer = getchar();

        if (is_input_buffer_clean() && '1' <= answer && answer <= '7')
            return answer;

        clear_input_buffer();
        printf("Try again\n");
    }
}


int select_option(Contact *data, int len)
{
    int answer = enter_menu_option();
    
    clear_screen();

	switch (answer) {
		case '1': add_contact(data, len); break;
		case '2': display_all_contacts(data, len); break;
		case '3': find_contact(data, len); break;
		case '4': delete_contact(data, len); break;
		case '5': return 1;
		case '6': save_contacts(data, len); break;
		case '7': load_contacts(data, len); break;
	}
	
	return 0;
}


void add_contact(Contact *data, int len)
{
	printf("Format: Firstname Lastname Phone Email\n\n");
	
	enter_contact(data, len);
	
	insertion_sort_for_contacts(data, len);
}


void enter_contact(Contact *data, int len)
{
	int k = 0;
	
	for (int i = 0; data[i].firstname[0] != '\0'; i++)
		k = i + 1;
		
	if (k >= len) {
	    printf("\nThe contact book is full!\n");
	    return;
	}
		
	scanf("%s %s %s %s", data[k].firstname,
						 data[k].lastname,
						 data[k].phone,
						 data[k].email);
	
	clear_input_buffer();
}


void display_all_contacts(Contact *data, int len)
{
	printf("Firstname  Lastname  Phone  Email");
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
	printf("%s %s %s %s\n", person.firstname,
							person.lastname,
							person.phone,
							person.email);
}


int is_input_buffer_clean()
{
    for (int c = getchar(); c != '\n' && c != EOF; c = getchar())
        if (!isspace(c))
            return 0;

    return 1;
}


void clear_input_buffer()
{
	for (int c = getchar(); c != '\n' && c != EOF; c = getchar())
		;
}


void clear_screen() {
#ifdef _WIN32
	system("cls");    // Windows
#else
	system("clear");  // Linux или Mac
#endif
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


void enter_full_name(char *name1, char *name2)
{
	scanf("%s %s", name1, name2);
	
	clear_input_buffer();
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


void save_contacts(Contact *data, int len)
{
	char file[CHAR_LIM] = {0};
	
	enter_file(file, sizeof(file));

	transfer_contacts(data, len, file);
}


void transfer_contacts(Contact *data, int len, char *file)
{
	FILE * fout = fopen(file, "w");

	if (!fout) {
		printf("\nFailed to write data to the specified file\n");
		return;
	}

	for (int i = 0; i < len; i++) {
		if (data[i].firstname[0] != '\0') {
			fprintf(fout, "%s %s %s %s\n", data[i].firstname,
										   data[i].lastname,
										   data[i].phone,
										   data[i].email);
		}
	}

	fclose(fout);

	printf("\nSave successful\n");
}


void enter_file(char *file, int max_name_len)
{
	printf("Enter the name of the file\n\n");
	
	fgets(file, max_name_len, stdin);
	
	file[strcspn(file, "\n")] = '\0';
}


void load_contacts(Contact *data, int len)
{
	char file[CHAR_LIM] = {0};

	enter_file(file, sizeof(file));

	if (!file_exists(file)) {
		printf("\nFile not found for import\n");
		return;
	}

	loading_contacts(data, len, file);

	printf("\nContacts added\n");
}


void loading_contacts(Contact *data, int len, char *file)
{
	FILE * fin = fopen(file, "r");

	for (int i = 0; i < len; i++) {
		if (data[i].firstname[0] != '\0')
			continue;

		int count = fscanf(fin, "%s %s %s %s", data[i].firstname,
											   data[i].lastname, 
											   data[i].phone,
											   data[i].email);
											   
		if (count != 4)
			break;						
	}

	fclose(fin);
}


int file_exists(char *file)
{
	FILE * fcheck = fopen(file, "r");

	if (!fcheck)
		return 0;

	fclose(fcheck);
	return 1;
}


