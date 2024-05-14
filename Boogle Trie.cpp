#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define cls system("cls");
#define size 26

#define WHITE "\e[1;37m"
#define RESET "\x1b[0m"

int choice;
int count = 1;	

/* Design */
void mainMenu();
void exit();
void releaseArt();
void searchArt();
void viewPrefixArt();
void viewAllArt();

typedef struct trieNode{
	struct trieNode* child[size];
	char wordDescription[101];
	int isEnd;
} trieNode;

trieNode* createNode(){
	trieNode* node = (trieNode*)malloc(sizeof(trieNode));
	
	strcpy(node->wordDescription, "");
	node->isEnd = 0;
	
	for(int i=0; i<size; i++){
		node->child[i] = NULL;
	}
	
	return node;
}

trieNode *insert(trieNode* root, char* word, char* wordDesc){
	trieNode* curr = root;
	
	for(int i=0; i<strlen(word); i++){
		int idx = word[i] - 'a';
		if(!curr->child[idx]){
			curr->child[idx] = createNode();
		}
		curr = curr->child[idx];
	}
	
	if(curr->isEnd == 1){
		strcpy(curr->wordDescription, wordDesc);
	}
	else{
		strcpy(curr->wordDescription, wordDesc);
		curr->isEnd = 1;
	}
	
	return root;
}

trieNode* searchTrie(trieNode* root, char* word){
	trieNode* curr = root;
	
	for(int i=0; i<strlen(word); i++){
		int idx = word[i] - 'a';
		if(curr->child[idx] == NULL){
			return NULL;
		}
		curr = curr->child[idx];
	}
	
	if(curr != NULL && curr->isEnd == 1){
		return curr;
	}
	
	return NULL; 
}

/* Start number 1 */
bool checkWord(char* word){
	int len = strlen(word);
	
	if(len <= 1){
		return false;
	}
	
	for(int i=0; i<len; i++){
		if(word[i] == ' '){
			return false;
		}
	}
	
	return true;
}

bool checkWordDesc(char* wordDesc){
	int temp = 0;
	
	for(int i=0; i<strlen(wordDesc); i++){
		if(wordDesc[i] == ' '){
			if(wordDesc[0] == ' '){
				printf("First character must not be space!\n");
				return false;
			}
			temp++;
		}
	}
	
	if(temp >= 2){
		return true;
	}
	
	return false;
}

void release(trieNode* root){
	cls;
	
	releaseArt();
	
	char word[101];
	char wordDesc[101];
	
	do{
		printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
		scanf("%[^\n]", &word); getchar();
		
		for(int i=0; i<strlen(word); i++){
			if(word[i] >= 'A' && word[i] <= 'Z'){
				word[i] += 32;
			}
		}
	} while(!checkWord(word));
	
	do{
		printf("Input a new slang word description [Must be more than 2 words]: ");
		scanf("%[^\n]", &wordDesc); getchar();
	} while(!checkWordDesc(wordDesc));
	
	if(searchTrie(root, word)){
		printf("\nSuccessfully updated a slang word.\n");
	}
	else{
		printf("\nSuccessfully released new slang word.\n");
	}
	root = insert(root, word, wordDesc);
	
	printf("Press enter to continue...");
	getchar();
	return mainMenu();
}
/* End  number 1*/


/* Start number 2 */
void search(trieNode* root){
	cls;
	
	searchArt();
	
	char searchWord[101];
	
	do{
		printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
		scanf("%[^\n]", &searchWord); getchar();
		
		for(int i=0; i<strlen(searchWord); i++){
			if(searchWord[i] >= 'A' && searchWord[i] <= 'Z'){
				searchWord[i] += 32;
			}
		}
	} while(!checkWord(searchWord));
	
	trieNode* found = searchTrie(root, searchWord);
	if(found){
		printf("\nSlang Word has found!\n");
		printf("Slang word  : %s\n", searchWord);
		printf("Description : %s\n", found->wordDescription);
	}
	else{
		printf("\nThere is no word \"%s\" in the dictionary.\n", searchWord);
	}
	
	printf("\nPress enter to continue...");
	getchar();
	return mainMenu();
}
/* End number 2 */


/* Start number 3 */
int searchPreWord(trieNode* root, char* preWord, char* buffer, int depth){
	if(!root){
		return 0;
	}
	
	if(preWord[0] != '\0'){
		int idx = preWord[0] - 'a';
		if(!root->child[idx]){
			return 0;
		}
		buffer[depth] = preWord[0];
		searchPreWord(root->child[idx], preWord+1, buffer, depth+1);
	}
	
	if(root->isEnd){
		buffer[depth] = '\0';
		printf("%2d. %s\n", count, buffer);
		count++;
	}
	
	int found = root->isEnd;
	for(int i=0; i<size; i++){
		if(root->child[i]){
			found = 1;
			buffer[depth] = i + 'a';
			searchPreWord(root->child[i], preWord, buffer, depth+1);
		}
	}
	
	return found;
}

void viewPrefix(trieNode* root){
	cls;
	
	viewPrefixArt();
	
	char preWord[101];
	count = 1;
	
	printf("Input a prefix to be searched: ");
	scanf("%s", &preWord); getchar;
	puts("");
	
	for(int i=0; i<strlen(preWord); i++){
		if(preWord[i] >= 'A' && preWord[i] <= 'Z'){
			preWord[i] += 32;
		}
	}
	
	char buffer[101];
	int depth = 0;
	int found = searchPreWord(root, preWord, buffer, depth);
	if(!found){
		printf("There is no prefix \"%s\" in the dictionary.\n\n", preWord);
	}
	else{
		printf("The list above is a words starts with \"%s\"\n\n", preWord);
	}
	printf("Press enter to continue...");
	getchar();
	getchar();
	return mainMenu();
}
/* End number 3*/


/* Start number 4*/
bool hasRoot(trieNode* root){
	trieNode* curr = root;
	
	for(int i = 0; i<size; i++){
		if(curr->child[i]){
			return true;
		}
	}
	
	return false;
}

void printTrie(trieNode* root, char* buffer, int idx, int* ind){
	
	if(root->isEnd){
		buffer[idx] = '\0';
		printf("%2d. %s\n", ++(*ind), buffer);
	}
	
	for(int i=0; i<size; i++){
		if(root->child[i]){
			buffer[idx] = i + 'a';
			printTrie(root->child[i], buffer, idx+1, ind);
		}
	}
	
}

void viewAll(trieNode* root){
	cls;
	
	viewAllArt();
	
	int idx = 0;
	int ind = 0;
	char buffer[101];
	
	if(!hasRoot(root)){
		printf("There is no slang word yet in the dictionary.\n");
	}
	else{
		printf("List of all slang words in the dictionary:\n");
		printTrie(root, buffer, idx, &ind);
	}
	
	printf("\nPress enter to continue...");
	getchar();
	return mainMenu();
}
/* End number 4 */


int main(){
	trieNode* root = createNode();
	
	printf(WHITE);
	mainMenu();
	while(true){
		switch(choice){
			case 1:{
				release(root);
				break;
			}
			case 2:{
				search(root);
				break;
			}
			case 3:{
				viewPrefix(root);
				break;
			}
			case 4:{
				viewAll(root);
				break;
			}
			case 5:{
				exit();
				break;
			}
			default:{
				mainMenu();
				break;
			}
		}
	}
	printf(RESET);
	
	return 0;
}


void mainMenu(){
	cls;
	puts("    ____                    __   ");
	puts("   / __ )____  ____  ____ _/ /__ ");
  	puts("  / __  / __ \\/ __ \\/ __ `/ / _ \\");
 	puts(" / /_/ / /_/ / /_/ / /_/ / /  __/");
	puts("/_____/\\____/\\____/\\__, /_/\\___/ ");
	puts("                  /____/         ");
	puts("");
	puts("1. Release a new slang word");
	puts("2. Search a slang word");
	puts("3. View all slang words starting with a certain prefix word");
	puts("4. View all slang words");
	puts("5. Exit");
	printf(">> ");
	scanf("%d", &choice); getchar();
}

void releaseArt(){
	puts("    ____       __                       _       __               __");
	puts("   / __ \\___  / /__  ____ _________    | |     / /___  _________/ /");
	puts("  / /_/ / _ \\/ / _ \\/ __ `/ ___/ _ \\   | | /| / / __ \\/ ___/ __  /");
	puts(" / _, _/  __/ /  __/ /_/ (__  )  __/   | |/ |/ / /_/ / /  / /_/ /");
	puts("/_/ |_|\\___/_/\\___/\\__,_/____/\\___/    |__/|__/\\____/_/   \\__,_/");
	puts("");
}

void searchArt(){
	puts("   _____                      __      _       __               __");
	puts("  / ___/___  ____ ___________/ /_    | |     / /___  _________/ /");
	puts("  \\__ \\/ _ \\/ __ `/ ___/ ___/ __ \\   | | /| / / __ \\/ ___/ __  /");
	puts(" ___/ /  __/ /_/ / /  / /__/ / / /   | |/ |/ / /_/ / /  / /_/ /");
	puts("/____/\\___/\\__,_/_/   \\___/_/ /_/    |__/|__/\\____/_/   \\__,_/");
	puts("");
}

void viewPrefixArt(){
	puts(" _    ___                  ____            _____       _       __               __");
	puts("| |  / (_)__ _      __    / __ \\________  / __(_)  __ | |     / /___  _________/ /");
	puts("| | / / / _ \\ | /| / /   / /_/ / ___/ _ \\/ /_/ / |/_/ | | /| / / __ \\/ ___/ __  /");
	puts("| |/ / /  __/ |/ |/ /   / ____/ /  /  __/ __/ />  <   | |/ |/ / /_/ / /  / /_/ /");  
	puts("|___/_/\\___/|__/|__/   /_/   /_/   \\___/_/ /_/_/|_|   |__/|__/\\____/_/   \\__,_/");
	puts("");
}

void viewAllArt(){
	puts(" _    ___                  ___    _____       __               __");
	puts("| |  / (_)__ _      __    /   |  / / / |     / /___  _________/ /");
	puts("| | / / / _ \\ | /| / /   / /| | / / /| | /| / / __ \\/ ___/ __  /");
	puts("| |/ / /  __/ |/ |/ /   / ___ |/ / / | |/ |/ / /_/ / /  / /_/ /");
	puts("|___/_/\\___/|__/|__/   /_/  |_/_/_/  |__/|__/\\____/_/   \\__,_/");
	puts("");
}

void exit(){
	cls;
	puts("  ________                __");
	puts(" /_  __/ /_  ____ _____  / /__    __  ______  __  __");
	puts("  / / / __ \\/ __ `/ __ \\/ //_/   / / / / __ \\/ / / /");
 	puts(" / / / / / / /_/ / / / / ,<     / /_/ / /_/ / /_/ /");
	puts("/_/ /_/ /_/\\__,_/_/ /_/_/|_|    \\__, /\\____/\\__,_/");
	puts("                               /____/");
	puts("");
	puts("             Have a nice day :)");
	puts("");
	exit(0);
}
