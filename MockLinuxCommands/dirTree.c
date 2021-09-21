#include <stdio.h>             // for I/O
#include <stdlib.h>            // for I/O
#include <libgen.h>            // for dirname()/basename()
#include <string.h>
#include <string.h>
#include <stdbool.h>

typedef struct node
{
    char name[64]; // name string of node
    char type; // node type; D: directory; F: file 
    
    // node pointers:
    struct node *child, *sibling, *parent;

}NODE;

NODE *root, *cwd, *start; // root and CWD and start pointers
char line[128]; // user input
char command[16], pathname[64]; // command and pathname strings
char dname[64], bname[64];

//char dname[64], bname[64]; // dirname and basename string holders
char *cmd[] = {"mkdir", "ls", "quit", "creat", "cd", "rmdir", "menu", "pwd", "save", "rm", "reload", "restart", 0};

int restart(NODE* r)
{
    if(r == NULL)
    {
        return 0;
    }

    restart(r->child);
    restart(r->sibling);
    
    printf("\nDeleting node: %s", r->name);
    free(r);
}

int initialize()
{
    root = (NODE *)malloc(sizeof(NODE));
    strcpy(root->name, "/");
    root->parent = root;
    root->sibling = root->child =  0;    
    root->type = 'D';
    cwd = root;
    printf("Root initialized success!\n");
}

int findCommand(char *command)
{
    int i = 0;
    while(cmd[i])
    {
        if(strcmp(command, cmd[i]) == 0)
            return i;
        i++;
    }
    return -1;
}

NODE *searchChild(NODE *parent, char *name)
{
    NODE *p;
    printf("search for %s in %s DIR\n", name, parent->name);

    if(parent != NULL)
    {
        p = parent->child; // assign parent dir
        if(p==0)
            return 0;
        while(p){
            if (name != NULL && strcmp(p->name, name) == 0) // compare
                return p;
            p = p->sibling; // traverse
        }
    }
    return 0; // return null
}

int insertChild(NODE *parent, NODE *newNode)
{
    NODE *p;
    printf("insert NODE %s into END of parent child list\n", newNode->name);
    p = parent->child; // assign parent child
    if(p == 0)
        parent->child = newNode; // assign first node if directory empty
    else{
        while(p->sibling)
            p = p->sibling;
        p->sibling = newNode; // add to end
    }
    newNode->parent = parent;
    newNode->child = 0;
    newNode->sibling = 0;
}

int setDandBnames(char* pn, bool *isPN)
{
    // first empty dname and bname
    strcpy(dname, "\0");
    strcpy(bname, "\0");

    char* token = strtok(pn, "/");    // split pathname, isolate first directory
    strcpy(bname, token);       // bname = token assumming no "/"
    token = strtok(NULL, "/");
    if(token != NULL)           // conditional checks if user entered a pathname
    {
        *isPN = true;
        for(token; token != NULL; token = strtok(NULL, "/"))
        {
            strcat(dname, bname);   // add previous token to directory name
            strcat(dname, "/");     // add path delemiter
            strcpy(bname, token);   // keep track of last token as basename
        }
        dname[strlen(dname)-1] = '\0';
    }
}

int mkdir(char *pn)
{
    NODE *p, *q;
    bool isPN = false;

    strcpy(dname, "\0");
    printf("\nmkdir: name=%s\n", pn);

    if(!strcmp(pn, "/") || !strcmp(pn, ".") || !strcmp(pn, "..") || !strcmp(pn, "")){ // checking special cases
        printf("Can't mkdir with %s\n", pn);
        return -1;
    }
    if(pn[0] == '/')      // assign start, whether root or existing cwd
        start = root;   
    else
        start = cwd;

    setDandBnames(pn, &isPN); // setting dname and bname in separate function
    printf("dname = %s, bname = %s\n", dname, bname);

    // meant to relocate starting point to mkdir in, if user entered a path
    if(isPN){  
        char *token = strtok(dname, "/");     // remove first directory
        while(token != NULL)
        {
            start = searchChild(start, token);  // find directories in pathname in succession
            token = strtok(NULL, "/");      // move to next directory
        }
    }

    // searching for duplicates
    p = searchChild(start, bname);   
    if(p)   // duplicate found
    {
        printf("Name %s already exists, mkdir FAILED!\n", bname);
        return -1;
    }

    if(start != NULL && start->type == 'D')
    {
        printf("------------------------------------------\n");
        printf("Ready to mkdir %s\n", bname);
        q = (NODE *)malloc(sizeof(NODE));   // allocating space of new directory
        q->type = 'D';  
        strcpy(q->name, bname);
        insertChild(start, q);
        printf("mkdir %s OK\n", bname);
        printf("------------------------------------------\n\n");
    }
    else if(start && start->type == 'F')
        printf("mkdir: %s is not a directory\n\n", dname);
    else
        printf("mkdir: %s directory not found\n\n", dname);

    return 0;
    
}

int creat(char *pn)
{
    NODE *p, *q;
    bool isPN = false;

    strcpy(dname, "\0");
    printf("\ncreat: name=%s\n", pn);

    if(!strcmp(pn, "/") || !strcmp(pn, ".") || !strcmp(pn, "..")){ // checking special cases
        printf("Can't creat with %s\n", pn);
        return -1;
    }
    if(pn[0] == '/')      // assign start, whether root or existing cwd
        start = root;   
    else
        start = cwd;

    setDandBnames(pn, &isPN); // setting dname and bname in separate function
    printf("dname = %s, bname = %s\n", dname, bname);

    // meant to relocate starting point to mkdir in, if user entered a path
    if(isPN){  
        char *token = strtok(dname, "/");     // remove first directory
        while(token != NULL)
        {
            start = searchChild(start, token);  // find directories in pathname in succession
            token = strtok(NULL, "/");      // move to next directory
        }
    }

    // searching for duplicates
    printf("Check whether %s already exists\n", bname);
    p = searchChild(start, bname);   
    if(p)   // duplicate found
    {
        printf("Name %s already exists, creat FAILED!\n", bname);
        return -1;
    }

    if(start != NULL && start->type == 'D')
    {
        printf("------------------------------------------\n");
        printf("Ready to creat %s\n", bname);
        q = (NODE *)malloc(sizeof(NODE));   // allocating space of new directory
        q->type = 'F';  
        strcpy(q->name, bname);
        insertChild(start, q);
        printf("creat %s OK\n", bname);
        printf("------------------------------------------\n\n");
    }
    else if(start && start->type == 'F')
        printf("creat: %s is not a directory\n\n", dname);
    else
        printf("creat: %s directory not found\n\n", dname);

    return 0;
}

int ls(char *path)
{
    NODE *p;

    printf("ls: pathname=%s\n", path);

    if(path[0] == '/')
        p = root;
    else
        p = cwd;

    char *token = strtok(path, "/");    // traverse path
    while(token != NULL)
    {
        p = searchChild(p, token);
        token = strtok(NULL, "/");
    }
    
    if(p) //assure p is not null
    {
        p = p->child;                       // enter first item of directory
        printf("-------cwd contents--------\n");
    }
    else
        printf("ls: %s is an invalid pathname\n\n", path);
        
    while(p){                           // printf first item, then the rest through siblign links 
    printf("[%c %s] \n", p->type, p->name);
    p = p->sibling;
    }
    printf("\n");
    return 0;
}

int fpwd(FILE *outfile, NODE *p)
{
    if(p == root || p == NULL)   // base case
    {
        return 0;
    }

    fpwd(outfile, p->parent); // tracking pwd by parent links from cwd
    if(p == cwd)    // last path to be printed
        fprintf(outfile, "/%s\n", p->name);
    else            // middle paths
        fprintf(outfile, "/%s", p->name);

}

int printFile(FILE* outfile, NODE *p)
{
    NODE* q = p->child; // assuming p = root;
    NODE *cD = p->child;
    // traverse to last items
    while (cD != NULL)  // if root has siblings, go through them too
    {   
        while(q != NULL)
        {    

            if(q->child)
            {
                // printFile(outfile, q->child);
                cwd = q;    // setting cwd to current path
                fprintf(outfile, "%c ", q->type);
                fpwd(outfile, q);    // print path from currentDirectory
                q = q->child; 
                cwd = q;  
                fprintf(outfile, "%c ", q->type);
                fpwd(outfile, q);   // print path from child
            }

            q = q->sibling;        
            cwd = q;
            if(q && q->type == 'F')     // assuring we dont print a directory that has already been printed
            {
                fprintf(outfile, "%c ", q->type);
                fpwd(outfile, q);    // print path from sibling 
            }

        }   
        cD = cD->sibling;
        q = cD;
    }
}

int save(char *fileName)
{
    FILE *outfile;
    if(strcmp(fileName, "") == 0) // if no file entered, default
        outfile = fopen("currentTree.txt", "w+");
    else
        outfile = fopen(fileName, "w+");

    NODE *p = root; // first directory

    printf("save: saving in %s\n\n", fileName);

    printFile(outfile, p);

    fclose(outfile);
    
}

int readFile(FILE *outfile)
{
    NODE* q;
    char type, pn[64];

    
    type = fgetc(outfile);  // get first character
    while(type != EOF)
    {
        fscanf(outfile, " %s\n", pn);   // get pathname after character
        printf("type=%c ; pn=%s\n", type, pn);
        if(type == 'D') // make directory if type character read D
            mkdir(pn);
        else if(type == 'F')    // make file if type character read F
            creat(pn);

        type = fgetc(outfile);     // get next character      
    }
    
    
}


int reload(char * filename)
{
    FILE *outfile;
    
    if(root->child != NULL)
    {
        printf("reload: Tree structure has already been populated\n\n");
        return 0;
    }
 
    if(strcmp(filename, "") == 0) // if no file entered, default
        outfile = fopen("currentTree.txt", "r+");
    else
        outfile = fopen(filename, "r+");
    
    readFile(outfile);

    fclose(outfile);

}

int quit()
{
    save("currentTree.txt");
    printf("Program exit\n");
    exit(0);

}

int cd(char* pn)
{
    NODE *p;
    bool isPN = false;
    char buffer[64];   // setDandBnames alters pn, so we save it in a buffer
    strcpy(buffer, pn);

    printf("cd: pathname=%s\n", pn);

    if(pn[0] == '/')  // check if starting from root or cwd
        start = root;
    else
        start = cwd;

    if(strcmp(pn, "/") != 0)    // assure user does not want to cd to root
        setDandBnames(pn, &isPN);
    
    printf("dname = %s, bname = %s\n", dname, bname);   // setting dname and bname in separate function
    
    if(isPN){  
        char *token = strtok(buffer, "/");     // remove first directory
        while(token != NULL)
        {
            if(strcmp(token, "..") == 0)    // allows us to go back a directory multiple times i.e. ../../.. or ../../D2
                cwd = cwd->parent;
            else
                cwd = searchChild(start, token);  // set cwd to first directory
            
            start = cwd;                      // set start to cwd
            token = strtok(NULL, "/");        // move to next directory
        }
    }
    else
    {
        if(!strcmp(pn, "..") && cwd->parent != NULL)
            cwd = cwd->parent;    // set cwd to parent directory
        else if(!strcmp(pn, "."))
            ;      // cwd already set to cwd
        else if(!strcmp(pn, "/"))
            cwd = root;     // set cwd to root directory
        else
        {
            p = searchChild(start, bname);    // if no path entered.
            if(p && p->type == 'F')
            {
                printf("cd: %s is not a directory\n\n", bname);
                return 0;
            } else if(p)
                cwd = p;

        }

    }
        
    if(cwd != NULL)
        printf("cd - successful!\n\n");
    else
        printf("cd - unsuccessful!cwd = %s\n\n", cwd->name);

    return 0;
}

int rmdir(char* pn)
{
    NODE *p, *prev, *parent;
    bool isPN = false;

    strcpy(dname, "\0");
    printf("\nrmdir: pathname=%s\n", pn);

    if(!strcmp(pn, "/") || !strcmp(pn, ".") || !strcmp(pn, "..")){ // checking special cases
        printf("Can't rmdir with %s\n", pn);
        return -1;
    }
    if(pn[0] == '/')      // assign start, whether root or existing cwd
        start = root;   
    else
        start = cwd;

    setDandBnames(pn, &isPN); // setting dname and bname in separate function
    printf("dname = %s, bname = %s\n", dname, bname);

    // meant to relocate starting point to rmdir in, if user entered a path
    if(isPN){  
        char *token = strtok(dname, "/");     // remove first directory
        while(token != NULL)
        {
            start = searchChild(start, token);  // find directories in pathname in succession
            token = strtok(NULL, "/");      // move to next directory
        }

    }

    if(start != NULL)   // find directory to remove
    {
        p = searchChild(start, bname);

        if(p == NULL)
        {
            printf("rmdir: %s is an invalid pathname\n\n", bname);
        }

        parent = p->parent->child;
        if(p && p->type == 'D') // p is found and is a directory
        {
            while(parent && strcmp(parent->name, p->name) != 0)   // case where p is one of parent's siblings
            {
                prev = parent;
                parent = parent->sibling;
            }

            if(parent && strcmp(parent->name, p->name) == 0)  // if p found in parent's siblings, and siblings have not been traversed to NULL
            {
                if(p->child)    // if p has a file or directory 
                    printf("rmdir: %s directory is not empty\n\n", bname);
                else if(strcmp(p->parent->child->name, p->name) == 0) // if p is parent's child, parent must point to sibling
                {
                    p->parent->child = p->sibling;
                    free(p);
                    printf("rmdir - successful!\n\n");
                }
                else{
                    prev->sibling = p->sibling;
                    free(p);
                    printf("rmdir - successful!\n\n");
                }
            }
            else
                printf("rmdir: %s directory was not found\n\n", bname);
        }
        else
            printf("rmdir: %s is not a directory\n\n", bname);
    }
    else
        printf("rmdir: %s directory not found\n\n", dname);

    return 0;
}

int menu()
{
    printf("valid commands = [mkdir|rmdir|creat|rm|cd|ls|pwd|save|reload|restart|quit]\n\n");
    return 0;
}

int pwd(NODE* p)
{
    if(p == root)   // base case
    {
        return 0;
    }

    pwd(p->parent); // tracking pwd by parent links from cwd
    if(p == cwd)    // last path to be printed
        printf("/%s\n\n", p->name);
    else            // middle paths
        printf("/%s", p->name);

}

int rm(char *pn)
{
    NODE *p, *prev, *parent;
    bool isPN = false;

    strcpy(dname, "\0");
    printf("\nrm: pathname=%s\n", pn);

    if(!strcmp(pn, "/") || !strcmp(pn, ".") || !strcmp(pn, "..")){ // checking special cases
        printf("Can't rmdir with %s\n", pn);
        return -1;
    }
    if(pathname[0] == '/')      // assign start, whether root or existing cwd
        start = root;   
    else
        start = cwd;

    setDandBnames(pn, &isPN); // setting dname and bname in separate function
    printf("dname = %s, bname = %s\n", dname, bname);

    // meant to relocate starting point to rmdir in, if user entered a path
    if(isPN){  
        char *token = strtok(dname, "/");     // remove first directory
        while(token != NULL)
        {
            start = searchChild(start, token);  // find directories in pathname in succession
            token = strtok(NULL, "/");      // move to next directory
        }

    }

    if(start != NULL)   // find directory to remove
    {
        p = searchChild(start, bname);
        if(p == NULL)
        {
            printf("rm: %s is an invalid pathname\n\n", bname);
            return 0;
        }
        parent = p->parent->child;
        if(p && p->type == 'F') // p is found and is a directory
        {
            while(parent && strcmp(parent->name, p->name) != 0)   // case where p is one of parent's siblings
            {
                prev = parent;
                parent = parent->sibling;
            }
            if(parent && strcmp(parent->name, p->name) == 0)  // if p found in parent's siblings, and siblings have not been traversed to NULL
            {
                if(p->child)    // if p has a file or directory 
                    printf("rm: %s directory is not empty\n\n", bname);
                else if(strcmp(p->parent->child->name, p->name) == 0) // if p is parent's child, parent must point to sibling
                {
                    p->parent->child = p->sibling;
                    free(p);
                    printf("rm - successful!\n\n");
                }
                else{
                    prev->sibling = p->sibling;
                    free(p);
                    printf("rm - successful!\n\n");
                }
            }
            else
                printf("rm: %s directory was not found\n\n", bname);
        }
        else
            printf("rm: %s is not a directory\n\n", bname);
    }
    else
        printf("rmdir: %s directory not found\n\n", dname);

    return 0;
}

int main()
{
    int i;  
    initialize();
   
    printf("NOTE: commands = [mkdir|rmdir|creat|rm|cd|ls|pwd|save|reload|quit]\n");

    while(1){
        printf("Enter command line: ");
        fgets(line, 128, stdin);    // get command line
        line[strlen(line) - 1] = 0; // eliminate \0 character

        command[0] = pathname[0] = 0;     // initialize global variables
        sscanf(line, "%s %s", command, pathname);
        printf("command=%s pathname=%s\n", command, pathname);

        if(command[0] == 0)
            continue;
        
        i = findCommand(command);
        switch (i)
        {
            case 0: mkdir(pathname); break;
            case 1: ls(pathname); break;
            case 2: quit();          break;
            case 3: creat(pathname);    break;
            case 4: cd(pathname);   break;
            case 5: rmdir(pathname);    break;
            case 6: menu(); break;
            case 7: 
                if(cwd != root) // pwd is recursive, dealing with special case here
                    pwd(cwd);
                else
                    printf("/\n\n");  

                break;
            case 8: save(pathname); break;
            case 9: rm(pathname); break;
            case 10: reload(pathname); break;
            case 11: restart(root); printf("\n"); initialize(); break;
            case -1: printf("Command not recognized, try again\n"); break;
        }
    }
    
}