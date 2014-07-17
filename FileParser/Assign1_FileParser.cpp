#include<cstdio>
#include<fstream>
#include<boost/regex.hpp>                                                                                        

using namespace std;

class File_Parser                     //class for parsing file which includes method to indentify the programming language,name of classes, methods and properties
{
    public:
        void identify_Language(char fileName[]);
        void identify_Class(char fileName[],int language_Flag);
        void function_List(char fileName[],int language_Flag);
        void properties_List(char fileName[],int language_Flag);
}object_fp1;                                                                     //global object of Class File_Parser

void File_Parser::identify_Language(char fileName[])                             //method to identify programming language
{
    int language_Flag=0;                                                         //variable language_Flag is used to identify which input file it is
    ifstream fin_stream;
    char line[100];                                                             //array of character line used to stored the line read from input file
    fin_stream.open(fileName,ios::in);
    const char* java_regex = "^[[:space:]]*""(public|private|protected)[[:space:]]*"" class""[[:space:]]\\w+"; //pattern for recognizing java language
    boost::regex p1(java_regex);
    const char* php_regex = "^[[:space:]]*""<""\\?php";                         //pattern for recognizing php language
    boost::regex p2(php_regex);
    const char* ruby_regex = "^[[:space:]]*def[[:space:]]*\\w+\\([[\\w+]]*\\)"; //pattern for recognizing ruby language
    boost::regex p3(ruby_regex);
    while(fin_stream.getline(line,100)!=0)                                     //loop to read lines from input from till the eof
    {
        if (regex_search(line,p1))                                             //condition to search java pattern in line read from input file
        {
            language_Flag=1;
        }
        else if(regex_search(line,p2))                                         //condition to search php pattern in line read from input file
        {
            language_Flag=2;
        }
        else if(regex_search(line,p3))                                         //condition to search ruby pattern in line read from input file
        {
            language_Flag=3;
        }
    }
    if(language_Flag==1)                                        //if language_Flag is 1, it means it is java language and method identify_Class is called
    {
        cout<<"Its Java Language"<<endl;
        fin_stream.close();
        identify_Class(fileName,language_Flag);
    }
    else if(language_Flag==2)                                   //if language_Flag is 2, it means it is php language and method identify_Class is called
    {
        cout<<"Its php Language"<<endl;
        fin_stream.close();
        identify_Class(fileName,language_Flag);
    }
    else if(language_Flag==3)                                  //if language_Flag is 3,it means it is ruby language and method identify_Class is called
    {
        cout<<"Its Ruby language"<<endl;
        fin_stream.close();
        identify_Class(fileName,language_Flag);
    }
    else if(language_Flag==0)                                             //if language_Flag is 0, it means input file is niether java nor php nor ruby file
    cout<<"Its niether Java nor php nor ruby Language!!"<<endl;
    exit(0);
}

void File_Parser::identify_Class(char fileName[],int language_Flag)      //method to list out class names
{
    char word[10],line[100];
    ifstream fin_stream;
    fin_stream.open(fileName,ios::in);
    cout<<"\nClasses are: \n";
    while(fin_stream.getline(line,100))                                 
    {
        if(language_Flag==1)                                            
        {
            const char* java_regex = "^[[:space:]]*""(public|private|protected)*[[:space:]]""class""[[:space:]]\\w+";   //pattern to find java class name
            boost::regex p1(java_regex);
            if(regex_search(line,p1))                                   //if condition for java regular expression pattern matches to lines form input file
            {
                ofstream fout_Stream;                                   
                fout_Stream.open("temp.txt",ios::out|ios::trunc);
                fout_Stream<<line;
                fout_Stream.close();
                ifstream word_Read;
                word_Read.open("temp.txt",ios::in);
                while(!word_Read.eof())
                {
                    word_Read>>word;
                    if(strcmp(word,"class")==0)                        //if first word is class then definitely next word would be class name
                    {
                        word_Read>>word;
                        cout<<word<<endl;                              //display class name
                    }
                }
            }
        }
        else if(language_Flag==2)                                                
        {
            const char* php_regex = "^[[:space:]]*""class""[[:space:]]\\w+";     //pattern to find php class name

            boost::regex p1(php_regex);
            if(regex_search(line,p1))                                  //if condition for php regular expression pattern matches to lines form input file
            {
                ofstream fout_Stream;
                fout_Stream.open("temp.txt",ios::out|ios::trunc);                //file output stream object to write line in temp.txt file
                fout_Stream<<line;
                fout_Stream.close();
                ifstream word_Read;
                word_Read.open("temp.txt",ios::in);
                while(!word_Read.eof())
                {
                    word_Read>>word;
                    if(strcmp(word,"class")==0)
                    {
                        word_Read>>word;
                        cout<<word<<endl;                                        //print class name
                    }
                }
            }
        }
        else if(language_Flag==3)
        {
            const char* rb_regex = "^[[:space:]]*""class""[[:space:]]\\w+";     //pattern to find ruby class name
            boost::regex p1(rb_regex);
            if(regex_search(line,p1))                                           //if condition for ruby regular expression pattern matches to lines form input file
            {
                ofstream fout_Stream;
                fout_Stream.open("temp.txt",ios::out|ios::trunc);               //file output stream object to write line in temp.txt file
                fout_Stream<<line;
                fout_Stream.close();
                ifstream word_Read;
                word_Read.open("temp.txt",ios::in);
                while(!word_Read.eof())
                {
                    word_Read>>word;
                    if(strcmp(word,"class")==0)
                    {
                        word_Read>>word;
                        cout<<word<<endl;                                       //print class name
                    }
                }
            }
        }

    }
    fin_stream.close();
    function_List(fileName,language_Flag);                                     
}

void File_Parser::function_List(char fileName[],int language_Flag)             //method to find the methods
{
    char word[100],line[100];
    ifstream fin_stream;
    fin_stream.open(fileName,ios::in);
    cout<<"\nMethods are: \n";
    while(fin_stream.getline(line,100))
    {
        if(language_Flag==1)
        {
            const char* java_regex = "^[[:space:]]*""(public|private|protected)*[[:space:]]""\\w+""[[:space:]]\\w+""(\\()"; //pattern to find method in java file
            boost::regex p1(java_regex);
            if(regex_search(line,p1))
            {
                ofstream fout_Stream;
                fout_Stream.open("temp.txt",ios::out|ios::trunc);
                fout_Stream<<line;
                fout_Stream.close();
                ifstream word_Read;
                word_Read.open("temp.txt",ios::in);
                while(!word_Read.eof())
                {
                    word_Read>>word;
                    word_Read>>word;
                    word_Read>>word;
                    cout<<word<<endl;                                          //print method name
                }
            }
        }
        else if(language_Flag==2)
        {
            const char* php_regex = "^[[:space:]]*""\\w*""[[:space:]]*""function""[[:space:]]""\\w+""(\\()";    //pattern to find method in php file
            boost::regex p1(php_regex);
            if(regex_search(line,p1))
            {
                ofstream fout_Stream;
                fout_Stream.open("temp.txt",ios::out|ios::trunc);
                fout_Stream<<line;
                fout_Stream.close();
                ifstream word_Read;
                word_Read.open("temp.txt",ios::in);
                while(!word_Read.eof())
                {
                    word_Read>>word;
                    if(strcmp(word,"function")==0)
                    {
                        word_Read>>word;
                        cout<<word<<endl;                                       //print method name if there is no access specifier written in php file
                    }
                    else
                    {
                        word_Read>>word;
                        if(strcmp(word,"function")==0)
                        {
                            word_Read>>word;
                            cout<<word<<endl;                                  //print method name if access specifier written in php file
                        }
                    }
                 }
             }
         }
        else if(language_Flag==3)
        {
            const char* rb_regex = "^[[:space:]]*""def""[[:space:]]\\w+""(\\(*)";      //pattern to find method in ruby file
            boost::regex p1(rb_regex);
            if(regex_search(line,p1))
            {
                ofstream fout_Stream;
                fout_Stream.open("temp.txt",ios::out|ios::trunc);
                fout_Stream<<line;
                fout_Stream.close();
                ifstream word_Read;
                word_Read.open("temp.txt",ios::in);
                while(!word_Read.eof())
                {
                    word_Read>>word;
                    if(strcmp(word,"def")==0)
                    {
                        word_Read>>word;
                        cout<<word<<endl;                                     //print method name after def
                    }
                }
            }
        }

    }
    fin_stream.close();
    properties_List(fileName,language_Flag);
}

void File_Parser::properties_List(char fileName[],int language_Flag)         // method to list out all properties of class
{
    char word[100],line[100];
    ifstream fin_stream;
    fin_stream.open(fileName,ios::in);
    cout<<"\nProperties are: \n";
    while(fin_stream.getline(line,100))
    {
        if(language_Flag==1)
        {
            const char* java_regex = "^[[:space:]]*""(public|private|protected)*[[:space:]]*""(String|Interger|Long|Double)*[[:space:]]""\\w+""[[:space:]]*""(;)";  //pattern to find properties of class in java file
            boost::regex p1(java_regex);
            if(regex_search(line,p1))                                        //if pattern matched with line of input file
            {
                ofstream fout_Stream;
                fout_Stream.open("temp.txt",ios::out|ios::trunc);
                fout_Stream<<line;
                fout_Stream.close();
                ifstream word_Read;
                word_Read.open("temp.txt",ios::in);
                while(!word_Read.eof())
                {
                    word_Read>>word;
                    word_Read>>word;
                    word_Read>>word;
                    cout<<word<<endl;                                        //print variable name
                }
            }
        }
        else if(language_Flag==2)
        {
            const char* php_regex = "^[[:space:]]*""(var|public)[[:space:]](\\$)\\w[[:space:]]*""(\\w*)[[:space:]]*""(\\w*)(;)";    //pattern to find properties of class in php file
            boost::regex p1(php_regex);
            if(regex_search(line,p1))                                        //if pattern matched to line from input file
            {
                ofstream fout_Stream;
                fout_Stream.open("temp.txt",ios::out|ios::trunc);
                fout_Stream<<line;
                fout_Stream.close();
                ifstream word_Read;
                word_Read.open("temp.txt",ios::in);
                word_Read>>word;
                word_Read>>word;
                cout<<word<<endl;                                           //print variable name
            }
        }
        else if(language_Flag==3)
        {
            const char* rb_regex = "^[[:space:]]*" "(@@)\\w[[:space:]]" "(\\w*)[[:space:]]*";       // pattern to find properties of class in ruby file
            boost::regex p1(rb_regex);
            if(regex_search(line,p1))                                       //if pattern matched to line from input file
            {
                ofstream fout_Stream;
                fout_Stream.open("temp.txt",ios::out|ios::trunc);
                fout_Stream<<line;
                fout_Stream.close();
                ifstream word_Read;
                word_Read.open("temp.txt",ios::in);
                while(!word_Read.eof())
                {
                    word_Read>>word;
                    word_Read>>word;
                    word_Read>>word;
                    cout<<word<<endl;                                       //print variable name
                }
            }
        }

    }
    fin_stream.close();
}

int main()                                                                  // execution start form main                                                                                                                        //
{
    char file_Name[10];                                                     //variable to store file name from user
    cout<<"Enter the file name: ";
    gets(file_Name);                                                        //get file name input from user
    object_fp1.identify_Language(file_Name);                                //call identify_Language method by global object object_fp1
    return 0;
}
