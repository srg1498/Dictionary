#include<iostream>
#include<bits/stdc++.h>
#include<cstring>

using namespace std;
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

const int alphabet_size=26;

struct word{
string key;
string meaning;
};

struct node
{
    struct node *children[alphabet_size];
    bool endofword;
};

class dictionary{
public:
    //string s;
    void insert(struct node *,string);
    node *getnode();
    void search(node *,string);
    void fileRead(node *);
    bool deleteWord(struct node *root, string word);
    void alphabeticalOrder(struct node* root, char allWords[], int index);
    void prefix_search(struct node* root, string prefix);
    void print_prefix_search(struct node* root, char allWords[], int index, string prefix);
    };

node * dictionary::getnode()
{
        struct node *tnode=new node;
            tnode->endofword=false;

        for(int i=0;i<alphabet_size;i++)
            tnode->children[i]=NULL;

        return tnode;
}

//function for insertion
void dictionary::insert(struct node *root,string m)
{
    struct node *temp=root;
    int index;
    for(int i=0;i<m.length();i++)
    {
        index=m[i]-'a';
        if(temp->children[index]==NULL)
            {
                temp->children[index]=getnode();
            }
        temp=temp->children[index];
    }
    temp->endofword=true;
}

//function for searching
void dictionary::search(struct node * root,string var)
{
    struct node * temp=root;
    int index;
    for(int i=0;i<var.length();i++)
    {
        index=var[i]-'a';
        if(root->children[index]==NULL)
            {
                cout<<"word not found";
                return;
            }
        root=root->children[index];
    }



string bigstring,str;
char c[200],a[200];
int i;


    ifstream myfile2;
    myfile2.open("myfile2.dat");
    while(!myfile2.eof())
        {
        getline(myfile2,bigstring);
        i=bigstring.find(".");
        str=bigstring.substr(0,i);
        //c=str;

        strcpy(c, str.c_str());
        //a=var;
        strcpy(a, var.c_str());
            if(strcmp(a ,c)==0)
                {
                cout<<endl<<"meaning of word  "<<var<<"\t ------->"<<bigstring.substr(i+1)<<endl;
                break;
                }


        }

        myfile2.close();


}

//function for deletion
bool dictionary:: deleteWord(struct node *root, string word)
{
    struct node *temp = root;
    for (int i = 0; i < word.length(); i++)
    {
        int index = (word[i]-'a');

        if (!temp->children[index])
            return false;

        temp = temp->children[index];
    }
    string c;
    if (temp != NULL && temp->endofword)
    {
        temp->endofword = false;

        ifstream myfile;
        ofstream temp;

        myfile.open("myfile.dat");
        temp.open("temp.dat");

        while(getline(myfile,c))
        {
            if(c!=word)
                temp<<c<<endl;
        }

        myfile.close();
        temp.close();

        remove("myfile.dat");

        rename("temp.dat","myfile.dat");
            return true;
    }
}

//function for reading from file
void dictionary:: fileRead(struct node * root)
{
    string data;
    ifstream myfile;

    myfile.open("myfile.dat");
    while(!myfile.eof())
{
    getline(myfile,data);
    insert(root,data);
}
    myfile.close();
}

//functiion to print in alphabetical order
void dictionary:: alphabeticalOrder(struct node* root, char allWords[], int index)
{
    struct node* temp = root;

    if(temp != NULL && temp->endofword == true)
        {
        for(int j = 0; j < index; j++)
         {
            cout << allWords[j];
         }

        cout << " ";
        cout << "\n";
        }

    for(int i = 0; i < alphabet_size; i++)
        {
        if(temp->children[i] != NULL)
        {
            allWords[index] = 'a' + i;
            alphabeticalOrder(temp->children[i], allWords, index + 1);
        }
        }
}

// function to print the results of a given prefix search
void dictionary:: print_prefix_search(struct node* root, char allWords[], int index, string prefix)
{
    struct node* temp = root;

    if(temp != NULL && temp->endofword == true)
        {
        cout << prefix;

        for(int j = 0; j < index; j++)
            {
            cout << allWords[j];
            }

        cout << " ";
        cout << "\n";
        }

    for(int i = 0; i < alphabet_size; i++)
        {
        if(temp->children[i] != NULL)
        {
            allWords[index] = 'a' + i;
            print_prefix_search(temp->children[i], allWords, index + 1, prefix);
        }
        }
}

// function to search the words that match the prefix entered
void dictionary::prefix_search(struct node* root, string prefix)
{
    struct node* temp = root;

    for(int i = 0; i < prefix.length(); i++)
        {
        int index = (prefix[i]-'a');
        temp = temp->children[index];
        }

    char allWords[50];
    print_prefix_search(temp, allWords, 0, prefix);
}

// the driver function of the program
int main()
{
    dictionary d;
    struct word w;
    string data;
        struct node *root=d.getnode();
        d.fileRead(root);

   while(1)
{

       int a;
        cout << "\nWhat would you like to do?\n";
        cout << "\n";
        cout << "1. Insert a word.\n";
        cout << "2. Search a word.\n";
        cout << "3. Delete a word.\n";
        cout << "4. Print entries of dictionary in alphabetical order.\n";
        cout << "5. Prefix search.\n";
        cout << "\n";

        fflush(stdin);
        string word;

       cin>>a;
       switch(a)
{
   case 1:
    {
        cout<<"Enter the word \t ------>"<<endl;
        cin>>w.key;
        cout<<endl<<"Enter the meaning \t ------>";
        cin>>w.meaning;
        string bigstring;
        bigstring=w.key+"."+w.meaning;

        ofstream myfile2;
        myfile2.open("myfile2.dat",ios::app);
        myfile2<<bigstring;
        myfile2<<endl;
        ofstream  myfile;
        myfile.open("myfile.dat",ios::app);
        myfile<<w.key;
        myfile<<endl;
        d.insert(root,w.key);

    myfile.close();
    myfile2.close();
        break;
    }


    case 2:
     {

        cout<<"enter word to be search \t ---------->";
        cin>>word;
        d.search(root,word);
        break;
     }

    case 3:
     {
        cout << "Which word would you like to delete? ";

        cin >> word;
        if(d.deleteWord(root, word))
        {
        cout << word << " has been successfully deleted from the Dictionary.\n";
        }

        else
        {
        cout << "No such word exists in the Dictionary.\n";
        }

        break;
        }


        case 4:
        {

        char allWords[50];
        d.alphabeticalOrder(root, allWords, 0);
        cout << "\n";

        break;
        }

        case 5:
        {
        cout << "Enter the word you would like to use as a prefix: ";
        cin >> word;
        cout << "\n";

        d.prefix_search(root, word);

        break;
        }
}
}

return 0;
}

